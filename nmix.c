#include <stdio.h>
#include <stdint.h>

#define LFSR_INITIAL 937
#define For(a,b) for(i = a; i<=b; i++)

int Nmix(int X, int R);
int INmix(int Y, int R);
int carry(int X, int R, int i);
int lfsr_gen();
void print_bits(uint16_t);
int get(int num, int i);

uint16_t lfsr = LFSR_INITIAL;

int main() {
  while(1) {
    lfsr = LFSR_INITIAL; //Not required to initialise lfsr everytime in actuall code.
    unsigned int X = 1;
    unsigned int R = 1;
    unsigned int Y = 1;
    printf("X : ");
    scanf("%d", &X);
    R = lfsr_gen();
    Y = Nmix(X,R);
    printf("Y : %d\n", Y);
    X = INmix(Y,R);
    printf("X : %d\n", X);
  }
}

int Nmix(int X, int R) {
  int x,r,c,y;
  int Y = 0;
  int i;
  For(0,16) {
    x = get(X, i);
    r = get(R, i);
    
    c = carry(X, R, i-1);
    y = x ^ r ^ c;
    //print_bits(y);
    Y = Y | y;
  }
  return Y;
}


int carry(int X, int R, int i) {
  int j;
  int c;
  
  c = (get(X,i-1) & get(X,i)) ^ (get(R,i-1) & get(R,i));

  for(j=0; j<=i; j++) {
    c = c ^ ( get(X,j) & get(R,j) );
  }

  /* if( i == -1) */
  /*   printf("C : %d", c); */
  
  return c;
}

int INmix(int Y, int R) {
  int x,r,d,y;
  int X = 0;
  int i;
  For(0,16) {
    y = get(Y, i);
    r = get(R, i);
    d = carry(X, R, i-1);
    x = y ^ r ^ d;
    //print_bits(y);
    X = X | x;
  }

  return X;
}

int get(int num, int i) {
  return num & (1 << i);
}


int lfsr_gen() {
  unsigned bit;
  bit = ((lfsr >> 1) ^ (lfsr >> 2) ^ (lfsr >> 4) ^ (lfsr >> 7));
  lfsr = (lfsr >> 1) | (bit << 15);
  return lfsr;
  //  print_bits(lfsr);
}

void print_bits(uint16_t n) {
  printf("%d : ", n);
  int i;
  for(i=15; i>=0; i--)
    ((n & (1 << i)) != 0) ? printf("%d", 1) : printf("%d", 0);
  
  printf("\n");
}

