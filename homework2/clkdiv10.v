module clkdiv10(
	input wire clk, 
	//input reg counter,
	output wire clkdiv
	);

reg [10:0]cnt;
assign clkdiv = cnt[10];

always @(posedge clk)
begin
	cnt <= (cnt === {11{1'b1}}) ? 11'h0 : cnt + 11'h1;
end

endmodule