#include "sha256.h"
#include "opencl.h"
#include "miner.h"
#include "opencl_helper.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

namespace opencl {

void OpenCL::load_source(const char *filename) {
  FILE *fp;

  fp = fopen(filename, "r");
  if (!fp) {
    LOG(ERROR) << "[ OpenCL: failed to load kernel source '" << filename << "' ]";
    exit(1);
  }
  source_str_ = (char *)malloc(MAX_SOURCE_SIZE);
  source_size_ = fread(source_str_, 1, MAX_SOURCE_SIZE, fp);
  fclose(fp);
  if (GET_VERBOSITY_LEVEL() >= VERBOSITY_NAME(INFO)) {
    LOG(PLAIN) << "[ OpenCL: loaded kernel source '" << filename << "' (" << source_size_ << " bytes) ]";
  }
}

void OpenCL::set_source(unsigned char *source, unsigned int length) {
  source_str_ = (char *)malloc(MAX_SOURCE_SIZE);
  memcpy(source_str_, source, length);
  source_size_ = length;
  if (GET_VERBOSITY_LEVEL() >= VERBOSITY_NAME(INFO)) {
    LOG(PLAIN) << "[ OpenCL: set kernel source (" << source_size_ << " bytes) ]";
  }
}

void OpenCL::print_devices() {
  cl_int cl_err = CL_SUCCESS;

  // platform
  CL_WRAPPER(clGetPlatformIDs(0, NULL, &platform_count_));
  platforms_ = (cl_platform_id *)malloc(platform_count_ * sizeof(cl_platform_id));
  CL_WRAPPER(clGetPlatformIDs(platform_count_, platforms_, NULL));

  // devices
  char buf[1024];
  num_devices_ = 0;
  for (uint p = 0; p < platform_count_; p++) {
    cl_err = clGetDeviceIDs(platforms_[p], CL_DEVICE_TYPE_ALL, 0, NULL, &device_count_);
    if (cl_err != CL_SUCCESS) {
      LOG(PLAIN) << "[ OpenCL: platform #" << p << " ERROR on calling \"clGetDeviceIDs(...)\", error code = " << cl_err
                 << " ]";
      continue;
    }

    devices_ = (cl_device_id *)malloc(device_count_ * sizeof(cl_device_id));
    CL_WRAPPER(clGetDeviceIDs(platforms_[p], CL_DEVICE_TYPE_ALL, device_count_, devices_, NULL));
    for (uint i = 0; i < device_count_; i++) {
      CL_WRAPPER(clGetDeviceInfo(devices_[i], CL_DEVICE_NAME, sizeof(buf), buf, NULL));
      if (GET_VERBOSITY_LEVEL() >= VERBOSITY_NAME(INFO)) {
        LOG(PLAIN) << "[ OpenCL: platform #" << p << " device #" << i << " " << buf << " ]";
      }
      num_devices_++;
    }
  }
}

int OpenCL::get_num_devices() {
  return num_devices_;
}

void OpenCL::create_context(cl_uint platform_idx, cl_uint device_idx) {
  char buf[1024];

  if (devices_ != NULL)
    free(devices_);

  CL_WRAPPER(clGetDeviceIDs(platforms_[platform_idx], CL_DEVICE_TYPE_ALL, 0, NULL, &device_count_));

  devices_ = (cl_device_id *)malloc(device_count_ * sizeof(cl_device_id));

  CL_WRAPPER(clGetDeviceIDs(platforms_[platform_idx], CL_DEVICE_TYPE_ALL, device_count_, devices_, NULL));
  CL_WRAPPER(clGetDeviceInfo(devices_[device_idx], CL_DEVICE_NAME, sizeof(buf), buf, NULL));
  CL_WRAPPER(clGetDeviceInfo(devices_[device_idx], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(max_work_group_size_),
                             &max_work_group_size_, NULL));

  if (GET_VERBOSITY_LEVEL() >= VERBOSITY_NAME(INFO)) {
    LOG(PLAIN) << "[ OpenCL: create context for platform #" << platform_idx << " device #" << device_idx << " " << buf
               << ", max work group size is " << max_work_group_size_ << " ]";
  }

  cl_int ret;
  context_ = clCreateContext(NULL, 1, &devices_[device_idx], NULL, NULL, &ret);
  CL_WRAPPER(ret);

  device_idx_ = device_idx;
  platform_idx_ = platform_idx;
}

void OpenCL::create_kernel(char *args, unsigned char *data, unsigned char *rdata, uint32_t gpu_threads, const uint8_t *target) {
  //  printf("[ OpenCL: create kernel ]\n");
  
  //////////////////////////////////////////// 
  ////////////////////////////////////////////
  
  static const int len = 123, n = 3;

  uint32_t PaddedMessage[16 * n];  // bring balance to the force, 512*3 bits
  memset(PaddedMessage, 0, 16 * n * sizeof(uint32_t));
  memcpy(PaddedMessage, data, len);
  ((uchar *)PaddedMessage)[len] = 0x80;  // guard bit after data
  uint32_t endiandata[16 * n];
  for (int k = 0; k < 16 * n; k++)
    be32enc(&endiandata[k], ((uint32_t *)PaddedMessage)[k]);
  ((uint32_t *)endiandata)[16 * n - 1] = len * 8;  // size to the end
  
  //////////////////////////////////////////// 
  ////////////////////////////////////////////
  
  #define LINE_END_FMT "\r\n"
  
  char defines_string[4096] = {""};
    
  for( int i = 0; i < 16 * n; i++ ) {
	
	// sprintf(defines_string, "%s -D CD%d=%u", defines_string, i, endiandata[i]);
	sprintf(defines_string, "%s" "#define CD%d %u" LINE_END_FMT, defines_string, i, endiandata[i]);
	
  }
      
  //////////////////////////////////////////// 
  ////////////////////////////////////////////
  
  /*
  
  for(int k = 0; k < gpu_threads; k++) {
    
	  // sprintf(defines_string, "%s" "#define RD%d {", defines_string, k);
	  sprintf(defines_string, "%s" "#define RD%d uchar loc_c_rdata_card_%d[32] = {", defines_string, k, k);
	  
	  for(int i = 0; i < 32; i++)
		sprintf(defines_string, "%s%u,", defines_string, rdata[i+32*k]);

	  sprintf(defines_string, "%s" "};" LINE_END_FMT, defines_string);
	  
  }
  
  */
    
  //////////////////////////////////////////// 
  ////////////////////////////////////////////
  
  /*
  
  sprintf(defines_string, "%s -D RDW={", defines_string);
  
  for(int k = 0; k < gpu_threads; k++) {
  	    
	  uint32_t rdata11 = (uint32_t)rdata[1+32*k] << 24 |
						 (uint32_t)rdata[2+32*k] << 16 |
						 (uint32_t)rdata[3+32*k] << 8 |
						 (uint32_t)rdata[4+32*k];
	  uint32_t rdata12 = (uint32_t)rdata[5+32*k] << 24 |
						 (uint32_t)rdata[6+32*k] << 16 |
						 (uint32_t)rdata[7+32*k] << 8 |
						 (uint32_t)rdata[8+32*k];
	  uint32_t rdata13 = (uint32_t)rdata[9+32*k] << 24 |
						 (uint32_t)rdata[10+32*k] << 16 |
						 (uint32_t)rdata[11+32*k] << 8 |
						 (uint32_t)rdata[12+32*k];
	  uint32_t rdata14 = (uint32_t)rdata[13+32*k] << 24 |
						 (uint32_t)rdata[14+32*k] << 16 |
						 (uint32_t)rdata[15+32*k] << 8 |
						 (uint32_t)rdata[16+32*k];
	  uint32_t rdata15 = (uint32_t)rdata[17+32*k] << 24 |
						 (uint32_t)rdata[18+32*k] << 16 |
						 (uint32_t)rdata[19+32*k] << 8 |
						 (uint32_t)rdata[20+32*k];
	  
	  sprintf(defines_string, "%s%u,", defines_string, rdata11);
	  sprintf(defines_string, "%s%u,", defines_string, rdata12);
	  sprintf(defines_string, "%s%u,", defines_string, rdata13);
	  sprintf(defines_string, "%s%u,", defines_string, rdata14);
	  sprintf(defines_string, "%s%u,", defines_string, rdata15);
	  
  }
  
  sprintf(defines_string, "%s}", defines_string);  
  
  */
  
  //////////////////////////////////////////// 
  ////////////////////////////////////////////
   
  uint32_t endiantarget[8];
  for (int k = 0; k < 8; k++)
    be32enc(&endiantarget[k], ((uint32_t *)target)[k]);

  for( int i = 0; i < 8; i++ ) {
	
	sprintf(defines_string, "%s" "#define TG%d %u" LINE_END_FMT, defines_string, i, endiantarget[i]);
	
  }
  
  //////////////////////////////////////////// 
  ////////////////////////////////////////////
  
  char *source_str_with_defines = (char *) malloc( MAX_SOURCE_SIZE );
   
  sprintf( source_str_with_defines, "%s" "%s", defines_string, source_str_ );
    	  
  size_t source_str_with_defines_size = strlen(defines_string) + source_size_; // strlen(source_str_with_defines);
  
  
  //////////////////////////////////////////// 
  ////////////////////////////////////////////
  
  cl_int ret; 
  
  // program_ = clCreateProgramWithSource(context_, 1, (const char **)&source_str_, (const size_t *)&source_size_, &ret);
  program_ = clCreateProgramWithSource(context_, 1, (const char **)&source_str_with_defines, (const size_t *)&source_str_with_defines_size , &ret);
  
  free(source_str_with_defines);
  
  CL_WRAPPER(ret);
  
  ret = clBuildProgram(program_, 1, &devices_[device_idx_], args, NULL, NULL);
  
  if (ret != CL_SUCCESS) {
    size_t blen = 0;
    CL_WRAPPER(clGetProgramBuildInfo(program_, devices_[device_idx_], CL_PROGRAM_BUILD_LOG, 0, NULL, &blen));

    char *buffer = (char *) malloc(blen);

    CL_WRAPPER(clGetProgramBuildInfo(program_, devices_[device_idx_], CL_PROGRAM_BUILD_LOG, blen, &buffer, NULL));

    LOG(ERROR) << "[ OpenCL: ERROR ]\n" << buffer << "\n";
    free(buffer);
    exit(4);
  }

  

  kernel_ = clCreateKernel(program_, "sha256", &ret);
  CL_WRAPPER(ret);
  
  
  
  command_queue_ = clCreateCommandQueue(context_, devices_[device_idx_], 0, &ret);
  CL_WRAPPER(ret);
}


// TODO
#define NOT_NEEDED_ARGS_DISABLE

void OpenCL::load_objects(uint32_t gpu_id, uint32_t cpu_id, unsigned char *data, const uint8_t *target,
                          unsigned char *rdata, uint32_t gpu_threads) {

  static const int len = 123, n = 3;

  uint32_t PaddedMessage[16 * n];  // bring balance to the force, 512*3 bits
  memset(PaddedMessage, 0, 16 * n * sizeof(uint32_t));
  memcpy(PaddedMessage, data, len);
  ((uchar *)PaddedMessage)[len] = 0x80;  // guard bit after data
  uint32_t endiandata[16 * n];
  for (int k = 0; k < 16 * n; k++)
    be32enc(&endiandata[k], ((uint32_t *)PaddedMessage)[k]);
  ((uint32_t *)endiandata)[16 * n - 1] = len * 8;  // size to the end

  uint32_t endiantarget[8];
  for (int k = 0; k < 8; k++)
    be32enc(&endiantarget[k], ((uint32_t *)target)[k]);

  //  std::cout << "PaddedMessage[" << 16 * n * sizeof(uint32_t) << "]: ";
  //  for (int z = 0; z < 16 * n; z++)
  //    printf("%08x ", endiandata[z]);
  //  std::cout << std::endl;

  cl_int ret;
  
  buffer_rdata_ = clCreateBuffer(context_, CL_MEM_READ_ONLY, sizeof(cl_uchar) * 32 * gpu_threads, NULL, &ret);
  CL_WRAPPER(ret);
  
  
  #ifndef NOT_NEEDED_ARGS_DISABLE
  
  buffer_data_ = clCreateBuffer(context_, CL_MEM_READ_ONLY, sizeof(cl_uint) * 16 * 3, NULL, &ret);
  CL_WRAPPER(ret);
    
  buffer_target_ = clCreateBuffer(context_, CL_MEM_READ_ONLY, sizeof(cl_uint) * 8, NULL, &ret);
  CL_WRAPPER(ret);
  
  #endif
  
  buffer_gpu_threads_= clCreateBuffer(context_, CL_MEM_READ_ONLY, sizeof(cl_uint), NULL, &ret);
  CL_WRAPPER(ret);
  buffer_cpu_id_ = clCreateBuffer(context_, CL_MEM_READ_ONLY, sizeof(cl_uint), NULL, &ret);
  CL_WRAPPER(ret);
  buffer_threads_ = clCreateBuffer(context_, CL_MEM_READ_ONLY, sizeof(cl_ulong), NULL, &ret);
  CL_WRAPPER(ret);
  buffer_start_nonce_ = clCreateBuffer(context_, CL_MEM_READ_ONLY, sizeof(cl_ulong), NULL, &ret);
  CL_WRAPPER(ret);
  buffer_expired_ = clCreateBuffer(context_, CL_MEM_READ_ONLY, sizeof(cl_uint), NULL, &ret);
  CL_WRAPPER(ret);
  buffer_result_ = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(cl_ulong) * 2, NULL, &ret);
  CL_WRAPPER(ret);
    

