
?
Command: %s
1870*	planAhead2?
?read_checkpoint -auto_incremental -incremental D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/utils_1/imports/synth_1/top_level.dcp2default:defaultZ12-2866h px? 
?
;Read reference checkpoint from %s for incremental synthesis3154*	planAhead2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/utils_1/imports/synth_1/top_level.dcp2default:defaultZ12-5825h px? 
T
-Please ensure there are no constraint changes3725*	planAheadZ12-7989h px? 
w
Command: %s
53*	vivadotcl2F
2synth_design -top top_level -part xc7k325tffg676-22default:defaultZ4-113h px? 
:
Starting synth_design
149*	vivadotclZ4-321h px? 
?
@Attempting to get a license for feature '%s' and/or device '%s'
308*common2
	Synthesis2default:default2
xc7k325t2default:defaultZ17-347h px? 
?
0Got license for feature '%s' and/or device '%s'
310*common2
	Synthesis2default:default2
xc7k325t2default:defaultZ17-349h px? 
W
Loading part %s157*device2$
xc7k325tffg676-22default:defaultZ21-403h px? 
?
[Reference run did not run incremental synthesis because %s; reverting to default synthesis
2138*designutils2+
the design is too small2default:defaultZ20-4072h px? 
?
?Flow is switching to default flow due to incremental criteria not met. If you would like to alter this behaviour and have the flow terminate instead, please set the following parameter config_implementation {autoIncr.Synth.RejectBehavior Terminate}2229*designutilsZ20-4379h px? 
?
HMultithreading enabled for synth_design using a maximum of %s processes.4828*oasys2
22default:defaultZ8-7079h px? 
a
?Launching helper process for spawning children vivado processes4827*oasysZ8-7078h px? 
`
#Helper process launched with PID %s4824*oasys2
170922default:defaultZ8-7075h px? 
?
%s*synth2?
wStarting RTL Elaboration : Time (s): cpu = 00:00:03 ; elapsed = 00:00:03 . Memory (MB): peak = 1592.516 ; gain = 0.000
2default:defaulth px? 
?
synthesizing module '%s'%s4497*oasys2
	top_level2default:default2
 2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
232default:default8@Z8-6157h px? 
?
synthesizing module '%s'%s4497*oasys2
	clk_wiz_02default:default2
 2default:default2?
?d:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/test_miner_ton.gen/sources_1/ip/clk_wiz_0/clk_wiz_0.v2default:default2
702default:default8@Z8-6157h px? 
?
synthesizing module '%s'%s4497*oasys2%
clk_wiz_0_clk_wiz2default:default2
 2default:default2?
?d:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/test_miner_ton.gen/sources_1/ip/clk_wiz_0/clk_wiz_0_clk_wiz.v2default:default2
682default:default8@Z8-6157h px? 
?
synthesizing module '%s'%s4497*oasys2
IBUF2default:default2
 2default:default2O
9D:/Xilinx_IDE/Vivado/2021.2/scripts/rt/data/unisim_comp.v2default:default2
552042default:default8@Z8-6157h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2
IBUF2default:default2
 2default:default2
12default:default2
12default:default2O
9D:/Xilinx_IDE/Vivado/2021.2/scripts/rt/data/unisim_comp.v2default:default2
552042default:default8@Z8-6155h px? 
?
synthesizing module '%s'%s4497*oasys2
	PLLE2_ADV2default:default2
 2default:default2O
9D:/Xilinx_IDE/Vivado/2021.2/scripts/rt/data/unisim_comp.v2default:default2
893972default:default8@Z8-6157h px? 
e
%s
*synth2M
9	Parameter BANDWIDTH bound to: OPTIMIZED - type: string 
2default:defaulth p
x
? 
c
%s
*synth2K
7	Parameter CLKFBOUT_MULT bound to: 18 - type: integer 
2default:defaulth p
x
? 
i
%s
*synth2Q
=	Parameter CLKFBOUT_PHASE bound to: 0.000000 - type: double 
2default:defaulth p
x
? 
i
%s
*synth2Q
=	Parameter CLKIN1_PERIOD bound to: 20.000000 - type: double 
2default:defaulth p
x
? 
d
%s
*synth2L
8	Parameter CLKOUT0_DIVIDE bound to: 10 - type: integer 
2default:defaulth p
x
? 
m
%s
*synth2U
A	Parameter CLKOUT0_DUTY_CYCLE bound to: 0.500000 - type: double 
2default:defaulth p
x
? 
h
%s
*synth2P
<	Parameter CLKOUT0_PHASE bound to: 0.000000 - type: double 
2default:defaulth p
x
? 
d
%s
*synth2L
8	Parameter COMPENSATION bound to: ZHOLD - type: string 
2default:defaulth p
x
? 
b
%s
*synth2J
6	Parameter DIVCLK_DIVIDE bound to: 1 - type: integer 
2default:defaulth p
x
? 
d
%s
*synth2L
8	Parameter STARTUP_WAIT bound to: FALSE - type: string 
2default:defaulth p
x
? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2
	PLLE2_ADV2default:default2
 2default:default2
22default:default2
12default:default2O
9D:/Xilinx_IDE/Vivado/2021.2/scripts/rt/data/unisim_comp.v2default:default2
893972default:default8@Z8-6155h px? 
?
synthesizing module '%s'%s4497*oasys2
BUFG2default:default2
 2default:default2O
9D:/Xilinx_IDE/Vivado/2021.2/scripts/rt/data/unisim_comp.v2default:default2
10832default:default8@Z8-6157h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2
BUFG2default:default2
 2default:default2
32default:default2
12default:default2O
9D:/Xilinx_IDE/Vivado/2021.2/scripts/rt/data/unisim_comp.v2default:default2
10832default:default8@Z8-6155h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2%
clk_wiz_0_clk_wiz2default:default2
 2default:default2
42default:default2
12default:default2?
?d:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/test_miner_ton.gen/sources_1/ip/clk_wiz_0/clk_wiz_0_clk_wiz.v2default:default2
682default:default8@Z8-6155h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2
	clk_wiz_02default:default2
 2default:default2
52default:default2
12default:default2?
?d:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/test_miner_ton.gen/sources_1/ip/clk_wiz_0/clk_wiz_0.v2default:default2
702default:default8@Z8-6155h px? 
?
synthesizing module '%s'%s4497*oasys2$
cmd_packets_ctrl2default:default2
 2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/cmd_packets_ctrl.sv2default:default2
12default:default8@Z8-6157h px? 
?
synthesizing module '%s'%s4497*oasys2
	uart_rx_m2default:default2
 2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/uart_ctrl.sv2default:default2
262default:default8@Z8-6157h px? 
c
%s
*synth2K
7	Parameter CLKS_PER_BIT bound to: 100 - type: integer 
2default:defaulth p
x
? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2
	uart_rx_m2default:default2
 2default:default2
62default:default2
12default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/uart_ctrl.sv2default:default2
262default:default8@Z8-6155h px? 
?
synthesizing module '%s'%s4497*oasys2
crc322default:default2
 2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/crc32.sv2default:default2
232default:default8@Z8-6157h px? 
?
synthesizing module '%s'%s4497*oasys2
crc_func2default:default2
 2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/crc32.sv2default:default2
872default:default8@Z8-6157h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2
crc_func2default:default2
 2default:default2
72default:default2
12default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/crc32.sv2default:default2
872default:default8@Z8-6155h px? 
?
-case statement is not full and has no default155*oasys2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/crc32.sv2default:default2
562default:default8@Z8-155h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2
crc322default:default2
 2default:default2
82default:default2
12default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/crc32.sv2default:default2
232default:default8@Z8-6155h px? 
?
synthesizing module '%s'%s4497*oasys2
	uart_tx_m2default:default2
 2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/uart_ctrl.sv2default:default2
1802default:default8@Z8-6157h px? 
c
%s
*synth2K
7	Parameter CLKS_PER_BIT bound to: 100 - type: integer 
2default:defaulth p
x
? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2
	uart_tx_m2default:default2
 2default:default2
92default:default2
12default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/uart_ctrl.sv2default:default2
1802default:default8@Z8-6155h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2$
cmd_packets_ctrl2default:default2
 2default:default2
102default:default2
12default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/cmd_packets_ctrl.sv2default:default2
12default:default8@Z8-6155h px? 
?
synthesizing module '%s'%s4497*oasys2!
system_mcores2default:default2
 2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/system_mcores.sv2default:default2
22default:default8@Z8-6157h px? 
?
%s
*synth2?
?	Parameter CORES_QNT bound to: 256'b0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001 
2default:defaulth p
x
? 
?
synthesizing module '%s'%s4497*oasys2
mcore_2r2default:default2
 2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/mcore.sv2default:default2
22default:default8@Z8-6157h px? 
?
synthesizing module '%s'%s4497*oasys2$
data_constructor2default:default2
 2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/data_constructor.sv2default:default2
12default:default8@Z8-6157h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2$
data_constructor2default:default2
 2default:default2
112default:default2
12default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/data_constructor.sv2default:default2
12default:default8@Z8-6155h px? 
?
synthesizing module '%s'%s4497*oasys2
	sha256_2r2default:default2
 2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/sha256_orig.sv2default:default2
22default:default8@Z8-6157h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2
	sha256_2r2default:default2
 2default:default2
122default:default2
12default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/sha256_orig.sv2default:default2
22default:default8@Z8-6155h px? 
?
synthesizing module '%s'%s4497*oasys2
comp_h2default:default2
 2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/mcore.sv2default:default2
2612default:default8@Z8-6157h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2
comp_h2default:default2
 2default:default2
132default:default2
12default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/mcore.sv2default:default2
2612default:default8@Z8-6155h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2
mcore_2r2default:default2
 2default:default2
142default:default2
12default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/mcore.sv2default:default2
22default:default8@Z8-6155h px? 
?
synthesizing module '%s'%s4497*oasys2#
tasks_generator2default:default2
 2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/tasks_generator.sv2default:default2
22default:default8@Z8-6157h px? 
?
%s
*synth2?
?	Parameter CORES_QNT bound to: 256'b0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001 
2default:defaulth p
x
? 
?
-case statement is not full and has no default155*oasys2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/tasks_generator.sv2default:default2
1462default:default8@Z8-155h px? 
?
synthesizing module '%s'%s4497*oasys2
mcore_1r2default:default2
 2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/mcore.sv2default:default2
1402default:default8@Z8-6157h px? 
?
synthesizing module '%s'%s4497*oasys2
	sha256_1r2default:default2
 2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/sha256_orig.sv2default:default2
4962default:default8@Z8-6157h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2
	sha256_1r2default:default2
 2default:default2
152default:default2
12default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/sha256_orig.sv2default:default2
4962default:default8@Z8-6155h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2
mcore_1r2default:default2
 2default:default2
162default:default2
12default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/mcore.sv2default:default2
1402default:default8@Z8-6155h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2#
tasks_generator2default:default2
 2default:default2
172default:default2
12default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/tasks_generator.sv2default:default2
22default:default8@Z8-6155h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2!
system_mcores2default:default2
 2default:default2
182default:default2
12default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/system_mcores.sv2default:default2
22default:default8@Z8-6155h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2
t_d1_reg2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1182default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2
t_d2_reg2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1192default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2
t_op_reg[3]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1202default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2
t_op_reg[2]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1202default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2
t_op_reg[1]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1202default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2
t_op_reg[0]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1202default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2
t_flags_reg2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1212default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_expire_reg[3]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1222default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_expire_reg[2]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1222default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_expire_reg[1]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1222default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_expire_reg[0]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1222default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[31]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[30]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[29]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[28]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[27]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[26]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[25]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[24]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[23]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[22]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[21]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[20]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[19]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[18]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[17]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[16]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[15]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[14]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[13]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[12]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[11]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_myaddr_reg[10]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_myaddr_reg[9]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_myaddr_reg[8]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_myaddr_reg[7]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_myaddr_reg[6]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_myaddr_reg[5]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_myaddr_reg[4]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_myaddr_reg[3]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_myaddr_reg[2]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_myaddr_reg[1]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_myaddr_reg[0]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1232default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[31]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[30]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[29]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[28]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[27]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[26]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[25]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[24]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[23]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[22]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[21]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[20]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[19]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[18]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[17]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[16]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[15]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[14]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[13]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[12]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[11]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_1_reg[10]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_rdata_1_reg[9]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_rdata_1_reg[8]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_rdata_1_reg[7]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_rdata_1_reg[6]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_rdata_1_reg[5]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_rdata_1_reg[4]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_rdata_1_reg[3]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_rdata_1_reg[2]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_rdata_1_reg[1]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2$
t_rdata_1_reg[0]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1242default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_pseed_reg[15]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_pseed_reg[14]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_pseed_reg[13]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_pseed_reg[12]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_pseed_reg[11]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2#
t_pseed_reg[10]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2"
t_pseed_reg[9]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2"
t_pseed_reg[8]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2"
t_pseed_reg[7]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2"
t_pseed_reg[6]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2"
t_pseed_reg[5]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2"
t_pseed_reg[4]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2"
t_pseed_reg[3]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2"
t_pseed_reg[2]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2"
t_pseed_reg[1]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2"
t_pseed_reg[0]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1252default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_2_reg[31]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1262default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_2_reg[30]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1262default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_2_reg[29]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1262default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_2_reg[28]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1262default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_2_reg[27]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1262default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_2_reg[26]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1262default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_2_reg[25]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1262default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_2_reg[24]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1262default:default8@Z8-7137h px? 
?
?Register %s in module %s has both Set and reset with same priority. This may cause simulation mismatches. Consider rewriting code 
4878*oasys2%
t_rdata_2_reg[23]2default:default2
	top_level2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
1262default:default8@Z8-7137h px? 
?
?Message '%s' appears more than %s times and has been disabled. User can change this message limit to see more message instances.
14*common2 
Synth 8-71372default:default2
1002default:defaultZ17-14h px? 
?
'done synthesizing module '%s'%s (%s#%s)4495*oasys2
	top_level2default:default2
 2default:default2
192default:default2
12default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/sources_1/new/top_level.sv2default:default2
232default:default8@Z8-6155h px? 
?
%s*synth2?
yFinished RTL Elaboration : Time (s): cpu = 00:00:07 ; elapsed = 00:00:08 . Memory (MB): peak = 1719.816 ; gain = 127.301
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
M
%s
*synth25
!Start Handling Custom Attributes
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
?Finished Handling Custom Attributes : Time (s): cpu = 00:00:08 ; elapsed = 00:00:09 . Memory (MB): peak = 1719.816 ; gain = 127.301
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
?Finished RTL Optimization Phase 1 : Time (s): cpu = 00:00:08 ; elapsed = 00:00:09 . Memory (MB): peak = 1719.816 ; gain = 127.301
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2.
Netlist sorting complete. 2default:default2
00:00:002default:default2 
00:00:00.2042default:default2
1719.8162default:default2
0.0002default:defaultZ17-268h px? 
e
-Analyzing %s Unisim elements for replacement
17*netlist2
12default:defaultZ29-17h px? 
j
2Unisim Transformation completed in %s CPU seconds
28*netlist2
02default:defaultZ29-28h px? 
K
)Preparing netlist for logic optimization
349*projectZ1-570h px? 
>

Processing XDC Constraints
244*projectZ1-262h px? 
=
Initializing timing engine
348*projectZ1-569h px? 
?
$Parsing XDC File [%s] for cell '%s'
848*designutils2?
?d:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/test_miner_ton.gen/sources_1/ip/clk_wiz_0/clk_wiz_0_board.xdc2default:default2%
clk_wiz_0_/inst	2default:default8Z20-848h px? 
?
-Finished Parsing XDC File [%s] for cell '%s'
847*designutils2?
?d:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/test_miner_ton.gen/sources_1/ip/clk_wiz_0/clk_wiz_0_board.xdc2default:default2%
clk_wiz_0_/inst	2default:default8Z20-847h px? 
?
$Parsing XDC File [%s] for cell '%s'
848*designutils2?
?d:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/test_miner_ton.gen/sources_1/ip/clk_wiz_0/clk_wiz_0.xdc2default:default2%
clk_wiz_0_/inst	2default:default8Z20-848h px? 
?
-Finished Parsing XDC File [%s] for cell '%s'
847*designutils2?
?d:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/test_miner_ton.gen/sources_1/ip/clk_wiz_0/clk_wiz_0.xdc2default:default2%
clk_wiz_0_/inst	2default:default8Z20-847h px? 
?
?Implementation specific constraints were found while reading constraint file [%s]. These constraints will be ignored for synthesis but will be used in implementation. Impacted constraints are listed in the file [%s].
233*project2?
?d:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/test_miner_ton.gen/sources_1/ip/clk_wiz_0/clk_wiz_0.xdc2default:default2/
.Xil/top_level_propImpl.xdc2default:defaultZ1-236h px? 
8
Deriving generated clocks
2*timingZ38-2h px? 
?
Parsing XDC File [%s]
179*designutils2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/constrs_1/new/top_level_constraints.xdc2default:default8Z20-179h px? 
?
Finished Parsing XDC File [%s]
178*designutils2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/constrs_1/new/top_level_constraints.xdc2default:default8Z20-178h px? 
?
?Implementation specific constraints were found while reading constraint file [%s]. These constraints will be ignored for synthesis but will be used in implementation. Impacted constraints are listed in the file [%s].
233*project2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.srcs/constrs_1/new/top_level_constraints.xdc2default:default2/
.Xil/top_level_propImpl.xdc2default:defaultZ1-236h px? 
?
Parsing XDC File [%s]
179*designutils2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.runs/synth_1/dont_touch.xdc2default:default8Z20-179h px? 
?
Finished Parsing XDC File [%s]
178*designutils2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.runs/synth_1/dont_touch.xdc2default:default8Z20-178h px? 
?
?Implementation specific constraints were found while reading constraint file [%s]. These constraints will be ignored for synthesis but will be used in implementation. Impacted constraints are listed in the file [%s].
233*project2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.runs/synth_1/dont_touch.xdc2default:default2/
.Xil/top_level_propImpl.xdc2default:defaultZ1-236h px? 
H
&Completed Processing XDC Constraints

245*projectZ1-263h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2.
Netlist sorting complete. 2default:default2
00:00:002default:default2 
00:00:00.0022default:default2
1781.9302default:default2
0.0002default:defaultZ17-268h px? 
~
!Unisim Transformation Summary:
%s111*project29
%No Unisim elements were transformed.
2default:defaultZ1-111h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common24
 Constraint Validation Runtime : 2default:default2
00:00:002default:default2 
00:00:00.0522default:default2
1781.9302default:default2
0.0002default:defaultZ17-268h px? 
?
[Reference run did not run incremental synthesis because %s; reverting to default synthesis
2138*designutils2+
the design is too small2default:defaultZ20-4072h px? 
?
?Flow is switching to default flow due to incremental criteria not met. If you would like to alter this behaviour and have the flow terminate instead, please set the following parameter config_implementation {autoIncr.Synth.RejectBehavior Terminate}2229*designutilsZ20-4379h px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
Finished Constraint Validation : Time (s): cpu = 00:00:16 ; elapsed = 00:00:16 . Memory (MB): peak = 1781.930 ; gain = 189.414
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
V
%s
*synth2>
*Start Loading Part and Timing Information
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
K
%s
*synth23
Loading part: xc7k325tffg676-2
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
?Finished Loading Part and Timing Information : Time (s): cpu = 00:00:16 ; elapsed = 00:00:16 . Memory (MB): peak = 1781.930 ; gain = 189.414
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
Z
%s
*synth2B
.Start Applying 'set_property' XDC Constraints
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
?Finished applying 'set_property' XDC Constraints : Time (s): cpu = 00:00:16 ; elapsed = 00:00:16 . Memory (MB): peak = 1781.930 ; gain = 189.414
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
3inferred FSM for state register '%s' in module '%s'802*oasys2
	state_reg2default:default2
crc322default:defaultZ8-802h px? 
?
3inferred FSM for state register '%s' in module '%s'802*oasys2!
r_SM_Main_reg2default:default2
	uart_tx_m2default:defaultZ8-802h px? 
?
3inferred FSM for state register '%s' in module '%s'802*oasys2!
rec_state_reg2default:default2$
cmd_packets_ctrl2default:defaultZ8-802h px? 
?
3inferred FSM for state register '%s' in module '%s'802*oasys2!
trs_state_reg2default:default2$
cmd_packets_ctrl2default:defaultZ8-802h px? 
?
3inferred FSM for state register '%s' in module '%s'802*oasys2
	state_reg2default:default2
	sha256_2r2default:defaultZ8-802h px? 
?
3inferred FSM for state register '%s' in module '%s'802*oasys2
	state_reg2default:default2
	sha256_1r2default:defaultZ8-802h px? 
?
3inferred FSM for state register '%s' in module '%s'802*oasys2
	state_reg2default:default2#
tasks_generator2default:defaultZ8-802h px? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2t
`                   State |                     New Encoding |                Previous Encoding 
2default:defaulth p
x
? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2s
_              STATE_IDLE |                                0 |                               00
2default:defaulth p
x
? 
?
%s
*synth2s
_           STATE_COMPUTE |                                1 |                               01
2default:defaulth p
x
? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
Gencoded FSM with state register '%s' using encoding '%s' in module '%s'3353*oasys2
	state_reg2default:default2

sequential2default:default2
crc322default:defaultZ8-3354h px? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2t
`                   State |                     New Encoding |                Previous Encoding 
2default:defaulth p
x
? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2s
_                  s_IDLE |                              000 |                              000
2default:defaulth p
x
? 
?
%s
*synth2s
_          s_TX_START_BIT |                              001 |                              001
2default:defaulth p
x
? 
?
%s
*synth2s
_          s_TX_DATA_BITS |                              010 |                              010
2default:defaulth p
x
? 
?
%s
*synth2s
_           s_TX_STOP_BIT |                              011 |                              011
2default:defaulth p
x
? 
?
%s
*synth2s
_               s_CLEANUP |                              100 |                              100
2default:defaulth p
x
? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
Gencoded FSM with state register '%s' using encoding '%s' in module '%s'3353*oasys2!
r_SM_Main_reg2default:default2

sequential2default:default2
	uart_tx_m2default:defaultZ8-3354h px? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2t
`                   State |                     New Encoding |                Previous Encoding 
2default:defaulth p
x
? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2s
_          STATE_REC_IDLE |                               00 |                              000
2default:defaulth p
x
? 
?
%s
*synth2s
_           STATE_REC_GNB |                               01 |                              001
2default:defaulth p
x
? 
?
%s
*synth2s
_      STATE_REC_CL_CRC32 |                               10 |                              011
2default:defaulth p
x
? 
?
%s
*synth2s
_      STATE_REC_CH_CRC32 |                               11 |                              010
2default:defaulth p
x
? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
Gencoded FSM with state register '%s' using encoding '%s' in module '%s'3353*oasys2!
rec_state_reg2default:default2

sequential2default:default2$
cmd_packets_ctrl2default:defaultZ8-3354h px? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2t
`                   State |                     New Encoding |                Previous Encoding 
2default:defaulth p
x
? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2s
_          STATE_TRS_IDLE |                           000001 |                              000
2default:defaulth p
x
? 
?
%s
*synth2s
_      STATE_TRS_CL_CRC32 |                           000010 |                              001
2default:defaulth p
x
? 
?
%s
*synth2s
_      STATE_TRS_PH_CRC32 |                           000100 |                              011
2default:defaulth p
x
? 
?
%s
*synth2s
_           STATE_TRS_PHB |                           001000 |                              010
2default:defaulth p
x
? 
?
%s
*synth2s
_           STATE_TRS_WTB |                           010000 |                              110
2default:defaulth p
x
? 
?
%s
*synth2s
_        STATE_TRS_WT_SUP |                           100000 |                              100
2default:defaulth p
x
? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
Gencoded FSM with state register '%s' using encoding '%s' in module '%s'3353*oasys2!
trs_state_reg2default:default2
one-hot2default:default2$
cmd_packets_ctrl2default:defaultZ8-3354h px? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2t
`                   State |                     New Encoding |                Previous Encoding 
2default:defaulth p
x
? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2s
_                 S0_IDLE |                              000 |                            00000
2default:defaulth p
x
? 
?
%s
*synth2s
_                      S1 |                              001 |                            00001
2default:defaulth p
x
? 
?
%s
*synth2s
_                      S2 |                              010 |                            00011
2default:defaulth p
x
? 
?
%s
*synth2s
_                      S3 |                              011 |                            00010
2default:defaulth p
x
? 
?
%s
*synth2s
_                      S4 |                              100 |                            00110
2default:defaulth p
x
? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
Gencoded FSM with state register '%s' using encoding '%s' in module '%s'3353*oasys2
	state_reg2default:default2

sequential2default:default2
	sha256_2r2default:defaultZ8-3354h px? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2t
`                   State |                     New Encoding |                Previous Encoding 
2default:defaulth p
x
? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2s
_                 S0_IDLE |                              000 |                            00000
2default:defaulth p
x
? 
?
%s
*synth2s
_                      S1 |                              001 |                            00001
2default:defaulth p
x
? 
?
%s
*synth2s
_                      S2 |                              010 |                            00011
2default:defaulth p
x
? 
?
%s
*synth2s
_                      S3 |                              011 |                            00010
2default:defaulth p
x
? 
?
%s
*synth2s
_                      S4 |                              100 |                            00110
2default:defaulth p
x
? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
Gencoded FSM with state register '%s' using encoding '%s' in module '%s'3353*oasys2
	state_reg2default:default2

sequential2default:default2
	sha256_1r2default:defaultZ8-3354h px? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2t
`                   State |                     New Encoding |                Previous Encoding 
2default:defaulth p
x
? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2s
_                  iSTATE |                              000 |                              000
2default:defaulth p
x
? 
?
%s
*synth2s
_                 iSTATE0 |                              001 |                              001
2default:defaulth p
x
? 
?
%s
*synth2s
_                 iSTATE1 |                              010 |                              011
2default:defaulth p
x
? 
?
%s
*synth2s
_                 iSTATE3 |                              011 |                              110
2default:defaulth p
x
? 
?
%s
*synth2s
_                 iSTATE2 |                              100 |                              010
2default:defaulth p
x
? 
?
%s
*synth2x
d---------------------------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
Gencoded FSM with state register '%s' using encoding '%s' in module '%s'3353*oasys2
	state_reg2default:default2

sequential2default:default2#
tasks_generator2default:defaultZ8-3354h px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
?Finished RTL Optimization Phase 2 : Time (s): cpu = 00:00:20 ; elapsed = 00:00:20 . Memory (MB): peak = 1781.930 ; gain = 189.414
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
L
%s
*synth24
 Start RTL Component Statistics 
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
K
%s
*synth23
Detailed RTL Component Info : 
2default:defaulth p
x
? 
:
%s
*synth2"
+---Adders : 
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input  512 Bit       Adders := 2     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input   33 Bit       Adders := 1     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   4 Input   32 Bit       Adders := 8     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   3 Input   32 Bit       Adders := 2     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input   32 Bit       Adders := 23    
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input   17 Bit       Adders := 2     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input   16 Bit       Adders := 3     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input    8 Bit       Adders := 2     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input    7 Bit       Adders := 1     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input    6 Bit       Adders := 6     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input    3 Bit       Adders := 2     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input    1 Bit       Adders := 1     
2default:defaulth p
x
? 
8
%s
*synth2 
+---XORs : 
2default:defaulth p
x
? 
Z
%s
*synth2B
.	   3 Input     32 Bit         XORs := 16    
2default:defaulth p
x
? 
Z
%s
*synth2B
.	   2 Input     32 Bit         XORs := 6     
2default:defaulth p
x
? 
Z
%s
*synth2B
.	   2 Input      1 Bit         XORs := 30    
2default:defaulth p
x
? 
Z
%s
*synth2B
.	   3 Input      1 Bit         XORs := 16    
2default:defaulth p
x
? 
Z
%s
*synth2B
.	   4 Input      1 Bit         XORs := 14    
2default:defaulth p
x
? 
Z
%s
*synth2B
.	   5 Input      1 Bit         XORs := 16    
2default:defaulth p
x
? 
Z
%s
*synth2B
.	   6 Input      1 Bit         XORs := 12    
2default:defaulth p
x
? 
Z
%s
*synth2B
.	   7 Input      1 Bit         XORs := 8     
2default:defaulth p
x
? 
Z
%s
*synth2B
.	   9 Input      1 Bit         XORs := 6     
2default:defaulth p
x
? 
=
%s
*synth2%
+---Registers : 
2default:defaulth p
x
? 
Z
%s
*synth2B
.	              512 Bit    Registers := 1     
2default:defaulth p
x
? 
Z
%s
*synth2B
.	              256 Bit    Registers := 2     
2default:defaulth p
x
? 
Z
%s
*synth2B
.	               33 Bit    Registers := 1     
2default:defaulth p
x
? 
Z
%s
*synth2B
.	               32 Bit    Registers := 163   
2default:defaulth p
x
? 
Z
%s
*synth2B
.	               21 Bit    Registers := 1     
2default:defaulth p
x
? 
Z
%s
*synth2B
.	               17 Bit    Registers := 2     
2default:defaulth p
x
? 
Z
%s
*synth2B
.	               16 Bit    Registers := 5     
2default:defaulth p
x
? 
Z
%s
*synth2B
.	                8 Bit    Registers := 546   
2default:defaulth p
x
? 
Z
%s
*synth2B
.	                6 Bit    Registers := 5     
2default:defaulth p
x
? 
Z
%s
*synth2B
.	                3 Bit    Registers := 3     
2default:defaulth p
x
? 
Z
%s
*synth2B
.	                1 Bit    Registers := 25    
2default:defaulth p
x
? 
9
%s
*synth2!
+---Muxes : 
2default:defaulth p
x
? 
X
%s
*synth2@
,	   5 Input  512 Bit        Muxes := 1     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input   33 Bit        Muxes := 1     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   5 Input   32 Bit        Muxes := 74    
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input   32 Bit        Muxes := 21    
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input   17 Bit        Muxes := 1     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   4 Input   17 Bit        Muxes := 1     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   6 Input   17 Bit        Muxes := 1     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   5 Input   16 Bit        Muxes := 3     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input   16 Bit        Muxes := 1     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   6 Input   16 Bit        Muxes := 1     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   5 Input    8 Bit        Muxes := 2     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   6 Input    8 Bit        Muxes := 66    
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input    8 Bit        Muxes := 127   
2default:defaulth p
x
? 
X
%s
*synth2@
,	   4 Input    8 Bit        Muxes := 37    
2default:defaulth p
x
? 
X
%s
*synth2@
,	  11 Input    8 Bit        Muxes := 1     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   4 Input    6 Bit        Muxes := 3     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   6 Input    6 Bit        Muxes := 3     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input    6 Bit        Muxes := 2     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   5 Input    3 Bit        Muxes := 4     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input    3 Bit        Muxes := 13    
2default:defaulth p
x
? 
X
%s
*synth2@
,	   8 Input    3 Bit        Muxes := 1     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   6 Input    3 Bit        Muxes := 1     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input    2 Bit        Muxes := 2     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   3 Input    2 Bit        Muxes := 1     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   4 Input    2 Bit        Muxes := 5     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   2 Input    1 Bit        Muxes := 288   
2default:defaulth p
x
? 
X
%s
*synth2@
,	   5 Input    1 Bit        Muxes := 208   
2default:defaulth p
x
? 
X
%s
*synth2@
,	   3 Input    1 Bit        Muxes := 1     
2default:defaulth p
x
? 
X
%s
*synth2@
,	   6 Input    1 Bit        Muxes := 77    
2default:defaulth p
x
? 
X
%s
*synth2@
,	   4 Input    1 Bit        Muxes := 90    
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
O
%s
*synth27
#Finished RTL Component Statistics 
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
H
%s
*synth20
Start Part Resource Summary
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2m
YPart Resources:
DSPs: 840 (col length:140)
BRAMs: 890 (col length: RAMB18 140 RAMB36 70)
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
K
%s
*synth23
Finished Part Resource Summary
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
W
%s
*synth2?
+Start Cross Boundary and Area Optimization
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
H
&Parallel synthesis criteria is not met4829*oasysZ8-7080h px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
?Finished Cross Boundary and Area Optimization : Time (s): cpu = 00:01:36 ; elapsed = 00:01:37 . Memory (MB): peak = 1842.016 ; gain = 249.500
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
?---------------------------------------------------------------------------------
Start ROM, RAM, DSP, Shift Register and Retiming Reporting
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
M
%s*synth25
!
ROM: Preliminary Mapping Report
2default:defaulth px? 
i
%s*synth2Q
=+------------+------------+---------------+----------------+
2default:defaulth px? 
j
%s*synth2R
>|Module Name | RTL Object | Depth x Width | Implemented As | 
2default:defaulth px? 
i
%s*synth2Q
=+------------+------------+---------------+----------------+
2default:defaulth px? 
j
%s*synth2R
>|sha256_2r   | K          | 64x32         | LUT            | 
2default:defaulth px? 
j
%s*synth2R
>|sha256_1r   | K          | 64x32         | LUT            | 
2default:defaulth px? 
j
%s*synth2R
>|sha256_1r   | K          | 64x32         | LUT            | 
2default:defaulth px? 
j
%s*synth2R
>|sha256_2r   | K          | 64x32         | LUT            | 
2default:defaulth px? 
j
%s*synth2R
>+------------+------------+---------------+----------------+

2default:defaulth px? 
?
%s*synth2?
?---------------------------------------------------------------------------------
Finished ROM, RAM, DSP, Shift Register and Retiming Reporting
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
R
%s
*synth2:
&Start Applying XDC Timing Constraints
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
?Finished Applying XDC Timing Constraints : Time (s): cpu = 00:01:40 ; elapsed = 00:01:41 . Memory (MB): peak = 1842.016 ; gain = 249.500
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
F
%s
*synth2.
Start Timing Optimization
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
}Finished Timing Optimization : Time (s): cpu = 00:01:47 ; elapsed = 00:01:48 . Memory (MB): peak = 1927.473 ; gain = 334.957
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
E
%s
*synth2-
Start Technology Mapping
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
|Finished Technology Mapping : Time (s): cpu = 00:01:53 ; elapsed = 00:01:54 . Memory (MB): peak = 1927.473 ; gain = 334.957
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s
*synth2'
Start IO Insertion
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
Q
%s
*synth29
%Start Flattening Before IO Insertion
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
T
%s
*synth2<
(Finished Flattening Before IO Insertion
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
H
%s
*synth20
Start Final Netlist Cleanup
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
K
%s
*synth23
Finished Final Netlist Cleanup
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
vFinished IO Insertion : Time (s): cpu = 00:01:57 ; elapsed = 00:01:58 . Memory (MB): peak = 1927.473 ; gain = 334.957
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
O
%s
*synth27
#Start Renaming Generated Instances
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
?Finished Renaming Generated Instances : Time (s): cpu = 00:01:57 ; elapsed = 00:01:58 . Memory (MB): peak = 1927.473 ; gain = 334.957
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
L
%s
*synth24
 Start Rebuilding User Hierarchy
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
?Finished Rebuilding User Hierarchy : Time (s): cpu = 00:01:59 ; elapsed = 00:02:00 . Memory (MB): peak = 1927.473 ; gain = 334.957
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
K
%s
*synth23
Start Renaming Generated Ports
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
?Finished Renaming Generated Ports : Time (s): cpu = 00:01:59 ; elapsed = 00:02:00 . Memory (MB): peak = 1927.473 ; gain = 334.957
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
M
%s
*synth25
!Start Handling Custom Attributes
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
?Finished Handling Custom Attributes : Time (s): cpu = 00:02:00 ; elapsed = 00:02:01 . Memory (MB): peak = 1927.473 ; gain = 334.957
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
J
%s
*synth22
Start Renaming Generated Nets
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
?Finished Renaming Generated Nets : Time (s): cpu = 00:02:00 ; elapsed = 00:02:01 . Memory (MB): peak = 1927.473 ; gain = 334.957
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
K
%s
*synth23
Start Writing Synthesis Report
2default:defaulth p
x
? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
A
%s
*synth2)

