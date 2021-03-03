`timescale 1 ns / 100 ps

module testbench(); /* No inputs, no outputs */

reg D = 1'b1; /* Represents clock, initial value is 0 */
reg E = 1'b0; /* Represents clock, initial value is 1 */

always begin
    #1.34 D = ~D; /* Toggle clock every 1ns */
end

always begin
    #2 E = ~E; /* Toggle clock every 2ns */
end

wire Q; /* For output of tested module */
wire Qbar;

D_flipflop  D_flipflop(.D(D), .E(E), .Q(Q), .Qbar(Qbar)); /* Tested module instance */

initial begin
    $dumpvars;      /* Open for dump of signals */
    $display("Test started...");   /* Write to console */
    #20 $finish;    /* Stop simulation after 10ns */
end

endmodule