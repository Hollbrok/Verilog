`include "D_latch.v"

module D_flipflop (
	input D, input E, output Q, output Qbar
);

wire Ebar = ~E;
//D_latch D_latch(.D(D), .E(Ebar), .Q(Q), .Qbar(Qbar));
wire Q2;
wire useless;
D_latch D1(.D(D), .E(Ebar), .Q(Q2), .Qbar(useless));
D_latch D2(.D(Q2), .E(E), .Q(Q), .Qbar(Qbar));
	
endmodule