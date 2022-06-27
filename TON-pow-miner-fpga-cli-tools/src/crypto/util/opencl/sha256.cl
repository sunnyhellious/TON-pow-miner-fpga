
/*
 * Copyright (c) 2010, Michal Tomlein
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *     1. Redistributions of source code must retain the above copyright notice,
 *        this list of conditions and the following disclaimer.
 *     2. Redistributions in binary form must reproduce the above copyright notice,
 *        this list of conditions and the following disclaimer in the documentation
 *        and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Original code by Angel Marin, Paul Johnston.
 * https://raw.githubusercontent.com/michal-tomlein/sha256crack/master/sha256.cl
 */


#define uint64_t unsigned long
#define uint32_t unsigned int
#define uint8_t unsigned char

// prototypes

// uint rotr(uint x, int n);
// uint ch(uint x, uint y, uint z);
// uint maj(uint x, uint y, uint z);
// uint sigma0(uint x);
// uint sigma1(uint x);
// uint gamma0(uint x);
// uint gamma1(uint x);

#define rotr(x, n) ( (x >> n) | (x << (32 - n)) )
#define ch(x, y, z) ( (x & y) ^ (~x & z) )
#define maj(x, y, z) ( (x & y) ^ (x & z) ^ (y & z) )
#define sigma0(x) ( rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22) )
#define sigma1(x) ( rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25) )
#define gamma0(x) ( rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3) )
#define gamma1(x) ( rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10) )

void sha256core(uint message[], uint n, uint source_binlength, uint H[]);

