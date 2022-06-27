
module ch (x, y, z, o);
	input [31:0] x, y, z;
	output [31:0] o;
	assign o = ( (x & y) ^ (~x & z) );
endmodule

module maj (x, y, z, o);
	input [31:0] x, y, z;
	output [31:0] o;
	assign o = ( (x & y) ^ (x & z) ^ (y & z) );
endmodule

module sigma0 (x, o);
	input [31:0] x;
	output [31:0] o;
	assign o = ( { x[1:0], x[31:2] } ^ { x[12:0], x[31:13] } ^ { x[21:0], x[31:22] } );
endmodule

module sigma1 (x, o);
	input [31:0] x;
	output [31:0] o;
	assign o = ( { x[5:0], x[31:6] } ^ { x[10:0], x[31:11] } ^ { x[24:0], x[31:25] } );
endmodule

module gamma0 (x, o);
	input [31:0] x;
	output [31:0] o;
	assign o = ( { x[6:0], x[31:7] } ^ { x[17:0], x[31:18] } ^ { 3'b000, x[31:3] } );
endmodule

module gamma1 (x, o);
	input [31:0] x;
	output [31:0] o;
	assign o = ( { x[16:0], x[31:17] } ^ { x[18:0], x[31:19] } ^ { 10'b0000000000, x[31:10] } );
endmodule

module sha256_1r_comb_core_v2 (
	input  wire [255:0]state_in,
	input  wire [511:0]data_in,
	output wire [255:0]state_out
);

	localparam Ks = {
		32'h428a2f98, 32'h71374491, 32'hb5c0fbcf, 32'he9b5dba5,
		32'h3956c25b, 32'h59f111f1, 32'h923f82a4, 32'hab1c5ed5,
		32'hd807aa98, 32'h12835b01, 32'h243185be, 32'h550c7dc3,
		32'h72be5d74, 32'h80deb1fe, 32'h9bdc06a7, 32'hc19bf174,
		32'he49b69c1, 32'hefbe4786, 32'h0fc19dc6, 32'h240ca1cc,
		32'h2de92c6f, 32'h4a7484aa, 32'h5cb0a9dc, 32'h76f988da,
		32'h983e5152, 32'ha831c66d, 32'hb00327c8, 32'hbf597fc7,
		32'hc6e00bf3, 32'hd5a79147, 32'h06ca6351, 32'h14292967,
		32'h27b70a85, 32'h2e1b2138, 32'h4d2c6dfc, 32'h53380d13,
		32'h650a7354, 32'h766a0abb, 32'h81c2c92e, 32'h92722c85,
		32'ha2bfe8a1, 32'ha81a664b, 32'hc24b8b70, 32'hc76c51a3,
		32'hd192e819, 32'hd6990624, 32'hf40e3585, 32'h106aa070,
		32'h19a4c116, 32'h1e376c08, 32'h2748774c, 32'h34b0bcb5,
		32'h391c0cb3, 32'h4ed8aa4a, 32'h5b9cca4f, 32'h682e6ff3,
		32'h748f82ee, 32'h78a5636f, 32'h84c87814, 32'h8cc70208,
		32'h90befffa, 32'ha4506ceb, 32'hbef9a3f7, 32'hc67178f2};

	genvar i;
	
	generate
	for(i=0; i<64; i=i+1)
	begin : RND
			
			wire [31:0] W;
			
			if(i<16)
			begin
				assign W = data_in[i*32+31:i*32];
			end
			else
			begin
				
				wire [31:0] gamma1_wim2_o; gamma1 gamma1_wim2_( RND[i-2].W, gamma1_wim2_o);
				wire [31:0] gamma0_wim15_o; gamma0 gamma0_wim15_( RND[i-15].W, gamma0_wim15_o);
				
				assign W = gamma1_wim2_o + RND[i-7].W + gamma0_wim15_o + RND[i-16].W ;
				
			end
						
			wire [31:0] T1, T2, a, b, c, d, e, f, g, h;
						
			if(i == 0) begin
			
				wire [31:0] sigma1_e_o; sigma1 	sigma1_e_ ( state_in[159:128], sigma1_e_o );
				wire [31:0] ch_e_f_g_o; ch 		ch_e_f_g_ ( state_in[159:128], state_in[191:160], state_in[223:192], ch_e_f_g_o );  
				wire [31:0] sigma0_a_o; sigma0 	sigma0_a_ ( state_in[31:0], sigma0_a_o );
				wire [31:0] maj_a_b_c_o; maj	maj_a_b_c_ ( state_in[31:0], state_in[63:32], state_in[95:64], maj_a_b_c_o );  
			
				assign T1 = state_in[255:224] + sigma1_e_o + ch_e_f_g_o + Ks[32*(63-i)+31:32*(63-i)] + W;
				assign T2 = sigma0_a_o + maj_a_b_c_o;

				assign h = state_in[223:192];
				assign g = state_in[191:160];
				assign f = state_in[159:128];
				assign e = state_in[127:96] + T1;
				assign d = state_in[95:64];
				assign c = state_in[63:32];
				assign b = state_in[31:0];
				assign a = T1 + T2;			
			
			end				
			else begin
			
				wire [31:0] sigma1_e_o; sigma1 	sigma1_e_ ( RND[i-1].e, sigma1_e_o );
				wire [31:0] ch_e_f_g_o; ch 		ch_e_f_g_ ( RND[i-1].e, RND[i-1].f, RND[i-1].g, ch_e_f_g_o );  
				wire [31:0] sigma0_a_o; sigma0 	sigma0_a_ ( RND[i-1].a, sigma0_a_o );
				wire [31:0] maj_a_b_c_o; maj	maj_a_b_c_ ( RND[i-1].a, RND[i-1].b, RND[i-1].c, maj_a_b_c_o );  
			
				assign T1 = RND[i-1].h + sigma1_e_o + ch_e_f_g_o + Ks[32*(63-i)+31:32*(63-i)] + W;
				assign T2 = sigma0_a_o + maj_a_b_c_o;

				assign h = RND[i-1].g;
				assign g = RND[i-1].f;
				assign f = RND[i-1].e;
				assign e = RND[i-1].d + T1;
				assign d = RND[i-1].c;
				assign c = RND[i-1].b;
				assign b = RND[i-1].a;
				assign a = T1 + T2;	
			
			end
				
	end
	endgenerate

	wire [31:0]a; assign a = state_in[ 31:  0];
	wire [31:0]b; assign b = state_in[ 63: 32];
	wire [31:0]c; assign c = state_in[ 95: 64];
	wire [31:0]d; assign d = state_in[127: 96];
	wire [31:0]e; assign e = state_in[159:128];
	wire [31:0]f; assign f = state_in[191:160];
	wire [31:0]g; assign g = state_in[223:192];
	wire [31:0]h; assign h = state_in[255:224];

	wire [31:0]a1; assign a1 = RND[63].a;
	wire [31:0]b1; assign b1 = RND[63].b;
	wire [31:0]c1; assign c1 = RND[63].c;
	wire [31:0]d1; assign d1 = RND[63].d;
	wire [31:0]e1; assign e1 = RND[63].e;
	wire [31:0]f1; assign f1 = RND[63].f;
	wire [31:0]g1; assign g1 = RND[63].g;
	wire [31:0]h1; assign h1 = RND[63].h;	

	wire [31:0]a2; assign a2 = a+a1;
	wire [31:0]b2; assign b2 = b+b1;
	wire [31:0]c2; assign c2 = c+c1;
	wire [31:0]d2; assign d2 = d+d1;
	wire [31:0]e2; assign e2 = e+e1;
	wire [31:0]f2; assign f2 = f+f1;
	wire [31:0]g2; assign g2 = g+g1;
	wire [31:0]h2; assign h2 = h+h1;
	
	assign state_out = {h2,g2,f2,e2,d2,c2,b2,a2};
	
endmodule
//


module sha256_comb_core_v2 (

	input [7:0] i_data [122:0], // input value - 123 bytes of data
	output [7:0] o_data [31:0]  // output value of sha256
			
);
	
	wire [31:0] i_data_normed [47:0]; // three blocks of data
	
	wire [255:0] cc_state_out;
	
	genvar gv_i;

	generate
	
	  for (gv_i = 0; gv_i < 30; gv_i = gv_i + 1) begin : gen_1
		  assign i_data_normed[gv_i] = {i_data[gv_i*4+0], i_data[gv_i*4+1], i_data[gv_i*4+2], i_data[gv_i*4+3]};
	  end
	  
	  assign i_data_normed[30] = {i_data[120], i_data[121], i_data[122], 8'h80};
	  
	  for (gv_i = 31; gv_i < 47; gv_i = gv_i + 1) begin : gen_2
		  assign i_data_normed[gv_i] = 32'h00000000;
	  end
	  
	  assign i_data_normed[47] = {8'h00, 8'h00, 8'h03, 8'hd8}; // 0x03d8 = 984 bits = 123 bytes  
	  
	  for (gv_i = 0; gv_i < 32; gv_i = gv_i + 1) begin : gen_3
	  	assign o_data[(31-gv_i)] = cc_state_out[gv_i*8+7:gv_i*8];
	  end
	  	  	  
	endgenerate
	
	wire [255:0] cc_init_state;
	assign cc_init_state = 256'h5be0cd191f83d9ab9b05688c510e527fa54ff53a3c6ef372bb67ae856a09e667;

	wire [255:0] cc_state_out_1;

	sha256_1r_comb_core_v2 sha256_1r_comb_core_v2_1 ( 

		.state_in	(cc_init_state),
		.data_in	( 
					  { 
						i_data_normed[15], i_data_normed[14], i_data_normed[13], i_data_normed[12], i_data_normed[11], i_data_normed[10], i_data_normed[9], 
						i_data_normed[8], i_data_normed[7], i_data_normed[6], i_data_normed[5], i_data_normed[4], i_data_normed[3], i_data_normed[2],
						i_data_normed[1], i_data_normed[0]  
					  } 
					),
		.state_out	(cc_state_out_1)
		
	);

	wire [255:0] cc_state_out_2;

	sha256_1r_comb_core_v2 sha256_1r_comb_core_v2_2 ( 

		.state_in	(cc_state_out_1),
		.data_in	( 
					  { 
						i_data_normed[31], i_data_normed[30], i_data_normed[29], i_data_normed[28], i_data_normed[27], i_data_normed[26], i_data_normed[25], 
						i_data_normed[24], i_data_normed[23], i_data_normed[22], i_data_normed[21], i_data_normed[20], i_data_normed[19], i_data_normed[18],
						i_data_normed[17], i_data_normed[16]  
					  } 
					),
		.state_out	(cc_state_out_2)
		
	);


	

	sha256_1r_comb_core_v2 sha256_1r_comb_core_v2_3 ( 

		.state_in	(cc_state_out_2),
		.data_in	( 
					  { 
						i_data_normed[47], i_data_normed[46], i_data_normed[45], i_data_normed[44], i_data_normed[43], i_data_normed[42], i_data_normed[41], 
						i_data_normed[40], i_data_normed[39], i_data_normed[38], i_data_normed[37], i_data_normed[36], i_data_normed[35], i_data_normed[34],
						i_data_normed[33], i_data_normed[32]  
					  } 
					),
		.state_out	(cc_state_out)
		
	);

endmodule
//


	
module sha256_comb_core_v2_clk3 (

	input i_n_reset,
	input i_clk,
	  
	input [7:0] i_data [122:0], // input value - 123 bytes of data
	input       i_start,
	  
	output [7:0] o_data [31:0], // output value of sha256
	output reg   o_ready
			
);
	
	wire [31:0] i_data_normed [47:0]; // three blocks of data
	
	wire [255:0] cc_state_out;
	
	genvar gv_i;

	generate
	
	  for (gv_i = 0; gv_i < 30; gv_i = gv_i + 1) begin : gen_1
		  assign i_data_normed[gv_i] = {i_data[gv_i*4+0], i_data[gv_i*4+1], i_data[gv_i*4+2], i_data[gv_i*4+3]};
	  end
	  
	  assign i_data_normed[30] = {i_data[120], i_data[121], i_data[122], 8'h80};
	  
	  for (gv_i = 31; gv_i < 47; gv_i = gv_i + 1) begin : gen_2
		  assign i_data_normed[gv_i] = 32'h00000000;
	  end
	  
	  assign i_data_normed[47] = {8'h00, 8'h00, 8'h03, 8'hd8}; // 0x03d8 = 984 bits = 123 bytes  
	  
	  for (gv_i = 0; gv_i < 32; gv_i = gv_i + 1) begin : gen_3
	  	assign o_data[(31-gv_i)] = cc_state_out[gv_i*8+7:gv_i*8];
	  end
	  	  	  
	endgenerate
	
	reg [255:0] cc_state_in;
	assign cc_init_state = 256'h5be0cd191f83d9ab9b05688c510e527fa54ff53a3c6ef372bb67ae856a09e667;
	
	reg [511:0] cc_data_in;
	
	reg [2:0] state;
	parameter ST_IDLE = 3'b000,
			  ST_T0   = 3'b001,
			  ST_T1   = 3'b011,
			  ST_T2   = 3'b010,
  			  ST_RD   = 3'b110;
	
	always @( posedge i_clk, negedge i_n_reset ) begin : r_rdata_1_fill_prcs 

		if ( i_n_reset == 1'b0 ) begin
		
			cc_state_in <= 256'd0;
			cc_data_in  <= 512'd0;
			
			state <= ST_IDLE;
			o_ready <= 1'b0;
		
		end
		else begin
		
			case (state)
		
				ST_IDLE : begin
				
					if ( i_start ) begin
					
						state <= ST_T0;											
						
					end
					
					o_ready <= 1'b0;
					
				end
				
				ST_T0 : begin
					
					cc_state_in <= 256'h5be0cd191f83d9ab9b05688c510e527fa54ff53a3c6ef372bb67ae856a09e667;	
					cc_data_in  <= { i_data_normed[15], i_data_normed[14], i_data_normed[13], i_data_normed[12], i_data_normed[11], i_data_normed[10], i_data_normed[9], 
									 i_data_normed[8], i_data_normed[7], i_data_normed[6], i_data_normed[5], i_data_normed[4], i_data_normed[3], i_data_normed[2],
									 i_data_normed[1], i_data_normed[0] };			

					state <= ST_T1;	
					
				end
				
				ST_T1 : begin
					
					cc_state_in <= cc_state_out;	
					cc_data_in  <= { i_data_normed[31], i_data_normed[30], i_data_normed[29], i_data_normed[28], i_data_normed[27], i_data_normed[26], i_data_normed[25], 
									 i_data_normed[24], i_data_normed[23], i_data_normed[22], i_data_normed[21], i_data_normed[20], i_data_normed[19], i_data_normed[18],
									 i_data_normed[17], i_data_normed[16] };
									 
					state <= ST_T2;
					
				end
				
				ST_T2 : begin
				
					cc_state_in <= cc_state_out;	
					cc_data_in  <= { i_data_normed[47], i_data_normed[46], i_data_normed[45], i_data_normed[44], i_data_normed[43], i_data_normed[42], i_data_normed[41], 
									 i_data_normed[40], i_data_normed[39], i_data_normed[38], i_data_normed[37], i_data_normed[36], i_data_normed[35], i_data_normed[34],
									 i_data_normed[33], i_data_normed[32] };
									 
					state <= ST_RD;
					
				end	
				
				ST_RD : begin
				
					state <= ST_IDLE;
				
					o_ready <= 1'b1;
					
				end						
			
				default : begin
					state <= ST_IDLE;
					o_ready <= 1'b0;				
				end
			
			endcase
		
		end

	end


	sha256_1r_comb_core_v2 sha256_1r_comb_core_v2_1 ( 

		.state_in	(cc_state_in),
		.data_in	(cc_data_in),
		.state_out	(cc_state_out)
		
	);
	
endmodule
//