  CL_WRAPPER(clEnqueueWriteBuffer(command_queue_, buffer_rdata_, CL_TRUE, 0, sizeof(cl_uchar) * 32 * gpu_threads, rdata, 0,
                                  NULL, NULL));
								  
  #ifndef NOT_NEEDED_ARGS_DISABLE
  								  
  CL_WRAPPER(clEnqueueWriteBuffer(command_queue_, buffer_data_, CL_TRUE, 0, sizeof(cl_uint) * 16 * 3, endiandata, 0,
                                   NULL, NULL));
								  
  CL_WRAPPER(clEnqueueWriteBuffer(command_queue_, buffer_target_, CL_TRUE, 0, sizeof(cl_uint) * 8, endiantarget, 0,
                                   NULL, NULL));
								   
  #endif
  
  CL_WRAPPER(clEnqueueWriteBuffer(command_queue_, buffer_gpu_threads_, CL_TRUE, 0, sizeof(cl_uint), &gpu_threads, 0,
                                  NULL, NULL));

  #ifndef NOT_NEEDED_ARGS_DISABLE

  CL_WRAPPER(clSetKernelArg(kernel_, 0, sizeof(buffer_rdata_), (void *)&buffer_rdata_));
  
  CL_WRAPPER(clSetKernelArg(kernel_, 1, sizeof(buffer_data_), (void *)&buffer_data_));  
  CL_WRAPPER(clSetKernelArg(kernel_, 2, sizeof(buffer_target_), (void *)&buffer_target_));
  
