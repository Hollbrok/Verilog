`include "SR_latch.v"

module D_latch (
	input D, input E, output Q, output Qbar
);

wire Dbar = ~D;
and(R, Dbar, E);
and(S, D, E);

SR_latch SRr_latch(.S(S), .R(R), .Q(Q), .Qbar(Qbar));

	
endmodule