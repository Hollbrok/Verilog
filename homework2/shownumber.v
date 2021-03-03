module shownumber( 
	input wire clk10,
	
	input wire [6:0]seg1,
	input wire [6:0]seg2,
	input wire [6:0]seg3,
	input wire [6:0]seg4,
	
	output reg [6:0]seg,
	output reg [3:0]segen
);

reg [1:0]flag;

always @(posedge clk10) begin
	flag <= (flag === 2'b11) ? 2'b0 : flag + 2'b1;
	if(flag === 2'b11) begin
		seg <= seg4;
		segen <= 4'b0111;
	end else if(flag === 2'b10) begin
		seg <= seg3;
		segen <= 4'b1011;
	end else if(flag === 2'b01) begin
		seg <= seg2;
		segen <= 4'b1101;
	end else begin
		seg <= seg1;
		segen <= 4'b1110;
	end
	
end

endmodule