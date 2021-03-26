module clk_div #(parameter X = 12)
(
	input clkIn,

	output clkOut
);

reg [X - 1 : 0]cnt = 0;

assign clkOut = cnt[X - 1];

always @(posedge clkIn) begin
    cnt <= cnt + 1;
end

endmodule