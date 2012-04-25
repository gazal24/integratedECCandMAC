// module xora (a,b,x,clock);
//    input  a, b,clock;
//    output wire [31:0] x;
   
// //   always @ (posedge clock) begin
// //      x = a || b;
// //   end

//    assign x[0] = a || b;
// endmodule // xora

// module xora_tb;
//    reg a,b,clock;
//    wire [31:0] c;
//    initial begin
//       $monitor ("a=%b, b=%b, c=%b, time=%d", a,b,c,$time);
//       #5 a = 1;
//       #5 b = 1;
//       #5 clock = 1;
//       $finish;
//    end

//    xora x0 ( .a(a), .b(b), .x(c), .clock(clock));
//    //xora x0 (a,b,c);
   
// endmodule // xora_tb


module add_bits (X, R, Y, clk, reset, dirty);
   input  [31:0] X, R;
   output [31:0] Y;
   input 	 clk,reset;
   output 	 dirty;
   
   reg [31:0] 	 Y;
   reg [5:0] 	 i;
   reg [5:0] 	 j;
   reg 		 dirty;
   
   always @(posedge clk) begin
      //	$display("meh");
      if(reset) begin
	 i = 0;
	 dirty = 1;
      end
      else begin
	 if(dirty) begin
	    if(j==0) begin //initialize
	       Y[i] = (X[0]&R[0]) ^ (R[i] & R[i-1]) ^ (X[i] & X[i-1]);
	       j = 1;
	    end
	    else begin
	       if(j == i) begin // termination
		  i = i + 1;
		  j = 0;
		  if(i == 32) begin
		     dirty = 0;
		  end
	       end
	       else begin // main code
		  Y[i] = Y[i] ^ X[j]&R[j];
		  j = j+1;
	       end
	    end // else: !if(j==0)
	 end // if (dirty)
      end // else: !if(reset)
   end // always (posedge clk or posedge reset)
endmodule // adder

module DFF();
   reg clk,reset,preset,d;
   reg q;
   
   always @ (posedge clk)
     if (reset) begin
	q <= 0;
     end else if (preset) begin
	q <= 1;
     end else begin
	q <= d;
     end
endmodule // DFF


module add_bits_tb;
   reg  [31:0] X,R;
   wire [31:0] Y;
   reg [4:0]   counter;
   reg 	       clk;

   initial 
     begin
	X = 1024 * 1024 + 2378923475;
	R = 84765823;
	counter = 0;
     end

   add_bits A1(.X(X), .R(R), .Y(Y), .clk(clk));
   
   always 
     begin
	//$display("meh");
	#1 clk = ~clk; 
     end

   always @(posedge clk)
     begin
	counter = counter + 1;
	if(counter == 2)
	  begin
	     $display("meh");
	     $monitor("X=%b,\nR=%b,\nY=%b,",X,R,Y);
	  end
     end
   
endmodule // add_tb