void sha256core(uint message[], uint n, uint source_binlength, uint H[]) {
  uint K[] = {0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
              0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
              0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
              0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
              0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
              0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
              0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
              0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2};
  H[0] = 0x6A09E667;
  H[1] = 0xBB67AE85;
  H[2] = 0x3C6EF372;
  H[3] = 0xA54FF53A;
  H[4] = 0x510E527F;
  H[5] = 0x9B05688C;
  H[6] = 0x1F83D9AB;
  H[7] = 0x5BE0CD19;

  uint a, b, c, d, e, f, g, h;
  uint T1, T2;

  //    for (int j=0; j<n; j++) {
  //      printf("message[%d]: ", j);
  //      for (uint i = 0; i < 16; i += 16) {
  //        for (uint t = 0; t < 64; t++) {
  //            if (t < 16) printf("%08x ", message[t+i + j<<4]);
  //        }
  //      }
  //      printf("\n");
  //    }  

#pragma unroll
  for (uint j = 0; j < (n << 4); j+=16) {
    
	uint W[64] = {message[j+0], message[j+1], message[j+2], message[j+3], message[j+4], message[j+5], message[j+6], 
				message[j+7], message[j+8], message[j+9], message[j+10], message[j+11], message[j+12], message[j+13], 
				message[j+14], message[j+15], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	// uint W[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    //            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// #pragma unroll
//    for (uint i = 0; i < 16; i += 16) {
	  
	  T1 = H[7] + sigma1(H[4]) + ch(H[4], H[5], H[6]) + K[0] + W[0];
	  T2 = sigma0(H[0]) + maj(H[0], H[1], H[2]);	  
	  
	  a = T1 + T2 ;
      b = H[0];
      c = H[1];
      d = H[2];
      e = H[3] + T1;
      f = H[4];
      g = H[5];
      h = H[6];

#pragma unroll	  
	  for (uint t = 1; t < 16; t++) {
		T1 = h + sigma1(e) + ch(e, f, g) + K[t] + W[t];
        T2 = sigma0(a) + maj(a, b, c);
		h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
	  }
	  
#pragma unroll
      for (uint t = 16; t < 64; t++) {
        
        W[t] = gamma1(W[t - 2]) + W[t - 7] + gamma0(W[t - 15]) + W[t - 16];
		  
        T1 = h + sigma1(e) + ch(e, f, g) + K[t] + W[t];
        T2 = sigma0(a) + maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;

        //            printf("t=%d: a=%08x b=%08x c=%08x d=%08x e=%08x f=%08x g=%08x h=%08x\n", t, a, b, c, d, e, f , g, h);
      }
	  
      H[0] += a;
      H[1] += b;
      H[2] += c;
      H[3] += d;
      H[4] += e;
      H[5] += f;
      H[6] += g;
      H[7] += h;

      //        printf("H[%d]: H0=%08x H1=%08x H2=%08x H3=%08x H4=%08x H5=%08x H6=%08x H7=%08x\n", j, H[0], H[1], H[2], H[3], H[4], H[5] , H[6], H[7]);
//  }
  }
}

/*
__kernel void sha256(__global const uchar *c_rdata, __global const uint32_t *c_data, __global const uint32_t *pTarget, 
					 __global const uint32_t *gpu_threads, __global const uint32_t *cpu_id, __global const uint64_t *threads, 
					 __global const uint64_t *startNonce, __global const uint32_t *expired, __global uint64_t *result) {
					 
					 
*/

__kernel void sha256(__global const uchar *c_rdata, __global const uint32_t *gpu_threads, __global const uint32_t *cpu_id, 
					 __global const uint64_t *threads, __global const uint64_t *startNonce, __global const uint32_t *expired, 
					 __global uint64_t *result) {
					 
  uint length = 48;
  uint H[8];
  
  int vcpu = get_global_id(1);
  uint64_t thread = get_global_id(0);
  uint64_t nonce = startNonce[0] + thread;

  // read rdata from offset
  // 24:31 bytes
  
  uint64_t tmp_1 = ( cpu_id[0] * gpu_threads[0] + vcpu ) << 5;  
   
  uint64_t tmp_rdata1 = ((uint64_t)c_rdata[tmp_1+24]) << 56 |
						((uint64_t)c_rdata[tmp_1+25]) << 48 |
						((uint64_t)c_rdata[tmp_1+26]) << 40 |
						((uint64_t)c_rdata[tmp_1+27]) << 32 |
						((uint64_t)c_rdata[tmp_1+28]) << 24 |
						((uint64_t)c_rdata[tmp_1+29]) << 16 |
						((uint64_t)c_rdata[tmp_1+30]) << 8 |
						((uint64_t)c_rdata[tmp_1+31]);

  // increment rdata1 & rdata2
  uint64_t rdata1 = tmp_rdata1 + nonce;

  uint32_t rdata01 = (CD1 & ~(0xff)) | (uint8_t)(expired[0] >> 24);
  uint32_t rdata02 = ((expired[0] << 8) & ~(0xff)) | (uint8_t)(CD2);

  uint32_t rdata10 = (CD10 & ~(0xff)) | (uint8_t)c_rdata[tmp_1+0];
  

  uint32_t rdata11 = (uint32_t)c_rdata[tmp_1+1] << 24 |
                     (uint32_t)c_rdata[tmp_1+2] << 16 |
                     (uint32_t)c_rdata[tmp_1+3] << 8 |
                     (uint32_t)c_rdata[tmp_1+4];
  uint32_t rdata12 = (uint32_t)c_rdata[tmp_1+5] << 24 |
                     (uint32_t)c_rdata[tmp_1+6] << 16 |
                     (uint32_t)c_rdata[tmp_1+7] << 8 |
                     (uint32_t)c_rdata[tmp_1+8];
  uint32_t rdata13 = (uint32_t)c_rdata[tmp_1+9] << 24 |
                     (uint32_t)c_rdata[tmp_1+10] << 16 |
                     (uint32_t)c_rdata[tmp_1+11] << 8 |
                     (uint32_t)c_rdata[tmp_1+12];
  uint32_t rdata14 = (uint32_t)c_rdata[tmp_1+13] << 24 |
                     (uint32_t)c_rdata[tmp_1+14] << 16 |
                     (uint32_t)c_rdata[tmp_1+15] << 8 |
                     (uint32_t)c_rdata[tmp_1+16];
  uint32_t rdata15 = (uint32_t)c_rdata[tmp_1+17] << 24 |
                     (uint32_t)c_rdata[tmp_1+18] << 16 |
                     (uint32_t)c_rdata[tmp_1+19] << 8 |
                     (uint32_t)c_rdata[tmp_1+20];				 
  uint32_t rdata16 = (uint32_t)c_rdata[tmp_1+21] << 24 |
                     (uint32_t)c_rdata[tmp_1+22] << 16 |
                     (uint32_t)c_rdata[tmp_1+23] << 8 | (uint8_t)(rdata1 >> 56);
					 
  uint32_t rdata17 = (uint32_t)(rdata1 >> 24);
  uint32_t rdata18 = ((uint32_t)(rdata1 << 8) & ~(0xff)) | (uint8_t)(CD18);

  uint32_t rdata22 = (CD22 & ~(0xff)) | (uint8_t)c_rdata[tmp_1+0];
  #define rdata23 rdata11 // uint32_t rdata23 = rdata11;
  #define rdata24 rdata12 // uint32_t rdata24 = rdata12;
  #define rdata25 rdata13 // uint32_t rdata25 = rdata13;
  #define rdata26 rdata14 // uint32_t rdata26 = rdata14;
  #define rdata27 rdata15 // uint32_t rdata27 = rdata15;
  #define rdata28 rdata16 // uint32_t rdata28 = rdata16;
  #define rdata29 rdata17 // uint32_t rdata29 = rdata17;
  uint32_t rdata30 = ((uint32_t)(rdata1 << 8) & ~(0xff)) | (uint8_t)(CD30);
      
  //  printf(
  //      "[%d:%lld]: rdata1=%016llX rdata01=%04x rdata02=%04x rdata16=%04x rdata17=%04x rdata18=%04x rdata28=%04x "
  //      "rdata29=%04x rdata30=%04x\n",
  //      vcpu, nonce, rdata1, rdata01, rdata02, rdata16, rdata17, rdata18, rdata28, rdata29, rdata30);

 
  uint n = 3;
  
  uint64_t startNonce_copy = startNonce[0];
  
  uint64_t rdata_incr = threads[0] / 16;
  
  #pragma unroll
  for (int i = 0; i < HPF; i++) {      
	  
	  uint binb[] = {CD0,  rdata01,    rdata02,    CD3,  CD4,  CD5,  CD6,  CD7,
				 CD8,  CD9,  rdata10,    rdata11,    rdata12,    rdata13,    rdata14,    rdata15,
				 rdata16,    rdata17,    rdata18,    CD19, CD20, CD21, rdata22,    rdata23,
				 rdata24,    rdata25,    rdata26,    rdata27,    rdata28,    rdata29,    rdata30, CD31,
				 CD32, CD33, CD34, CD35, CD36, CD37, CD38, CD39,
				 CD40, CD41, CD42, CD43, CD44, CD45, CD46, CD47};
				 
	  //  printf("data0[%d:%lu]: %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x\n", vcpu,
	  //         nonce, CD0, rdata01, rdata02, CD3, CD4, CD5, CD6, CD7, CD8,
	  //         CD9, rdata10, rdata11, rdata12, rdata13, rdata14, rdata15);
	  //  printf("data1[%d:%lu]: %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x\n", vcpu,
	  //         nonce, rdata16, rdata17, rdata18, CD19, CD20, CD21, rdata22, rdata23, rdata24, rdata25,
	  //         rdata26, rdata27, rdata28, rdata29, rdata30, CD31);
	  //  printf("data2[%d:%lu]: %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x\n", vcpu, nonce,
	  //         CD32, CD33, CD34, CD35, CD36, CD37, CD38, CD39, CD40,
	  //         CD41, CD42, CD43, CD44, CD45, CD46, CD47);

	  //     printf("binb [%d]: ", 16 * n);
	  //     for (i = 0; i < 16 * n; i++) {
	  //       printf("%08x ", binb[i]);
	  //     }
	  //     printf("\n");

	  sha256core(binb, n, length, H);

	  // printf("H[%d:%d:%lu]: H0=%08x H1=%08x H2=%08x H3=%08x H4=%08x H5=%08x H6=%08x H7=%08x\n", cpu_id[0], vcpu, nonce, H[0], H[1], H[2], H[3], H[4], H[5] , H[6], H[7]);

	  // alternative memcmp
	  // check s0
	  if (H[0] < TG0) {
		result[0] = nonce;
		result[1] = vcpu; return;
	  } else if (H[0] > TG0) {
		goto next_try;
	  } else if (H[0] == TG0) {
		// check s1
		if (H[1] < TG1) {
		  result[0] = nonce;
		  result[1] = vcpu; return;

		  //      printf("%d: hash[%d:%lld]: %08x = %08x, %04x < %04x\n", cpu_id[0], vcpu, nonce, H[0], TG0, H[1],
		  //             TG1);
		  //
		  //      printf("%d: data0[%d:%lld]: %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x\n",
		  //             cpu_id[0], vcpu, nonce, CD0, rdata01, rdata02, CD3, CD4, CD5, CD6, CD7,
		  //             CD8, CD9, rdata10, rdata11, rdata12, rdata13, rdata14, rdata15);
		  //
		  //      printf("%d: data1[%d:%lld]: %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x\n",
		  //             cpu_id[0], vcpu, nonce, rdata16, rdata17, rdata18, CD19, CD20, CD21, rdata22, rdata23,
		  //             rdata24, rdata25, rdata26, rdata27, rdata28, rdata29, rdata30, CD31);
		  //
		  //      printf("%d: data2[%d:%lld]: %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x\n",
		  //             cpu_id[0], vcpu, nonce, CD32, CD33, CD34, CD35, CD36, CD37, CD38,
		  //             CD39, CD40, CD41, CD42, CD43, CD44, CD45, CD46,
		  //             CD47);
		  //
		  //      printf("%d: hash[%d:%lld]: %04x %04x %04x %04x %04x %04x %04x %04x\n", cpu_id[0], vcpu, nonce, H[0], H[1], H[2],
		  //             H[3], H[4], H[5], H[6], H[7]);
		  //
		  //      printf("%d: complexity[%d:%lld]: %04x %04x %04x %04x %04x %04x %04x %04x\n", cpu_id[0], vcpu, nonce, TG0,
		  //             TG1, TG2, TG3, TG4, TG5, TG6, TG7);
		  //
		  //      printf("%d: rdata[%d:%lld]: %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x", cpu_id[0], vcpu,
		  //             nonce, c_rdata[tmp_1+0],
		  //             c_rdata[tmp_1+1], c_rdata[tmp_1+2],
		  //             c_rdata[tmp_1+3], c_rdata[tmp_1+4],
		  //             c_rdata[tmp_1+5], c_rdata[tmp_1+6],
		  //             c_rdata[tmp_1+7], c_rdata[tmp_1+8],
		  //             c_rdata[tmp_1+9], c_rdata[tmp_1+10],
		  //             c_rdata[tmp_1+11], c_rdata[tmp_1+12],
		  //             c_rdata[tmp_1+13], c_rdata[tmp_1+14],
		  //             c_rdata[tmp_1+15]);
		  //
		  //      printf("%02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x\n",
		  //             c_rdata[tmp_1+16], c_rdata[tmp_1+17],
		  //             c_rdata[tmp_1+18], c_rdata[tmp_1+19],
		  //             c_rdata[tmp_1+20], c_rdata[tmp_1+21],
		  //             c_rdata[tmp_1+22], c_rdata[tmp_1+23],
		  //             c_rdata[tmp_1+24], c_rdata[tmp_1+25],
		  //             c_rdata[tmp_1+26], c_rdata[tmp_1+27],
		  //             c_rdata[tmp_1+28], c_rdata[tmp_1+29],
		  //             c_rdata[tmp_1+30],
		  //             c_rdata[tmp_1+31]);

		} else if (H[1] > TG1) {
		  goto next_try;
		} else if (H[1] == TG1) {
		  // check s2
		  if (H[2] < TG2) {
			result[0] = nonce;
			result[1] = vcpu; return;
		  } else if (H[2] > TG2) {
			goto next_try;
		  } else if (H[2] == TG2) {
			// check s3
			if (H[3] < TG3) {
			  result[0] = nonce;
			  result[1] = vcpu; return;
			} else if (H[3] > TG3) {
			  goto next_try;
			} else if (H[3] == TG3) {
			  // check s4
			  if (H[4] < TG4) {
				result[0] = nonce;
				result[1] = vcpu; return;
			  } else if (H[4] > TG4) {
				goto next_try;
			  } else if (H[4] == TG4) {
				// check s5
				if (H[5] < TG5) {
				  result[0] = nonce;
				  result[1] = vcpu; return;
				} else if (H[5] > TG5) {
				  goto next_try;
				} else if (H[5] == TG5) {
				  // check s6
				  if (H[6] < TG6) {
					result[0] = nonce;
					result[1] = vcpu; return;
				  } else if (H[6] > TG6) {
					goto next_try;
				  } else if (H[6] == TG6) {
					// check s7
					if (H[7] < TG7) {
					  result[0] = nonce;
					  result[1] = vcpu; return;
					} else {
					  goto next_try;
					}
				  }
				}
			  }
			}
		  }
		}
	  }
	  
	  next_try : ;
	  
	  startNonce_copy = startNonce_copy + rdata_incr;
	  
	  nonce = startNonce_copy + thread;
	  
	  // increment rdata1 & rdata2
	  rdata1 = tmp_rdata1 + nonce;	  
	  
	  rdata16 = (uint32_t)c_rdata[tmp_1+21] << 24 |
                     (uint32_t)c_rdata[tmp_1+22] << 16 |
                     (uint32_t)c_rdata[tmp_1+23] << 8 | (uint8_t)(rdata1 >> 56);
					 
	  rdata17 = (uint32_t)(rdata1 >> 24);
	    
	  rdata18 = ((uint32_t)(rdata1 << 8) & ~(0xff)) | (uint8_t)(CD18);
	  
	  rdata30 = ((uint32_t)(rdata1 << 8) & ~(0xff)) | (uint8_t)(CD30);
	  
	  
	}
}
