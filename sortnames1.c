/*

GPR2, Aufgabe 1.

What the programm does right now:
    -   Reads from a specific file (textfiles/ue1_names1.txt) line by line;
        lines can be at most 256 characters long, line break and '\n' included.
    -   Puts every line into the node of a linked list (new elements are added at the start of the list)
    -   Counts the number of elements in the list
    -   Does Bubble Sort on the list; now taakes the length and uppercase/lowercase rules into account
    -   Prints the list onto the screen

To Do/Fix/Work on:
    -   Case where the list is shorther than 3 elements
    -   Programm only works perfectly if there's a line-break at the end of
        the document. Fix that.
    -   Error cases + messages
    -   Reading the sorted list into the file
    -   Menu for chosing which file to read from/to
    -   (More) Test cases
    -   Testing, and if necessarily fixing the sorting; special cases I haven't thought of yet?
    -   Code cleanup; moving things into functions, reducing repetitive code,
         simplifying loops and if/else branched etc
    -   If possible, switch to sorting as file is read into the list, through Insertion Sort
    -   Else Optimise Bubble Sort (see slides on sorting alg. for Bubble Sort opsitimisation method)
    -   I'm getting a warning about using MS-DOS style paths, need to look into that, test program on
        other computer
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

    F1 = fopen("textfiles/ue1_names1.txt", "r");

    struct node *head = NULL;
    struct node *node_for_one_name;
    int node_counter=0;
        /*  Do not forget to return the counter to zero for
            every new document once we want to sort
            several documents in one run of the programm!
            Btw, would love to do this without a counter, but no idea if it's possible and how.
        */

    /*   reads each line, including the linebreak into the string*/
    while (fgets(current_line, NAMENSLAENGE, F1))
    {
        node_for_one_name=malloc(sizeof(struct node));
        /*  copy the current line into a list node */
        strcpy(node_for_one_name->name, current_line);

    // Add the current node at the start of the list
        if (head != NULL)
        {
            node_for_one_name->next=head;
        }
        head=node_for_one_name;
        node_counter++;

    }
    fclose(F1);


/*  Implementing Bubble Sort.
    (Picked Bubble Sort because there's not as much going through the whole list,
    we only ever look at the next element.)

    Note about the vocabulary I use in the comments (and variable names):
    I'm going to assume the list goes top to bottom rather than left to right
    (meaning, the next element is downwards, not to the right).
*/

    struct node *before_swap;   // Will be the node before the two that might get swapped
    struct node *down_move;     // Will be the node that gets moved down the list if there's a swap
    struct node *up_move;       // Will be the node that gets moved up the list if there's a swap


        /*
            Bubble Sort.
            Doesn't work if list doesn't have at least 3 elements.
            Need to either define special cases for fewer elements, change the
            struct pointers, or switch to other sorting method.
        */
    for(;node_counter > 0; node_counter--)
    {

        down_move=head;
        up_move=head->next;

        if (compare_strings(down_move->name,up_move->name)==2)
        {
            swap_head_and_next(down_move,up_move);
            head=up_move;
        }
        // Now for the elements after head; there's a lot of repeated code here.
        before_swap=head;
        down_move=head->next;
        up_move=down_move->next;

        while (up_move != NULL) // once up_move has reached NULL we're done
        {
            if(compare_strings(down_move->name,up_move->name)==2)
                swap_any_other_two(before_swap,down_move,up_move);
            /* Now everything gets moved one node down*/
            up_move=before_swap->next->next->next;
            down_move=before_swap->next->next;
            before_swap=before_swap->next;
        }
    }

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

    printf ("Number of elements in list: %d", node_counter);


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
