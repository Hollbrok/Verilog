module shownumber( 
	input wire clk10,
	input wire [6:0]seg1,
	input wire [6:0]seg2,
	input wire [6:0]seg3,
	input wire [6:0]seg4,
	output reg [6:0]seg = 0,
	output reg [3:0]segen = 0
);

reg [1:0]flag = 0;

always @(posedge clk10) begin
	flag <= flag + 1'b1;
end

always @(*) begin
    case (flag)

        2'b00: segen  = 4'b1110;
        2'b01: segen  = 4'b1101;
        2'b10: segen  = 4'b1011;
        2'b11: segen  = 4'b0111;

    endcase
end

always @(*) begin
    case (flag)

        2'b00: seg = seg1;
        2'b01: seg = seg2;
        2'b10: seg = seg3;
        2'b11: seg = seg4;
        
    endcase
end



endmodule