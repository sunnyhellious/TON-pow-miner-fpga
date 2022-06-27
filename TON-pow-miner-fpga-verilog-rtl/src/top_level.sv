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
    input   i_clk_50,          // input system clock domain
    input   i_cmd_uart_rx,  // command uart input RX 
    output  o_cmd_uart_tx,  // command uart output TX
    
    output  o_led           // led indication 
);

wire i_clk;

clk_wiz_0 clk_wiz_0_ (

    .clk_out1(i_clk),
    .reset(~i_n_reset),
    .clk_in1(i_clk_50)
    
);


wire [7:0] packet_rx [63:0];
wire [5:0] len_rx;
wire new_rx;

reg [7:0] packet_tx [63:0];
reg [5:0] len_tx;
reg new_tx;

wire tx_busy;

cmd_packets_ctrl cmd_packets_ctrl_0 (
  
	.i_n_reset(i_n_reset),
	.i_clk(i_clk),
    
	.i_uart_rx(i_cmd_uart_rx),
	.o_uart_tx(o_cmd_uart_tx),
    
	.o_rx_packet(packet_rx),
    .o_rx_packet_new(new_rx),
    .o_rx_packet_len(len_rx),
    .o_rx_busy(),	
    
    .i_tx_packet(packet_tx),
    .i_tx_packet_new(new_tx), 	
    .i_tx_packet_len(len_tx),
    .o_tx_busy(tx_busy)
        
);

reg [7:0] t_d1;
reg [7:0] t_d2;
reg [7:0] t_op [3:0];
reg [7:0] t_flags;
reg [7:0] t_expire [3:0]; 
reg [7:0] t_myaddr [31:0];
reg [7:0] t_rdata_1 [31:0];
reg [7:0] t_pseed [15:0];
reg [7:0] t_rdata_2 [31:0];

reg [7:0] t_target [31:0];

reg t_start;
reg t_stop;

// wire t_rf;

// wire [7:0] t_data [31:0];
wire [255:0] sha256;
reg [255:0] r_sha256;


wire t_found;

wire [15:0] tasks_srs_acks_qnt;

wire [7:0] task_rdata_1 [31:0];
wire [7:0] task_rdata_2 [31:0];

reg [7:0] r_task_rdata_1 [31:0];
reg [7:0] r_task_rdata_2 [31:0];

reg found;

localparam [31:0] COREQ_QNT = 32'd45;

system_mcores #(.CORES_QNT(COREQ_QNT)) system_mcores_1 (

    .i_n_reset(i_n_reset),
	.i_clk(i_clk),

    .i_start(t_start),
	.i_stop(t_stop),

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
	
	.o_tasks_srs_acks_qnt(tasks_srs_acks_qnt),
	.o_task_rdata_1(task_rdata_1),
	.o_task_rdata_2(task_rdata_2),
	.o_found(t_found),
	.o_sha256(sha256),
	
	.o_bf() // busy flag
	
);


reg state;

reg [31:0] tcnt;

reg [15:0] tasks_srs_acks_qnt_OLD;

