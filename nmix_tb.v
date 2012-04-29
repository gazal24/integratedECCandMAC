`timescale 1ns / 1ps

module nmix_tb;
   reg [31:0]  X,R;
   wire [31:0] Y;

   reg 	       clk;
   reg 	       reset;
   reg [4:0]   counter;

   initial begin
      clk = 0;
      counter = 0;
      X = 1024 * 1024 + 2378923475;
      R = 84765823;

      // Following RESET code should be last to be executed in this INITIAL block
      reset = 0;
      #1 reset = 1;
      #1 reset = 0;
   end
   
   nmix uut(.X(X), .R(R), .Y(Y), .clk(clk), .reset(reset));
   
   always begin
      #1 clk = ~clk; 
      // $monitor("X=%b,\nR=%b,\nY=%b,",X,R,XY);
   end
   
endmodule // nmix_tb
