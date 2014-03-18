/*

GPR2, Aufgabe 1.

What the programm does right now:
    -   Reads from a specific file (textfiles/ue1_names2.txt) line by line;
            lines can be at most 256 characters long, line break and '\n' included.
    -   Sort them into a dynamically created linked list
    -   Prints the list onto the screen

To Do/Fix/Work on:
    -   Programm only works perfectly if there's a line-break at the end of the document (after the last element). Fix that.
    -   Linking with other .c file (and everything related to that)
    -   Reading the sorted list into the file
    -   Reverse sorting
    -   (More) Test cases; creating 5 input/output files
    -   Testing, and if necessarily fixing the sorting; special cases I haven't thought of yet etc
    -   Code cleanup? (moving things into functions, reducing repetitive code,
         simplifying loops and if/else branched etc)
    -   ...
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NAMENSLAENGE 256

struct node{
    char name[NAMENSLAENGE];
    struct node *next;
};

/*
    Gave the struct pointers the same names in the function as the ones in main
    because anything else would just get confusing.
*/
void swap_head_and_next(struct node *down_move, struct node *up_move)
{
    down_move->next=up_move->next;
    up_move->next=down_move;
}

void swap_any_other_two(struct node *before_swap, struct node *down_move, struct node *up_move)
{
    before_swap->next=up_move;
    down_move->next=up_move->next;
    up_move->next=down_move;
}


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


int main()
{
    FILE *F1;
    char current_line [NAMENSLAENGE];

    F1 = fopen("textfiles/ue1_names2.txt", "r");

    struct node *head = NULL;
    struct node *to_be_inserted;
    struct node *before_insertion;  // Will be the node after which the new node might get inserted
    struct node *compared_with;     // Will be the node after which the new node might get inserted

    /*   reads each line, including the linebreak into the string*/
    while (fgets(current_line, NAMENSLAENGE, F1))
    {
        to_be_inserted=malloc(sizeof(struct node));

        /*  copy the current line into a list node: */
        strcpy(to_be_inserted->name, current_line);

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
    fclose(F1);


// Printing the list
// This is just for checking if the created list looks as expected
// Will be removed when the list is printed into another file instead

    struct node *traversenode1;
    traversenode1=head;
    while(traversenode1!=NULL)
    {
        printf("%s", traversenode1->name);
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
