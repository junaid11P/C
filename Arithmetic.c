#include<stdio.h>
#include<math.h>
void main()
{
  int a;
  float b,sum,sub,mul,div;
printf("Enter the number 1:");
scanf("%d",&a);
printf("Enter the number 2:");
scanf("%f",&b);
sum=a+b;
sub=a-b;
mul=a*b;
div=a/b;
printf("The sum of %d and %f is:%f\n",a,b,sum);
printf("The substraction of %d and %f is:%f\n",a,b,sub);
printf("The multiplication of %d and %f is:%f\n",a,b,mul);
printf("The division of %d and %f is:%f\n",a,b,div);
}
