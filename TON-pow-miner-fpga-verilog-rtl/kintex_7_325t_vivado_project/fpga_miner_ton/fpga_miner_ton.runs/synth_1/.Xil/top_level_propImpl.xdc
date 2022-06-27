set_property SRC_FILE_INFO {cfile:d:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/test_miner_ton.gen/sources_1/ip/clk_wiz_0/clk_wiz_0.xdc rfile:../../../test_miner_ton.gen/sources_1/ip/clk_wiz_0/clk_wiz_0.xdc id:1 order:EARLY scoped_inst:clk_wiz_0_/inst} [current_design]
set_property SRC_FILE_INFO {cfile:D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/constrs_1/new/top_level_constraints.xdc rfile:../../../fpga_miner_ton.srcs/constrs_1/new/top_level_constraints.xdc id:2} [current_design]
current_instance clk_wiz_0_/inst
set_property src_info {type:SCOPED_XDC file:1 line:57 export:INPUT save:INPUT read:READ} [current_design]
set_input_jitter [get_clocks -of_objects [get_ports clk_in1]] 0.200
current_instance
set_property src_info {type:XDC file:2 line:3 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN E25 [get_ports {o_led}]
set_property src_info {type:XDC file:2 line:6 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN D20 [get_ports {i_cmd_uart_rx}]
set_property src_info {type:XDC file:2 line:9 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN A24 [get_ports {o_cmd_uart_tx}]
set_property src_info {type:XDC file:2 line:12 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN F22 [get_ports i_clk_50]
set_property src_info {type:XDC file:2 line:16 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN AB26 [get_ports i_n_reset]
