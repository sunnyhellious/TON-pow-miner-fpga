
set_property IOSTANDARD LVCMOS33 [get_ports {o_led}]
set_property PACKAGE_PIN E25 [get_ports {o_led}]

set_property IOSTANDARD LVCMOS33 [get_ports {i_cmd_uart_rx}]
set_property PACKAGE_PIN D20 [get_ports {i_cmd_uart_rx}]

set_property IOSTANDARD LVCMOS33 [get_ports {o_cmd_uart_tx}]
set_property PACKAGE_PIN A24 [get_ports {o_cmd_uart_tx}]

set_property IOSTANDARD LVCMOS33 [get_ports i_clk_50]
set_property PACKAGE_PIN F22 [get_ports i_clk_50]
# create_clock -name SYS_CLK_50 -period 20 [get_ports i_clk_50]

set_property IOSTANDARD LVCMOS18 [get_ports i_n_reset]
set_property PACKAGE_PIN AB26 [get_ports i_n_reset]

set_property BITSTREAM.CONFIG.SPI_BUSWIDTH 4 [current_design]