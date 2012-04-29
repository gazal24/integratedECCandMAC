module dff(clk,reset,preset,d, q);
   input clk,reset,preset,d;
   output q;
   
   wire   clk,reset,preset,d;
   reg 	  q;
   
   always @ (posedge clk)
     if (reset) begin
	q <= 0;
     end else if (preset) begin
	q <= 1;
     end else begin
	q <= d;
     end
   
endmodule // dff_sync_reset_sync_preset


module ca_tb();
   reg clk,reset,preset,d;
   wire q;

   dff uud(.clk(clk),.reset(reset),.preset(preset),.d(d), .q(q));
   initial begin
      $monitor("CLK = %b RESET = %b PRESET = %b D = %b Q = %b", clk,reset,preset,d,q);
      clk = 0;
      #1 reset  = 0;
      preset = 0;
      d = 1;
      #1 reset = 1;
      #2 reset = 0;
      #2 preset = 1;
      #2 preset = 0;
/* -----\/----- EXCLUDED -----\/-----
      repeat (8) begin
	 #2 d      = ~d;
      end
 -----/\----- EXCLUDED -----/\----- */
      
      #20 $finish;
      
   end
   
   always
     d = ~d;
     #1 clk = ~clk;
   
endmodule