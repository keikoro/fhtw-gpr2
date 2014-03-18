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

    FILE *input;
    char *inputfile = "\0";
    char *outputfile = "\0";
    int *reverse = (int*)malloc(sizeof(int));

    char *outputfilename = "testoutputfile.c";

    checkstdin(argc, argv, inputfile, outputfile, reverse);

    // TODO remove later on
    printf("%d\n", *reverse);
    printf("%c\n", *inputfile);

    struct node *head;
    /*
        input will later be determined by the readfiles programm; for now it's statically set to textfiles/ue1_names.txt
    */
    input = fopen("input3.n", "r");

    /*  read_and_sort needs a file pointer as an argument, and returns a pointer to a "struct node".
        In practice, it returns what will then become the start (head) of the list.
    */
    head = read_and_sort(input);

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
