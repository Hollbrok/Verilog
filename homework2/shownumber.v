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

always @(posedge clk10)
begin
	flag <= flag + 1'b1;
	if(flag === 2'b11)
		begin
			seg   = seg4;
			segen = 4'b0111;
		end 
	else if(flag === 2'b10) 
		begin
			seg   = seg3;
			segen = 4'b1011;
		end 
	else if(flag === 2'b01) 
		begin
			seg   = seg2;
			segen = 4'b1101;
		end 
	else if(flag === 2'b00) 
	begin	
		seg   = seg1;
		segen = 4'b1110;
	end
end

endmodule