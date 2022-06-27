# iverilog -g2012 -o tb.vvp tb.sv top_level.sv uart_ctrl.sv crc32.sv fifo.sv cmd_packets_ctrl.sv sha256.sv data_constructor.sv mcore.sv
iverilog -g2012 -o tb.vvp tb.sv uart_ctrl.sv crc32.sv fifo.sv cmd_packets_ctrl.sv sha256_orig.sv data_constructor.sv mcore.sv system_mcores.sv tasks_generator.sv 
vvp tb.vvp
# gtkwave tb.vcd &> /dev/null &
