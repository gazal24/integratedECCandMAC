#include <stdio.h>
#include <stdint.h>

#define LFSR_INITIAL 937
#define For(a,b) for(i = a; i<=b; i++)
#define ULL unsigned long long
#define t 16

ULL Nmix(ULL X, ULL R);
ULL INmix(ULL Y, ULL R);
ULL carry(ULL X, ULL R, int i);
ULL lfsr_gen();
void print_bits(ULL);
ULL get(ULL num, int i);

ULL lfsr = LFSR_INITIAL;

int main() {
  while(1) {
    lfsr = LFSR_INITIAL; //Not required to initialise lfsr everytime in actuall code.
    ULL X = 1;
    ULL R = 1;
    ULL Y = 1;
    printf("X : ");
    scanf("%llu", &X);
    R = lfsr_gen();
    Y = Nmix(X,R);
    printf("Y : %llu\n", Y);
    X = INmix(Y,R);
    printf("X : %llu\n", X);
  }
}

ULL Nmix(ULL X, ULL R) {
  int x,r,c,y;
  ULL Y = 0;
  int i;
  For(0,t) {
    x = get(X, i);
    r = get(R, i);
    
    c = carry(X, R, i-1);
    y = x ^ r ^ c;
    //print_bits(y);
    Y = Y | y;
  }
  return Y;
}


ULL carry(ULL X, ULL R, int i) {
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

ULL INmix(ULL Y, ULL R) {
  int x,r,d,y;
  ULL X = 0;
  int i;
  For(0,t) {
    y = get(Y, i);
    r = get(R, i);
    d = carry(X, R, i-1);
    x = y ^ r ^ d;
    //print_bits(y);
    X = X | x;
  }

  return X;
}

ULL get(ULL num, int i) {
  return num & (1 << i);
}


ULL lfsr_gen() {
  ULL bit;
  bit = ((lfsr >> 1) ^ (lfsr >> 2) ^ (lfsr >> 4) ^ (lfsr >> 7));
  lfsr = (lfsr >> 1) | (bit << t-1);
  return lfsr;
  //  print_bits(lfsr);
}

void print_bits(ULL n) {
  printf("%llu : ", n);
  int i;
  for(i=t-1; i>=0; i--)
    ((n & (1 << i)) != 0) ? printf("%d", 1) : printf("%d", 0);
  
  printf("\n");
}

