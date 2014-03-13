/*
Reads from file ue1_names.txt, prints the content on the screen.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAMENSLAENGE 256

struct node{
    char name[NAMENSLAENGE];
    struct node *next;
};


int main()
{

    FILE *F1;
    char line [NAMENSLAENGE];
    F1 = fopen("ue1_names.txt", "r");

    struct node *head = NULL;

    struct node *namenode;
    while (fgets (line, NAMENSLAENGE, F1))
    {
        fputs(line,stdout);
    }
    fclose(F1);
    return 0;
}
