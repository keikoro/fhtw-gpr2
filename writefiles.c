/*
write data into a file
*/

int writefiles(int argc, char *argv[])
{
    int i = 0;
    int max = 10;
    char *outputname = "testoutput.c";

    FILE *output;
    output = fopen(outputname, "w");

    for (; i<=max; ++i)
    {
        fprintf(output, "Das ist die %d. Zeile Text.\n", i);
    }

    return 0;
}

