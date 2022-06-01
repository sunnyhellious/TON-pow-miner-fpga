`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: MelnoDrew
// 
// Create Date: 08.05.2022 18:06:54
// Design Name: 
// Module Name: top_level
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module top_level
(
    input   i_n_reset,      // asynchronous negative reset 
    input   i_clk,          // input system clock domain
    input   i_cmd_uart_rx,  // command uart input RX 
    output  o_cmd_uart_tx,  // command uart output TX
    
    output  o_led           // led indication 
);


wire [7:0] packet_0 [63:0];
wire [5:0] len_0;
wire new_0;
 
cmd_packets_ctrl cmd_packets_ctrl_0 (
  
	.i_n_reset(i_n_reset),
	.i_clk(i_clk),
    
	.i_uart_rx(i_cmd_uart_rx),
	.o_uart_tx(o_cmd_uart_tx),
    
	.o_rx_packet(packet_0),
    .o_rx_packet_new(new_0),
    .o_rx_packet_len(len_0),
    .o_rx_busy(),	
    
    .i_tx_packet(packet_0),
    .i_tx_packet_new(new_0), 	
    .i_tx_packet_len(len_0),
    .o_tx_busy()
        
);

reg [32:0] r_led;
always @(posedge i_clk, negedge i_n_reset) begin

    if (i_n_reset == 1'b0) begin // asynchronous negative reset condition 
        r_led <= 33'b0;                    
    end 
    else begin 
        r_led <= r_led == 33'd100000000 ? 32'b0 : r_led + 32'd1;  
    end

end

assign o_led = r_led >= 50000000 ? 1'b1 : 1'b0; 
    
endmodule
