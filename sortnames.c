#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define NAMENSLAENGE 257
#include "choosefiles.c"
#include "readandsort.c"
#include "writefiles.c"

int main(int argc, char *argv[])
{

    FILE *input;
    // FILE *output;
    char *outputname = "testoutputfile.c";
    // char *outputname2 = "haha.c";

    readfiles(argc, argv);

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

    writefiles(outputname, myoutputlist);


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
