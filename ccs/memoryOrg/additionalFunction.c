//#include "additionalFunction.h"

#org 0x1000, 0x11FF
int test1(int num1, int num2)
{
   return num1 + num2;
}


int sub(int num1, int num2)
{
   return num1 - num2;
}
#org 0x1200
int sub_caller(int num1, int num2)
{
   return sub(num1, num2);
}
