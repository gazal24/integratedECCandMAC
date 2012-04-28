`timescale 1ns / 1ps

module nmix (X, R, Y, XY,clk, reset, dirty);
   input  [31:0] X, R;
   output [31:0] Y;
   input 	 clk,reset;
   output 	 dirty;
   output [31:0] XY;
   
   reg [31:0] 	 XY;
   reg [31:0] 	 Y;
   reg [5:0] 	 i;
   reg [5:0] 	 j;
   reg 		 dirty;

   always @(posedge clk) begin

      if(reset) begin
	 $display("im in reset");
	 i <= 1;
	 j <= 0;
	 dirty <= 1;
      end else if(dirty == 1) begin
	 if(j == 0) begin //initialize
	    Y[i] = (X[0]&R[0]) ^ (R[i] & R[i]) ^ (X[i] & X[i]);
	    j <= 1;
	    $display("hey i was in Initialization ALSO %b with i=%b", Y,i);
	 end else if(j == i) begin // termination
	    i = i+1;
	    j <= 0;
	    if(i == 31) begin
	       dirty = 0;
	    end
	 end else begin // main code
	    $display("hey now the main code with j=%b", j);
	    Y[i] = Y[i] ^ (X[j]&R[j]);
	    j = j+1;
	 end
      end // if (dirty == 1)
   end // always @ (posedge clk)

endmodule // nmix
