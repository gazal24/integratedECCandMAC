module dff(clk,reset,preset,d, q);
   input clk,reset,preset,d;
   output q;
   
   wire   clk,reset,preset,d;
   reg 	  q;
   
   always @ (posedge clk or negedge clk) begin
      if (reset) begin
	 q <= 0;
      end else if (preset) begin
	 q <= 1;
      end else begin
	 q = d;
      end
   end
   
endmodule // dff
