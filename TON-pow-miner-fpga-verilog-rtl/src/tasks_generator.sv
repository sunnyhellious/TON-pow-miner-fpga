
module tasks_generator #(parameter [255:0] CORES_QNT = 1) (

	input i_n_reset,
	input i_clk,

	input [7:0] i_d1,
	input [7:0] i_d2,
	input [7:0] i_op 	  [3:0],
	input [7:0] i_flags,
	input [7:0] i_expire  [3:0], 
	input [7:0] i_myaddr  [31:0], 
	input [7:0] i_pseed   [15:0],

	input		i_start_nf, 			// start new flag

	input [7:0] i_start_rdata_1 [31:0],
	input [7:0] i_start_rdata_2 [31:0],

	input 		i_gen_term, 			// terminate generation

	output          o_task_nf,			// task new flag
	output [15:0] 	o_task_core_num,
	output [7:0] 	o_task_rdata_1 [31:0],
	output [7:0] 	o_task_rdata_2 [31:0],
		
	input 			i_tasks_sr_ack,		// tasks single round accepted / calculated
	
	output reg [15:0] o_tasks_srs_acks_qnt, // tasks single rounds acks qnt -> full hashrate will be calculated via very quick formula ( o_tasks_srs_acks_qnt * CORES_QNT ) / t_secs
	
	output [31:0] o_state [7:0],
	
	output o_bf // busy flag
	
	
);

	reg [511:0] rdata_cnt;
	reg [15:0] 	task_core_num_cnt;

    reg r_task_nf;

	wire [511:0] start_rdata;
	
	wire [511:0] rdata_inced;
		
	wire [511:0] rdata_cnt_fliped;
	
	genvar gv_j;
	
	generate
	
		 for (gv_j = 0; gv_j < 64; gv_j = gv_j + 1) begin
		 
		 	// assign rdata_cnt_fliped[511 - gv_j] = rdata_cnt[gv_j];
		 	assign rdata_cnt_fliped[7+gv_j*8:0+gv_j*8] = rdata_cnt[7+(63-gv_j)*8:0+(63-gv_j)*8];
		 			 	
		 end
	
	endgenerate
	
	
	assign rdata_inced = start_rdata + rdata_cnt_fliped;
		
	wire fst_block_change;
	
	assign o_task_nf = fst_block_change ? 1'b0 : r_task_nf;
	
	reg [20:0] rdata_1_old;
	
	assign fst_block_change = rdata_1_old != rdata_inced[20:0]  ? 1'b1 : 1'b0;

	genvar gv_i;
	
	reg 			mc1r_start;
	wire 			mc1r_rf;
	wire [255:0] 	mc1r_sha256;
	
	reg [255:0] 	r_mc1r_sha256;
		
	
	assign o_task_core_num = task_core_num_cnt;

	generate

	  for (gv_i = 0; gv_i < 32; gv_i = gv_i + 1) begin
		  
		  assign start_rdata[ gv_i*8+7 : gv_i*8 ] 	  		= i_start_rdata_1[gv_i];
		  assign start_rdata[ (gv_i+32)*8+7 : (gv_i+32)*8 ] = i_start_rdata_2[gv_i];
		  
		  // assign o_task_rdata_1[gv_i] = start_rdata[ gv_i*8+7 : gv_i*8 ] + rdata_cnt_fliped[ gv_i*8+7 : gv_i*8 ];
		  // assign o_task_rdata_2[gv_i] = start_rdata[ (gv_i+32)*8+7 : (gv_i+32)*8 ] + rdata_cnt_fliped[ (gv_i+32)*8+7 : (gv_i+32)*8 ] ;
		  
		  assign o_task_rdata_1[gv_i] = rdata_inced[ gv_i*8+7 : gv_i*8 ];
		  assign o_task_rdata_2[gv_i] = rdata_inced[ (gv_i+32)*8+7 : (gv_i+32)*8 ];
		  
	  end
	  
	  for (gv_i = 0; gv_i < 8; gv_i = gv_i + 1) begin
	 
		// assign o_state[gv_i] = {r_mc1r_sha256[31+32*gv_i:24+32*gv_i], r_mc1r_sha256[23+32*gv_i:16+32*gv_i], r_mc1r_sha256[15+32*gv_i:8+32*gv_i], r_mc1r_sha256[7+32*gv_i:0+32*gv_i]};	
        assign o_state[gv_i] = {r_mc1r_sha256[7+32*gv_i:0+32*gv_i], r_mc1r_sha256[15+32*gv_i:8+32*gv_i], r_mc1r_sha256[23+32*gv_i:16+32*gv_i], r_mc1r_sha256[31+32*gv_i:24+32*gv_i]};	
        
        // assign o_state[gv_i] = {8'h00, r_mc1r_sha256[15+32*gv_i:8+32*gv_i], r_mc1r_sha256[23+32*gv_i:16+32*gv_i], r_mc1r_sha256[31+32*gv_i:24+32*gv_i]};	
		
	  end
		
	endgenerate

	reg [2:0] state;

	assign o_bf = state != 3'b000 ? 1'b1 : 1'b0;

	always @( posedge i_clk, negedge i_n_reset ) begin

		if(i_n_reset == 1'b0) begin

			r_task_nf			<= 1'b0;

			rdata_cnt 		    <= {512{1'b0}};
			
			task_core_num_cnt 	<= 16'd0;

			state				<= 3'b000;
			
			o_tasks_srs_acks_qnt <= 16'd0;
			
			mc1r_start	 		<= 1'b0; 
			
			r_mc1r_sha256 		<= 256'd0;
			
			rdata_1_old 		<= 21'd0;
					 
		end
		else begin
		
			rdata_1_old 		<=  rdata_inced[21:0];
		
		    if(i_gen_term == 1'b1) begin
		      
		      state <= 3'b000;
		      
		    end
		    else begin
		
                case(state)
                    
                    3'b000 : begin
                        
                        rdata_cnt 			 <= {{511{1'b0}}, 1'b0};
                        task_core_num_cnt 	 <= 16'd0;
                        
                        o_tasks_srs_acks_qnt <= 16'd0;
                        
                        r_task_nf <= 1'b0;
                        
                        if (i_start_nf)	begin	
                        
                            mc1r_start <= 1'b1;		
                            
                            state <= 3'b001;
                                                    
                        end
                                                
                    
                    end
                    
                    3'b001 : begin 
    
                        mc1r_start <= 1'b0;
                                                            
                        if( mc1r_rf == 1'b1 ) begin
                                                
                            r_mc1r_sha256 <= mc1r_sha256;	
                            
                            r_task_nf <= 1'b1;				
                            
                            state <= 3'b011;
                            
                        end
                        
                    end
                    
                    3'b011 : begin
                                                                                
                        if(fst_block_change) begin
                            r_task_nf <= 1'b0;
                            state <= 3'b110;
                        end
                        else begin
                            task_core_num_cnt <= task_core_num_cnt + 16'd1;
                            if( task_core_num_cnt == CORES_QNT ) begin
                                r_task_nf <= 1'b0;
                                state <= 3'b010;
                            end
                            else begin
                                rdata_cnt <= rdata_cnt + 512'd1;
                                r_task_nf <= 1'b1;					
                            end
                        end                     
                                                
                    end
                    
                    3'b010 : begin                      
                        
                        if( i_tasks_sr_ack == 1'b1 ) begin
                            task_core_num_cnt <= 16'd0;
                            r_task_nf <= 1'b1;
                            o_tasks_srs_acks_qnt <= o_tasks_srs_acks_qnt + 16'd1;
                            state <= 3'b011;                            
                        end
       
                    end
                    
                    3'b110 : begin                     
                                         
                        task_core_num_cnt <= 16'd0;
                        r_task_nf <= 1'b0;
                        o_tasks_srs_acks_qnt <= o_tasks_srs_acks_qnt + 16'd1;
                        state <= 3'b001;
                        mc1r_start <= 1'b1;
                       
                    end
                        
                endcase
            
			end
						
		end
		
	end
	
	always @(o_tasks_srs_acks_qnt) begin
	
	end
	
	mcore_1r mcore_1r_1 (
  
		.i_n_reset(i_n_reset),
		.i_clk(i_clk),

		// input data

		.i_d1(i_d1),
		.i_d2(i_d2),
		.i_op(i_op),
		.i_flags(i_flags),
		.i_expire(i_expire), 
		.i_myaddr(i_myaddr), 
		
		.i_rdata_1(o_task_rdata_1),
		
		.i_pseed(i_pseed),
		
		.i_rdata_2(o_task_rdata_2),

		// enable signal

		.i_start(mc1r_start),
		
		.o_rf(mc1r_rf),	// ready flag

		// found output	

		.o_sha256(mc1r_sha256)
		
	);

endmodule
//