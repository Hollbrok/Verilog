module top(
    input CLK,
	 output DS_EN1, DS_EN2, DS_EN3, DS_EN4,
	 output DS_A, DS_B, DS_C, DS_D, DS_E, DS_F, DS_G
);

//assign {DS_EN1, DS_EN2, DS_EN3, DS_EN4} = 4'b0011;

wire clkdiv1;
wire clkdiv10;

wire [15:0]hex;

wire [6:0]seg_1;
wire [6:0]seg_2;
wire [6:0]seg_3;
wire [6:0]seg_4;

clkdiv Clkdiv1( .clk(CLK), .clkdiv(clkdiv1));
cnthex Cnthex1( .clk(clkdiv1), .hex(hex));

clkdiv10 Clkdiv10( .clk(CLK), .clkdiv(clkdiv10));

hex2seg Hex2seg1( .hex(hex[3:0]), .seg(seg_1));
hex2seg Hex2seg2( .hex(hex[7:4]), .seg(seg_2));
hex2seg Hex2seg3( .hex(hex[11:8]), .seg(seg_3));
hex2seg Hex2seg4( .hex(hex[15:12]), .seg(seg_4));

wire [6:0]seg;
wire [3:0]segen;
shownumber Shownumber1( .clk10(clkdiv10), .seg1(seg_1), .seg2(seg_2), .seg3(seg_3), .seg4(seg_4), .seg(seg), .segen(segen));

assign {DS_EN1, DS_EN2, DS_EN3, DS_EN4} = segen;
assign {DS_A, DS_B, DS_C, DS_D, DS_E, DS_F, DS_G} = seg;


endmodule
