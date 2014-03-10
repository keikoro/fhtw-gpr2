/*
A programm to practice read from and into a file.

*/

#include <stdio.h>
#include <string.h>


int main()
{
    FILE *fp;
    char c [10];
    fp = fopen("testinput_auf1.txt", "r");
    for (int i=0; (c[i] = getc(fp))!=EOF; i++)
        c[i] = getc(fp);
    printf("%s", c);
    return 0;
}
