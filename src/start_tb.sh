iverilog -g2012 -o tb.vvp tb.v top_level.v uart_ctrl.v crc32.v fifo.v cmd_packets_ctrl.v sha256.v data_constructor.v mcore.v
vvp tb.vvp
# gtkwave tb.vcd &> /dev/null &