Report BlackBoxes: 
2default:defaulth p
x
? 
J
%s
*synth22
+-+--------------+----------+
2default:defaulth p
x
? 
J
%s
*synth22
| |BlackBox name |Instances |
2default:defaulth p
x
? 
J
%s
*synth22
+-+--------------+----------+
2default:defaulth p
x
? 
J
%s
*synth22
+-+--------------+----------+
2default:defaulth p
x
? 
A
%s*synth2)

Report Cell Usage: 
2default:defaulth px? 
G
%s*synth2/
+------+----------+------+
2default:defaulth px? 
G
%s*synth2/
|      |Cell      |Count |
2default:defaulth px? 
G
%s*synth2/
+------+----------+------+
2default:defaulth px? 
G
%s*synth2/
|1     |BUFG      |     2|
2default:defaulth px? 
G
%s*synth2/
|2     |CARRY4    |   688|
2default:defaulth px? 
G
%s*synth2/
|3     |LUT1      |     1|
2default:defaulth px? 
G
%s*synth2/
|4     |LUT2      |  2095|
2default:defaulth px? 
G
%s*synth2/
|5     |LUT3      |  2187|
2default:defaulth px? 
G
%s*synth2/
|6     |LUT4      |  1554|
2default:defaulth px? 
G
%s*synth2/
|7     |LUT5      |  1084|
2default:defaulth px? 
G
%s*synth2/
|8     |LUT6      |  5888|
2default:defaulth px? 
G
%s*synth2/
|9     |MUXF7     |  2059|
2default:defaulth px? 
G
%s*synth2/
|10    |MUXF8     |   704|
2default:defaulth px? 
G
%s*synth2/
|11    |PLLE2_ADV |     1|
2default:defaulth px? 
G
%s*synth2/
|12    |FDCE      |  8768|
2default:defaulth px? 
G
%s*synth2/
|13    |FDPE      |    70|
2default:defaulth px? 
G
%s*synth2/
|14    |FDRE      |  1240|
2default:defaulth px? 
G
%s*synth2/
|15    |IBUF      |     3|
2default:defaulth px? 
G
%s*synth2/
|16    |OBUF      |     2|
2default:defaulth px? 
G
%s*synth2/
+------+----------+------+
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
?
%s*synth2?
?Finished Writing Synthesis Report : Time (s): cpu = 00:02:00 ; elapsed = 00:02:01 . Memory (MB): peak = 1927.473 ; gain = 334.957
2default:defaulth px? 
~
%s
*synth2f
R---------------------------------------------------------------------------------
2default:defaulth p
x
? 
r
%s
*synth2Z
FSynthesis finished with 0 errors, 0 critical warnings and 1 warnings.
2default:defaulth p
x
? 
?
%s
*synth2?
Synthesis Optimization Runtime : Time (s): cpu = 00:01:47 ; elapsed = 00:01:57 . Memory (MB): peak = 1927.473 ; gain = 272.844
2default:defaulth p
x
? 
?
%s
*synth2?
?Synthesis Optimization Complete : Time (s): cpu = 00:02:00 ; elapsed = 00:02:01 . Memory (MB): peak = 1927.473 ; gain = 334.957
2default:defaulth p
x
? 
B
 Translating synthesized netlist
