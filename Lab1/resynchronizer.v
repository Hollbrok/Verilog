module resynchronizer 
(
    input wire clka,
    input wire clkb,

    input wire [15:0] data_input,
    input wire asend,

    //input wire aready,
    output reg [15:0] bout
);

    reg [2:0] aenable;
    reg [2:0] ack;

    reg [15:0] aData;
    reg [15:0] bData;
	
	reg aready;
	
// Initialization
    initial begin
        aenable = 3'b0;
        ack     = 3'b0;
        aready  = 1;

        aData   = 16'b0;
        bData   = 16'b0;
        bout    = 16'b0;
		  aready  = 0;
    end
    
// Releazing aenable [2] with shifting (with clkb)
    always @(posedge clkb)
    begin
        aenable[0] <= aenable[1];
    end
    always @(posedge clkb)
    begin
        aenable[1] <= aenable[2];
    end

// Releasing ack [2] with shifting (with clka)
    always @(posedge clka)
    begin
        ack[0] <= ack[1];
    end
    always @(posedge clka)
    begin
        ack[1] <= ack[2];
    end

////////////////////////////////////////////////////////////
    always @(clka)
    begin
        if (aready && asend)
            aData <= data_input;
    end
    
    always @(posedge clkb) 
    begin 
        if (~ack[2] && aenable[0])
            bData <= aData;
    end

    always @(clka)
    begin
        if (aready && asend)
            aready <= 0;
        else if (~ack[0] && ~aenable[2])
            aready <= 1;
    end
    
    always @(clka)
    begin
        if (aready && asend)
            aenable[2] <= 1;
        else if (ack[0])
            aenable[2] <= 0;
    end

    always @(posedge clkb)
    begin
        if (aenable[0] && ~ack[2])
            ack[2] <= 1;
        else if (~aenable[0] && ack[2])
            ack[2] <= 0;
    end

    always @(posedge clkb)
    begin
        bout <= bData;
    end

endmodule