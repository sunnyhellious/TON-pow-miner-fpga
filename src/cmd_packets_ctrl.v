module cmd_packets_ctrl (
  
    input	        i_n_reset,
    input	        i_clk,
    
    input	        i_uart_rx,
    output	        o_uart_tx,
    
    // cmd
    output [7:0]	o_rx_packet [63:0],	// 64 bytes - maximum size of packet
    output			o_rx_packet_new, 	// new packet flag
    output [5:0]	o_rx_packet_len,
    output 			o_rx_busy,	
    
    // answer
    input [7:0]		i_tx_packet [63:0],	// 64 bytes - maximum size of packet
    input 			i_tx_packet_new, 	
    input [5:0]		i_tx_packet_len,
    output 			o_tx_busy
        
);

parameter RT_LINE_SHUTUP_TOUT   = 16'd6510; // how many clocks of rx or tx line must be shut up for end of packet detection mechanism

// RECEIVE part variables

parameter STATE_REC_IDLE 		= 3'b000; // idle - no hot f*ck in this state, only ice cold f*ck in this state
parameter STATE_REC_GNB	        = 3'b001; // get new byte
parameter STATE_REC_CL_CRC32	= 3'b011; // calc crc32
parameter STATE_REC_CH_CRC32	= 3'b010; // check crc32

reg [2:0] rec_state; 
reg [7:0] rec_packet [63:0];
reg [5:0] rec_packet_len;
reg 	  rec_packet_new;
reg [15:0] rec_timer;

wire [7:0] rx_byte_bus;
		
assign o_rx_packet 	   = rec_packet; 
assign o_rx_packet_len = rec_packet_len;
assign o_rx_packet_new = rec_packet_new;

reg crc_0_load;
reg crc_0_finish;
reg [7:0] crc_0_load_byte;
reg [5:0] crc_0_bytes_cnt;
wire [31:0] crc_0_result;

assign o_rx_busy = rec_state != STATE_REC_IDLE ? 1'b1 : 1'b0;

// TRANSMIT part variables

parameter STATE_TRS_IDLE 		= 3'b000; // idle - no fuck in this state
parameter STATE_TRS_CL_CRC32	= 3'b001; // calc crc32
parameter STATE_TRS_PH_CRC32	= 3'b011; // push calculated crc32 to tx packet
parameter STATE_TRS_PHB	        = 3'b010; // push byte to tx
parameter STATE_TRS_WTB	        = 3'b110; // wait when byte transmitted
parameter STATE_TRS_WT_SUP      = 3'b100; // wait shut up line timeout


reg [2:0] trs_state; 
reg [7:0] trs_packet [63:0];
reg [5:0] trs_packet_len;
reg [5:0] trs_bytes_cnt;
reg 	  trs_packet_new;
reg [15:0] trs_timer;

reg [7:0] uart_tx_m_0_load_byte;
reg uart_tx_m_0_load;
wire uart_tx_m_0_busy;

assign o_tx_busy = trs_state != STATE_TRS_IDLE ? 1'b1 : 1'b0;

reg crc_1_load;
reg crc_1_finish;
reg [7:0] crc_1_load_byte;
reg [5:0] crc_1_bytes_cnt;
wire [31:0] crc_1_result;


// FSMs are below