350*projectZ1-571h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2.
Netlist sorting complete. 2default:default2
00:00:012default:default2 
00:00:00.2522default:default2
1927.4732default:default2
0.0002default:defaultZ17-268h px? 
h
-Analyzing %s Unisim elements for replacement
17*netlist2
34522default:defaultZ29-17h px? 
j
2Unisim Transformation completed in %s CPU seconds
28*netlist2
02default:defaultZ29-28h px? 
K
)Preparing netlist for logic optimization
349*projectZ1-570h px? 
u
)Pushed %s inverter(s) to %s load pin(s).
98*opt2
02default:default2
02default:defaultZ31-138h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2.
Netlist sorting complete. 2default:default2
00:00:002default:default2 
00:00:00.0022default:default2
1927.4732default:default2
0.0002default:defaultZ17-268h px? 
~
!Unisim Transformation Summary:
%s111*project29
%No Unisim elements were transformed.
2default:defaultZ1-111h px? 
g
$Synth Design complete, checksum: %s
562*	vivadotcl2
d8287b9b2default:defaultZ4-1430h px? 
U
Releasing license: %s
83*common2
	Synthesis2default:defaultZ17-83h px? 
?
G%s Infos, %s Warnings, %s Critical Warnings and %s Errors encountered.
28*	vivadotcl2
792default:default2
1032default:default2
02default:default2
02default:defaultZ4-41h px? 
^
%s completed successfully
29*	vivadotcl2 
synth_design2default:defaultZ4-42h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2"
synth_design: 2default:default2
00:02:072default:default2
00:02:082default:default2
1927.4732default:default2
334.9572default:defaultZ17-268h px? 
?
 The %s '%s' has been generated.
621*common2

checkpoint2default:default2?
?D:/pow-miner-fpga/TON-pow-miner-fpga-verilog/kintex_7_325t_vivado_project/fpga_miner_ton/fpga_miner_ton.runs/synth_1/top_level.dcp2default:defaultZ17-1381h px? 
?
%s4*runtcl2|
hExecuting : report_utilization -file top_level_utilization_synth.rpt -pb top_level_utilization_synth.pb
2default:defaulth px? 
?
Exiting %s at %s...
206*common2
Vivado2default:default2,
Mon Jun 27 15:09:57 20222default:defaultZ17-206h px? 


End Record