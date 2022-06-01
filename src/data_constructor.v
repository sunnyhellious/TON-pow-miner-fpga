module data_constructor (
	
	input [7:0] i_d1,
	input [7:0] i_d2, 			    // 121 * 2;
	input [7:0] i_op 	 [3:0],
	input [7:0] i_flags, 			// -4
	input [7:0] i_expire [3:0], 
	input [7:0] i_myaddr [31:0], 
	input [7:0] i_rdata [31:0], // rdata1 
	input [7:0] i_pseed  [15:0], 
	// input [7:0] i_rdata2 [31:0],
	
	input [7:0] i_rdata_inc [31:0],
	
 	output [7:0] o_data [122:0]

);

	wire [7:0] rdata_inced [31:0];

	assign {

		rdata_inced[0],
		rdata_inced[1],
		rdata_inced[2],
		rdata_inced[3],
		rdata_inced[4],
		rdata_inced[5],
		rdata_inced[6],
		rdata_inced[7],

		rdata_inced[8],
		rdata_inced[9],
		rdata_inced[10],
		rdata_inced[11],
		rdata_inced[12],
		rdata_inced[13],
		rdata_inced[14],
		rdata_inced[15],
		
		rdata_inced[16],
		rdata_inced[17],
		rdata_inced[18],
		rdata_inced[19],
		rdata_inced[20],
		rdata_inced[21],
		rdata_inced[22],
		rdata_inced[23],

		rdata_inced[24],
		rdata_inced[25],
		rdata_inced[26],
		rdata_inced[27],
		rdata_inced[28],
		rdata_inced[29],
		rdata_inced[30],
		rdata_inced[31]

	} = {

		i_rdata[0],
		i_rdata[1],
		i_rdata[2],
		i_rdata[3],
		i_rdata[4],
		i_rdata[5],
		i_rdata[6],
		i_rdata[7],

		i_rdata[8],
		i_rdata[9],
		i_rdata[10],
		i_rdata[11],
		i_rdata[12],
		i_rdata[13],
		i_rdata[14],
		i_rdata[15],
		
		i_rdata[16],
		i_rdata[17],
		i_rdata[18],
		i_rdata[19],
		i_rdata[20],
		i_rdata[21],
		i_rdata[22],
		i_rdata[23],

		i_rdata[24],
		i_rdata[25],
		i_rdata[26],
		i_rdata[27],
		i_rdata[28],
		i_rdata[29],
		i_rdata[30],
		i_rdata[31]

	} + {

		i_rdata_inc[0],
		i_rdata_inc[1],
		i_rdata_inc[2],
		i_rdata_inc[3],
		i_rdata_inc[4],
		i_rdata_inc[5],
		i_rdata_inc[6],
		i_rdata_inc[7],

		i_rdata_inc[8],
		i_rdata_inc[9],
		i_rdata_inc[10],
		i_rdata_inc[11],
		i_rdata_inc[12],
		i_rdata_inc[13],
		i_rdata_inc[14],
		i_rdata_inc[15],
		
		i_rdata_inc[16],
		i_rdata_inc[17],
		i_rdata_inc[18],
		i_rdata_inc[19],
		i_rdata_inc[20],
		i_rdata_inc[21],
		i_rdata_inc[22],
		i_rdata_inc[23],

		i_rdata_inc[24],
		i_rdata_inc[25],
		i_rdata_inc[26],
		i_rdata_inc[27],
		i_rdata_inc[28],
		i_rdata_inc[29],
		i_rdata_inc[30],
		i_rdata_inc[31]
		
	};

	genvar gv_i;

	generate

	  assign o_data[0] = i_d1;
	  assign o_data[1] = i_d2;

	  for (gv_i = 0; gv_i < 4; gv_i = gv_i + 1) begin
		  assign o_data[2+gv_i] = i_op[gv_i];
	  end
	  
	  assign o_data[6] = i_flags;
	  
	  for (gv_i = 0; gv_i < 4; gv_i = gv_i + 1) begin
		  assign o_data[7+gv_i] = i_expire[gv_i];
	  end
	  
	  for (gv_i = 0; gv_i < 32; gv_i = gv_i + 1) begin
		  assign o_data[11+gv_i] = i_myaddr[gv_i];
	  end
	  
	  for (gv_i = 0; gv_i < 32; gv_i = gv_i + 1) begin
		  assign o_data[43+gv_i] = rdata_inced[gv_i]; // i_rdata1[gv_i];
	  end
	  
	  for (gv_i = 0; gv_i < 16; gv_i = gv_i + 1) begin
		  assign o_data[75+gv_i] = i_pseed[gv_i];
	  end
	  
	  for (gv_i = 0; gv_i < 32; gv_i = gv_i + 1) begin
		  assign o_data[91+gv_i] = rdata_inced[gv_i]; // i_rdata2[gv_i];
	  end
	  
	endgenerate

endmodule
