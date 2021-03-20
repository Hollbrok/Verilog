module rom #(parameter LENGTH = 16, parameter WIDTH = 32)
(
	input [WIDTH - 1:0]address,
	input clk,
	
	output reg [WIDTH - 1:0]number
);

reg [WIDTH - 1:0]mem[LENGTH - 1:0];

initial begin
    $readmemh("number.txt", mem);
end

always @(posedge clk) begin
    number <= mem[address];
end

endmodule