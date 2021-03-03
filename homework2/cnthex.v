module cnthex( 
					input clk, 
					output reg [15:0]hex = 0
);

always @(posedge clk) begin
	hex <= hex + 16'b1;
end

endmodule