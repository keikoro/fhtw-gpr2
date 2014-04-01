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

/*
checkstdin

function to
- check user input on standard input
*/

void checkstdin(int argc, char *argv[], char **programfilename, char **inputfilename, char **outputfilename, int *r)
{
    int getflags = 0;
    int i = 0, j = 0;
    *r = 0;

    FILE *input;
    FILE *output;

    while ((getflags = getopt(argc, argv, "r")) != -1)
    {
        /*  suppress auto system error msgs on wrong flags */
        //opterr = 0;
        switch (getflags)
        {
            case 'r':
                *r = 1;
                break;
            /*  if unknown flags were given */
            case '?':
                /*  print out printable flags */
                if (isprint(optopt))
                {
                    fprintf(stderr, "%s: wrong option %c\n", argv[0], optopt);
                }
                /*  for non-printable characters */
                else
                {
                    fprintf(stderr, "%s: wrong option %c\n", argv[0], optopt);
                }
                exit(1);
                break;
        }
    }

    /*  loop through file names */
    for (i = optind; i < argc; i++)
    {
         j++;
    }

    if (j >= 2)
    {
        *programfilename = argv[0];
        *inputfilename = argv[optind];
        *outputfilename = argv[optind+1];

        /*  check for existence of inputfilename */
        if((input=fopen(*inputfilename, "r")) != NULL)
        {
            /*  check for writability of outputfilename
                (file might only be writeable by certain users)
            */
            if((output=fopen(*outputfilename, "w")) != NULL)
            {
                fclose(input);
            }
            else
            {
                fprintf(stderr, "%s: cannot open output file: %s\n", *programfilename, *outputfilename);
                fclose(input);
                exit(1);
            }
        }
        else
        {
            fprintf(stderr, "%s: cannot open input file: %s\n", argv[0], *inputfilename);
            exit(1);
        }
    }
    /*  if there aren't enough filenames */
    else
    {
        fprintf(stderr, "%s: wrong number of input or output files\n", argv[0]);
        exit(1);
    }
}


/*
compare_strings
read_and_sort_reverse
read_and_sort

functions to
- read a file line by line
- sort all lines
- output data into linked list
*/

struct node{
    char name[NAMENSLAENGE];
    struct node *next;
};

int compare_strings (char *s1, char *s2)
/*  Returns 1 if s1 should be placed first by the established rules (or if the two strings are exactly the same).
    Returns 2 if s2 sshould be placed first.
*/
{
    int i=0;
    int comes_first=1;
    while( (s1[i] != '\n') && (s2[i] != '\n' ))
    {
        if ( tolower (s1[i]) < tolower (s2[i]))
        {
            comes_first=1;
            break;
        }
        else if ( tolower(s1[i]) > tolower(s2[i]) )
        {
            comes_first=2;
            break;
        }
        else
        // The case where taken tolower, the current 2 letter are the same:
        {
            if ( (s1[i+1] != '\n') && (s2[i+1] != '\n') )
                // The two letters are the some (lowercase), so compare the next letters
                i++;
            else
            {
                if ( (s1[i+1] == '\n') && (s2[i+1] != '\n') )
                {
                    comes_first=1;
                    break;
                }
                if ( (s1[i+1] != '\n') && (s2[i+1] == '\n') )
                {
                    comes_first=2;
                    break;
                }
                if ( (s1[i+1] == '\n') && (s2[i+1] == '\n') )
                {
                    int leave_the_do_while_loop=0;
                    for(int j=0; j<=i; j++)
                    {
                        if ((s1[j]) > (s2[j]))
                        {
                            leave_the_do_while_loop = 1;
                            comes_first=1;
                            break;
                        }
                        else if ((s1[j]) == (s2[j]))
                        {
                            if((s1[j+1] == '\n') && (s2[j+1] == '\n'))
                            {
                                comes_first = 1;
                                leave_the_do_while_loop = 1;
                                break;
                            }
                            // incrementation of j as per loop instruction

                        }
                        else
                        {
                            comes_first=2;
                            leave_the_do_while_loop = 1;
                            break;
                        }
                    }
                    if(leave_the_do_while_loop == 1)
                        break;
                }

            }

        }
    }
    return (comes_first);
}

struct node* read_and_sort(char *programfile, char *inputname)
{
    FILE *input;
    char *programname = programfile;
    char *filename = inputname;
    struct node* head=NULL;
    char current_line [NAMENSLAENGE];

    struct node *to_be_inserted;
    struct node *before_insertion;  // Will be the node after which the new node might get inserted
    struct node *compared_with;     // Will be the node after which the new node might get inserted

    input = fopen(filename, "r");
    

