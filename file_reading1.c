/*
A programm to practice read from and into a file.
*/

#include <stdio.h>
#include <string.h>

int main()
{
    int n = 5;
    FILE *F1;
    char *line [10];
    F1 = fopen("testinput_auf1.txt", "r");
    fgets (line, n, F1);
    printf("%s", line);
    return 0;
}
