
module mcore_2r (
  
	input i_n_reset,
	input i_clk,

	// input data

	input [7:0] i_d1,
	input [7:0] i_d2,
	input [7:0] i_op 	  [3:0],
	input [7:0] i_flags,
	input [7:0] i_expire  [3:0], 
	input [7:0] i_myaddr  [31:0], 
	input [7:0] i_rdata_1 [31:0],
	input [7:0] i_pseed   [15:0],
	input [7:0] i_rdata_2 [31:0],
	
	input [31:0] i_state [7:0],  

	// target

	input [7:0] i_target [31:0],

	// enable signal

	input       i_start,
	
	output 		o_rf,	// ready flag

	// found output	

	output [255:0] 	o_sha256,
	output   	 	o_found
	

);

	wire comp_h_res;

	wire [7:0] constr_data [58:0];

	wire [7:0] sha256 [31:0];
		
	assign o_found = o_rf && comp_h_res ? 1'b1 : 1'b0;
	
	reg [7:0] r_rdata_1 [31:0];
	reg [7:0] r_rdata_2 [31:0];

	genvar gv_i;

	generate
	
		for (gv_i = 0; gv_i < 32; gv_i = gv_i + 1) begin
	
			always @( posedge i_clk, negedge i_n_reset ) begin : r_rdata_1_fill_prcs 

			  if ( i_n_reset == 1'b0 )
				r_rdata_1[gv_i] <= 8'd0;
			  else if( i_start )
				r_rdata_1[gv_i] <= i_rdata_1[gv_i];
				
			end
			
			always @( posedge i_clk, negedge i_n_reset ) begin : r_rdata_2_fill_prcs 

			  if ( i_n_reset == 1'b0 )
				r_rdata_2[gv_i] <= 8'd0;
			  else if( i_start )
				r_rdata_2[gv_i] <= i_rdata_2[gv_i];
				
			end
			
		end			
		
		for (gv_i = 0; gv_i < 8; gv_i = gv_i + 1) begin
		  assign o_sha256[gv_i*32+31:gv_i*32] = { sha256[gv_i*4+3], sha256[gv_i*4+2], sha256[gv_i*4+1], sha256[gv_i*4+0] };		  
		end
		
	endgenerate
	
	data_constructor data_constructor_0 (
	
		.i_d1(i_d1),
		.i_d2(i_d2),
		.i_op(i_op),
		.i_flags(i_flags),
		.i_expire(i_expire), 
		.i_myaddr(i_myaddr), 
		.i_rdata_1(r_rdata_1),
		.i_pseed(i_pseed),
		.i_rdata_2(r_rdata_2),
	
	 	.o_data(),
	 	.o_data_1(),
		.o_data_2(constr_data)
		
	);
	
	wire [31:0] tt_cd_20;
	assign tt_cd_20 = constr_data[20];
	
	wire [7:0] tt;
	assign tt = constr_data[1];
	
	reg st_delayed;
	
	always @( posedge i_clk, negedge i_n_reset ) begin

	  if ( i_n_reset == 1'b0 )
		st_delayed <= 1'b0;
	  else
		st_delayed <= i_start;
		
	end

	sha256_2r sha256_2r_1 (

		.i_n_reset(i_n_reset),
		.i_clk(i_clk),
		  
		.i_data(constr_data),
		.i_state(i_state),
		.i_start(st_delayed),
		  
		.o_data(sha256),
		.o_ready(o_rf)
				
	);

	comp_h comp_h_1 (
		.i_h(sha256),
		.i_target(i_target),
		.res(comp_h_res)
	);
	
endmodule 
// end mcore_2r

module mcore_1r (
  
	input i_n_reset,
	input i_clk,

	// input data

	input [7:0] i_d1,
	input [7:0] i_d2,
	input [7:0] i_op 	  [3:0],
	input [7:0] i_flags,
	input [7:0] i_expire  [3:0], 
	input [7:0] i_myaddr  [31:0], 
	input [7:0] i_rdata_1 [31:0],
	input [7:0] i_pseed   [15:0],
	input [7:0] i_rdata_2 [31:0],


	// enable signal

	input       i_start,
	
	output 		o_rf,	// ready flag

	// found output	

	output [255:0] 	o_sha256
	

);

	wire [7:0] constr_data [63:0];

	wire [7:0] sha256 [31:0];
		
	reg [7:0] r_rdata_1 [31:0];
	reg [7:0] r_rdata_2 [31:0];

	genvar gv_i;

	generate
	
		for (gv_i = 0; gv_i < 32; gv_i = gv_i + 1) begin
	
			always @( posedge i_clk, negedge i_n_reset ) begin : r_rdata_1_fill_prcs 

			  if ( i_n_reset == 1'b0 )
				r_rdata_1[gv_i] <= 8'd0;
			  else if( i_start )
				r_rdata_1[gv_i] <= i_rdata_1[gv_i];
				
			end
			
			always @( posedge i_clk, negedge i_n_reset ) begin : r_rdata_2_fill_prcs 

			  if ( i_n_reset == 1'b0 )
				r_rdata_2[gv_i] <= 8'd0;
			  else if( i_start )
				r_rdata_2[gv_i] <= i_rdata_2[gv_i];
				
			end
			
		end			
		
		for (gv_i = 0; gv_i < 8; gv_i = gv_i + 1) begin
		  assign o_sha256[gv_i*32+31:gv_i*32] = { sha256[gv_i*4+3], sha256[gv_i*4+2], sha256[gv_i*4+1], sha256[gv_i*4+0] };		  
		end
		
	endgenerate
	
	data_constructor data_constructor_0 (
	
		.i_d1(i_d1),
		.i_d2(i_d2),
		.i_op(i_op),
		.i_flags(i_flags),
		.i_expire(i_expire), 
		.i_myaddr(i_myaddr), 
		.i_rdata_1(r_rdata_1),
		.i_pseed(i_pseed),
		.i_rdata_2(r_rdata_2),
		
	 	.o_data(),
	 	.o_data_1(constr_data),
		.o_data_2()
	 	
	 	
		
	);
	
	wire [7:0] tt;
	assign tt = constr_data[1];
	
	reg st_delayed;
	
	always @( posedge i_clk, negedge i_n_reset ) begin

	  if ( i_n_reset == 1'b0 )
		st_delayed <= 1'b0;
	  else
		st_delayed <= i_start;
		
	end

	sha256_1r sha256_1r_1 (

		.i_n_reset(i_n_reset),
		.i_clk(i_clk),
		  
		.i_data(constr_data),
		.i_start(st_delayed),
		  
		.o_data(sha256),
		.o_ready(o_rf)
				
	);
	
endmodule 
// end mcore

// module which compares calculated sha256 value with target value
module comp_h (

	input [7:0] i_h [31:0],
	input [7:0] i_target [31:0],
	
	output res
);

	assign res = 
		
		{

			i_h[0],
			i_h[1],
			i_h[2],
			i_h[3],
			i_h[4],
			i_h[5],
			i_h[6],
			i_h[7],

			i_h[8],
			i_h[9],
			i_h[10],
			i_h[11],
			i_h[12],
			i_h[13],
			i_h[14],
			i_h[15],

			i_h[16],
			i_h[17],
			i_h[18],
			i_h[19],
			i_h[20],
			i_h[21],
			i_h[22],
			i_h[23],

			i_h[24],
			i_h[25],
			i_h[26],
			i_h[27],
			i_h[28],
			i_h[29],
			i_h[30],
			i_h[31]

		} 
		
		<
		
		{
		
			i_target[0],
			i_target[1],
			i_target[2],
			i_target[3],
			i_target[4],
			i_target[5],
			i_target[6],
			i_target[7],

			i_target[8],
			i_target[9],
			i_target[10],
			i_target[11],
			i_target[12],
			i_target[13],
			i_target[14],
			i_target[15],

			i_target[16],
			i_target[17],
			i_target[18],
			i_target[19],
			i_target[20],
			i_target[21],
			i_target[22],
			i_target[23],

			i_target[24],
			i_target[25],
			i_target[26],
			i_target[27],
			i_target[28],
			i_target[29],
			i_target[30],
			i_target[31]

		} ;

endmodule
// end comp_h

