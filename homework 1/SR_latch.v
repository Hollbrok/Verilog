module SR_latch (
	input S, input R, output Q, output Qbar
);

assign Q = ~ (R | Qbar);
assign Qbar = ~ (S | Q);
//nor(Q, R, Qbar);
//nor(Qbar, S, Q);
	
endmodule