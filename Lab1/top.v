module top(
    input CLK,
	 output DS_EN1, DS_EN2, DS_EN3, DS_EN4,
	 output DS_A, DS_B, DS_C, DS_D, DS_E, DS_F, DS_G
);

//assign {DS_EN1, DS_EN2, DS_EN3, DS_EN4} = 4'b0011;

//wire clkdiv1;
//wire clkdiv2;

wire [6:0]seg_1;
wire [6:0]seg_2;
wire [6:0]seg_3;
wire [6:0]seg_4;

//clkdiv #(.X(24)) clkdiv_counter( .clk(CLK), .clkdiv(clkdiv1));
//cnthex Cnthex1( .clk(clkdiv1), .hex(hex));

//clkdiv #(.X(10)) Clkdiv_update( .clk(CLK), .clkdiv(clkdiv2));

wire clk_counter;
wire clk_updater;
wire clk_sendler;
wire clkA;
wire clkB;

clkdiv #(21)     Counter( .clk(CLK), .clkdiv(clk_counter)); 
clkdiv #(16)     Updater( .clk(CLK), .clkdiv(clk_updater)); 
clkdiv #(17) 	  Sendler( .clk(CLK), .clkdiv(clk_sendler));  
clkdiv #(21)     Clk_a  ( .clk(CLK), .clkdiv(clka));           
clkdiv #(21)     Clk_b  ( .clk(CLK), .clkdiv(clkb));           





always @(posedge clk_counter) begin                   
	grey_address <= grey_address + 1;	
end 
	 
wire [15:0]grey_num;
reg [3:0]grey_address = 0;
	 
rom grey_data(.clock(clk_counter), .address(grey_address), .q(grey_num));

wire [15:0] new_num;
//reg aready;

//resynchronizer clkdmncrossing( .clka(clkA), .clkb(clkB),
//                                   .data_input(grey_num), .asend(clk_sendler), .bout(new_num));
	
wire clk;
crossing pll_inst(.inclk0(CLK), .c0(clk));
wire [15:0] data;
cpu_top cpu_top(.clk(clk), .data_out(data)); 
	
hex2seg Hex2seg1( .hex(data[3:0]),   .seg(seg_1));
hex2seg Hex2seg2( .hex(data[7:4]),   .seg(seg_2));
hex2seg Hex2seg3( .hex(data[11:8]),  .seg(seg_3));
hex2seg Hex2seg4( .hex(data[15:12]), .seg(seg_4));

wire [6:0]seg;
wire [3:0]segen;

shownumber Shownumber1( .clk10(clk_updater), .seg1(seg_1), .seg2(seg_2), .seg3(seg_3), .seg4(seg_4), .seg(seg), .segen(segen));

assign {DS_EN1, DS_EN2, DS_EN3, DS_EN4} = segen;
assign {DS_A, DS_B, DS_C, DS_D, DS_E, DS_F, DS_G} = seg;


endmodule
