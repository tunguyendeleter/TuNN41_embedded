#include "math.h"
__attribute__((section (".user_data")))static int a = 5;
__attribute__((section (".user_data")))static int b = 10;
__attribute__((section (".user_bss")))int Sum;
__attribute__((section (".user_code")))int f_Sum(int x,int y){return x + y;}

__attribute__((section (".user_data"))) int ddata = 12;
int edata = 13;
int fdata = 14;
/*Declare function*/
/*Declare variable*/

int main(void)
{
	ddata = f_Sum(a,b);
	edata = f_Sum(a,b);
	fdata = f_Sum(a,b);
}
