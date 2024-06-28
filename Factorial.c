#include <stdio.h>
int factorial(int n);
int main()
{
  int num;
printf("Enter the positive integer:");
scanf("%d",&num);
if(num<0)
{
printf("factorial is not defined for negative integer");
}
else
{
printf("factorial of %d is %d\n",num,factorial(num));
}
return 0;
}
int factorial(int n)
{
  if(n==0)
{
return 1;
}
else
{
return n*factorial(n-1);
}
}
