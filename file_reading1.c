/*
Reads from file ue1_names.txt, prints the content on the screen.
*/

#include <stdio.h>
#include <string.h>

int main()
{
    FILE *F1;
    char line [100];
    F1 = fopen("ue1_names.txt", "r");
    while (fgets (line, 25, F1))
    {
        fputs(line,stdout);
    }
    fclose(F1);
    return 0;
}
