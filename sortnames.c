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
#include "readandsort.c"
#include "checkstdin.c"

#include "writefiles.c"

int main(int argc, char *argv[])
{
    // char *inputfile = (char*)malloc(256*sizeof(char));
    // char *outputfile = (char*)malloc(256*sizeof(char));
    int *reverse = (int*)malloc(sizeof(int));
    int *stopthis = (int*)malloc(sizeof(int));
    char *outputstring = (char*)malloc(256*sizeof(char));


    char *outputfilename = "testoutputfile.c";
    char *filename = "input3.n";

    outputstring = checkstdin(argc, argv, reverse, stopthis);
    printf("outputstring: %s\n", outputstring);

    // TODO remove later on
    // printf("reverse: %d\n", *reverse);


    struct node *head;

    // the input file to read from

    /*  read_and_sort needs a file pointer as an argument, and returns a pointer to a "struct node".
        In practice, it returns what will then become the start (head) of the list.
    */
    if(*reverse == 0)
    {
        head = read_and_sort(filename);
    }
    else
    {
        head = read_and_sort_reverse(filename);
    }

    struct node *myoutputlist;
    myoutputlist=head;

    /*  start function to write list into a file */
    writefiles(outputfilename, myoutputlist);

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
