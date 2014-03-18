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

Return 1 in main() on any of these errors.


TODO:
- check if input file contains names (if not: print mgs, *stopthis = 1;
)
-> happens in another function

DONE:
- separation of flags from other input (which is interpreted as file names)
attn: atm, only flags in front of a first file name are considered (unclear)
e.g. -t -p name name name
not: -t name name name -p
- check for wrong flags (if there are: print msg, *stopthis = 1;
)
- check if input file exists (if not: print msg, *stopthis = 1;
)
- check if output file can be opened (if not: print msg, *stopthis = 1;
)
*/

char *checkstdin(int argc, char *argv[], int *reverseflag, int *stopflag)
{
    int getflags = 0;
    int *reverse = reverseflag;
    int *stopthis = stopflag;

    char separator[2] = "|";
    char *inputfilename;
    char *outputfilename;
    char *outputstring = (char*)malloc(256*sizeof(char));
    int i = 0, j = 0;

    FILE *input;
    FILE *output;

    while ((getflags = getopt(argc, argv, "r")) != -1)
    {
        /*  suppress auto system error msgs on wrong flags */
        opterr = 0;
        switch (getflags)
        {
            case 'r':
                *reverse = 1;
                break;
            /*  if unknown flags were given */
            case '?':
                /*  print out printable flags */
                if (isprint(optopt))
                {
                    printf("sortnames: wrong option %c\n", optopt);
                }
                /*  for non-printable characters */
                else
                {
                    printf("sortnames: wrong option %#x\n", optopt);
                }
                *stopthis = 1;
                return outputstring;
                break;
        }
    }

    /*  loop through file names */
    for (i = optind; i < argc; i++)
    {
         j++;
    }

    if (j >= 2)
    {
        inputfilename = argv[optind];
        outputfilename = argv[optind+1];

        /*  check for existence of inputfilename */
        if((input=fopen(inputfilename, "r")) != NULL)
        {
            /*  check for writability of outputfilename
                (file might only be writeable by certain users)
            */
            if((output=fopen(outputfilename, "w")) != NULL)
            {
                if (*reverse == 1)
                {
                    // sort list in reverse order
                }
                /*  name of input file, name of output file
                    split by separator */
                outputstring = strcat(outputstring, inputfilename);
                outputstring = strcat(outputstring, separator);
                outputstring = strcat(outputstring, outputfilename);
                return outputstring;

                fclose(input);
                fclose(output);
            }
            else
            {
                printf("sortnames: cannot open output file: %s\n", outputfilename);
                fclose(input);

                *stopthis = 1;
                outputstring = "\0";
                return outputstring;
            }
        }
        else
        {
            printf("sortnames: cannot open input file: %s\n", inputfilename);

            *stopthis = 1;
            outputstring = "\0";
            return outputstring;
        }
    }
    /*  if there aren't enough filenames */
    else
    {
        printf("sortnames: wrong number of input or output files\n");

        *stopthis = 1;
        outputstring = "\0";
        return outputstring;
    }
    *stopthis = 0;
}