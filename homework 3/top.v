module top(
    input CLK,
	 output DS_EN1, DS_EN2, DS_EN3, DS_EN4,
	 output DS_A, DS_B, DS_C, DS_D, DS_E, DS_F, DS_G
);

//assign {DS_EN1, DS_EN2, DS_EN3, DS_EN4} = 4'b0011;

wire clkdiv1;
wire clkdiv10;

wire [15:0]grey_num;
reg [3:0]grey_address = 0;

wire [6:0]seg_1;
wire [6:0]seg_2;
wire [6:0]seg_3;
wire [6:0]seg_4;

clkdiv #(.X(24)) clkdiv_counter( .clk(CLK), .clkdiv(clkdiv1));
//cnthex Cnthex1( .clk(clkdiv1), .hex(hex));

clkdiv #(.X(10)) Clkdiv_update( .clk(CLK), .clkdiv(clkdiv10));

always @(posedge clkdiv1) begin                   
	grey_address <= grey_address + 1;      
end
	 
rom grey_data(.clock(clkdiv1), .address(grey_address), .q(grey_num));


hex2seg Hex2seg1( .hex(grey_num[3:0]),   .seg(seg_1));
hex2seg Hex2seg2( .hex(grey_num[7:4]),   .seg(seg_2));
hex2seg Hex2seg3( .hex(grey_num[11:8]),  .seg(seg_3));
hex2seg Hex2seg4( .hex(grey_num[15:12]), .seg(seg_4));

wire [6:0]seg;
wire [3:0]segen;

shownumber Shownumber1( .clk10(clkdiv10), .seg1(seg_1), .seg2(seg_2), .seg3(seg_3), .seg4(seg_4), .seg(seg), .segen(segen));

assign {DS_EN1, DS_EN2, DS_EN3, DS_EN4} = segen;
assign {DS_A, DS_B, DS_C, DS_D, DS_E, DS_F, DS_G} = seg;


endmodule
