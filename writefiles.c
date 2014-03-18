/*
write data into a file
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

    return 0;
}

