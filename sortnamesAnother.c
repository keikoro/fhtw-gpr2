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


    outputstring = checkstdin(argc, argv, reverse, stopthis);

    char *input_file_name = (char*)malloc(256*sizeof(char));
    char *output_file_name = (char*)malloc(256*sizeof(char));

    int i=0;
    for(; outputstring[i] !='|'; i++)
    {
        input_file_name[i] = outputstring[i];
    }
    i++;
    for(; outputstring[i]!='|'; i++)
    {
        output_file_name[i] = outputstring[i];
    }
    printf("%s",output_file_name);
    printf("%s",input_file_name);

    // TODO remove later on
    // printf("reverse: %d\n", *reverse);


    struct node *head;

    // the input file to read from

    /*  read_and_sort needs a file pointer as an argument, and returns a pointer to a "struct node".
        In practice, it returns what will then become the start (head) of the list.
    */
    if(*reverse == 0)
    {
        head = read_and_sort(input_file_name);
    }
    else
    {
        head = read_and_sort_reverse(input_file_name);
    }

    struct node *myoutputlist;
    myoutputlist=head;

    /*  start function to write list into a file */
    writefiles(input_file_name, myoutputlist);

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
