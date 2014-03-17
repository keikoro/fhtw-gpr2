/*
A user is supposed to enter two file names: one for an input file from which a list of names should be read, one for an output file to which this list of names should be written after it's been sorted.

The user can choose to use the option/flag "-r" which sorts the list in reverse order.

Caveats:
- if other flags than -r are used, print:
sortnames: wrong option <OPTION> (with option being the wrong flag w/o -)
- if one or both of the two file names are missing, print:
sortnames: wrong number of input or output files
- if the input file cannot be found, print:
sortnames: cannot open input file: <NAME> (name being the typed name)
- if the input file contains other values than names, print:
sortnames: wrong input format
- if the output file cannot be opened, print:
sortnames: cannot open output file <NAME>
*/


/*
TODO:
- check if input file exists (if not: print msg)
- check if input file contains names (if not: print mgs)
- check if output file can be opened (if not: print msg)
- return 0 or 1 in main function, depending on input


DONE:
- separation of flags from other input (which is interpreted as file names)
attn: atm, only flags in front of a first file name are considered (unclear)
e.g. -t -p name name name
not: -t name name name -p
- print message on input of wrong flags
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

int readfiles(int argc, char *argv[])
{
    int getflags = 0;
    int reverse = 0;
    char *inputfile;
    char *outputfile;
    int i = 0, j = 0;

    while ((getflags = getopt(argc, argv, "r")) != -1)
    {
        /*  suppress auto system error msgs on wrong flags */
        opterr = 0;

        switch (getflags)
        {
            case 'r':
                reverse = 1;
                break;
            /*  if unknown flags were given */
            case '?':
                /*  print out printable flags */
                if (isprint(optopt))
                {
                    printf("%s: wrong option %c\n", argv[0], optopt);
                }
                /*  for non-printable characters */
                else
                {
                    printf("%s: wrong option %#x\n", argv[0], optopt);
                }
                break;
        }
    }

    /*  loop through file names */
    for (i = optind; i < argc; i++)
    {
        // TODO remove print statement
         // printf ("%s\n", argv[i]);
         j++;
    }

    if (j >= 2)
    {
        inputfile = argv[optind];
        outputfile = argv[optind+1];
        // TODO remove later on
        printf("alles passt\n");

        if (reverse == 1)
        {
            printf("reverse, go!\n");
        }

    }
    /*  if there aren't enough filenames */
    else
    {
        printf("%s: wrong number of input or output files\n", argv[0]);
        return 1;
    }

    return 0;

}

int main(int argc, char *argv[])
{
    readfiles(argc, argv);
    return 0;
}
