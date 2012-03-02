#include <stdio.h>
#define For(a,b) for(i = a; i<=b; i++)
int Nmix(int X, int R);
int carry(int X, int R, int i);
int main()
{
  int i;

  while(1)
    {
     unsigned int X = 1;
     unsigned int R = 1;
     unsigned int Y = 1;
     printf("X : ");
     scanf("%d", &X);
     printf("R : ");
     scanf("%d", &R);
     Y = Nmix(X,R);
     printf("\nY : %d\n", Y);

     }
}

int Nmix(int X, int R)
{
  int x,r,c,y;
  int Y = 0;
  int i;
  For(0,8)
    {
    x = get(X, i);
    r = get(R, i);
    
    c = carry(X, R, i);
    y = x ^ r ^ c;
    printf("%d ", y);
    Y = Y | y;
  }
  return Y;
}

int get(int num, int i)
{
  return num & (1 << i);
}

/* int lfsr */
/* { */
/* } */

int carry(int X, int R, int i)
{
  int j;
  int c;

  c = (get(X,i-1) & get(X,i)) ^ (get(R,i-1) & get(R,i));
  for(j=0; j<i; j++) {
    c = c ^ ( get(X,j) & get(R,j) );
  }
  
  return c;
  
}
