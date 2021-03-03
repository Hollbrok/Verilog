module cnthex( input wire clk, output reg [15:0]hex);

always @(posedge clk)
begin
	hex <= (hex === 16'hffff) ? 16'h0 : hex + 16'h1;
end

endmodule