module clkdiv(
	input wire clk, 
	//input reg counter,
	output wire clkdiv
	);

reg [22:0]cnt;
assign clkdiv = cnt[22];

always @(posedge clk)
begin
	cnt <= (cnt === {23{1'b1}}) ? 23'h0 : cnt + 23'h1;
end

endmodule