always @(posedge i_clk, negedge i_n_reset) begin 
    
    if (i_n_reset == 1'b0) begin // asynchronous negative reset condition 
        // wire [7:0] packet_rx [63:0];
        // wire [5:0] len_rx;
        // wire new_rx;
        
        r_sha256 <= 256'd0;
        
        state <= 1'b0;
        tcnt <= 32'd0;    
        tasks_srs_acks_qnt_OLD <= 16'h00;
        found <= 1'b0;   
        
        packet_tx[0]		<= 8'd0; // of course this sh*t is quiet dump, but currently this project is quiet lasy
		packet_tx[1]		<= 8'd0;
		packet_tx[2]		<= 8'd0;
		packet_tx[3]		<= 8'd0;
        packet_tx[4]		<= 8'd0;
		packet_tx[5]		<= 8'd0;
		packet_tx[6]		<= 8'd0;
		packet_tx[7]		<= 8'd0;
		packet_tx[8]		<= 8'd0;
		packet_tx[9]		<= 8'd0;
		packet_tx[10]		<= 8'd0;
		packet_tx[11]		<= 8'd0;
        packet_tx[12]		<= 8'd0;
		packet_tx[13]		<= 8'd0;
		packet_tx[14]		<= 8'd0;
		packet_tx[15]		<= 8'd0;
		packet_tx[16]		<= 8'd0;
		packet_tx[17]		<= 8'd0;
		packet_tx[18]		<= 8'd0;
		packet_tx[19]		<= 8'd0;
        packet_tx[20]		<= 8'd0;
		packet_tx[21]		<= 8'd0;
		packet_tx[22]		<= 8'd0;
		packet_tx[23]		<= 8'd0;
		packet_tx[24]		<= 8'd0;
		packet_tx[25]		<= 8'd0;
		packet_tx[26]		<= 8'd0;
		packet_tx[27]		<= 8'd0;
        packet_tx[28]		<= 8'd0;
		packet_tx[29]		<= 8'd0;
		packet_tx[30]		<= 8'd0;
		packet_tx[31]		<= 8'd0;
		packet_tx[32]		<= 8'd0;
		packet_tx[33]		<= 8'd0;
		packet_tx[34]		<= 8'd0;
		packet_tx[35]		<= 8'd0;
        packet_tx[36]		<= 8'd0;
		packet_tx[37]		<= 8'd0;
		packet_tx[38]		<= 8'd0;
		packet_tx[39]		<= 8'd0;
		packet_tx[40]		<= 8'd0;
		packet_tx[41]		<= 8'd0;
		packet_tx[42]		<= 8'd0;
        packet_tx[43]		<= 8'd0;
		packet_tx[44]		<= 8'd0;
		packet_tx[45]		<= 8'd0;
		packet_tx[46]		<= 8'd0;
		packet_tx[47]		<= 8'd0;
		packet_tx[48]		<= 8'd0;
		packet_tx[49]		<= 8'd0;
		packet_tx[50]		<= 8'd0;
        packet_tx[51]		<= 8'd0;
		packet_tx[52]		<= 8'd0;
		packet_tx[53]		<= 8'd0;
		packet_tx[54]		<= 8'd0;
		packet_tx[55]		<= 8'd0;
		packet_tx[56]		<= 8'd0;
		packet_tx[57]		<= 8'd0;
		packet_tx[58]		<= 8'd0;
        packet_tx[59]		<= 8'd0;
		packet_tx[60]		<= 8'd0;
		packet_tx[61]		<= 8'd0;
		packet_tx[62]		<= 8'd0;
		packet_tx[63]		<= 8'd0;
		
		r_task_rdata_1[0] <= 8'h00; 
        r_task_rdata_1[1] <= 8'h00; 
        r_task_rdata_1[2] <= 8'h00; 
        r_task_rdata_1[3] <= 8'h00; 
        r_task_rdata_1[4] <= 8'h00; 
        r_task_rdata_1[5] <= 8'h00; 
        r_task_rdata_1[6] <= 8'h00; 
        r_task_rdata_1[7] <= 8'h00; 
        r_task_rdata_1[8] <= 8'h00; 
        r_task_rdata_1[9] <= 8'h00; 
        r_task_rdata_1[10] <= 8'h00; 
        r_task_rdata_1[11] <= 8'h00; 
        r_task_rdata_1[12] <= 8'h00; 
        r_task_rdata_1[13] <= 8'h00; 
        r_task_rdata_1[14] <= 8'h00; 
        r_task_rdata_1[15] <= 8'h00; 
        r_task_rdata_1[16] <= 8'h00; 
        r_task_rdata_1[17] <= 8'h00;
        r_task_rdata_1[18] <= 8'h00;  
        r_task_rdata_1[19] <= 8'h00; 
        r_task_rdata_1[20] <= 8'h00; 
        r_task_rdata_1[21] <= 8'h00; 
        r_task_rdata_1[22] <= 8'h00; 
        r_task_rdata_1[23] <= 8'h00; 
        r_task_rdata_1[24] <= 8'h00; 
        r_task_rdata_1[25] <= 8'h00; 
        r_task_rdata_1[26] <= 8'h00; 
        r_task_rdata_1[27] <= 8'h00; 
        r_task_rdata_1[28] <= 8'h00; 
        r_task_rdata_1[29] <= 8'h00; 
        r_task_rdata_1[30] <= 8'h00; 
        r_task_rdata_1[31] <= 8'h00;
        
        r_task_rdata_2[0] <= 8'h00; 
        r_task_rdata_2[1] <= 8'h00; 
        r_task_rdata_2[2] <= 8'h00; 
        r_task_rdata_2[3] <= 8'h00; 
        r_task_rdata_2[4] <= 8'h00; 
        r_task_rdata_2[5] <= 8'h00; 
        r_task_rdata_2[6] <= 8'h00; 
        r_task_rdata_2[7] <= 8'h00; 
        r_task_rdata_2[8] <= 8'h00; 
        r_task_rdata_2[9] <= 8'h00; 
        r_task_rdata_2[10] <= 8'h00; 
        r_task_rdata_2[11] <= 8'h00; 
        r_task_rdata_2[12] <= 8'h00; 
        r_task_rdata_2[13] <= 8'h00; 
        r_task_rdata_2[14] <= 8'h00; 
        r_task_rdata_2[15] <= 8'h00; 
        r_task_rdata_2[16] <= 8'h00; 
        r_task_rdata_2[17] <= 8'h00; 
        r_task_rdata_2[18] <= 8'h00; 
        r_task_rdata_2[19] <= 8'h00; 
        r_task_rdata_2[20] <= 8'h00; 
        r_task_rdata_2[21] <= 8'h00; 
        r_task_rdata_2[22] <= 8'h00; 
        r_task_rdata_2[23] <= 8'h00; 
        r_task_rdata_2[24] <= 8'h00; 
        r_task_rdata_2[25] <= 8'h00; 
        r_task_rdata_2[26] <= 8'h00; 
        r_task_rdata_2[27] <= 8'h00; 
        r_task_rdata_2[28] <= 8'h00; 
        r_task_rdata_2[29] <= 8'h00; 
        r_task_rdata_2[30] <= 8'h00; 
        r_task_rdata_2[31] <= 8'h00;
		
        len_tx <= 6'd0;
        new_tx <= 1'b0;   
        
        t_start <= 1'b0;
        
        t_stop <= 1'b0;
                         
    end 
    else begin 
    
        tasks_srs_acks_qnt_OLD <= tasks_srs_acks_qnt;
    
        case(state)
                            
            1'b0 : begin
            
                t_stop <= 1'b0;
            
                tcnt <= 32'd0;   
            
                new_tx <= 1'b0;
                
                if ( new_rx && (packet_rx[0] == 8'h01) && ( len_rx == ( 6'd44 + 6'd4 ) ) ) begin
                                                        
                    t_d1 <= packet_rx[1];
                    t_d2 <= packet_rx[2];
                    
                    t_op[0] <= packet_rx[3];
                    t_op[1] <= packet_rx[4];
                    t_op[2] <= packet_rx[5];
                    t_op[3] <= packet_rx[6];
                    
                    t_flags <= packet_rx[7];
                    
                    t_expire[0] <= packet_rx[8];
                    t_expire[1] <= packet_rx[9];
                    t_expire[2] <= packet_rx[10];
                    t_expire[3] <= packet_rx[11];
                    
                    t_myaddr[0] <= packet_rx[12];
                    t_myaddr[1] <= packet_rx[13];
                    t_myaddr[2] <= packet_rx[14];
                    t_myaddr[3] <= packet_rx[15];
                    t_myaddr[4] <= packet_rx[16];
                    t_myaddr[5] <= packet_rx[17];
                    t_myaddr[6] <= packet_rx[18];
                    t_myaddr[7] <= packet_rx[19];
                    t_myaddr[8] <= packet_rx[20];
                    t_myaddr[9] <= packet_rx[21];
                    t_myaddr[10] <= packet_rx[22];
                    t_myaddr[11] <= packet_rx[23];
                    t_myaddr[12] <= packet_rx[24];
                    t_myaddr[13] <= packet_rx[25];
                    t_myaddr[14] <= packet_rx[26];
                    t_myaddr[15] <= packet_rx[27];
                    t_myaddr[16] <= packet_rx[28];
                    t_myaddr[17] <= packet_rx[29];
                    t_myaddr[18] <= packet_rx[30];
                    t_myaddr[19] <= packet_rx[31];
                    t_myaddr[20] <= packet_rx[32];
                    t_myaddr[21] <= packet_rx[33];
                    t_myaddr[22] <= packet_rx[34];
                    t_myaddr[23] <= packet_rx[35];
                    t_myaddr[24] <= packet_rx[36];
                    t_myaddr[25] <= packet_rx[37];
                    t_myaddr[26] <= packet_rx[38];
                    t_myaddr[27] <= packet_rx[39];
                    t_myaddr[28] <= packet_rx[40];
                    t_myaddr[29] <= packet_rx[41];
                    t_myaddr[30] <= packet_rx[42];
                    t_myaddr[31] <= packet_rx[43];
                    
                    packet_tx[0] <= 8'h81;
                    len_tx <= 6'd1 + 6'd4;
                    new_tx <= 1'b1;
                    
                    
                end
                else if ( new_rx && (packet_rx[0] == 8'h02) && ( len_rx == ( 6'd49 + 6'd4 ) ) ) begin
                                                        
                    t_rdata_1[0] <= packet_rx[1];
                    t_rdata_1[1] <= packet_rx[2];
                    t_rdata_1[2] <= packet_rx[3];
                    t_rdata_1[3] <= packet_rx[4];
                    t_rdata_1[4] <= packet_rx[5];
                    t_rdata_1[5] <= packet_rx[6];
                    t_rdata_1[6] <= packet_rx[7];
                    t_rdata_1[7] <= packet_rx[8];
                    t_rdata_1[8] <= packet_rx[9];
                    t_rdata_1[9] <= packet_rx[10];
                    t_rdata_1[10] <= packet_rx[11];
                    t_rdata_1[11] <= packet_rx[12];
                    t_rdata_1[12] <= packet_rx[13];
                    t_rdata_1[13] <= packet_rx[14];
                    t_rdata_1[14] <= packet_rx[15];
                    t_rdata_1[15] <= packet_rx[16];
                    t_rdata_1[16] <= packet_rx[17];
                    t_rdata_1[17] <= packet_rx[18];
                    t_rdata_1[18] <= packet_rx[19];
                    t_rdata_1[19] <= packet_rx[20];
                    t_rdata_1[20] <= packet_rx[21];
                    t_rdata_1[21] <= packet_rx[22];
                    t_rdata_1[22] <= packet_rx[23];
                    t_rdata_1[23] <= packet_rx[24];
                    t_rdata_1[24] <= packet_rx[25];
                    t_rdata_1[25] <= packet_rx[26];
                    t_rdata_1[26] <= packet_rx[27];
                    t_rdata_1[27] <= packet_rx[28];
                    t_rdata_1[28] <= packet_rx[29];
                    t_rdata_1[29] <= packet_rx[30];
                    t_rdata_1[30] <= packet_rx[31];
                    t_rdata_1[31] <= packet_rx[32]; 
                    
                    t_pseed[0] <= packet_rx[33];
                    t_pseed[1] <= packet_rx[34];
                    t_pseed[2] <= packet_rx[35];
                    t_pseed[3] <= packet_rx[36];
                    t_pseed[4] <= packet_rx[37];
                    t_pseed[5] <= packet_rx[38];
                    t_pseed[6] <= packet_rx[39];
                    t_pseed[7] <= packet_rx[40];
                    t_pseed[8] <= packet_rx[41];
                    t_pseed[9] <= packet_rx[42];
                    t_pseed[10] <= packet_rx[43];
                    t_pseed[11] <= packet_rx[44];
                    t_pseed[12] <= packet_rx[45];
                    t_pseed[13] <= packet_rx[46];
                    t_pseed[14] <= packet_rx[47];
                    t_pseed[15] <= packet_rx[48];
                    
                    packet_tx[0] <= 8'h82;
                    len_tx <= 6'd1 + 6'd4;
                    new_tx <= 1'b1;
                    
               end     
               else if ( new_rx && (packet_rx[0] == 8'h03) && ( len_rx == ( 6'd33 + 6'd4 ) ) ) begin
                                                        
                    t_rdata_2[0] <= packet_rx[1];
                    t_rdata_2[1] <= packet_rx[2];
                    t_rdata_2[2] <= packet_rx[3];
                    t_rdata_2[3] <= packet_rx[4];
                    t_rdata_2[4] <= packet_rx[5];
                    t_rdata_2[5] <= packet_rx[6];
                    t_rdata_2[6] <= packet_rx[7];
                    t_rdata_2[7] <= packet_rx[8];
                    t_rdata_2[8] <= packet_rx[9];
                    t_rdata_2[9] <= packet_rx[10];
                    t_rdata_2[10] <= packet_rx[11];
                    t_rdata_2[11] <= packet_rx[12];
                    t_rdata_2[12] <= packet_rx[13];
                    t_rdata_2[13] <= packet_rx[14];
                    t_rdata_2[14] <= packet_rx[15];
                    t_rdata_2[15] <= packet_rx[16];
                    t_rdata_2[16] <= packet_rx[17];
                    t_rdata_2[17] <= packet_rx[18];
                    t_rdata_2[18] <= packet_rx[19];
                    t_rdata_2[19] <= packet_rx[20];
                    t_rdata_2[20] <= packet_rx[21];
                    t_rdata_2[21] <= packet_rx[22];
                    t_rdata_2[22] <= packet_rx[23];
                    t_rdata_2[23] <= packet_rx[24];
                    t_rdata_2[24] <= packet_rx[25];
                    t_rdata_2[25] <= packet_rx[26];
                    t_rdata_2[26] <= packet_rx[27];
                    t_rdata_2[27] <= packet_rx[28];
                    t_rdata_2[28] <= packet_rx[29];
                    t_rdata_2[29] <= packet_rx[30];
                    t_rdata_2[30] <= packet_rx[31];
                    t_rdata_2[31] <= packet_rx[32]; 
                    
                    packet_tx[0] <= 8'h83;
                    len_tx <= 6'd1 + 6'd4;
                    new_tx <= 1'b1;
                                        
               end      
               else if ( new_rx && (packet_rx[0] == 8'h04) && ( len_rx == ( 6'd33 + 6'd4 ) ) ) begin
                                                        
                    t_target[0] <= packet_rx[1];
                    t_target[1] <= packet_rx[2];
                    t_target[2] <= packet_rx[3];
                    t_target[3] <= packet_rx[4];
                    t_target[4] <= packet_rx[5];
                    t_target[5] <= packet_rx[6];
                    t_target[6] <= packet_rx[7];
                    t_target[7] <= packet_rx[8];
                    t_target[8] <= packet_rx[9];
                    t_target[9] <= packet_rx[10];
                    t_target[10] <= packet_rx[11];
                    t_target[11] <= packet_rx[12];
                    t_target[12] <= packet_rx[13];
                    t_target[13] <= packet_rx[14];
                    t_target[14] <= packet_rx[15];
                    t_target[15] <= packet_rx[16];
                    t_target[16] <= packet_rx[17];
                    t_target[17] <= packet_rx[18];
                    t_target[18] <= packet_rx[19];
                    t_target[19] <= packet_rx[20];
                    t_target[20] <= packet_rx[21];
                    t_target[21] <= packet_rx[22];
                    t_target[22] <= packet_rx[23];
                    t_target[23] <= packet_rx[24];
                    t_target[24] <= packet_rx[25];
                    t_target[25] <= packet_rx[26];
                    t_target[26] <= packet_rx[27];
                    t_target[27] <= packet_rx[28];
                    t_target[28] <= packet_rx[29];
                    t_target[29] <= packet_rx[30];
                    t_target[30] <= packet_rx[31];
                    t_target[31] <= packet_rx[32]; 
                    
                    packet_tx[0] <= 8'h84;
                    len_tx <= 6'd1 + 6'd4;
                    new_tx <= 1'b1;
                                        
               end      
               else if ( new_rx && (packet_rx[0] == 8'h05) && ( len_rx == ( 6'd1 + 6'd4 ) ) ) begin
                    
                    state <= 1'b1;
                    
                    t_start <= 1'b1;
                    
                    found <= 1'b0;
                    
                    packet_tx[0] <= 8'h85;
                    len_tx <= 6'd1 + 6'd4;
                    new_tx <= 1'b1;
               
               end
               else begin
                     new_tx <= 1'b0;
               end 
               
                 
            end
        
            1'b1 : begin
                
                t_start <= 1'b0;
                
                if ( t_found == 1'b1 ) begin
                    
                    found <= 1'b1;
                                                    
                    r_task_rdata_1[0] <= task_rdata_1[0]; 
                    r_task_rdata_1[1] <= task_rdata_1[1]; 
                    r_task_rdata_1[2] <= task_rdata_1[2]; 
                    r_task_rdata_1[3] <= task_rdata_1[3]; 
                    r_task_rdata_1[4] <= task_rdata_1[4]; 
                    r_task_rdata_1[5] <= task_rdata_1[5]; 
                    r_task_rdata_1[6] <= task_rdata_1[6]; 
                    r_task_rdata_1[7] <= task_rdata_1[7]; 
                    r_task_rdata_1[8] <= task_rdata_1[8]; 
                    r_task_rdata_1[9] <= task_rdata_1[9]; 
                    r_task_rdata_1[10] <= task_rdata_1[10]; 
                    r_task_rdata_1[11] <= task_rdata_1[11]; 
                    r_task_rdata_1[12] <= task_rdata_1[12]; 
                    r_task_rdata_1[13] <= task_rdata_1[13]; 
                    r_task_rdata_1[14] <= task_rdata_1[14]; 
                    r_task_rdata_1[15] <= task_rdata_1[15]; 
                    r_task_rdata_1[16] <= task_rdata_1[16]; 
                    r_task_rdata_1[17] <= task_rdata_1[17];
                    r_task_rdata_1[18] <= task_rdata_1[18];  
                    r_task_rdata_1[19] <= task_rdata_1[19]; 
                    r_task_rdata_1[20] <= task_rdata_1[20]; 
                    r_task_rdata_1[21] <= task_rdata_1[21]; 
                    r_task_rdata_1[22] <= task_rdata_1[22]; 
                    r_task_rdata_1[23] <= task_rdata_1[23]; 
                    r_task_rdata_1[24] <= task_rdata_1[24]; 
                    r_task_rdata_1[25] <= task_rdata_1[25]; 
                    r_task_rdata_1[26] <= task_rdata_1[26]; 
                    r_task_rdata_1[27] <= task_rdata_1[27]; 
                    r_task_rdata_1[28] <= task_rdata_1[28]; 
                    r_task_rdata_1[29] <= task_rdata_1[29]; 
                    r_task_rdata_1[30] <= task_rdata_1[30]; 
                    r_task_rdata_1[31] <= task_rdata_1[31];
                    
                    r_task_rdata_2[0] <= task_rdata_2[0]; 
                    r_task_rdata_2[1] <= task_rdata_2[1]; 
                    r_task_rdata_2[2] <= task_rdata_2[2]; 
                    r_task_rdata_2[3] <= task_rdata_2[3]; 
                    r_task_rdata_2[4] <= task_rdata_2[4]; 
                    r_task_rdata_2[5] <= task_rdata_2[5]; 
                    r_task_rdata_2[6] <= task_rdata_2[6]; 
                    r_task_rdata_2[7] <= task_rdata_2[7]; 
                    r_task_rdata_2[8] <= task_rdata_2[8]; 
                    r_task_rdata_2[9] <= task_rdata_2[9]; 
                    r_task_rdata_2[10] <= task_rdata_2[10]; 
                    r_task_rdata_2[11] <= task_rdata_2[11]; 
                    r_task_rdata_2[12] <= task_rdata_2[12]; 
                    r_task_rdata_2[13] <= task_rdata_2[13]; 
                    r_task_rdata_2[14] <= task_rdata_2[14]; 
                    r_task_rdata_2[15] <= task_rdata_2[15]; 
                    r_task_rdata_2[16] <= task_rdata_2[16]; 
                    r_task_rdata_2[17] <= task_rdata_2[17]; 
                    r_task_rdata_2[18] <= task_rdata_2[18]; 
                    r_task_rdata_2[19] <= task_rdata_2[19]; 
                    r_task_rdata_2[20] <= task_rdata_2[20]; 
                    r_task_rdata_2[21] <= task_rdata_2[21]; 
                    r_task_rdata_2[22] <= task_rdata_2[22]; 
                    r_task_rdata_2[23] <= task_rdata_2[23]; 
                    r_task_rdata_2[24] <= task_rdata_2[24]; 
                    r_task_rdata_2[25] <= task_rdata_2[25]; 
                    r_task_rdata_2[26] <= task_rdata_2[26]; 
                    r_task_rdata_2[27] <= task_rdata_2[27]; 
                    r_task_rdata_2[28] <= task_rdata_2[28]; 
                    r_task_rdata_2[29] <= task_rdata_2[29]; 
                    r_task_rdata_2[30] <= task_rdata_2[30]; 
                    r_task_rdata_2[31] <= task_rdata_2[31];
                    
                    r_sha256 <= sha256;
                    
                    t_stop <= 1'b1;
                                        
                end
                else if ( new_rx && (packet_rx[0] == 8'h06) && ( len_rx == ( 6'd1 + 6'd4 ) ) ) begin
                    
                    state <= 1'b0;
                    
                    found <= 1'b0;
                    
                    t_stop <= 1'b1;
                    
                    packet_tx[0] <= 8'h86;
                    len_tx <= 6'd1 + 6'd4;
                    new_tx <= 1'b1;
               
                end 
                else if ( new_rx && (packet_rx[0] == 8'h07) && ( len_rx == ( 6'd1 + 6'd4 ) ) ) begin
                
                    packet_tx[0] <= 8'h87;
                
                    packet_tx[1] <= tcnt[7:0];
                    packet_tx[2] <= tcnt[15:8];
                    packet_tx[3] <= tcnt[23:16];
                    packet_tx[4] <= tcnt[31:24];
                    
                    packet_tx[5] <= tasks_srs_acks_qnt[7:0];
                    packet_tx[6] <= tasks_srs_acks_qnt[15:8];
                    
                    packet_tx[7] <= found == 1'b1 ? 8'hFF : 8'h00;
                    
                    packet_tx[8] <= COREQ_QNT [7:0];
                    packet_tx[9] <= COREQ_QNT [15:8];
                    packet_tx[10] <= COREQ_QNT [23:16];
                    packet_tx[11] <= COREQ_QNT [31:24];
                                                              
                    len_tx <= 6'd12 + 6'd4;
                    
                    new_tx <= 1'b1;
                    
                    tcnt <= ( tasks_srs_acks_qnt == 16'hFFFF ) && ( tasks_srs_acks_qnt_OLD == 16'hFFFE ) ? 32'd1 : 32'd0;
                    
                     
                 
                end
                else if ( new_rx && (packet_rx[0] == 8'h08) && ( len_rx == ( 6'd1 + 6'd4 ) ) ) begin
                
                    packet_tx[0] <= 8'h88;
                
                    packet_tx[1] <= r_task_rdata_1[0]; 
                    packet_tx[2] <= r_task_rdata_1[1]; 
                    packet_tx[3] <= r_task_rdata_1[2]; 
                    packet_tx[4] <= r_task_rdata_1[3]; 
                    packet_tx[5] <= r_task_rdata_1[4]; 
                    packet_tx[6] <= r_task_rdata_1[5]; 
                    packet_tx[7] <= r_task_rdata_1[6]; 
                    packet_tx[8] <= r_task_rdata_1[7]; 
                    packet_tx[9] <= r_task_rdata_1[8]; 
                    packet_tx[10] <= r_task_rdata_1[9]; 
                    packet_tx[11] <= r_task_rdata_1[10]; 
                    packet_tx[12] <= r_task_rdata_1[11]; 
                    packet_tx[13] <= r_task_rdata_1[12]; 
                    packet_tx[14] <= r_task_rdata_1[13]; 
                    packet_tx[15] <= r_task_rdata_1[14]; 
                    packet_tx[16] <= r_task_rdata_1[15]; 
                    packet_tx[17] <= r_task_rdata_1[16]; 
                    packet_tx[18] <= r_task_rdata_1[17];
                    packet_tx[19] <= r_task_rdata_1[18]; 
                    packet_tx[20] <= r_task_rdata_1[19]; 
                    packet_tx[21] <= r_task_rdata_1[20]; 
                    packet_tx[22] <= r_task_rdata_1[21]; 
                    packet_tx[23] <= r_task_rdata_1[22]; 
                    packet_tx[24] <= r_task_rdata_1[23]; 
                    packet_tx[25] <= r_task_rdata_1[24]; 
                    packet_tx[26] <= r_task_rdata_1[25]; 
                    packet_tx[27] <= r_task_rdata_1[26]; 
                    packet_tx[28] <= r_task_rdata_1[27]; 
                    packet_tx[29] <= r_task_rdata_1[28]; 
                    packet_tx[30] <= r_task_rdata_1[29]; 
                    packet_tx[31] <= r_task_rdata_1[30]; 
                    packet_tx[32] <= r_task_rdata_1[31];
                                        
                    len_tx <= 6'd33 + 6'd4;
                    
                    new_tx <= 1'b1;
                    
                end
                else if ( new_rx && (packet_rx[0] == 8'h09) && ( len_rx == ( 6'd1 + 6'd4 ) ) ) begin
                
                    packet_tx[0] <= 8'h89;
                
                    packet_tx[1] <= r_task_rdata_2[0]; 
                    packet_tx[2] <= r_task_rdata_2[1]; 
                    packet_tx[3] <= r_task_rdata_2[2]; 
                    packet_tx[4] <= r_task_rdata_2[3]; 
                    packet_tx[5] <= r_task_rdata_2[4]; 
                    packet_tx[6] <= r_task_rdata_2[5]; 
                    packet_tx[7] <= r_task_rdata_2[6]; 
                    packet_tx[8] <= r_task_rdata_2[7]; 
                    packet_tx[9] <= r_task_rdata_2[8]; 
                    packet_tx[10] <= r_task_rdata_2[9]; 
                    packet_tx[11] <= r_task_rdata_2[10]; 
                    packet_tx[12] <= r_task_rdata_2[11]; 
                    packet_tx[13] <= r_task_rdata_2[12]; 
                    packet_tx[14] <= r_task_rdata_2[13]; 
                    packet_tx[15] <= r_task_rdata_2[14]; 
                    packet_tx[16] <= r_task_rdata_2[15]; 
                    packet_tx[17] <= r_task_rdata_2[16]; 
                    packet_tx[18] <= r_task_rdata_2[17];
                    packet_tx[19] <= r_task_rdata_2[18]; 
                    packet_tx[20] <= r_task_rdata_2[19]; 
                    packet_tx[21] <= r_task_rdata_2[20]; 
                    packet_tx[22] <= r_task_rdata_2[21]; 
                    packet_tx[23] <= r_task_rdata_2[22]; 
                    packet_tx[24] <= r_task_rdata_2[23]; 
                    packet_tx[25] <= r_task_rdata_2[24]; 
                    packet_tx[26] <= r_task_rdata_2[25]; 
                    packet_tx[27] <= r_task_rdata_2[26]; 
                    packet_tx[28] <= r_task_rdata_2[27]; 
                    packet_tx[29] <= r_task_rdata_2[28]; 
                    packet_tx[30] <= r_task_rdata_2[29]; 
                    packet_tx[31] <= r_task_rdata_2[30]; 
                    packet_tx[32] <= r_task_rdata_2[31];
                                        
                    len_tx <= 6'd33 + 6'd4;
                    
                    new_tx <= 1'b1;
                    
                end
                else if ( new_rx && (packet_rx[0] == 8'h0A) && ( len_rx == ( 6'd1 + 6'd4 ) ) ) begin
                
                    packet_tx[0] <= 8'h8A;
                
                    packet_tx[1] <= r_sha256[7:0]; 
                    packet_tx[2] <= r_sha256[15:8]; 
                    packet_tx[3] <= r_sha256[23:16]; 
                    packet_tx[4] <= r_sha256[31:24]; 
                    packet_tx[5] <= r_sha256[39:32]; 
                    packet_tx[6] <= r_sha256[47:40]; 
                    packet_tx[7] <= r_sha256[55:48]; 
                    packet_tx[8] <= r_sha256[63:56];
                     
                    packet_tx[9] <= r_sha256[71:64]; 
                    packet_tx[10] <= r_sha256[79:72]; 
                    packet_tx[11] <= r_sha256[87:80]; 
                    packet_tx[12] <= r_sha256[95:88]; 
                    packet_tx[13] <= r_sha256[103:96]; 
                    packet_tx[14] <= r_sha256[111:104]; 
                    packet_tx[15] <= r_sha256[119:112];
                    packet_tx[16] <= r_sha256[127:120]; 
                    
                    packet_tx[17] <= r_sha256[135:128]; 
                    packet_tx[18] <= r_sha256[143:136]; 
                    packet_tx[19] <= r_sha256[151:144]; 
                    packet_tx[20] <= r_sha256[159:152]; 
                    packet_tx[21] <= r_sha256[167:160]; 
                    packet_tx[22] <= r_sha256[175:168]; 
                    packet_tx[23] <= r_sha256[183:176]; 
                    packet_tx[24] <= r_sha256[191:184]; 
                    
                    packet_tx[25] <= r_sha256[199:192]; 
                    packet_tx[26] <= r_sha256[207:200]; 
                    packet_tx[27] <= r_sha256[215:208]; 
                    packet_tx[28] <= r_sha256[223:216]; 
                    packet_tx[29] <= r_sha256[231:224]; 
                    packet_tx[30] <= r_sha256[239:232]; 
                    packet_tx[31] <= r_sha256[247:240];
                    packet_tx[32] <= r_sha256[255:248]; 
                                                            
                    len_tx <= 6'd33 + 6'd4;
                    
                    new_tx <= 1'b1;
                    
                end
                else begin
                    
                    new_tx <= 1'b0;
                
                    if( ( tasks_srs_acks_qnt == 16'hFFFF ) && ( tasks_srs_acks_qnt_OLD == 16'hFFFE ) )
                        tcnt <= tcnt + 32'd1;
                    
                end
                
                 
                
            end
        
        endcase
    end

end



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
