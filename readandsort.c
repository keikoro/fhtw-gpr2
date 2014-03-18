/*

GPR2, Aufgabe 1.

What the programm does right now:
    -   Reads from a specific file (textfiles/ue1_namesWrongInputFormat.txt) line by line;
            lines can be at most 257 characters long, line break and '\n' included.
    -   Sort them into a dynamically created linked list
    -   Prints the list onto the screen

To Do/Fix/Work on:
    -   Check for wrong input character
    -   Programm only works perfectly if there's a line-break at the end of the document (after the last element). Fix that.
    -   Linking with other .c file (and everything related to that)
    -   Reading the sorted list into the file
    -   Reverse sorting
    -   (More) Test cases; creating 5 input/output files
    -   Testing, and if necessarily fixing the sorting; special cases I haven't thought of yet etc
    -   Code cleanup? (moving things into functions, reducing repetitive code,
         simplifying loops and if/else branched etc)
jn j     -   ...
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

struct node* read_and_sort(FILE *F1)
{
    struct node* head=NULL;
    char current_line [NAMENSLAENGE];

    struct node *to_be_inserted;
    struct node *before_insertion;  // Will be the node after which the new node might get inserted
    struct node *compared_with;     // Will be the node after which the new node might get inserted

    /*   reads each line, including the linebreak into the string*/
    while (fgets(current_line, NAMENSLAENGE, F1))
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
        printf ("sortnames: wrong input format");
        break;//return (1);
        /* TODO: Test this (= test wrong input format!)
        */
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
    fclose(F1);
    return (head);
}
