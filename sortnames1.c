/*

GPR2, Aufgabe 1.

What the programm does right now:
    -   Reads from a specific file (ue1_names2.txt) line by line;
        lines can be at most 256 characters long, line break and '\0' included.
    -   Puts every line into the node of a linked list (new elements are added at the start of the list)
    -   Counts the number of elements in the list
    -   Does Bubble Sort of the list
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
    -   Optimise Bubble Sort (see slides on sorting alg. from first semester)
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


int main()
{

    FILE *F1;
    char current_line [NAMENSLAENGE];

    F1 = fopen("textfiles/ue1_names2.txt", "r");

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




/*  Implementing Bubble Sort.
    (Picked Bubble Sort because there's not as much going through the whole list,
    we only ever look at the next element.)

    Note about the vocabulary I use in the comments (and variable names):
    I'm going to assume the list goes top to bottom rather than left to right
    (meaning, the next element is downwards, not to the right).
*/

    struct node *before_swap;   // Will be the node before the two that might get swapped
    struct node *down_move;     // Will be the the node that gets moved down the list if there's a swap
    struct node *up_move;       // Will be the the node that gets moved up the list if there's a swap


        /*
            Bubble Sort.
            Doesn't work if list doesn't have at least 3 elements.
        */
    for(;node_counter > 0; node_counter--)
    {
        /* The following is only for the swap of head and head->mext
            Ideally, harmonizse this later so the distinction is
            only necessary for a small part of the program or not at all
        */
        down_move=head;
        up_move=head->next;

        for(int i=0; (down_move->name[i] != '\0') && (up_move->name[i] != '\0');)
        {
            if ( (tolower(down_move->name[i]) ) >= (tolower(up_move->name[i])))
            {
				if( (tolower(down_move->name[i])) == (tolower(up_move->name[i])) )
                /* Only if the letters are the some, check if only of them is uppercase and the
                    other lowercase*/
				{
					if(down_move->name[i] < up_move->name[i])
                    {
                        swap_head_and_next(down_move,up_move); // function that swaps the pointers around
                        head=up_move;
                        break;
                    }
                    else
                        if(down_move->name[i] > up_move->name[i]) break;

                        else i++; // Later just put this into the for instruction

				}
                else
				{
					swap_head_and_next(down_move,up_move); // function that swaps the pointers around
					head=up_move;
					break;
                }
            }
            else break;
        }
        // Now for comparisons of elements after the head
        before_swap=head;
        down_move=head->next;
        up_move=down_move->next;
            /* move_down and move_up are the next two elements of
                the list after the head*/

        while (up_move != NULL) // once up_move has reached NULL we're done
        {
            for(int i=0; (down_move->name[i] != '\0') && (up_move->name[i] != '\0');)
            {
                if ((tolower(down_move->name[i])) >= (tolower(up_move->name[i]))) // Compare the letters independently of case
                {
                    if( (tolower(down_move->name[i])) == (tolower(up_move->name[i])) )
                    {
                        if(down_move->name[i] < up_move->name[i])
                        {
                            swap_any_other_two(before_swap,down_move,up_move);
                            break;
                        }
                        else
                            if(down_move->name[i] > up_move->name[i]) break;

                            else i++; // Later just put the for instruction
                    }
                    else
					{
						swap_any_other_two(before_swap,down_move,up_move);
						break;
					}
				}
                else break;
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
