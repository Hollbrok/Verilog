module clkdiv10(
	input wire clk, 
	//input reg counter,
	output wire clkdiv
	);

reg [11:0]cnt = 0;
assign clkdiv = cnt[11];

always @(posedge clk)
begin
	cnt <= (cnt === {12{1'b1}}) ? 12'h0 : cnt + 12'h1;
end

endmodule