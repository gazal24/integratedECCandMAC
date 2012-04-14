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


module add_bits (a, b, c);
   input [31:0] a, b;
   output [31:0] c;
   assign c = a & b;
endmodule // adder

module add_tb;
   reg [31:0] X,R;
   wire [31:0] Y;
   initial begin
      $monitor("X=%b,\nR=%b,\nY=%b,",X,R,Y);
      X = 1024 * 1024 + 2378923475;
      R = 84765823;
      $finish;
   end
   adder A1(.a(X), .b(R), .c(Y));
endmodule // add_tb
