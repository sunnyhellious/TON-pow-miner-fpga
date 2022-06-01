
module mcore #(parameter [255:0] CORE_NUM = 0, parameter [255:0] CORES_QNT = 1) (
  
	input i_n_reset,
	input i_clk,

	// input data

	input [7:0] i_d1,
	input [7:0] i_d2,
	input [7:0] i_op 	 [3:0],
	input [7:0] i_flags,
	input [7:0] i_expire [3:0], 
	input [7:0] i_myaddr [31:0], 
	input [7:0] i_rdata [31:0],
	input [7:0] i_pseed  [15:0],

	// target

	input [7:0] i_target [31:0],

	// enable signal

	input       i_enable,

	// found output	

	output [7:0] o_data [31:0],
	output reg   o_found

);

	parameter [255:0] CORE_NQ = CORE_NUM*CORES_QNT; // NUM * QNT

	wire comp_h_res;

	reg [255:0] rdata_cnt;

	wire [7:0] constr_data [122:0];

	reg sha256_start;
	wire [7:0] sha256 [31:0];
	wire sha256_ready;

	reg [3:0] state;
	parameter 
		ST_IDLE = 4'b0000,
		ST_WORK = 4'b0001;
		
	always @( posedge i_clk, negedge i_n_reset ) begin

	  if ( i_n_reset == 1'b0 ) begin
	  	state <= ST_IDLE;
	  	rdata_cnt <= CORE_NQ;
	  	sha256_start <= 1'b0;
	  	o_found <= 1'b0;
	  end
	  else begin
	  	
	  	case(state)
	  	
	  		ST_IDLE : begin
	  			
	  			rdata_cnt 	 <= CORE_NQ;
	  			
	  			if( i_enable == 1'b1 ) begin
	  				state <= ST_WORK;
	  				sha256_start <= 1'b1;
	  			end		

	  		end
	  		
	  		ST_WORK : begin
	  			
	  			if ( sha256_ready && comp_h_res ) begin 
	  				o_found <= 1'b1;
	  				sha256_start <= 1'b0;
	  			end
	  			else if ( i_enable == 1'b0 ) begin
	  				state <= ST_IDLE;	
	  			end 
	  			else if ( sha256_ready ) begin
		  			rdata_cnt <= rdata_cnt + 256'd1;
	  			end				  			 
	  			  			 		
	  		end
	  		
	  	
	  	endcase 
	  
	  end
	  
	end

	genvar gv_i;
	generate
	  for (gv_i = 0; gv_i < 32; gv_i = gv_i + 1) begin
		  assign o_data[gv_i] = sha256[gv_i];
	  end
	endgenerate
	
	wire [7:0] rdata_cnt_tda [31:0];
	generate
	  for (gv_i = 0; gv_i < 32; gv_i = gv_i + 1) begin
		  assign rdata_cnt_tda[gv_i] = rdata_cnt[ 7+gv_i*8 : gv_i*8 ];
	  end
	endgenerate

	data_constructor data_constructor_0 (
		
		.i_d1(i_d1),
		.i_d2(i_d2),
		.i_op(i_op),
		.i_flags(i_flags),
		.i_expire(i_expire), 
		.i_myaddr(i_myaddr), 
		.i_rdata(i_rdata),
		.i_pseed(i_pseed),
		
		.i_rdata_inc( rdata_cnt_tda ),
		
	 	.o_data(constr_data)

	);

	sha256 sha256_1 (
	  
	  .i_n_reset(i_n_reset),
	  .i_clk(i_clk),
	  
	  .i_data(constr_data), // input value - 192 bytes of data
	  .i_start(sha256_start),
	  
	  .o_data(sha256), // output value of sha256
	  .o_ready(sha256_ready)

	);

	comp_h comp_h_1 (
		.i_h(sha256),
		.i_target(i_target),
		.res(comp_h_res)
	);

endmodule 
// end mcore


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
