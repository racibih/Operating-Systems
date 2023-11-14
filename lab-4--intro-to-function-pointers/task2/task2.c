#include <stdio.h>
#include <stdlib.h>

/* IMPLEMENT ME: Declare your functions here */
typedef int (*fnctns) (int, int);

int add (int a, int b);
int sub (int a, int b);
int mult (int a, int b);
int divide (int a, int b);
int ex (int a, int b);


int main (void)
{  
  int iput = 0;
  fnctns arr[5]={add,sub,mult,divide,ex};
	int a = 6;
  int b = 3;

  /* IMPLEMENT ME: Insert your algorithm here */
  while(iput<=4){ 
  printf("\nOperand ‘a’ : %d | Operand ‘b’ : %d\nSpecify the operation to perform \n(0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : exit):",a,b);
	  scanf("%d", &iput);
  printf("x = %d \n",arr[iput](a,b));  
  }
return 0;
}

/* IMPLEMENT ME: Define your functions here */
int add (int a, int b) { printf ("Adding 'a' and 'b'\n"); return a + b; }
int sub (int a, int b) { printf ("Subtracting 'b' from 'a'\n"); return  a - b; }
int mult (int a, int b) { printf ("Multiplying 'a' and 'b'\n"); return a * b; }
int divide (int a, int b) { printf ("Dividing 'a' by 'b'\n"); return a / b; }
int ex (int a, int b) { printf ("Exiting...\n"); exit(0); }
