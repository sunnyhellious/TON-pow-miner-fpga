module data_constructor (
	
	input [7:0] i_d1,
	input [7:0] i_d2, 			    // 121 * 2;
	input [7:0] i_op 	  [3:0],
	input [7:0] i_flags, 			// -4
	input [7:0] i_expire  [3:0], 
	input [7:0] i_myaddr  [31:0], // 11 + 32 = 43 
	input [7:0] i_rdata_1 [31:0], // 64-43 = 21 -> r_data_1[31:11] - the end of first block
	input [7:0] i_pseed   [15:0], 
	input [7:0] i_rdata_2 [31:0],
	
 	output [7:0] o_data [122:0],
 	
	output [7:0] o_data_1 [63:0],
	output [7:0] o_data_2 [58:0]

);

	genvar gv_i;
	
	wire [983:0] tt;
	
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
		  assign o_data[43+gv_i] = i_rdata_1[gv_i];
	  end
	  
	  for (gv_i = 0; gv_i < 16; gv_i = gv_i + 1) begin
		  assign o_data[75+gv_i] = i_pseed[gv_i];
	  end
	  
	  for (gv_i = 0; gv_i < 32; gv_i = gv_i + 1) begin
		  assign o_data[91+gv_i] = i_rdata_2[gv_i];
	  end
	  
	  for (gv_i = 0; gv_i < 123; gv_i = gv_i + 1) begin
		  assign tt[8*gv_i+7:8*gv_i] = o_data[gv_i];
	  end
	  
	  ///////
	  
	  assign o_data_1[0] = i_d1;
	  assign o_data_1[1] = i_d2;

	  for (gv_i = 0; gv_i < 4; gv_i = gv_i + 1) begin
		  assign o_data_1[2+gv_i] = i_op[gv_i];
	  end
	  
	  assign o_data_1[6] = i_flags;
	  
	  for (gv_i = 0; gv_i < 4; gv_i = gv_i + 1) begin
		  assign o_data_1[7+gv_i] = i_expire[gv_i];
	  end
	  
	  for (gv_i = 0; gv_i < 32; gv_i = gv_i + 1) begin
		  assign o_data_1[11+gv_i] = i_myaddr[gv_i];
	  end
	  
	  for (gv_i = 0; gv_i < 21; gv_i = gv_i + 1) begin
		  assign o_data_1[43+gv_i] = i_rdata_1[gv_i];
	  end
	  
	  ///////
	 
	  for (gv_i = 21; gv_i < 32; gv_i = gv_i + 1) begin
		  assign o_data_2[gv_i-21] = i_rdata_1[gv_i];
	  end
	  
	  for (gv_i = 0; gv_i < 16; gv_i = gv_i + 1) begin
		  assign o_data_2[11+gv_i] = i_pseed[gv_i];
	  end
	  
	  for (gv_i = 0; gv_i < 32; gv_i = gv_i + 1) begin
		  assign o_data_2[27+gv_i] = i_rdata_2[gv_i];
	  end
	  
	  //
	  
	endgenerate
	
	

endmodule
