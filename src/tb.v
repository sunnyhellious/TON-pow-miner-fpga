`timescale 1ns / 1ps

module tb ( );

reg rst_n;
reg clk_50;
always #10 clk_50 = !clk_50;

wire rx, rx_new;
wire [7:0] rx_byte;
uart_rx_m #( .CLKS_PER_BIT(434) ) tb_uart_rx_m_0 (

    .i_n_Reset      (rst_n),
    .i_Clock        (clk_50),
    .i_Rx_Serial    (rx),
    .o_Rx_DV        (rx_new),
    .o_Rx_Byte      (rx_byte)

);

wire tx, tx_act;
reg tx_new;
reg [7:0] tx_byte;
uart_tx_m #( .CLKS_PER_BIT(434) ) tb_uart_tx_m_0 (

    .i_n_Reset      (rst_n), 
    .i_Clock        (clk_50),
    .i_Tx_DV        (tx_new),
    .i_Tx_Byte      (tx_byte),
    .o_Tx_Active    (tx_act),
    .o_Tx_Serial    (tx),
    .o_Tx_Done      () 

);  

top_level top_level_0 (

    .i_n_reset(rst_n),
    .i_clk(clk_50),      
    .i_cmd_uart_rx(tx),
    .o_cmd_uart_tx(rx),  
    .o_led()

);  

reg [7:0] t_d1;
reg [7:0] t_d2;
reg [7:0] t_op [3:0];
reg [7:0] t_flags;
reg [7:0] t_expire [3:0]; 
reg [7:0] t_myaddr [31:0]; 
reg [7:0] t_rdata [31:0];
reg [7:0] t_pseed [15:0];

reg [7:0] t_target [31:0];

reg t_enable;

wire [7:0] t_data [31:0];
wire t_found;

mcore #( .CORE_NUM(0), .CORES_QNT(1) ) mcore_1 (
  
	.i_n_reset(rst_n),
	.i_clk(clk_50),

	.i_d1(t_d1),
	.i_d2(t_d2),
	.i_op(t_op),
	.i_flags(t_flags),
	.i_expire(t_expire), 
	.i_myaddr(t_myaddr), 
	.i_rdata(t_myaddr),
	.i_pseed(t_pseed),

	.i_target(t_target),

	.i_enable(t_enable),

	.o_data(t_data),
	.o_found(t_found)

);

integer i;

initial begin                                                  

    $dumpfile("tb.vcd");
    $dumpvars(0,tb);

    clk_50  = 1'd0;
    rst_n   = 1'd0;
    tx_byte = 8'd0;
    tx_new  = 1'd0;
    
    t_d1 = 8'h00;
	t_d2 = 8'h00;
	
	t_op[0] = 8'h00;
	t_op[1]	= 8'h00;
	t_op[2]	= 8'h00;
	t_op[3]	= 8'h00;
	
	t_flags = 8'h0;
	
	t_expire[0] = 8'h00;
	t_expire[1]	= 8'h00;
	t_expire[2]	= 8'h00;
	t_expire[3]	= 8'h00;

	t_myaddr[0]		= 8'h00;
	t_myaddr[1]		= 8'h00;
	t_myaddr[2]		= 8'h00;
	t_myaddr[3]		= 8'h00;
	t_myaddr[4]		= 8'h00;
	t_myaddr[5]		= 8'h00;
	t_myaddr[6]		= 8'h00;
	t_myaddr[7]		= 8'h00;
	t_myaddr[8]		= 8'h00;
	t_myaddr[9]		= 8'h00;
	t_myaddr[10]	= 8'h00;
	t_myaddr[11]	= 8'h00;
	t_myaddr[12]	= 8'h00;
	t_myaddr[13]	= 8'h00;
	t_myaddr[14]	= 8'h00;
	t_myaddr[15]	= 8'h00;
	t_myaddr[16]	= 8'h00;
	t_myaddr[17]	= 8'h00;
	t_myaddr[18]	= 8'h00;
	t_myaddr[19]	= 8'h00;
	t_myaddr[20]	= 8'h00;
	t_myaddr[21]	= 8'h00;
	t_myaddr[22]	= 8'h00;
	t_myaddr[23]	= 8'h00;
	t_myaddr[24]	= 8'h00;
	t_myaddr[25]	= 8'h00;
	t_myaddr[26]	= 8'h00;
	t_myaddr[27]	= 8'h00;
	t_myaddr[28]	= 8'h00;
	t_myaddr[29]	= 8'h00;
	t_myaddr[30]	= 8'h00;
	t_myaddr[31]	= 8'h00;
	
	t_rdata[0]	= 8'hFF;
	t_rdata[1]	= 8'h00;
	t_rdata[2]	= 8'h00;
	t_rdata[3]	= 8'h00;
	t_rdata[4]	= 8'h00;
	t_rdata[5]	= 8'h00;
	t_rdata[6]	= 8'h00;
	t_rdata[7]	= 8'h00;
	t_rdata[8]	= 8'h00;
	t_rdata[9]	= 8'h00;
	t_rdata[10]	= 8'h00;
	t_rdata[11]	= 8'h00;
	t_rdata[12]	= 8'h00;
	t_rdata[13]	= 8'h00;
	t_rdata[14]	= 8'h00;
	t_rdata[15]	= 8'h00;
	t_rdata[16]	= 8'h00;
	t_rdata[17]	= 8'h00;
	t_rdata[18]	= 8'h00;
	t_rdata[19]	= 8'h00;
	t_rdata[20]	= 8'h00;
	t_rdata[21]	= 8'h00;
	t_rdata[22]	= 8'h00;
	t_rdata[23]	= 8'h00;
	t_rdata[24]	= 8'h00;
	t_rdata[25]	= 8'h00;
	t_rdata[26]	= 8'h00;
	t_rdata[27]	= 8'h00;
	t_rdata[28]	= 8'h00;
	t_rdata[29]	= 8'h00;
	t_rdata[30]	= 8'hFF;
	t_rdata[31]	= 8'hFF;
	
	t_pseed[0]	= 8'h00;
	t_pseed[1]	= 8'h00;
	t_pseed[2]	= 8'h00;
	t_pseed[3]	= 8'h00;
	t_pseed[4]	= 8'h00;
	t_pseed[5]	= 8'h00;
	t_pseed[6]	= 8'h00;
	t_pseed[7]	= 8'h00;
	t_pseed[8]	= 8'h00;
	t_pseed[9]	= 8'h00;
	t_pseed[10]	= 8'h00;
	t_pseed[11]	= 8'h00;
	t_pseed[12]	= 8'h00;
	t_pseed[13]	= 8'h00;
	t_pseed[14]	= 8'h00;
	t_pseed[15]	= 8'h00;
	
	t_enable = 1'b0;
	
	t_target[0]		= 8'h00;
	t_target[1]		= 8'h00;
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
	
	t_enable = 1'd1;

	@(posedge t_found);
	
	t_enable = 1'd0;

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

    $display("testbench penetrated"); 
    $display("H[0] = %h", { t_data[3], t_data[2], t_data[1], t_data[0] });
	$display("H[1] = %h", { t_data[7], t_data[6], t_data[5], t_data[4] });
	$display("H[2] = %h", { t_data[11], t_data[10], t_data[9], t_data[8] });
	$display("H[3] = %h", { t_data[15], t_data[14], t_data[13], t_data[12] });
	$display("H[4] = %h", { t_data[19], t_data[18], t_data[17], t_data[16] });
	$display("H[5] = %h", { t_data[23], t_data[22], t_data[21], t_data[20] });
	$display("H[6] = %h", { t_data[27], t_data[26], t_data[25], t_data[24] });
	$display("H[7] = %h", { t_data[31], t_data[30], t_data[29], t_data[28] });

    $finish;
                  
end 




endmodule
 
