module ca_tb();
   reg clk,reset,preset,d;
   wire q;

   dff uud(.clk(clk),.reset(reset),.preset(preset),.d(d), .q(q));
   initial begin
      $monitor("CLK = %b RESET = %b PRESET = %b D = %b Q = %b", clk,reset,preset,d,q);
      clk = 0;
      #1 reset  = 0;
      preset = 0;
      d = 0;
      #1 reset = 1;
      #2 reset = 0;
      #2 preset = 1;
      #2 preset = 0;
      #20 $finish;
      
   end
   
   always begin
      #1 clk = ~clk;
   end
   always begin
     #1 d = ~d;
   end
endmodule