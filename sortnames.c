/*
TODO:
- Reverse sorting
- ALL 5 test cases
- check for faults in input1.n
- check for faults in input2.n
- more testing of correct sort order
- use user-defined input & output files
- exit program on return 1
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
    char *inputfile = "\0";
    char *outputfile = "\0";
    int *reverse = (int*)malloc(sizeof(int));
    char *outputfilename = "testoutputfile.c";
    char *filename = "input3.n";

    if(checkstdin(argc, argv, inputfile, outputfile, reverse) == 1) {
        return 1;
    }

    // TODO remove later on
    printf("%d\n", *reverse);
    printf("%c\n", *inputfile);

    struct node *head;

    // the input file to read from

    /*  read_and_sort needs a file pointer as an argument, and returns a pointer to a "struct node".
        In practice, it returns what will then become the start (head) of the list.
    */
    head = read_and_sort(filename);

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

    printf("hallo\n");

    return 0;
}
