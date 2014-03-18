/*
TODO:
- ALL 5 test cases
- more testing of correct sort order
- use user-defined input & output files
- exit program on return 1 - generate return 1 in main if wrong input format
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define NAMENSLAENGE 257
#include "checkstdin.c"
#include "readandsort.c"
#include "writefiles.c"

int main(int argc, char *argv[])
{
    char *inputfile = (char*)malloc(256*sizeof(char));

    char *outputfile = (char*)malloc(256*sizeof(char));
    int *reverse = (int*)malloc(sizeof(int));
    int *stopthis = (int*)malloc(sizeof(int));
    char *outputstring = (char*)malloc(256*sizeof(char));
    int k = 0;
    // int l = 0;
    char separator[2] = "|";

    outputstring = checkstdin(argc, argv, reverse, stopthis);

    while (*outputstring)
    {
        if (strchr(separator, *outputstring))
        {
            break;
        }
        else
        {
            inputfile[k] = *outputstring;
        }
        k++;
        outputstring++;
    }

    // inputfile[k+1] = "\0";
    // printf("inputfile: %s\n", inputfile);

    struct node *head;

    if(*reverse == 0)
    {
        head = read_and_sort(inputfile);
    }
    else
    {
        head = read_and_sort_reverse(inputfile);
    }

    struct node *myoutputlist;
    myoutputlist=head;

    /*  start function to write list into a file */
    writefiles(outputfile, myoutputlist);

    // Deleting the list; should be moved into writefiles.c later
    struct node *traversenode2;
    while(head!=NULL)
    {
        traversenode2=head;
        head=traversenode2->next;
        free(traversenode2);
    }

    return 0;
}
