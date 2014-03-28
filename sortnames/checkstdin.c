/*
GPR2 UE1, UE2

if13b076 - Linda Spindler
if13b070 - K Kollmann


***
CHECKSTDIN

function to
- check user input on standard input

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
                exit(1);
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

        // test if -r flag works as expected with getopt included
        // result: test successful! \o/
        //printf("optind = %d\n, reverse = %d\n", optind, *reverse);

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
            exit(1);
            outputstring = "\0";
            return outputstring;
        }
    }
    /*  if there aren't enough filenames */
    else
    {
        printf("sortnames: wrong number of input or output files\n");

        *stopthis = 1;
        exit(1);
        outputstring = "\0";
        return outputstring;
    }
    *stopthis = 0;
}
