#include<stdio.h>
int main()
{
  FILE *file;
char filename[]="Example.txt";
char line="This is a new line to append for existing example.txt file\n";

file=fopen(filename,"a");
if(file==NULL)
{
printf("Unable to open file.\n");
return 1;
}
fputs(line,file);
fclose(file);
printf("Line appended to the file.\n");
return 0;
}
