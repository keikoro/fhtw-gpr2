/*

GPR2, Aufgabe 1.

What the programm does right now:
    -   Reads from a specific file (ue1_names3.txt, to be found in the textfiles directory on the github repository)
        line by line; lines can be at most 256 characters long, line break and '\0' included.
    -   Puts every line into the node of a linked list (new elements are added at the start of the list)
    -   Counts the number of elements in the list
    -   Does a first run of Bubble Sort:
            By first letter only
            By ASCII code number only
            Irgnores first and last word of list
    -   Prints the list onto the screen

What needs to be implemented:
    -   Next runs of Bubble Sort (unless we want to use a different sorting method, which might be better;
            I explained why I picked this one in the program)
    -   Taking the first and last line on the list into account while sorting
    -   Sorting by second, third etc letter
    -   Taking into account upper and lower case (see exercice instructions)
    -   Taking into account line lenght (all other things being equal short word before longer word)
    -   Error cases
    -   Reading the sorted list into the file
    -   Menu for chosing which file to read from/to
    -   Test cases
    -   ...

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAMENSLAENGE 256

struct node{
    char name[NAMENSLAENGE];
    struct node *next;
};


int main()
{

    FILE *F1;
    char current_line [NAMENSLAENGE];

    F1 = fopen("ue1_names.txt", "r");

    struct node *head = NULL;
    struct node *node_for_one_name;
    int node_counter=0;
        /*  Do not forget to return the counter to zero for
            every new document once we want to sort
            several documents in one run of the programm!
            Btw, would love to do this without a counter, but no idea if it's possible and how.
        */

    while (fgets(current_line, NAMENSLAENGE, F1))  /*   reads each line, including the linebreak
                                                        into the string*/
    {
        node_for_one_name=malloc(sizeof(struct node));
        strcpy(node_for_one_name->name, current_line); // copy the current line into a list node

    // Add the current node at the start of the list
        if (head != NULL)
        {
            node_for_one_name->next=head;
        }
        head=node_for_one_name;
        node_counter++;

    }
    fclose(F1);




/*  Implementing Bubble Sort
    (picked Bubble Sort because there's not as much going through the whole list,
    we only ever look at the next element).

    Note about the vocabulary I use in the comments (and variable names):
    I'm going to assume the list goes top to bottom rather than left to right
    (meaning, the next element is downwards, not to the right).
*/

    struct node *before_swap;   // The node before the two that might get swapped
    struct node *down_move;     // The node that will be moved down the list if there's a swap
    struct node *up_move;       // The node that will be moved up the list if there's a swap


        /*
            Bubble Sort.
            Doesn't work if list doesn't have at least 3 elements.
            Doesn't work for the last two elements.
        */

    for(;node_counter > 0; node_counter--)
    {
        int first_run = 1;
        /* The following is only for the swap of head and head->mext
            Ideally, harmonizse this somehow later so the distinction is
            only necessary for a small part of the program or not at all
        */
        down_move=head;
        up_move=head->next;

        if ((down_move->name[0]) > (up_move->name[0]))
        {
            down_move->next=up_move->next;
            up_move->next=down_move;
            head=up_move;
        }

        // Now for comparisons of elements after the head:
        before_swap=head;
        down_move=head->next;
        up_move=down_move->next;
            /* move_down and move_up are the next two element of
                the list after the head*/

        while (up_move != NULL) // once up_move has reached NULL we're done
        {
            if ((down_move->name[0]) > (up_move->name[0]))
                /* Comparing only the first letter for now. Will have
                    to implement loop for going through whole word
                    later.
                */
            {
                before_swap->next=up_move;
                down_move->next=up_move->next;
                up_move->next=down_move;
            }
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