// FSM for RECEIVE (yes, of course we know how to write in three always blocks)
always @(posedge i_clk, negedge i_n_reset) begin
	if( i_n_reset == 1'b0 ) begin

		rec_state           <= STATE_REC_IDLE;
        
        rec_packet_len      <= 6'd0;
        rec_packet_new		<= 1'b0;
        rec_timer           <= 16'd0;

        crc_0_load          <= 1'b0;                    
        crc_0_finish        <= 1'b0;
        crc_0_load_byte     <= 8'd0;
        crc_0_bytes_cnt     <= 6'd0;
        
        rec_packet[0]		<= 8'd0;  // of course this sh*t is quiet dump, but currently this project is quiet lasy
		rec_packet[1]		<= 8'd0;
		rec_packet[2]		<= 8'd0;
		rec_packet[3]		<= 8'd0;
        rec_packet[4]		<= 8'd0;
		rec_packet[5]		<= 8'd0;
		rec_packet[6]		<= 8'd0;
		rec_packet[7]		<= 8'd0;
		rec_packet[8]		<= 8'd0;
		rec_packet[9]		<= 8'd0;
		rec_packet[10]		<= 8'd0;
		rec_packet[11]		<= 8'd0;
        rec_packet[12]		<= 8'd0;
		rec_packet[13]		<= 8'd0;
		rec_packet[14]		<= 8'd0;
		rec_packet[15]		<= 8'd0;
		rec_packet[16]		<= 8'd0;
		rec_packet[17]		<= 8'd0;
		rec_packet[18]		<= 8'd0;
		rec_packet[19]		<= 8'd0;
        rec_packet[20]		<= 8'd0;
		rec_packet[21]		<= 8'd0;
		rec_packet[22]		<= 8'd0;
		rec_packet[23]		<= 8'd0;
		rec_packet[24]		<= 8'd0;
		rec_packet[25]		<= 8'd0;
		rec_packet[26]		<= 8'd0;
		rec_packet[27]		<= 8'd0;
        rec_packet[28]		<= 8'd0;
		rec_packet[29]		<= 8'd0;
		rec_packet[30]		<= 8'd0;
		rec_packet[31]		<= 8'd0;
		rec_packet[32]		<= 8'd0;
		rec_packet[33]		<= 8'd0;
		rec_packet[34]		<= 8'd0;
		rec_packet[35]		<= 8'd0;
        rec_packet[36]		<= 8'd0;
		rec_packet[37]		<= 8'd0;
		rec_packet[38]		<= 8'd0;
		rec_packet[39]		<= 8'd0;
		rec_packet[40]		<= 8'd0;
		rec_packet[41]		<= 8'd0;
		rec_packet[42]		<= 8'd0;
        rec_packet[43]		<= 8'd0;
		rec_packet[44]		<= 8'd0;
		rec_packet[45]		<= 8'd0;
		rec_packet[46]		<= 8'd0;
		rec_packet[47]		<= 8'd0;
		rec_packet[48]		<= 8'd0;
		rec_packet[49]		<= 8'd0;
		rec_packet[50]		<= 8'd0;
        rec_packet[51]		<= 8'd0;
		rec_packet[52]		<= 8'd0;
		rec_packet[53]		<= 8'd0;
		rec_packet[54]		<= 8'd0;
		rec_packet[55]		<= 8'd0;
		rec_packet[56]		<= 8'd0;
		rec_packet[57]		<= 8'd0;
		rec_packet[58]		<= 8'd0;
        rec_packet[59]		<= 8'd0;
		rec_packet[60]		<= 8'd0;
		rec_packet[61]		<= 8'd0;
		rec_packet[62]		<= 8'd0;
		rec_packet[63]		<= 8'd0;

    end
    else begin

        case ( rec_state ) 

            STATE_REC_IDLE : begin

                if ( rx_new == 1'b1 ) begin

                    rec_timer                   <= 16'd0;                    
                    rec_packet_len              <= 6'd1;
                    rec_packet[rec_packet_len]  <= rx_byte_bus;
                    rec_state                   <= STATE_REC_GNB;

                end
                else begin

                    rec_packet_len      <= 6'd0;
                    rec_packet_new		<= 1'b0;
                    rec_timer           <= 16'd0;	
                    
                    crc_0_load          <= 1'b0;                    
                    crc_0_finish        <= 1'b0;
                    crc_0_load_byte     <= 8'd0;
                    crc_0_bytes_cnt     <= 6'd0;

                		    
                end

            end
            //

            STATE_REC_GNB : begin

                if ( rx_new == 1'b1 ) begin
                    rec_timer <= 16'd0;                    
                    rec_packet_len <= rec_packet_len + 6'd1;
                    rec_packet[rec_packet_len] <= rx_byte_bus;
                end
                else begin
                    rec_timer <= rec_timer + 16'd1;
                    if ( rec_timer >= RT_LINE_SHUTUP_TOUT ) begin

                        if ( rec_packet_len > 6'd4 ) begin

                            crc_0_load_byte <= rec_packet[0];
                            crc_0_bytes_cnt <= 6'd1;
                            crc_0_load      <= 1'b1;

                            rec_state       <= STATE_REC_CL_CRC32;
                            
                        end
                        else
                            rec_state       <= STATE_REC_IDLE;              

                    end
                    
                end

            end
            //

            STATE_REC_CL_CRC32 : begin
                    
                crc_0_load_byte <= rec_packet[crc_0_bytes_cnt];
               	crc_0_bytes_cnt <= crc_0_bytes_cnt + 6'd1;
                    
                if ( crc_0_bytes_cnt >= ( rec_packet_len - 6'd4 ) ) begin                    
                	crc_0_load		<= 1'b0;
                	crc_0_finish	<= 1'b1;
                	rec_state       <= STATE_REC_CH_CRC32;              
                end

            end 
            //
            
            STATE_REC_CH_CRC32 : begin
                    
            	crc_0_finish	<= 1'b0;
            	
            	if ( crc_0_result == {
            		rec_packet[rec_packet_len-6'd1],
            		rec_packet[rec_packet_len-6'd2],
            		rec_packet[rec_packet_len-6'd3],            		            		
            		rec_packet[rec_packet_len-6'd4]            		
            	} ) begin
           			rec_packet_new <= 1'b1;       		
            	end 
            	
            	rec_state <= STATE_REC_IDLE;              

            end 
            //

            default : rec_state <= STATE_REC_IDLE;
			     
	
		endcase

        
	
	end
end      

reg uart_tx_m_0_busy_OLD;
      
// FSM for TRANSMIT (yes, of course we know how to write in three always blocks)
always @(posedge i_clk, negedge i_n_reset) begin
	if( i_n_reset == 1'b0 ) begin

		trs_state           <= STATE_TRS_IDLE;
        
        trs_packet[0]		<= 8'd0; // of course this sh*t is quiet dump, but currently this project is quiet lasy
		trs_packet[1]		<= 8'd0;
		trs_packet[2]		<= 8'd0;
		trs_packet[3]		<= 8'd0;
        trs_packet[4]		<= 8'd0;
		trs_packet[5]		<= 8'd0;
		trs_packet[6]		<= 8'd0;
		trs_packet[7]		<= 8'd0;
		trs_packet[8]		<= 8'd0;
		trs_packet[9]		<= 8'd0;
		trs_packet[10]		<= 8'd0;
		trs_packet[11]		<= 8'd0;
        trs_packet[12]		<= 8'd0;
		trs_packet[13]		<= 8'd0;
		trs_packet[14]		<= 8'd0;
		trs_packet[15]		<= 8'd0;
		trs_packet[16]		<= 8'd0;
		trs_packet[17]		<= 8'd0;
		trs_packet[18]		<= 8'd0;
		trs_packet[19]		<= 8'd0;
        trs_packet[20]		<= 8'd0;
		trs_packet[21]		<= 8'd0;
		trs_packet[22]		<= 8'd0;
		trs_packet[23]		<= 8'd0;
		trs_packet[24]		<= 8'd0;
		trs_packet[25]		<= 8'd0;
		trs_packet[26]		<= 8'd0;
		trs_packet[27]		<= 8'd0;
        trs_packet[28]		<= 8'd0;
		trs_packet[29]		<= 8'd0;
		trs_packet[30]		<= 8'd0;
		trs_packet[31]		<= 8'd0;
		trs_packet[32]		<= 8'd0;
		trs_packet[33]		<= 8'd0;
		trs_packet[34]		<= 8'd0;
		trs_packet[35]		<= 8'd0;
        trs_packet[36]		<= 8'd0;
		trs_packet[37]		<= 8'd0;
		trs_packet[38]		<= 8'd0;
		trs_packet[39]		<= 8'd0;
		trs_packet[40]		<= 8'd0;
		trs_packet[41]		<= 8'd0;
		trs_packet[42]		<= 8'd0;
        trs_packet[43]		<= 8'd0;
		trs_packet[44]		<= 8'd0;
		trs_packet[45]		<= 8'd0;
		trs_packet[46]		<= 8'd0;
		trs_packet[47]		<= 8'd0;
		trs_packet[48]		<= 8'd0;
		trs_packet[49]		<= 8'd0;
		trs_packet[50]		<= 8'd0;
        trs_packet[51]		<= 8'd0;
		trs_packet[52]		<= 8'd0;
		trs_packet[53]		<= 8'd0;
		trs_packet[54]		<= 8'd0;
		trs_packet[55]		<= 8'd0;
		trs_packet[56]		<= 8'd0;
		trs_packet[57]		<= 8'd0;
		trs_packet[58]		<= 8'd0;
        trs_packet[59]		<= 8'd0;
		trs_packet[60]		<= 8'd0;
		trs_packet[61]		<= 8'd0;
		trs_packet[62]		<= 8'd0;
		trs_packet[63]		<= 8'd0;
        
        trs_packet_len      <= 6'd0;
        trs_bytes_cnt		<= 6'd0;
        trs_timer           <= 16'd0;

        crc_1_load          <= 1'b0;                    
        crc_1_finish        <= 1'b0;
        crc_1_load_byte     <= 8'd0;
        crc_1_bytes_cnt     <= 6'd0;

		
		uart_tx_m_0_load_byte 	<= 8'd0;
		uart_tx_m_0_load  		<= 1'd0;

		uart_tx_m_0_busy_OLD <= 1'b0;


    end
    else begin
		
		uart_tx_m_0_busy_OLD <= uart_tx_m_0_busy;
		
        case ( trs_state ) 

            STATE_TRS_IDLE : begin

                if ( i_tx_packet_new == 1'b1 ) begin

                    trs_timer           <= 16'd0;                    
                    trs_packet_len      <= i_tx_packet_len;
                    trs_bytes_cnt		<= 6'd0;
                    
            		trs_packet[0]		<= i_tx_packet[0];
					trs_packet[1]		<= i_tx_packet[1];
					trs_packet[2]		<= i_tx_packet[2];
					trs_packet[3]		<= i_tx_packet[3];
					trs_packet[4]		<= i_tx_packet[4];
					trs_packet[5]		<= i_tx_packet[5];
					trs_packet[6]		<= i_tx_packet[6];
					trs_packet[7]		<= i_tx_packet[7];
					trs_packet[8]		<= i_tx_packet[8];
					trs_packet[9]		<= i_tx_packet[9];
					trs_packet[10]		<= i_tx_packet[10];
					trs_packet[11]		<= i_tx_packet[11];
					trs_packet[12]		<= i_tx_packet[12];
					trs_packet[13]		<= i_tx_packet[13];
					trs_packet[14]		<= i_tx_packet[14];
					trs_packet[15]		<= i_tx_packet[15];
					trs_packet[16]		<= i_tx_packet[16];
					trs_packet[17]		<= i_tx_packet[17];
					trs_packet[18]		<= i_tx_packet[18];
					trs_packet[19]		<= i_tx_packet[19];
					trs_packet[20]		<= i_tx_packet[20];
					trs_packet[21]		<= i_tx_packet[21];
					trs_packet[22]		<= i_tx_packet[22];
					trs_packet[23]		<= i_tx_packet[23];
					trs_packet[24]		<= i_tx_packet[24];
					trs_packet[25]		<= i_tx_packet[25];
					trs_packet[26]		<= i_tx_packet[26];
					trs_packet[27]		<= i_tx_packet[27];
					trs_packet[28]		<= i_tx_packet[28];
					trs_packet[29]		<= i_tx_packet[29];
					trs_packet[30]		<= i_tx_packet[30];
					trs_packet[31]		<= i_tx_packet[31];
					trs_packet[32]		<= i_tx_packet[32];
					trs_packet[33]		<= i_tx_packet[33];
					trs_packet[34]		<= i_tx_packet[34];
					trs_packet[35]		<= i_tx_packet[35];
					trs_packet[36]		<= i_tx_packet[36];
					trs_packet[37]		<= i_tx_packet[37];
					trs_packet[38]		<= i_tx_packet[38];
					trs_packet[39]		<= i_tx_packet[39];
					trs_packet[40]		<= i_tx_packet[40];
					trs_packet[41]		<= i_tx_packet[41];
					trs_packet[42]		<= i_tx_packet[42];
					trs_packet[43]		<= i_tx_packet[43];
					trs_packet[44]		<= i_tx_packet[44];
					trs_packet[45]		<= i_tx_packet[45];
					trs_packet[46]		<= i_tx_packet[46];
					trs_packet[47]		<= i_tx_packet[47];
					trs_packet[48]		<= i_tx_packet[48];
					trs_packet[49]		<= i_tx_packet[49];
					trs_packet[50]		<= i_tx_packet[50];
					trs_packet[51]		<= i_tx_packet[51];
					trs_packet[52]		<= i_tx_packet[52];
					trs_packet[53]		<= i_tx_packet[53];
					trs_packet[54]		<= i_tx_packet[54];
					trs_packet[55]		<= i_tx_packet[55];
					trs_packet[56]		<= i_tx_packet[56];
					trs_packet[57]		<= i_tx_packet[57];
					trs_packet[58]		<= i_tx_packet[58];
					trs_packet[59]		<= i_tx_packet[59];
					trs_packet[60]		<= i_tx_packet[60];
					trs_packet[61]		<= i_tx_packet[61];
					trs_packet[62]		<= i_tx_packet[62];
					trs_packet[63]		<= i_tx_packet[63];
                    
					crc_1_load_byte		<= i_tx_packet[0];              
                    crc_1_bytes_cnt 	<= 6'd1;
                    crc_1_load			<= 1'b1;
                    
                    trs_state           <= STATE_TRS_CL_CRC32;

                end
                else begin

                    trs_packet_len      <= 6'd0;
                    trs_bytes_cnt		<= 6'd0;
                    trs_timer           <= 16'd0;	
                    
                    crc_1_load          <= 1'b0;                    
                    crc_1_finish        <= 1'b0;
                    crc_1_load_byte     <= 8'd0;
                    crc_1_bytes_cnt     <= 6'd0;
                		    
                end

            end
            //

            STATE_TRS_CL_CRC32 : begin

				crc_1_load_byte <= trs_packet[crc_1_bytes_cnt];
               	crc_1_bytes_cnt <= crc_1_bytes_cnt + 6'd1;
                    
                if ( crc_1_bytes_cnt >= ( trs_packet_len - 6'd4 ) ) begin                    
                	crc_1_load		<= 1'b0;
                	crc_1_finish	<= 1'b1;
                	trs_state       <= STATE_TRS_PH_CRC32;              
                end                

            end
            //

            STATE_TRS_PH_CRC32 : begin
	           	crc_1_finish					  <= 1'b0;
               	trs_packet[trs_packet_len - 6'd4] <= crc_1_result[7:0];
				trs_packet[trs_packet_len - 6'd3] <= crc_1_result[15:8];
				trs_packet[trs_packet_len - 6'd2] <= crc_1_result[23:16];
				trs_packet[trs_packet_len - 6'd1] <= crc_1_result[31:24];
				
			 					
				trs_state <= STATE_TRS_PHB;              
            end 
            //
            
            STATE_TRS_PHB : begin
 				
 				if ( trs_bytes_cnt < ( trs_packet_len - 6'd0 ) ) begin
 					uart_tx_m_0_load_byte 	<= trs_packet[trs_bytes_cnt];
					uart_tx_m_0_load  		<= 1'd1;
					trs_bytes_cnt			<= trs_bytes_cnt + 6'd1;
					trs_state 				<= STATE_TRS_WTB;
 				end
 				else begin 
					uart_tx_m_0_load_byte 	<= 8'd0;
					uart_tx_m_0_load  		<= 1'd0;
 					trs_state 				<= STATE_TRS_WT_SUP;
 				end
                
            end 
            //
            
            STATE_TRS_WTB : begin
            	
            	uart_tx_m_0_load <= 1'b0;
            	
            	if ( ( uart_tx_m_0_busy == 1'b0 ) && ( uart_tx_m_0_busy_OLD == 1'b1 ) )
            		trs_state <= STATE_TRS_PHB;
            
            end
            //           
            
            STATE_TRS_WTB : begin
            	
            	trs_timer <= trs_timer + 16'd1;
            	
            	if ( trs_timer >= RT_LINE_SHUTUP_TOUT )
            		trs_state <= STATE_TRS_IDLE;
            
            end
            //           

            default : trs_state <= STATE_TRS_IDLE;
			     
	
		endcase

        
	
	end
end


      
uart_rx_m #( .CLKS_PER_BIT(434) ) uart_rx_m_0 (
    .i_n_Reset      (i_n_reset),
    .i_Clock        (i_clk),
    .i_Rx_Serial    (i_uart_rx),
    .o_Rx_DV        (rx_new),
    .o_Rx_Byte      (rx_byte_bus)
);

crc32 crc32_0 (
    .i_clk      (i_clk),
    .i_n_rst    (i_n_reset),
    .i_load     (crc_0_load),    
    .i_finish   (crc_0_finish),
    .i_data     (crc_0_load_byte),
    .o_crc      (crc_0_result)
);

uart_tx_m #( .CLKS_PER_BIT(434) ) uart_tx_m_0 (
    .i_n_Reset		(i_n_reset),
    .i_Clock		(i_clk),
	.i_Tx_DV		(uart_tx_m_0_load),
	.i_Tx_Byte		(uart_tx_m_0_load_byte),
	.o_Tx_Active	(uart_tx_m_0_busy),
	.o_Tx_Serial	(o_uart_tx),
	.o_Tx_Done		()
);

crc32 crc32_1 (
    .i_clk      (i_clk),
    .i_n_rst    (i_n_reset),
    .i_load     (crc_1_load),    
    .i_finish   (crc_1_finish),
    .i_data     (crc_1_load_byte),
    .o_crc      (crc_1_result)
);



   
endmodule
