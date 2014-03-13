/*
Reads from file ue1_names.txt, prints the content on the screen.
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

    while (fgets(current_line, NAMENSLAENGE, F1))  /*   reads each line, including the linebreak
                                                        into the string*/
    {
        node_for_one_name=malloc(sizeof(struct node));
        strcpy(node_for_one_name->name, current_line); // copy the current line into a list node

    // Add the current node at the start of the list
        if (head!=NULL)
        {
            node_for_one_name->next=head;
        }
        head=node_for_one_name;
    }
    fclose(F1);

// Printing the current list (should probably remove this before reading in a _really_ long file)
// This is just for easy checking if the created list looks as expected
// Should move this into a function
    struct node *traversenode1;
    traversenode1=head;
    while(traversenode1!=NULL)
    {
        printf("%s", traversenode1->name);
        traversenode1=traversenode1->next;
    }

// Deleting the list; should also be moved into a function later
    struct node *traversenode2;
    while(head!=NULL)
    {
        traversenode2=head;
        head=traversenode2->next;
        free(traversenode2);
    }


    return 0;
}
