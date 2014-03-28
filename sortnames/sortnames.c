/*
GPR2 Hausuebung 1

Gruppenarbeit:
if13b076 - Linda Spindler
if13b070 - K Kollmann
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
    int *reverse = (int*)malloc(sizeof(int));
    int *stopthis = (int*)malloc(sizeof(int));
    char *outputstring = (char*)malloc(256*sizeof(char));
    int k=0, l=0, m=0;
    char separator[2] = "|";

    outputstring = checkstdin(argc, argv, reverse, stopthis);

    /*  loop through concatenated outputstring
        (contains input file name, output filename) */
    while (*outputstring)
    {
        if (strchr(separator, *outputstring))
        {
            m = 1;
        }
        // get the input string
        else if (m != 1)
        {
            inputfile[k] = *outputstring;
            k++;
        }
        // get the output string
        else
        {
            outputfile[l] = *outputstring;
            l++;
        }
        outputstring++;
    }

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
