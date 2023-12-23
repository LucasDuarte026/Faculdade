module decoder1035(output o, input [15:0] inp);

  // Create the negated input by using the bitwise NOT operator
  wire [15:0] ninp = ~inp;

  // Perform the AND operation with selected bits from inp and ninp
  assign o = inp[0] & inp[1] & ninp[2] & inp[3] & ninp[4] & ninp[5] & 
             ninp[6] & ninp[7] & ninp[8] & ninp[9] & inp[10] & ninp[11] & 
             ninp[12] & ninp[13] & ninp[14] & ninp[15];

endmodule