  CL_WRAPPER(clSetKernelArg(kernel_, 3, sizeof(buffer_gpu_threads_), (void *)&buffer_gpu_threads_));
  CL_WRAPPER(clSetKernelArg(kernel_, 4, sizeof(buffer_cpu_id_), (void *)&buffer_cpu_id_));
  CL_WRAPPER(clSetKernelArg(kernel_, 5, sizeof(buffer_threads_), (void *)&buffer_threads_));
  CL_WRAPPER(clSetKernelArg(kernel_, 6, sizeof(buffer_start_nonce_), (void *)&buffer_start_nonce_));
  CL_WRAPPER(clSetKernelArg(kernel_, 7, sizeof(buffer_expired_), (void *)&buffer_expired_));
  CL_WRAPPER(clSetKernelArg(kernel_, 8, sizeof(buffer_result_), (void *)&buffer_result_));  
  
  #else 
   
  CL_WRAPPER(clSetKernelArg(kernel_, 0, sizeof(buffer_rdata_), (void *)&buffer_rdata_));
  
  // CL_WRAPPER(clSetKernelArg(kernel_, 1, sizeof(buffer_data_), (void *)&buffer_data_));  
  // CL_WRAPPER(clSetKernelArg(kernel_, 2, sizeof(buffer_target_), (void *)&buffer_target_));
  
