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
    int flagcount = 0;
    int i = 0, j = 0;

    while ((getflags = getopt(argc, argv, "r")) != -1)
    {
        /*  suppress auto system error msgs on wrong flags */
        opterr = 0;

        switch (getflags)
        {
            case 'r':
                flagcount++;
                reverse = 1;
                break;
            /*  if unknown flags were given */
            case '?':
                flagcount++;
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

    /*  go through filenames */
    for (i = optind; i < argc; i++)
    {
         printf ("%s\n", argv[i]);
         j++;
    }

    /*  if there aren't enough filenames */
    if (j <  2) {
        printf("%s: wrong number of input or output files\n", argv[0]);
    }


        // char inputfile = argv[1];
        // char outputfile = argv[2];


        for(; i<argc; i++)
        {
            printf("argv is %s\n", argv[i]);
        }
        return 0;

}

int main(int argc, char *argv[])
{

    readfiles(argc, argv);
    // getopt (int argc, char *const *argv, const char *options)


    // printf("%s", inputfile);
    // printf("%s", outputfile);


    // printf("Welcome to sortname - a program that allows you to sort a list of names stored in a file and save this sorted list to another file! \nTo start the program, Please enter the names of the originating file and the one you want to save the sorted list to (if the latter does not exist yet, a new file with your desired name will be created).

    //     %s\n", );

    return 0;
}
