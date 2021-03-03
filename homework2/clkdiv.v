module clkdiv(
	input wire clk, 
	output wire clkdiv
	);

reg [20:0]cnt = 0;
assign clkdiv = cnt[20];

always @(posedge clk)
begin
	cnt <= (cnt === {21{1'b1}}) ? 21'h0 : cnt + 21'h1;
end

endmodule