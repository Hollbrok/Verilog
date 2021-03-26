module clkdiv #(parameter X = 21)
(
	input wire clk, 
	output wire clkdiv
);

reg [X - 1:0]cnt = 0;
assign clkdiv = cnt[X - 1];

always @(posedge clk)
begin
	cnt <= (cnt === {X{1'b1}}) ? 0 : cnt + 1;
end

endmodule