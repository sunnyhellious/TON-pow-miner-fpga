`timescale 1ns / 1ps

module tb ( );

reg rst_n;
reg clk_50;
always #10 clk_50 = !clk_50;

reg [7:0] t_d1;
reg [7:0] t_d2;
reg [7:0] t_op [3:0];
reg [7:0] t_flags;
reg [7:0] t_expire  [3:0]; 
reg [7:0] t_myaddr  [31:0]; 
reg [7:0] t_rdata_1 [31:0];
reg [7:0] t_pseed   [15:0];
reg [7:0] t_rdata_2 [31:0];

reg [7:0] t_target [31:0];

reg smc_1_start;
reg smc_1_stop;

wire [7:0] smc_1_task_rdata_1 [31:0];
wire [7:0] smc_1_task_rdata_2 [31:0];
wire smc_1_found;
wire smc_1_bf;

wire [255:0] smc_1_sha256;

wire [15:0] smc_1_tasks_srs_acks_qnt;

system_mcores #( .CORES_QNT(1) ) system_mcores_1 (

	.i_n_reset(rst_n),
	.i_clk(clk_50),
	
	.i_start(smc_1_start),
	.i_stop(smc_1_stop),

	.i_d1(t_d1),
	.i_d2(t_d2),
	.i_op(t_op),
	.i_flags(t_flags),
	.i_expire(t_expire), 
	.i_myaddr(t_myaddr), 
	.i_rdata_1(t_rdata_1),
	.i_pseed(t_pseed),
	.i_rdata_2(t_rdata_2),

	.i_target(t_target),
	
	.o_tasks_srs_acks_qnt(smc_1_tasks_srs_acks_qnt),
	.o_task_rdata_1(smc_1_task_rdata_1),
	.o_task_rdata_2(smc_1_task_rdata_2),
	.o_found(smc_1_found),
	.o_sha256(smc_1_sha256),
	
	.o_bf(smc_1_bf)
  
);

integer i;

parameter FILL = 8'hFF;

initial begin                                                  

    $dumpfile("tb.vcd");
	$dumpvars(0,tb);

    clk_50  = 1'd0;
    rst_n   = 1'd0;
    
    // tx_byte = 8'd0;
    // tx_new  = 1'd0;
    
    t_d1 = 8'h11;
	t_d2 = 8'h22;
	t_op[0] = 8'h33;
	t_op[1]	= 8'h44;
	t_op[2]	= 8'h55;
	t_op[3]	= 8'h66;
	t_flags = 8'h77;
	t_expire[0] = 8'h88;
	t_expire[1]	= 8'h99;
	t_expire[2]	= 8'hAA;
	t_expire[3]	= 8'hBB;
	t_myaddr[0]		= 8'hCC;
	t_myaddr[1]		= 8'hDD;
	t_myaddr[2]		= 8'hEE;
	t_myaddr[3]		= 8'hFF;
	t_myaddr[4]		= 8'h11;
	t_myaddr[5]		= 8'h22;
	t_myaddr[6]		= 8'h33;
	t_myaddr[7]		= 8'h44;
	t_myaddr[8]		= 8'h55;
	t_myaddr[9]		= 8'h66;
	t_myaddr[10]	= 8'h77;
	t_myaddr[11]	= 8'h88;
	t_myaddr[12]	= 8'h99;
	t_myaddr[13]	= 8'hAA;
	t_myaddr[14]	= 8'hBB;
	t_myaddr[15]	= 8'hCC;
	t_myaddr[16]	= 8'hDD;
	t_myaddr[17]	= 8'hEE;
	t_myaddr[18]	= 8'hFF;
	t_myaddr[19]	= 8'h11;
	t_myaddr[20]	= 8'h22;
	t_myaddr[21]	= 8'h33;
	t_myaddr[22]	= 8'h44;
	t_myaddr[23]	= 8'h55;
	t_myaddr[24]	= 8'h66;
	t_myaddr[25]	= 8'h77;
	t_myaddr[26]	= 8'h88;
	t_myaddr[27]	= 8'h99;
	t_myaddr[28]	= 8'hAA;
	t_myaddr[29]	= 8'hBB;
	t_myaddr[30]	= 8'hCC;
	t_myaddr[31]	= 8'hDD;
	t_rdata_1[0]	= 8'hEE;
	t_rdata_1[1]	= 8'hFF;
	t_rdata_1[2]	= 8'h11;
	t_rdata_1[3]	= 8'h22;
	t_rdata_1[4]	= 8'h33;
	t_rdata_1[5]	= 8'h44;
	t_rdata_1[6]	= 8'h55;
	t_rdata_1[7]	= 8'h66;
	t_rdata_1[8]	= 8'h77;
	t_rdata_1[9]	= 8'h88;
	t_rdata_1[10]	= 8'h99;
	t_rdata_1[11]	= 8'hAA;
	t_rdata_1[12]	= 8'hBB;
	t_rdata_1[13]	= 8'hCC;
	t_rdata_1[14]	= 8'hDD;
	t_rdata_1[15]	= 8'hEE;
	t_rdata_1[16]	= 8'hFF;
	t_rdata_1[17]	= 8'h11;
	t_rdata_1[18]	= 8'h22;
	t_rdata_1[19]	= 8'h33;
	t_rdata_1[20]	= 8'h44;
	t_rdata_1[21]	= 8'h55;
	t_rdata_1[22]	= 8'h66;
	t_rdata_1[23]	= 8'h77;
	t_rdata_1[24]	= 8'h88;
	t_rdata_1[25]	= 8'h99;
	t_rdata_1[26]	= 8'hAA;
	t_rdata_1[27]	= 8'hBB;
	t_rdata_1[28]	= 8'hCC;
	t_rdata_1[29]	= 8'hDD;
	t_rdata_1[30]	= 8'hEE;
	t_rdata_1[31]	= 8'hFF;
	t_pseed[0]	= 8'h11;
	t_pseed[1]	= 8'h22;
	t_pseed[2]	= 8'h33;
	t_pseed[3]	= 8'h44;
	t_pseed[4]	= 8'h55;
	t_pseed[5]	= 8'h66;
	t_pseed[6]	= 8'h77;
	t_pseed[7]	= 8'h88;
	t_pseed[8]	= 8'h99;
	t_pseed[9]	= 8'hAA;
	t_pseed[10]	= 8'hBB;
	t_pseed[11]	= 8'hCC;
	t_pseed[12]	= 8'hDD;
	t_pseed[13]	= 8'hEE;
	t_pseed[14]	= 8'hFF;
	t_pseed[15]	= 8'h11;
	t_rdata_2[0]	= 8'h22;
	t_rdata_2[1]	= 8'h33;
	t_rdata_2[2]	= 8'h44;
	t_rdata_2[3]	= 8'h55;
	t_rdata_2[4]	= 8'h66;
	t_rdata_2[5]	= 8'h77;
	t_rdata_2[6]	= 8'h88;
	t_rdata_2[7]	= 8'h99;
	t_rdata_2[8]	= 8'hAA;
	t_rdata_2[9]	= 8'hBB;
	t_rdata_2[10]	= 8'hCC;
	t_rdata_2[11]	= 8'hDD;
	t_rdata_2[12]	= 8'hEE;
	t_rdata_2[13]	= 8'hFF;
	t_rdata_2[14]	= 8'h11;
	t_rdata_2[15]	= 8'h22;
	t_rdata_2[16]	= 8'h33;
	t_rdata_2[17]	= 8'h44;
	t_rdata_2[18]	= 8'h55;
	t_rdata_2[19]	= 8'h66;
	t_rdata_2[20]	= 8'h77;
	t_rdata_2[21]	= 8'h88;
	t_rdata_2[22]	= 8'h99;
	t_rdata_2[23]	= 8'hAA;
	t_rdata_2[24]	= 8'hBB;
	t_rdata_2[25]	= 8'hCC;
	t_rdata_2[26]	= 8'hDD;
	t_rdata_2[27]	= 8'hEE;
	t_rdata_2[28]	= 8'hFF;
	t_rdata_2[29]	= 8'h11;
	t_rdata_2[30]	= 8'h22;
	t_rdata_2[31]	= 8'h33;
			
	smc_1_start = 1'b0;
	smc_1_stop = 1'b0;
	
	t_target[0]		= 8'h00;
	t_target[1]		= 8'hFF;
	t_target[2]		= 8'hFF;
	t_target[3]		= 8'hFF;
	t_target[4]		= 8'hFF;
	t_target[5]		= 8'hFF;
	t_target[6]		= 8'hFF;
	t_target[7]		= 8'hFF;
	t_target[8]		= 8'hFF;
	t_target[9]		= 8'hFF;
	t_target[10]	= 8'hFF;
	t_target[11]	= 8'hFF;
	t_target[12]	= 8'hFF;
	t_target[13]	= 8'hFF;
	t_target[14]	= 8'hFF;
	t_target[15]	= 8'hFF;
	t_target[16]	= 8'hFF;
	t_target[17]	= 8'hFF;
	t_target[18]	= 8'hFF;
	t_target[19]	= 8'hFF;
	t_target[20]	= 8'hFF;
	t_target[21]	= 8'hFF;
	t_target[22]	= 8'hFF;
	t_target[23]	= 8'hFF;
	t_target[24]	= 8'hFF;
	t_target[25]	= 8'hFF;
	t_target[26]	= 8'hFF;
	t_target[27]	= 8'hFF;
	t_target[28]	= 8'hFF;
	t_target[29]	= 8'hFF;
	t_target[30]	= 8'hFF;
	t_target[31]	= 8'hFF;
    
    #1000;

    rst_n   = 1'd1;

	#1000;
	
	smc_1_start = 1'd1;

	@(posedge smc_1_found);
	
	smc_1_start = 1'd0;
	
	// smc_1_start = 1'd0;

	/*
    // send four zero bytes 
    @(posedge clk_50); tx_byte = 8'h00; #20; tx_new = 1; #20; tx_new = 0; #20; @(negedge tx_act);
    @(posedge clk_50); tx_byte = 8'h00; #20; tx_new = 1; #20; tx_new = 0; #20; @(negedge tx_act);
    @(posedge clk_50); tx_byte = 8'h00; #20; tx_new = 1; #20; tx_new = 0; #20; @(negedge tx_act);
    @(posedge clk_50); tx_byte = 8'h00; #20; tx_new = 1; #20; tx_new = 0; #20; @(negedge tx_act);
	
	// send crc32 for four zero bytes
	// 0x2144df1c
	@(posedge clk_50); tx_byte = 8'h1c; #20; tx_new = 1; #20; tx_new = 0; #20; @(negedge tx_act);
    @(posedge clk_50); tx_byte = 8'hdf; #20; tx_new = 1; #20; tx_new = 0; #20; @(negedge tx_act);
    @(posedge clk_50); tx_byte = 8'h44; #20; tx_new = 1; #20; tx_new = 0; #20; @(negedge tx_act);
    @(posedge clk_50); tx_byte = 8'h21; #20; tx_new = 1; #20; tx_new = 0; #20; @(negedge tx_act);

	// wait some not determined quantity of time
    #(1000*1000);
    */
    
    /*
    $display("Data:"); 
	for(i=0; i < 123; i=i+1) begin
		 $display("%h", test_data[i]);
	end
	*/

    $display ("testbench penetrated"); 
    $display ("H = %h", smc_1_sha256 );
    $display ("QNT = %d", smc_1_tasks_srs_acks_qnt);
    $display ("%0t ns", $time);
    
    // #1000;

    $finish;
                  
end 







endmodule
 
