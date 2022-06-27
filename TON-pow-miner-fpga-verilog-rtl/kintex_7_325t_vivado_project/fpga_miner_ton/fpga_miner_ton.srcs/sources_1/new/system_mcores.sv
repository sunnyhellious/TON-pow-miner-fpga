
module system_mcores #(parameter [255:0] CORES_QNT = 1) (

	input i_n_reset,
	input i_clk,

	input i_start,
    input i_stop,

	input [7:0] i_d1,
	input [7:0] i_d2,
	input [7:0] i_op 	  [3:0],
	input [7:0] i_flags,
	input [7:0] i_expire  [3:0], 
	input [7:0] i_myaddr  [31:0], 
	input [7:0] i_rdata_1 [31:0],
	input [7:0] i_pseed   [15:0],
	input [7:0] i_rdata_2 [31:0],
	
	input [7:0] i_target [31:0],
	
	output [15:0]  o_tasks_srs_acks_qnt,
	output [7:0]   o_task_rdata_1 [31:0],
	output [7:0]   o_task_rdata_2 [31:0],
	output 		   o_found,
	output [255:0] o_sha256,
	
	output o_bf // busy flag
	
);

	wire tg_1_task_nf;
	wire [15:0] tg_1_task_core_num;
	wire [7:0] tg_1_task_rdata_1 [31:0];
	wire [7:0] tg_1_task_rdata_2 [31:0];
		
	wire tg_1_tasks_sr_ack;
	
	wire [15:0] tg_1_tsaq;
	
	wire tg_1_gen_term;
	 	
	wire [31:0] tg_state [7:0];
	
	tasks_generator #( .CORES_QNT(CORES_QNT) ) tg_1 (

		.i_n_reset			(i_n_reset),
		.i_clk				(i_clk),

		
		.i_d1(i_d1),
		.i_d2(i_d2),
		.i_op(i_op),
		.i_flags(i_flags),
		.i_expire(i_expire), 
		.i_myaddr(i_myaddr), 
		.i_pseed(i_pseed),

		.i_start_nf			(i_start),
		.i_start_rdata_1	(i_rdata_1),
		.i_start_rdata_2 	(i_rdata_2),


		.i_gen_term			(tg_1_gen_term),

		.o_task_nf			(tg_1_task_nf),
		.o_task_core_num	(tg_1_task_core_num),
		.o_task_rdata_1		(tg_1_task_rdata_1),
		.o_task_rdata_2		(tg_1_task_rdata_2),
		
		.i_tasks_sr_ack		(tg_1_tasks_sr_ack),
		
		.o_tasks_srs_acks_qnt ( o_tasks_srs_acks_qnt ),
		
		.o_state			(tg_state),
		
		.o_bf 				(o_bf)
		
	);

	wire [(CORES_QNT-1):0] mcore_x_start;	
	
	wire [255:0] mcore_x_sha256 [(CORES_QNT-1):0];
	wire [(CORES_QNT-1):0] mcore_x_found;
	wire [(CORES_QNT-1):0] mcore_x_rf;
	
	wire mcores_any_found;
	assign mcores_any_found = ( | mcore_x_rf ) & ( | mcore_x_found );
	
	assign tg_1_gen_term = i_stop || mcores_any_found;
	
	assign o_found = mcores_any_found;
		

	
	genvar gv_i;
		
	generate
				
		for (gv_i = 0; gv_i < CORES_QNT; gv_i = gv_i + 1) begin

			assign mcore_x_start[gv_i] = ( tg_1_task_core_num == gv_i ) && ( tg_1_task_nf == 1'b1 ) ? 1'b1 : 1'b0;

			mcore_2r mcore_2r_x (
			  
				.i_n_reset(i_n_reset),
				.i_clk(i_clk),

				.i_d1(i_d1),
				.i_d2(i_d2),
				.i_op(i_op),
				.i_flags(i_flags),
				.i_expire(i_expire), 
				.i_myaddr(i_myaddr), 
				.i_rdata_1(tg_1_task_rdata_1),
				.i_pseed(i_pseed),
				.i_rdata_2(tg_1_task_rdata_2),
				
				.i_state(tg_state),

				.i_target(i_target),

				.i_start(mcore_x_start[gv_i]),
				
				.o_rf(mcore_x_rf[gv_i]),

				.o_sha256( mcore_x_sha256[gv_i] ),
				.o_found( mcore_x_found[gv_i] )
			);
			
		end
		
		for (gv_i = 0; gv_i < 32; gv_i = gv_i + 1) begin
			assign o_task_rdata_1[gv_i] = tg_1_task_rdata_1[gv_i];
			assign o_task_rdata_2[gv_i] = tg_1_task_rdata_2[gv_i]; 
		end		
		
	endgenerate
	
	assign tg_1_tasks_sr_ack = mcore_x_rf[0];
	
	assign o_sha256 = mcore_x_sha256[0];

endmodule
// end system_mcores