  CL_WRAPPER(clSetKernelArg(kernel_, 1, sizeof(buffer_gpu_threads_), (void *)&buffer_gpu_threads_));
  CL_WRAPPER(clSetKernelArg(kernel_, 2, sizeof(buffer_cpu_id_), (void *)&buffer_cpu_id_));
  CL_WRAPPER(clSetKernelArg(kernel_, 3, sizeof(buffer_threads_), (void *)&buffer_threads_));
  CL_WRAPPER(clSetKernelArg(kernel_, 4, sizeof(buffer_start_nonce_), (void *)&buffer_start_nonce_));
  CL_WRAPPER(clSetKernelArg(kernel_, 5, sizeof(buffer_expired_), (void *)&buffer_expired_));
  CL_WRAPPER(clSetKernelArg(kernel_, 6, sizeof(buffer_result_), (void *)&buffer_result_));
    
  #endif
  
}

void OpenCL::release() {
  CL_WRAPPER(clReleaseCommandQueue(command_queue_));
  CL_WRAPPER(clReleaseKernel(kernel_));
  CL_WRAPPER(clReleaseProgram(program_));
  CL_WRAPPER(clReleaseContext(context_));
  CL_WRAPPER(clReleaseDevice(devices_[device_idx_]));

  CL_WRAPPER(clReleaseMemObject(buffer_result_));
  CL_WRAPPER(clReleaseMemObject(buffer_expired_));
  CL_WRAPPER(clReleaseMemObject(buffer_start_nonce_));
  CL_WRAPPER(clReleaseMemObject(buffer_threads_));
  CL_WRAPPER(clReleaseMemObject(buffer_cpu_id_));
  CL_WRAPPER(clReleaseMemObject(buffer_gpu_threads_));
  
  #ifndef NOT_NEEDED_ARGS_DISABLE
  
  CL_WRAPPER(clReleaseMemObject(buffer_target_));
  CL_WRAPPER(clReleaseMemObject(buffer_data_));
  
  #endif
  
  CL_WRAPPER(clReleaseMemObject(buffer_rdata_));

  free(devices_);
  free(platforms_);
  free(source_str_);
}

