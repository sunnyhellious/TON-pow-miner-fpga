
module sha256_2r (
  
  input i_n_reset,
  input i_clk,
 
  input [7:0] i_data [58:0], // input value - 59 bytes of data
  input [31:0] i_state [7:0],  
  input       i_start,
  
  output [7:0] o_data [31:0], // output value of sha256
  output reg   o_ready
  
);

	// Constants

	reg [31:0] K [63:0];

	always @(i_clk) begin

		K[0]	= 32'h428A2F98;
		K[1]	= 32'h71374491;
		K[2]    = 32'hB5C0FBCF;
		K[3]	= 32'hE9B5DBA5;
		K[4]	= 32'h3956C25B;
		K[5]	= 32'h59F111F1;
		K[6]	= 32'h923F82A4;
		K[7]	= 32'hAB1C5ED5;
		K[8]	= 32'hD807AA98;
		K[9]	= 32'h12835B01;
		K[10]	= 32'h243185BE;
		K[11]	= 32'h550C7DC3;
		K[12]	= 32'h72BE5D74;
		K[13]	= 32'h80DEB1FE;
		K[14]	= 32'h9BDC06A7;
		K[15]	= 32'hC19BF174;
		K[16]	= 32'hE49B69C1;
		K[17]	= 32'hEFBE4786;
		K[18]	= 32'h0FC19DC6;
		K[19]	= 32'h240CA1CC;
		K[20]	= 32'h2DE92C6F;
		K[21]	= 32'h4A7484AA;
		K[22]	= 32'h5CB0A9DC;
		K[23]	= 32'h76F988DA;
		K[24]	= 32'h983E5152;
		K[25]	= 32'hA831C66D;
		K[26]	= 32'hB00327C8;
		K[27]	= 32'hBF597FC7;
		K[28]	= 32'hC6E00BF3;
		K[29]	= 32'hD5A79147;
		K[30]	= 32'h06CA6351;
		K[31]	= 32'h14292967;
		K[32]	= 32'h27B70A85;
		K[33]	= 32'h2E1B2138;
		K[34]	= 32'h4D2C6DFC;
		K[35]	= 32'h53380D13;
		K[36]	= 32'h650A7354;
		K[37]	= 32'h766A0ABB;
		K[38]	= 32'h81C2C92E;
		K[39]	= 32'h92722C85;
		K[40]	= 32'hA2BFE8A1;
		K[41]	= 32'hA81A664B;
		K[42]	= 32'hC24B8B70;
		K[43]	= 32'hC76C51A3;
		K[44]	= 32'hD192E819;
		K[45]	= 32'hD6990624;
		K[46]	= 32'hF40E3585;
		K[47]	= 32'h106AA070;
		K[48]	= 32'h19A4C116;
		K[49]	= 32'h1E376C08;
		K[50]	= 32'h2748774C;
		K[51]	= 32'h34B0BCB5;
		K[52]	= 32'h391C0CB3;
		K[53]	= 32'h4ED8AA4A;
		K[54]	= 32'h5B9CCA4F;
		K[55]	= 32'h682E6FF3;
		K[56]	= 32'h748F82EE;
		K[57]	= 32'h78A5636F;
		K[58]	= 32'h84C87814;
		K[59]	= 32'h8CC70208;
		K[60]	= 32'h90BEFFFA;
		K[61]	= 32'hA4506CEB;
		K[62]	= 32'hBEF9A3F7;
		K[63]	= 32'hC67178F2;

	end

	wire [31:0] i_data_normed [31:0]; // two blocks of data

	genvar gv_i;

	generate
	  for (gv_i = 0; gv_i < 14; gv_i = gv_i + 1) begin : gen_1
		  assign i_data_normed[gv_i] = {i_data[gv_i*4+0], i_data[gv_i*4+1], i_data[gv_i*4+2], i_data[gv_i*4+3]};
	  end
	  
	  assign i_data_normed[14] = {i_data[56], i_data[57], i_data[58], 8'h80};
	  
	  for (gv_i = 15; gv_i < 31; gv_i = gv_i + 1) begin : gen_2
		  assign i_data_normed[gv_i] = 32'h00000000;
	  end
	  
	  assign i_data_normed[31] = {8'h00, 8'h00, 8'h03, 8'hd8}; // 0x03d8 = 984 bits = 123 bytes  
	  
	endgenerate

	reg [31:0] H [7:0]; 
	reg [31:0] W [63:0]; 

	wire [31:0] tt_H0;
	assign tt_H0 = H[0];
	
	wire [31:0] tt_idn2;
	assign tt_idn2 = {i_data[2*4+0], i_data[2*4+1], i_data[2*4+2], i_data[2*4+3]};

	assign o_data[0] = H[0][31:24];
	assign o_data[1] = H[0][23:16];
	assign o_data[2] = H[0][15:8];
	assign o_data[3] = H[0][7:0];

	assign o_data[4] = H[1][31:24];
	assign o_data[5] = H[1][23:16];
	assign o_data[6] = H[1][15:8];
	assign o_data[7] = H[1][7:0];

	assign o_data[8]  = H[2][31:24];
	assign o_data[9]  = H[2][23:16];
	assign o_data[10] = H[2][15:8];
	assign o_data[11] = H[2][7:0];

	assign o_data[12] = H[3][31:24];
	assign o_data[13] = H[3][23:16];
	assign o_data[14] = H[3][15:8];
	assign o_data[15] = H[3][7:0];

	assign o_data[16] = H[4][31:24];
	assign o_data[17] = H[4][23:16];
	assign o_data[18] = H[4][15:8];
	assign o_data[19] = H[4][7:0];

	assign o_data[20] = H[5][31:24];
	assign o_data[21] = H[5][23:16];
	assign o_data[22] = H[5][15:8];
	assign o_data[23] = H[5][7:0];

	assign o_data[24] = H[6][31:24];
	assign o_data[25] = H[6][23:16];
	assign o_data[26] = H[6][15:8];
	assign o_data[27] = H[6][7:0];

	assign o_data[28] = H[7][31:24];
	assign o_data[29] = H[7][23:16];
	assign o_data[30] = H[7][15:8];
	assign o_data[31] = H[7][7:0];

	reg [31:0] a, b, c, d, e, f, g, h;

	reg [4:0] state;

	parameter 
	  S0_IDLE = 5'b00000,
	  S1 	  = 5'b00001,
	  S2 	  = 5'b00011,
	  S3 	  = 5'b00010,
	  S4 	  = 5'b00110;

	reg [7:0] cnt_S2;
	reg cnt_Rounds;

	wire [4:0] cnt_Rounds_mul16;
	assign cnt_Rounds_mul16 = { 4'b0000, cnt_Rounds } << 4;

	wire [31:0] tmp_T1;
	assign tmp_T1 = H[7] + 
		                ( {H[4][5:0], H[4][31:6]} ^ {H[4][10:0], H[4][31:11]} ^ {H[4][24:0], H[4][31:25]} ) +
		                ( (H[4] & H[5]) ^ (~H[4] & H[6]) ) +
		                K[0]; 
		                
		                
	wire [31:0] tmp_T2;     
	assign tmp_T2 = ( {H[0][1:0], H[0][31:2]} ^ {H[0][12:0], H[0][31:13]} ^ {H[0][21:0], H[0][31:22]} ) +
		                 ( (H[0] & H[1]) ^ (H[0] & H[2]) ^ (H[1] & H[2]) );
		            
	wire [31:0] tmp_T1_2_pre;
	assign tmp_T1_2_pre = 
	  h +
	  ( {e[5:0], e[31:6]} ^ {e[10:0], e[31:11]} ^ {e[24:0], e[31:25]} ) +
	  ( (e & f) ^ (~e & g) ) +
	  K[cnt_S2];

	wire [31:0] tmp_T2_2;
	assign tmp_T2_2 =  ( {a[1:0], a[31:2]} ^ {a[12:0], a[31:13]} ^ {a[21:0], a[31:22]} ) +
		                    ( (a & b) ^ (a & c) ^ (b & c) );

	wire [31:0] tmp_Wtm2; 
	assign tmp_Wtm2 = W[cnt_S2 - 2];
	wire [31:0] tmp_Wtm15; 
	assign tmp_Wtm15 = W[cnt_S2 - 15];

	wire [31:0] tmp_Wt;
	assign tmp_Wt =
	  ( {tmp_Wtm2[16:0], tmp_Wtm2[31:17]} ^ {tmp_Wtm2[18:0], tmp_Wtm2[31:19]} ^ (tmp_Wtm2 >> 10) ) +
	  W[cnt_S2 - 7] +
	  ( {tmp_Wtm15[6:0], tmp_Wtm15[31:7]}  ^ {tmp_Wtm15[17:0], tmp_Wtm15[31:18]}  ^ (tmp_Wtm15 >> 3) ) +
	  W[cnt_S2 - 16];
 
	wire [31:0] tmp_T1_3_1;
	assign tmp_T1_3_1 = tmp_T1_2_pre + W[cnt_S2];
	
	wire [31:0] tt_W14;
	assign tt_W14 = W[14];

	wire [31:0] tmp_T1_3_2;
	assign tmp_T1_3_2 = tmp_T1_2_pre + tmp_Wt;

	always @( posedge i_clk, negedge i_n_reset ) begin

	  if ( i_n_reset == 1'b0 ) begin
		
		state <= S0_IDLE;
		
		o_ready <= 1'b0;
		    
		a <= 32'd0;
		b <= 32'd0;
		c <= 32'd0;
		d <= 32'd0;
		e <= 32'd0;
		f <= 32'd0;
		g <= 32'd0;
		h <= 32'd0;
		    
		H[0] <= 32'd0;
		H[1] <= 32'd0;
		H[2] <= 32'd0;
		H[3] <= 32'd0;
		H[4] <= 32'd0;
		H[5] <= 32'd0;
		H[6] <= 32'd0;
		H[7] <= 32'd0;
		
		W[0]	<= 32'd0;  // of course this sh*t is quiet dump, but currently this project is quiet lasy
		W[1]	<= 32'd0;
		W[2]	<= 32'd0;
		W[3]	<= 32'd0;
		W[4]	<= 32'd0;
		W[5]	<= 32'd0;
		W[6]	<= 32'd0;
		W[7]	<= 32'd0;
		W[8]	<= 32'd0;
		W[9]	<= 32'd0;
		W[10]	<= 32'd0;
		W[11]	<= 32'd0;
		W[12]	<= 32'd0;
		W[13]	<= 32'd0;
		W[14]	<= 32'd0;
		W[15]	<= 32'd0;
		W[16]	<= 32'd0;
		W[17]	<= 32'd0;
		W[18]	<= 32'd0;
		W[19]	<= 32'd0;
		W[20]	<= 32'd0;
		W[21]	<= 32'd0;
		W[22]	<= 32'd0;
		W[23]	<= 32'd0;
		W[24]	<= 32'd0;
		W[25]	<= 32'd0;
		W[26]	<= 32'd0;
		W[27]	<= 32'd0;
		W[28]	<= 32'd0;
		W[29]	<= 32'd0;
		W[30]	<= 32'd0;
		W[31]	<= 32'd0;
		W[32]	<= 32'd0;
		W[33]	<= 32'd0;
		W[34]	<= 32'd0;
		W[35]	<= 32'd0;
		W[36]	<= 32'd0;
		W[37]	<= 32'd0;
		W[38]	<= 32'd0;
		W[39]	<= 32'd0;
		W[40]	<= 32'd0;
		W[41]	<= 32'd0;
		W[42]	<= 32'd0;
		W[43]	<= 32'd0;
		W[44]	<= 32'd0;
		W[45]	<= 32'd0;
		W[46]	<= 32'd0;
		W[47]	<= 32'd0;
		W[48]	<= 32'd0;
		W[49]	<= 32'd0;
		W[50]	<= 32'd0;
		W[51]	<= 32'd0;
		W[52]	<= 32'd0;
		W[53]	<= 32'd0;
		W[54]	<= 32'd0;
		W[55]	<= 32'd0;
		W[56]	<= 32'd0;
		W[57]	<= 32'd0;
		W[58]	<= 32'd0;
		W[59]	<= 32'd0;
		W[60]	<= 32'd0;
		W[61]	<= 32'd0;
		W[62]	<= 32'd0;
		W[63]	<= 32'd0;
		
		cnt_S2 <= 8'd0;
		cnt_Rounds <= 1'b0;
			   
	  end
	  else begin

		case ( state )
		  
		  S0_IDLE : begin
		  
		    o_ready <= 1'b0;
		    
		    if ( i_start == 1'b1 ) begin
		    
		      state <= S1;
		    
		      H[0] <= i_state[0];
			  H[1] <= i_state[1];
			  H[2] <= i_state[2];
			  H[3] <= i_state[3];
			  H[4] <= i_state[4];
			  H[5] <= i_state[5];
			  H[6] <= i_state[6];
			  H[7] <= i_state[7];
		      
		      cnt_Rounds <= 1'b0;
		      
		    end          
		          
		  end
		  
		  S1 : begin    
		        
		  	W[0]		<= i_data_normed[cnt_Rounds_mul16 + 0];  // of course this sh*t is quiet dump, but currently this project is quiet lasy
			W[1]		<= i_data_normed[cnt_Rounds_mul16 + 1];
			W[2]		<= i_data_normed[cnt_Rounds_mul16 + 2];
			W[3]		<= i_data_normed[cnt_Rounds_mul16 + 3];
			W[4]		<= i_data_normed[cnt_Rounds_mul16 + 4];
			W[5]		<= i_data_normed[cnt_Rounds_mul16 + 5];
			W[6]		<= i_data_normed[cnt_Rounds_mul16 + 6];
			W[7]		<= i_data_normed[cnt_Rounds_mul16 + 7];
			W[8]		<= i_data_normed[cnt_Rounds_mul16 + 8];
			W[9]		<= i_data_normed[cnt_Rounds_mul16 + 9];
			W[10]		<= i_data_normed[cnt_Rounds_mul16 + 10];
			W[11]		<= i_data_normed[cnt_Rounds_mul16 + 11];
			W[12]		<= i_data_normed[cnt_Rounds_mul16 + 12];
			W[13]		<= i_data_normed[cnt_Rounds_mul16 + 13];
			W[14]		<= i_data_normed[cnt_Rounds_mul16 + 14];
			W[15]		<= i_data_normed[cnt_Rounds_mul16 + 15];
			W[16]		<= 32'd0;
			W[17]		<= 32'd0;
			W[18]		<= 32'd0;
			W[19]		<= 32'd0;
			W[20]		<= 32'd0;
			W[21]		<= 32'd0;
			W[22]		<= 32'd0;
			W[23]		<= 32'd0;
			W[24]		<= 32'd0;
			W[25]		<= 32'd0;
			W[26]		<= 32'd0;
			W[27]		<= 32'd0;
			W[28]		<= 32'd0;
			W[29]		<= 32'd0;
			W[30]		<= 32'd0;
			W[31]		<= 32'd0;
			W[32]		<= 32'd0;
			W[33]		<= 32'd0;
			W[34]		<= 32'd0;
			W[35]		<= 32'd0;
			W[36]		<= 32'd0;
			W[37]		<= 32'd0;
			W[38]		<= 32'd0;
			W[39]		<= 32'd0;
			W[40]		<= 32'd0;
			W[41]		<= 32'd0;
			W[42]		<= 32'd0;
			W[43]		<= 32'd0;
			W[44]		<= 32'd0;
			W[45]		<= 32'd0;
			W[46]		<= 32'd0;
			W[47]		<= 32'd0;
			W[48]		<= 32'd0;
			W[49]		<= 32'd0;
			W[50]		<= 32'd0;
			W[51]		<= 32'd0;
			W[52]		<= 32'd0;
			W[53]		<= 32'd0;
			W[54]		<= 32'd0;
			W[55]		<= 32'd0;
			W[56]		<= 32'd0;
			W[57]		<= 32'd0;
			W[58]		<= 32'd0;
			W[59]		<= 32'd0;
			W[60]		<= 32'd0;
			W[61]		<= 32'd0;
			W[62]		<= 32'd0;
			W[63]		<= 32'd0;
		          
		     
		    a <= tmp_T1 + i_data_normed[cnt_Rounds_mul16 + 0] + tmp_T2;
		    b <= H[0]; 
		    c <= H[1];
		    d <= H[2];
		    e <= H[3] + tmp_T1 + i_data_normed[cnt_Rounds_mul16 + 0];
		    f <= H[4];
		    g <= H[5];
		    h <= H[6];
		    
		    cnt_S2 <= 8'd1;
		     
		    state <= S2;
		     
		  end
		  
		  
		  S2 : begin
		            
		    h <= g;
		    g <= f;
		    f <= e;
		    e <= d + tmp_T1_3_1;
		    d <= c;
		    c <= b;
		    b <= a;
		    a <= tmp_T1_3_1 + tmp_T2_2;
		    
		    cnt_S2 <= cnt_S2 + 8'd1;
		    
		    state <= cnt_S2 >= 8'd15 ? S3 : S2;
		
		  end
		  
		  S3 : begin
		  
		    W[cnt_S2] <= tmp_Wt;
			  
		    h <= g;
		    g <= f;
		    f <= e;
		    e <= d + tmp_T1_3_2;
		    d <= c;
		    c <= b;
		    b <= a;
		    a <= tmp_T1_3_2 + tmp_T2_2;
		    
		    cnt_S2 <= cnt_S2 + 8'd1;
		    
		    state <= cnt_S2 >= 8'd63 ? S4 : S3;

		  end
		  
		  S4 : begin
		  
		    cnt_Rounds <= cnt_Rounds + 1'b1;
		  
		    H[0] <= H[0] + a;
		    H[1] <= H[1] + b;
		    H[2] <= H[2] + c;
		    H[3] <= H[3] + d;
		    H[4] <= H[4] + e;
		    H[5] <= H[5] + f;
		    H[6] <= H[6] + g;
		    H[7] <= H[7] + h;
		    
		    if ( cnt_Rounds == 1'b1 ) begin
		      state <= S0_IDLE;
		      o_ready <= 1'b1; // we shoot towards the consumer of information
		    end
		    else begin 
		      state <= S1;        
		    end
		  
		  end
		  
		  default : begin
		    state <= S0_IDLE;
		  end

		endcase  

	  end

	end

endmodule
// sha256_r2 end


module sha256_1r (
  
  input i_n_reset,
  input i_clk,
  
  input [7:0] i_data [63:0], // input value - 64 bytes of data
  input       i_start,
  
  output [7:0] o_data [31:0], // output value of sha256
  output reg   o_ready
  
);


	// Constants

	reg [31:0] K [63:0];

	always @(i_clk) begin

		K[0]	= 32'h428A2F98;
		K[1]	= 32'h71374491;
		K[2]   = 32'hB5C0FBCF;
		K[3]	= 32'hE9B5DBA5;
		K[4]	= 32'h3956C25B;
		K[5]	= 32'h59F111F1;
		K[6]	= 32'h923F82A4;
		K[7]	= 32'hAB1C5ED5;
		K[8]	= 32'hD807AA98;
		K[9]	= 32'h12835B01;
		K[10]	= 32'h243185BE;
		K[11]	= 32'h550C7DC3;
		K[12]	= 32'h72BE5D74;
		K[13]	= 32'h80DEB1FE;
		K[14]	= 32'h9BDC06A7;
		K[15]	= 32'hC19BF174;
		K[16]	= 32'hE49B69C1;
		K[17]	= 32'hEFBE4786;
		K[18]	= 32'h0FC19DC6;
		K[19]	= 32'h240CA1CC;
		K[20]	= 32'h2DE92C6F;
		K[21]	= 32'h4A7484AA;
		K[22]	= 32'h5CB0A9DC;
		K[23]	= 32'h76F988DA;
		K[24]	= 32'h983E5152;
		K[25]	= 32'hA831C66D;
		K[26]	= 32'hB00327C8;
		K[27]	= 32'hBF597FC7;
		K[28]	= 32'hC6E00BF3;
		K[29]	= 32'hD5A79147;
		K[30]	= 32'h06CA6351;
		K[31]	= 32'h14292967;
		K[32]	= 32'h27B70A85;
		K[33]	= 32'h2E1B2138;
		K[34]	= 32'h4D2C6DFC;
		K[35]	= 32'h53380D13;
		K[36]	= 32'h650A7354;
		K[37]	= 32'h766A0ABB;
		K[38]	= 32'h81C2C92E;
		K[39]	= 32'h92722C85;
		K[40]	= 32'hA2BFE8A1;
		K[41]	= 32'hA81A664B;
		K[42]	= 32'hC24B8B70;
		K[43]	= 32'hC76C51A3;
		K[44]	= 32'hD192E819;
		K[45]	= 32'hD6990624;
		K[46]	= 32'hF40E3585;
		K[47]	= 32'h106AA070;
		K[48]	= 32'h19A4C116;
		K[49]	= 32'h1E376C08;
		K[50]	= 32'h2748774C;
		K[51]	= 32'h34B0BCB5;
		K[52]	= 32'h391C0CB3;
		K[53]	= 32'h4ED8AA4A;
		K[54]	= 32'h5B9CCA4F;
		K[55]	= 32'h682E6FF3;
		K[56]	= 32'h748F82EE;
		K[57]	= 32'h78A5636F;
		K[58]	= 32'h84C87814;
		K[59]	= 32'h8CC70208;
		K[60]	= 32'h90BEFFFA;
		K[61]	= 32'hA4506CEB;
		K[62]	= 32'hBEF9A3F7;
		K[63]	= 32'hC67178F2;

	end

	wire [31:0] i_data_normed [15:0]; // three blocks of data

	genvar gv_i;

	generate
	  
	  for (gv_i = 0; gv_i < 16; gv_i = gv_i + 1) begin : gen_1
		  assign i_data_normed[gv_i] = {i_data[gv_i*4+0], i_data[gv_i*4+1], i_data[gv_i*4+2], i_data[gv_i*4+3]};
	  end
	  	  
	endgenerate

	reg [31:0] H [7:0]; 
	reg [31:0] W [63:0]; 

	wire [31:0] tt_H0;
	assign tt_H0 = H[0];

	assign o_data[0] = H[0][31:24];
	assign o_data[1] = H[0][23:16];
	assign o_data[2] = H[0][15:8];
	assign o_data[3] = H[0][7:0];

	assign o_data[4] = H[1][31:24];
	assign o_data[5] = H[1][23:16];
	assign o_data[6] = H[1][15:8];
	assign o_data[7] = H[1][7:0];

	assign o_data[8]  = H[2][31:24];
	assign o_data[9]  = H[2][23:16];
	assign o_data[10] = H[2][15:8];
	assign o_data[11] = H[2][7:0];

	assign o_data[12] = H[3][31:24];
	assign o_data[13] = H[3][23:16];
	assign o_data[14] = H[3][15:8];
	assign o_data[15] = H[3][7:0];

	assign o_data[16] = H[4][31:24];
	assign o_data[17] = H[4][23:16];
	assign o_data[18] = H[4][15:8];
	assign o_data[19] = H[4][7:0];

	assign o_data[20] = H[5][31:24];
	assign o_data[21] = H[5][23:16];
	assign o_data[22] = H[5][15:8];
	assign o_data[23] = H[5][7:0];

	assign o_data[24] = H[6][31:24];
	assign o_data[25] = H[6][23:16];
	assign o_data[26] = H[6][15:8];
	assign o_data[27] = H[6][7:0];

	assign o_data[28] = H[7][31:24];
	assign o_data[29] = H[7][23:16];
	assign o_data[30] = H[7][15:8];
	assign o_data[31] = H[7][7:0];
	
	reg [31:0] a, b, c, d, e, f, g, h;

	reg [4:0] state;

	parameter 
	  S0_IDLE = 5'b00000, // 0
	  S1 = 5'b00001, // 1
	  S2 = 5'b00011, // 3
	  S3 = 5'b00010, // 2
	  S4 = 5'b00110; // 6

	reg [7:0] cnt_S2; // sixty four iterations
	
	wire [31:0] tmp_T1;
	assign tmp_T1 = H[7] + 
		                ( {H[4][5:0], H[4][31:6]} ^ {H[4][10:0], H[4][31:11]} ^ {H[4][24:0], H[4][31:25]} ) +     // sigma1(H[4])
		                ( (H[4] & H[5]) ^ (~H[4] & H[6]) ) +                                                      // ch(H[4], H[5], H[6])
		                K[0]; 
		                // + W[0];
		                
	wire [31:0] tmp_T2;     
	assign tmp_T2 = ( {H[0][1:0], H[0][31:2]} ^ {H[0][12:0], H[0][31:13]} ^ {H[0][21:0], H[0][31:22]} ) +     // sigma0(H[0]) + 
		                 ( (H[0] & H[1]) ^ (H[0] & H[2]) ^ (H[1] & H[2]) );                                        // maj(H[0], H[1], H[2]);
		            
	// T1 = h + sigma1(e) + ch(e, f, g) + K[t] + W[t];
	// T2 = sigma0(a) + maj(a, b, c); 

	wire [31:0] tmp_T1_2_pre;
	assign tmp_T1_2_pre = 
	  h + 
	  ( {e[5:0], e[31:6]} ^ {e[10:0], e[31:11]} ^ {e[24:0], e[31:25]} ) +   // sigma1(e)
	  ( (e & f) ^ (~e & g) ) +                                              // ch(e, f, g)
	  K[cnt_S2]; // + 
	  // W[cnt_S2];

	wire [31:0] tmp_T2_2;
	assign tmp_T2_2 =  ( {a[1:0], a[31:2]} ^ {a[12:0], a[31:13]} ^ {a[21:0], a[31:22]} ) +     // sigma0(a) + 
		                    ( (a & b) ^ (a & c) ^ (b & c) );                                        // maj(a, b, c);


	// W[t] = gamma1(W[t - 2]) + W[t - 7] + gamma0(W[t - 15]) + W[t - 16];

	wire [31:0] tmp_Wtm2; 
	assign tmp_Wtm2 = W[cnt_S2 - 2];
	wire [31:0] tmp_Wtm15; 
	assign tmp_Wtm15 = W[cnt_S2 - 15];

	wire [31:0] tmp_Wt;
	assign tmp_Wt = 
	  ( {tmp_Wtm2[16:0], tmp_Wtm2[31:17]} ^ {tmp_Wtm2[18:0], tmp_Wtm2[31:19]} ^ (tmp_Wtm2 >> 10) ) + // gamma1(W[t - 2]) 
	  W[cnt_S2 - 7] + // + W[t - 7] 
	  ( {tmp_Wtm15[6:0], tmp_Wtm15[31:7]}  ^ {tmp_Wtm15[17:0], tmp_Wtm15[31:18]}  ^ (tmp_Wtm15 >> 3) ) + // + gamma0(W[t - 15]) 
	  W[cnt_S2 - 16]; // + W[t - 16];

	wire [31:0] tmp_T1_3_1;
	assign tmp_T1_3_1 = tmp_T1_2_pre + W[cnt_S2];

	wire [31:0] tmp_T1_3_2;
	assign tmp_T1_3_2 = tmp_T1_2_pre + tmp_Wt;

	always @( posedge i_clk, negedge i_n_reset ) begin

	  if ( i_n_reset == 1'b0 ) begin
		
		state <= S0_IDLE;
		
		o_ready <= 1'b0;
		    
		a <= 32'd0;
		b <= 32'd0;
		c <= 32'd0;
		d <= 32'd0;
		e <= 32'd0;
		f <= 32'd0;
		g <= 32'd0;
		h <= 32'd0;
		    
		H[0] <= 32'd0;
		H[1] <= 32'd0;
		H[2] <= 32'd0;
		H[3] <= 32'd0;
		H[4] <= 32'd0;
		H[5] <= 32'd0;
		H[6] <= 32'd0;
		H[7] <= 32'd0;
		
		W[0]		<= 32'd0;  // of course this sh*t is quiet dump, but currently this project is quiet lasy
		W[1]		<= 32'd0;
		W[2]		<= 32'd0;
		W[3]		<= 32'd0;
		W[4]		<= 32'd0;
		W[5]		<= 32'd0;
		W[6]		<= 32'd0;
		W[7]		<= 32'd0;
		W[8]		<= 32'd0;
		W[9]		<= 32'd0;
		W[10]		<= 32'd0;
		W[11]		<= 32'd0;
		W[12]		<= 32'd0;
		W[13]		<= 32'd0;
		W[14]		<= 32'd0;
		W[15]		<= 32'd0;
		W[16]		<= 32'd0;
		W[17]		<= 32'd0;
		W[18]		<= 32'd0;
		W[19]		<= 32'd0;
		W[20]		<= 32'd0;
		W[21]		<= 32'd0;
		W[22]		<= 32'd0;
		W[23]		<= 32'd0;
		W[24]		<= 32'd0;
		W[25]		<= 32'd0;
		W[26]		<= 32'd0;
		W[27]		<= 32'd0;
		W[28]		<= 32'd0;
		W[29]		<= 32'd0;
		W[30]		<= 32'd0;
		W[31]		<= 32'd0;
		W[32]		<= 32'd0;
		W[33]		<= 32'd0;
		W[34]		<= 32'd0;
		W[35]		<= 32'd0;
		W[36]		<= 32'd0;
		W[37]		<= 32'd0;
		W[38]		<= 32'd0;
		W[39]		<= 32'd0;
		W[40]		<= 32'd0;
		W[41]		<= 32'd0;
		W[42]		<= 32'd0;
		W[43]		<= 32'd0;
		W[44]		<= 32'd0;
		W[45]		<= 32'd0;
		W[46]		<= 32'd0;
		W[47]		<= 32'd0;
		W[48]		<= 32'd0;
		W[49]		<= 32'd0;
		W[50]		<= 32'd0;
		W[51]		<= 32'd0;
		W[52]		<= 32'd0;
		W[53]		<= 32'd0;
		W[54]		<= 32'd0;
		W[55]		<= 32'd0;
		W[56]		<= 32'd0;
		W[57]		<= 32'd0;
		W[58]		<= 32'd0;
		W[59]		<= 32'd0;
		W[60]		<= 32'd0;
		W[61]		<= 32'd0;
		W[62]		<= 32'd0;
		W[63]		<= 32'd0;
		
		cnt_S2 <= 8'd0;
	   
	  end
	  else begin

		case ( state )
		  
		  S0_IDLE : begin
		  
		    o_ready <= 1'b0;
		    
		    if ( i_start == 1'b1 ) begin
		    
		      state <= S1;
		    
		      H[0] <= 32'h6A09E667;
			  H[1] <= 32'hBB67AE85;
			  H[2] <= 32'h3C6EF372;
			  H[3] <= 32'hA54FF53A;
			  H[4] <= 32'h510E527F;
			  H[5] <= 32'h9B05688C;
			  H[6] <= 32'h1F83D9AB;
			  H[7] <= 32'h5BE0CD19;
		     		      
		    end          
		          
		  end
		  
		  S1 : begin    
		        
		  	W[0]		<= i_data_normed[0];  // of course this sh*t is quiet dump, but currently this project is quiet lasy
			W[1]		<= i_data_normed[1];
			W[2]		<= i_data_normed[2];
			W[3]		<= i_data_normed[3];
			W[4]		<= i_data_normed[4];
			W[5]		<= i_data_normed[5];
			W[6]		<= i_data_normed[6];
			W[7]		<= i_data_normed[7];
			W[8]		<= i_data_normed[8];
			W[9]		<= i_data_normed[9];
			W[10]		<= i_data_normed[10];
			W[11]		<= i_data_normed[11];
			W[12]		<= i_data_normed[12];
			W[13]		<= i_data_normed[13];
			W[14]		<= i_data_normed[14];
			W[15]		<= i_data_normed[15];
			W[16]		<= 32'd0;
			W[17]		<= 32'd0;
			W[18]		<= 32'd0;
			W[19]		<= 32'd0;
			W[20]		<= 32'd0;
			W[21]		<= 32'd0;
			W[22]		<= 32'd0;
			W[23]		<= 32'd0;
			W[24]		<= 32'd0;
			W[25]		<= 32'd0;
			W[26]		<= 32'd0;
			W[27]		<= 32'd0;
			W[28]		<= 32'd0;
			W[29]		<= 32'd0;
			W[30]		<= 32'd0;
			W[31]		<= 32'd0;
			W[32]		<= 32'd0;
			W[33]		<= 32'd0;
			W[34]		<= 32'd0;
			W[35]		<= 32'd0;
			W[36]		<= 32'd0;
			W[37]		<= 32'd0;
			W[38]		<= 32'd0;
			W[39]		<= 32'd0;
			W[40]		<= 32'd0;
			W[41]		<= 32'd0;
			W[42]		<= 32'd0;
			W[43]		<= 32'd0;
			W[44]		<= 32'd0;
			W[45]		<= 32'd0;
			W[46]		<= 32'd0;
			W[47]		<= 32'd0;
			W[48]		<= 32'd0;
			W[49]		<= 32'd0;
			W[50]		<= 32'd0;
			W[51]		<= 32'd0;
			W[52]		<= 32'd0;
			W[53]		<= 32'd0;
			W[54]		<= 32'd0;
			W[55]		<= 32'd0;
			W[56]		<= 32'd0;
			W[57]		<= 32'd0;
			W[58]		<= 32'd0;
			W[59]		<= 32'd0;
			W[60]		<= 32'd0;
			W[61]		<= 32'd0;
			W[62]		<= 32'd0;
			W[63]		<= 32'd0;
		          
		     
		    a <= tmp_T1 + i_data_normed[0] + tmp_T2;
		    b <= H[0]; 
		    c <= H[1];
		    d <= H[2];
		    e <= H[3] + tmp_T1 + i_data_normed[0];
		    f <= H[4];
		    g <= H[5];
		    h <= H[6];
		    
		    cnt_S2 <= 8'd1;
		     
		    state <= S2;
		     
		  end
		  
		  
		  S2 : begin
		            
		    h <= g;
		    g <= f;
		    f <= e;
		    e <= d + tmp_T1_3_1;
		    d <= c;
		    c <= b;
		    b <= a;
		    a <= tmp_T1_3_1 + tmp_T2_2;
		    
		    cnt_S2 <= cnt_S2 + 8'd1;
		    
		    state <= cnt_S2 >= 8'd15 ? S3 : S2;
		
		  end
		  
		  S3 : begin
		  
		    W[cnt_S2] <= tmp_Wt;
			  
		    h <= g;
		    g <= f;
		    f <= e;
		    e <= d + tmp_T1_3_2;
		    d <= c;
		    c <= b;
		    b <= a;
		    a <= tmp_T1_3_2 + tmp_T2_2;
		    
		    cnt_S2 <= cnt_S2 + 8'd1;
		    
		    state <= cnt_S2 >= 8'd63 ? S4 : S3;

		  end
		  
		  S4 : begin
		  		  
		    H[0] <= H[0] + a;
		    H[1] <= H[1] + b;
		    H[2] <= H[2] + c;
		    H[3] <= H[3] + d;
		    H[4] <= H[4] + e;
		    H[5] <= H[5] + f;
		    H[6] <= H[6] + g;
		    H[7] <= H[7] + h;
		    
			state <= S0_IDLE;
			o_ready <= 1'b1; // we shoot towards the consumer of information
		    
		  
		  end
		  
		  default : begin
		    state <= S0_IDLE;
		  end

		endcase  

	  end

	end

endmodule
// sha256_r1 end
