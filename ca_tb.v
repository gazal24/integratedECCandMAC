module ca_tb();
   reg clk,reset,preset;
   reg [0:7] in;
   wire [0:7] out;

   // for file
   reg [0:7]  data;
   reg [0:7]  count;
   integer    fd;
   integer    code, dummy;
   reg [8*10:1] str;
   // end for flle
   
   CA uud(.clk(clk),.reset(reset),.in(in),.out(out));
   initial begin
      $monitor("CLK = %b RESET = %b PRESET = %b D = %b Q = %b", clk,reset,preset,in,out);
      clk = 0;
      #1 reset  = 0;
      preset = 0;
      in = 0;
      fd = $fopen("input.txt","r"); 
      #1 reset = 1;
      #2 reset = 0;
      #2 preset = 1;
      #2 preset = 0;
      // #20 $finish;
   end
   
   always @(posedge clk) begin
      data = 0;
      code = 1;
      count = 0;
      $monitor("data = %x", data);
      while (count < 8) begin
	 code = $fgets(str, fd);
         dummy = $sscanf(str, "%x", data);
	 if(code == 0)
	   $finish;
	 else if(data == 0)
	   in[count] = 0;
	 else 
	   in[count] = 1;
	 count = count + 1;
      end
   end
   
   always begin
      #1 clk = ~clk;
   end
   always
     #1 in = in + 1;
   
endmodule