HashResult OpenCL::scan_hash(uint cpu_id, uint32_t gpu_threads, td::uint64 threads, td::uint64 start_nonce, uint expired) {

  // printf("start_nonce = %lu 0x%016x\n", start_nonce, start_nonce);
  
  // printf("gpu_threads = %d\n", gpu_threads);

  td::uint64 start = (start_nonce / gpu_threads);  
   
  cl_ulong result[2] = {UINT64_MAX, UINT64_MAX};
    
  CL_WRAPPER(clEnqueueWriteBuffer(command_queue_, buffer_cpu_id_, CL_TRUE, 0, sizeof(cl_uint), &cpu_id, 0, NULL, NULL));
  CL_WRAPPER(
      clEnqueueWriteBuffer(command_queue_, buffer_threads_, CL_TRUE, 0, sizeof(cl_ulong), &threads, 0, NULL, NULL));
  CL_WRAPPER(
      clEnqueueWriteBuffer(command_queue_, buffer_start_nonce_, CL_TRUE, 0, sizeof(cl_ulong), &start, 0, NULL, NULL));
  CL_WRAPPER(
      clEnqueueWriteBuffer(command_queue_, buffer_expired_, CL_TRUE, 0, sizeof(cl_uint), &expired, 0, NULL, NULL));
  CL_WRAPPER(clEnqueueWriteBuffer(command_queue_, buffer_result_, CL_TRUE, 0, sizeof(result), result, 0, NULL, NULL));

  size_t global_work_size[2] = {threads / gpu_threads, gpu_threads};
  
  // CL_WRAPPER(clEnqueueNDRangeKernel(command_queue_, kernel_, 2, NULL, global_work_size, p_local_work_size, 0, NULL, NULL));
  CL_WRAPPER(clEnqueueNDRangeKernel(command_queue_, kernel_, 2, NULL, global_work_size, NULL, 0, NULL, NULL));
  CL_WRAPPER(clFinish(command_queue_));
  
  clEnqueueReadBuffer(command_queue_, buffer_result_, CL_TRUE, 0, sizeof(result), result, 0, NULL, NULL);
  	
  HashResult r;
  r.nonce = result[0];
  r.vcpu = result[1];
  r.cpu_id = cpu_id;
  return r;
}

}  // namespace opencl
