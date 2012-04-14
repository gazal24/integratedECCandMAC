#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cstdlib>

#define NUMBER_OF_CELLS 128
#define TEXT "Post-quantum cryptography refers to research on cryptographic primitives (usually public-key cryptosystems) that are not breakable using quantum computers."

using namespace std;
bool cell_func(int rule, bool l, bool s, bool r);
int main()
{
  //CELL OF CELLULAR AUTOMATA
  typedef struct {
    int id;
    int rule;
    bool p_value;
    bool n_value;
  }cell;

  int i,j,k;

  //===============
  // NON LINEAR CA

  cell* CA = (cell*)malloc(sizeof(cell)*NUMBER_OF_CELLS);
  //DEFINE NON-LINEAR CELLULAR AUTOMATA
  for(i=0; i<128;)
    {
      CA[i++].rule = 30;
      CA[i++].rule = 60;
      CA[i++].rule = 90;
      CA[i++].rule = 120;
      CA[i++].rule = 150;
      CA[i++].rule = 180;
      CA[i++].rule = 210;
      CA[i++].rule = 240;
    }



  //===============
  // LINEAR CA

  //CREATE MATRIX
  bool T[128][128];

  //DEFINE LINEAR CELLULAR AUTOMATA  <150, 150, 90,150,90,150,90,150>
  int lca[128];
  for(i=0; i<128;)
    { lca[i++] = 150;
      lca[i++] = 150;
      lca[i++] = 90;
      lca[i++] = 150;
      lca[i++] = 90;
      lca[i++] = 150;
      lca[i++] = 90;
      lca[i++] = 150;
    }
  
  //INITIALIZE MATRIX TO ZERO FIRST
  for(i=0; i<128; i++)
    for(j=0; j<128; j++)
      T[i][j] = 0;

  //INITIALIZE MATRIX WITH CA VALUES
  T[0][0] = 1;
  T[0][1] = 1;
  for(i=1; i<127; i++)
    switch(lca[i])
      {
      case 90:
	T[i][i-1] = 1;
	T[i][i+1] = 1;
	break;
	
      case 150:
	T[i][i-1] = 1;
	T[i][i] = 1;
	T[i][i+1] = 1;
	break;
      }
  T[127][126] = 1;
  T[127][127] = 1;  
  

  //PRINT MATRIX
  /*  for(i=0; i<128; i++)
      {
      for(j=0; j<128; j++)
      {
      cout << T[i][j];
      }
      cout << endl << endl;
      }
  */  

  bool *bits = (bool*)malloc(sizeof(bool)*128); //STORES THE INPUT BIT STREAM
  bool *mac = (bool*)malloc(sizeof(bool)*128);  //STORES THE MAC GENERATED. MAC = T(M)
  bool *val = (bool*)malloc(sizeof(bool)*128);  //STORES NEXT-BITSTREAM + MAC
  bool *bits_8 = (bool*)malloc(sizeof(bool)*8); //STORE BINARY REPRESENTAION OF A INPUT CHARACTER
  bool *block_cipher = (bool*)malloc(sizeof(bool)*128);  //STORES THE BLOCK CIPHER GENERATED. 
  string buf = TEXT;
  int pointer = 0;
  int num;
  int index = 0;
  int key[128];
  for(i=0; i<128; i++)
    key[i] = rand()%2;

  //INITIALIZE NON-LINEAR CA WITH KEY
  for(i=0; i<128; i++)	CA[i].p_value = key[i];
  

  
  while(pointer < buf.length())
    {
      index = 0;
      while(index<128) 
	{
	  num = buf[pointer++]; //READ AN INPUT CHARACTER TO CONVERT IT TO BINARY
	  i = 7;
	  while(i>=0)
	    {
	      bits_8[i--] = num%2;
	      num = num/2;
	    }
      
	  i = 0;
	  while(i<8)
	    {
	      bits[index++] = bits_8[i++]; //APPEND IT TO THE INPUT BITSTREAM VECTOR
	    }
	}      
      //bits[] contain 128 bit message block
      cout << endl;



      //KEY [NON-LINEAR CA]
      cout << "KEY : ";
      for(i=0; i<128; i++)
	{
	  if (i==0)
	    CA[i].n_value = cell_func(CA[i].rule, 0, CA[i].p_value, CA[i+1].p_value);
	  else if (i==127)
	    CA[i].n_value = cell_func(CA[i].rule, CA[i-1].p_value, CA[i].p_value, 0);
	  else 
	    CA[i].n_value = cell_func(CA[i].rule, CA[i-1].p_value, CA[i].p_value, CA[i+1].p_value);
	  cout << CA[i].n_value;
	}
      
      for(i=0; i<128; i++) CA[i].p_value = CA[i].n_value; //UPDATE D-FLIP-FLOP
      //KEY READY


      //MAC [LINEAR CA]

      for(i=0; i<128; i++)  val[i] = val[i] ^ bits[i]; //ADD BITS[] TO VAL[]

      for(i=0; i<128; i++)
	for(j=0; j<1; j++)
	  {
	    mac[i] = 0;
	    for(k=0; k<128; k++)
	      mac[i] = mac[i] ^ (T[i][k] & val[k]); //MATRIX MULTIPLICATION. MAC[] IS GENERATED.
	  }

      for(i=0; i<128; i++)  val[i] = mac[i]; //COPY MAC[] TO VAL[]
      
      //ENCRYPT THE MESSAGE [BLOCK CIPHER]
      for(i=0; i<128; i++) block_cipher[i] = CA[i].p_value ^ mac[i];

      cout << endl << "MAC : ";
      for(i=0; i<128; i++) cout << mac[i];

      cout << endl << "BLOCK CIPHER : ";
      for(i=0; i<128; i++) cout << block_cipher[i];      
      

      cout << endl;
      fflush(0);
      sleep(1);
    }
  cout << endl;
}


bool cell_func(int rule, bool l, bool s, bool r)
{
  switch(rule)
    {
    case 30 : return ((s&r) ^ (l) ^ (s) ^ (r));
      break;
    case 60 : return (l) ^ (s);
      break;
    case 90 : return (l) ^ (r);
      break;
    case 120 : return (l) ^ (s&r);
      break;
    case 150 : return (l) ^ (s) ^ (r);
      break;
    case 180 : return (l) ^ (s) ^ (s&r);
      break;
    case 210 : return (l) ^ (r) ^ (s&r);
	break;
    case 240 : return (s);
	break;
    }
}
