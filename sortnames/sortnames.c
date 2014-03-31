/*
GPR2 UE1, UE2

if13b076 - Linda Spindler
if13b070 - K Kollmann


***
SORTNAMES

Sort names stored in an input file, write them to an output file.
Sort them in reverse order if flag -r is given.

Input example:
sortnames [-r] <inputfile> <outputfile>


Caveats:
- if other flags than -r are used, print:
sortnames: wrong option <OPTION> (with option being the wrong flag w/o "-")
- if one or both of the two file names are missing, print:
sortnames: wrong number of input or output files
- if the input file cannot be found, print:
sortnames: cannot open input file: <NAME> (name being the given file name)
- if the input file contains other values than A-Za-z1-9_ or spaces, print:
sortnames: wrong input format
- if the output file cannot be opened, print:
sortnames: cannot open output file <NAME> (name being the given file name)

Return 1 in main() on any of these errors.

sortnames.c is the main file including the main() function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>
#define NAMENSLAENGE 257
#include "checkstdin.c"
#include "readandsort.c"
#include "writefiles.c"

int main(int argc, char *argv[])
{
    char *inputfile = (char*)malloc(256*sizeof(char));
    char *outputfile = (char*)malloc(256*sizeof(char));
    char *programfile = (char*)malloc(256*sizeof(char));    
    int r = 0;

    checkstdin(argc, argv, &programfile, &inputfile, &outputfile, &r);
	
	
    struct node *head;

    if(r == 0)
    {
        head = read_and_sort(programfile, inputfile);
    }
    else
    {
        head = read_and_sort_reverse(programfile, inputfile);
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
