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
    FILE *output;

    readfiles(argc, argv);

    struct node *head;
    /*
        input will later be determined by the readfiles programm; for now it's statically set to textfiles/ue1_names.txt
    */
    input = fopen("textfiles/ue1_names1.txt", "r");

    /*  read_and_sort needs a file pointer as an argument, and returns a pointer to a "struct node".
        In practice, it returns what will then become the start (head) of the list.
    */
    head = read_and_sort(input);

    struct node *traversenode1;
    traversenode1=head;

    char *outputname = "bla.c";
    output = fopen(outputname, "w");

    while(traversenode1!=NULL)
    {
        fprintf(output, "%s", traversenode1->name);
        traversenode1=traversenode1->next;
    }

    // Deleting the list; should be moved into a function later
    struct node *traversenode2;
    while(head!=NULL)
    {
        traversenode2=head;
        head=traversenode2->next;
        free(traversenode2);
    }

    return 0;
}