    /*   reads each line, including the linebreak into the string*/
    while (fgets(current_line, NAMENSLAENGE, input))
    {
        to_be_inserted=malloc(sizeof(struct node));

        /*  copy the current line into a list node: */
        strcpy(to_be_inserted->name, current_line);
        /* Checking if line ends with a linebreak, add one if not */
        if (to_be_inserted->name[strlen(to_be_inserted->name)-1] != '\n')
        {
            to_be_inserted->name[strlen(to_be_inserted->name)-1] = '\n';
            to_be_inserted->name[strlen(to_be_inserted->name)] = '\0';
        }

        int wrong_input_format = 0;
        for(int i=0; i<=strlen(to_be_inserted->name)-2; i++)
        /* Check for wrong input format;
            Character is neither A-Z, nor a-z, nor a dash, nor a space
        */
        {
            if(
               !(
                (   (to_be_inserted->name[i] >= 'A') && (to_be_inserted->name[i] <= 'Z') )
                    ||
                (   (to_be_inserted->name[i] >= 'a') && (to_be_inserted->name[i] <= 'z') )
                    ||
                    ( isspace(to_be_inserted->name[i]) )
                    ||
                    (to_be_inserted->name[i] == '-')
                )
            )
                wrong_input_format = 1;
        }

    if (wrong_input_format == 1)
    {
        fprintf(stderr, "%s: wrong input format\n", programname);
        head=NULL;
        fclose(input);
        exit(1);
        return(head);
    }
    /*Find right spot to insert the new node into: */
        if (head == NULL)
        {
            head=to_be_inserted;
        }
        else
        {
            if(compare_strings(head->name, to_be_inserted->name)==2)
            {
                to_be_inserted->next=head;
                head=to_be_inserted;
            }
            else
            {
                before_insertion=head;
                compared_with=head->next;
                while (compared_with != NULL)
                {
                    if(compare_strings(to_be_inserted->name,compared_with->name)==1)
                    {
                        before_insertion->next=to_be_inserted;
                        to_be_inserted->next=compared_with;
                        break;
                    }
                    else
                    {
                        before_insertion=before_insertion->next;
                        compared_with=compared_with->next;
                    }
                }
                if (compared_with==NULL)
                /* If the new node has to be placed at the end of the current list
                */
                {
                    before_insertion->next=to_be_inserted;
                }
            }
        }
    }
    fclose(input);
    return (head);
}


struct node* read_and_sort_reverse(char *programfile, char *inputname)
{
    FILE *input;
    char *filename = inputname;
    char *programname = programfile;
    struct node* head=NULL;
    char current_line [NAMENSLAENGE];

    struct node *to_be_inserted;
    struct node *before_insertion;  // Will be the node after which the new node might get inserted
    struct node *compared_with;     // Will be the node after which the new node might get inserted

    input = fopen(filename, "r");


    /*   reads each line, including the linebreak into the string*/
    while (fgets(current_line, NAMENSLAENGE, input))
    {
        to_be_inserted=malloc(sizeof(struct node));

        /*  copy the current line into a list node: */
        strcpy(to_be_inserted->name, current_line);
        /* Checking if line ends with a linebreak, add one if not */
        if (to_be_inserted->name[strlen(to_be_inserted->name)-1] != '\n')
        {
            to_be_inserted->name[strlen(to_be_inserted->name)-1] = '\n';
            to_be_inserted->name[strlen(to_be_inserted->name)] = '\0';
        }

        int wrong_input_format = 0;
        for(int i=0; i<=strlen(to_be_inserted->name)-2; i++)
        /* Check for wrong input format;
            Character is neither A-Z, nor a-z, nor a dash, nor a space
        */
        {
            if(
               !(
                (   (to_be_inserted->name[i] >= 'A') && (to_be_inserted->name[i] <= 'Z') )
                    ||
                (   (to_be_inserted->name[i] >= 'a') && (to_be_inserted->name[i] <= 'z') )
                    ||
                    ( isspace(to_be_inserted->name[i]) )
                    ||
                    (to_be_inserted->name[i] == '-')
                )
            )
                wrong_input_format = 1;
        }

    if (wrong_input_format == 1)
    /*Needs to end the whole programm, not just this function as it does now.*/

    {
        fprintf(stderr, "%s: wrong input format\n", programname);
        head=NULL;
        fclose(input);
        exit(1);
        return(head);
    }
    /*Find right spot to insert the new node into: */
        if (head == NULL)
        {
            head=to_be_inserted;
        }
        else
        {
            if(compare_strings(head->name, to_be_inserted->name)==1)
            {
                to_be_inserted->next=head;
                head=to_be_inserted;
            }
            else
            {
                before_insertion=head;
                compared_with=head->next;
                while (compared_with != NULL)
                {
                    if(compare_strings(to_be_inserted->name,compared_with->name)==2)
                    {
                        before_insertion->next=to_be_inserted;
                        to_be_inserted->next=compared_with;
                        break;
                    }
                    else
                    {
                        before_insertion=before_insertion->next;
                        compared_with=compared_with->next;
                    }
                }
                if (compared_with==NULL)
                /* If the new node has to be placed at the end of the current list
                */
                {
                    before_insertion->next=to_be_inserted;
                }
            }
        }
    }
    fclose(input);
    return (head);
}


/*
writefiles

function to
- write data into a file
*/

int writefiles(char *outputfilename, struct node *myoutputlist)
{
    char *outputname = outputfilename;
    struct node *outputlist = myoutputlist;

    FILE *output;
    output = fopen(outputname, "w");

    while(outputlist!=NULL)
    {
        fprintf(output, "%s", outputlist->name);
        outputlist=outputlist->next;
    }
    
    fclose(output);
    return 0;
}


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
