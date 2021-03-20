module rom_fetcher(
    input clk,

    output [15:0]q
);

reg [7:0]pc = 0;
wire [7:0]pc_next = pc + 1;

rom #(.WIDTH(16)) rom(.clk(clk), .addr(pc), .q(q));

always @(posedge clk) begin
    pc <= pc_next;
end

endmodule