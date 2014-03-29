/*
GPR2 UE1, UE2

if13b076 - Linda Spindler
if13b070 - K Kollmann


***
READANDSORT

function to
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

struct node* read_and_sort(char *inputname)
{
    FILE *input;
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
        printf("sortnames: wrong input format\n");
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


struct node* read_and_sort_reverse(char *inputname)
{
    FILE *input;
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
    /*Needs to end the whole programm, not just this function as it does now.*/

    {
        printf("sortnames: wrong input format\n");
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