`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 14.05.2022 23:12:19
// Design Name: 
// Module Name: fifo
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

module fifo (

    input           i_clk, 
    input           i_rst_n,
     
    input           i_wr, 
    input           i_rd, 
    
    input  [7:0]    i_data_in,
    output [7:0]    o_data_out,
    
    output          o_fifo_full, 
    output          o_fifo_empty, 
    output          o_fifo_threshold, 
    output          o_fifo_overflow, 
    output          o_fifo_underflow
    
);  
    
    wire[4:0] wptr,rptr;  
    wire fifo_we,fifo_rd;   
    
    write_pointer wr_p_0 (    
        .i_clk(i_clk),
        .i_rst_n(i_rst_n),
        .i_wr(i_wr),
        .i_fifo_full(o_fifo_full),
        .o_wptr(wptr),
        .o_fifo_we(fifo_we)
    );  
    
    read_pointer rd_p_0 (
        .i_clk(i_clk),
        .i_rst_n(i_rst_n),
        
        .i_rd(i_rd),
        .i_fifo_empty(o_fifo_empty),
        
        .o_fifo_rd(fifo_rd),    
        .o_rptr(rptr)
    );
      
    
   memory_array mem_arr_0 (
    
        .i_clk(i_clk),
        .i_rst_n(i_rst_n),
        
        .i_fifo_we(fifo_we),
        
        .i_wptr(wptr),
        .i_rptr(rptr),

        .i_data_in(i_data_in), 
        .o_data_out(o_data_out)
    
    );
    
    status_signal st_sig_0 (

        .i_clk(i_clk),
        .i_rst_n(i_rst_n),
        
        .i_wr(i_wr), 
        .i_rd(i_wr), 
        .i_fifo_we(fifo_we), 
        .i_fifo_rd(fifo_rd),
        
        .i_wptr(wptr),
        .i_rptr(rptr),
        
        .o_fifo_full(o_fifo_full), 
        .o_fifo_empty(o_fifo_empty), 
        .o_fifo_threshold(o_fifo_threshold), 
        .o_fifo_overflow(o_fifo_overflow), 
        .o_fifo_underflow(o_fifo_underflow)
        
    );  
    
endmodule  
// fifo end

module memory_array (

    input   i_clk,
    input   i_rst_n,
    
    input   i_fifo_we,
    
    input   [4:0] i_wptr,
    input   [4:0] i_rptr,
    
     
    input   [7:0] i_data_in, 
    output  [7:0] o_data_out
  
);  
   
    reg[7:0] data_out2[15:0];     

    always @(posedge i_clk) begin // , negedge i_rst_n  
        if(i_fifo_we)   
            data_out2[i_wptr[3:0]] <= i_data_in;  
    end
      
    assign o_data_out = data_out2[i_rptr[3:0]];
      
endmodule 
// memory_array end 

module read_pointer ( 
    
    input               i_clk,
    input               i_rst_n,
    
    input               i_rd,
    input               i_fifo_empty,
    
    output              o_fifo_rd,    
    output reg [4:0]    o_rptr   
    
);
      
    assign o_fifo_rd = ( ~i_fifo_empty ) & i_rd;
      
    always @( posedge i_clk, negedge i_rst_n ) begin  
    if (i_rst_n == 1'b0) 
        o_rptr <= 5'd0;  
    else
        if(o_fifo_rd)  
            o_rptr <= o_rptr + 5'd1;  
        else  
            o_rptr <= o_rptr;  
    end  
    
endmodule  
// read_pointer

module status_signal (
    input i_clk,
    input i_rst_n,
    
    input i_wr, 
    input i_rd, 
    input i_fifo_we, 
    input i_fifo_rd,
    
    input [4:0] i_wptr,
    input [4:0] i_rptr,
    
    output reg o_fifo_full, 
    output reg o_fifo_empty, 
    output reg o_fifo_threshold, 
    output reg o_fifo_overflow, 
    output reg o_fifo_underflow
    
);
    
    wire fbit_comp, overflow_set, underflow_set;  
    wire pointer_equal;  
    wire[4:0] pointer_result;  
      
    assign fbit_comp        = i_wptr[4] ^ i_rptr[4];  
    assign pointer_equal    = (i_wptr[3:0] - i_rptr[3:0]) ? 1'b0 : 1'b1;  
    assign pointer_result   = i_wptr[4:0] - i_rptr[4:0];  
    assign overflow_set     = o_fifo_full & i_wr;  
    assign underflow_set    = o_fifo_empty & i_rd;
      
    always @(*) begin  
        o_fifo_full      = fbit_comp & pointer_equal;  
        o_fifo_empty     = (~fbit_comp) & pointer_equal;  
        o_fifo_threshold = (pointer_result[4]||pointer_result[3]) ? 1:0;  
    end  
    
    always @(posedge i_clk, negedge i_rst_n) begin  
        if(i_rst_n == 1'b0) 
            o_fifo_overflow <= 1'b0;  
        else if( (overflow_set==1'b1) && (i_fifo_rd == 1'b0) )  
            o_fifo_overflow <=1'b1;  
        else if( i_fifo_rd )  
            o_fifo_overflow <= 1'b0;  
        else  
            o_fifo_overflow <= o_fifo_overflow;  
        end 
         
    always @(posedge i_clk, negedge i_rst_n) begin  
        if(i_rst_n == 1'b0)
            o_fifo_underflow <= 1'b0;  
        else if( ( underflow_set == 1'b1 ) && ( i_fifo_we==1'b0 ) )  
            o_fifo_underflow <= 1'b1;  
        else if(i_fifo_we)  
            o_fifo_underflow <= 1'b0;  
        else  
            o_fifo_underflow <= o_fifo_underflow;  
    end  
    
endmodule  
// status_signal end

 
module write_pointer (
    input i_clk,
    input i_rst_n,
    input i_wr,
    input i_fifo_full,
    output reg [4:0] o_wptr,
    output o_fifo_we    
);
    
    assign o_fifo_we = (~i_fifo_full) & i_wr;  
    
    always @(posedge i_clk, negedge i_rst_n) begin  
        if( i_rst_n == 1'b0 ) 
            o_wptr <= 5'd0;  
        else if(o_fifo_we)  
            o_wptr <= o_wptr + 5'd1;  
        else  
            o_wptr <= o_wptr;  
    end  
    
endmodule 
// status_signal end
