/*
GPR2 UE1, UE2

if13b076 - Linda Spindler
if13b070 - K Kollmann


***
CHECKSTDIN

function to
- check user input on standard input

*/

void checkstdin(int argc, char *argv[], char **inputfilename, char **outputfilename, int *r)
{
	int getflags = 0;
    int i = 0, j = 0;
    *r = 0;

    FILE *input;
    FILE *output;

    while ((getflags = getopt(argc, argv, "r")) != -1)
    {
        /*  suppress auto system error msgs on wrong flags */
        //opterr = 0;
        switch (getflags)
        {
            case 'r':
				*r = 1;
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
                exit(1);
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
        *inputfilename = argv[optind];
        *outputfilename = argv[optind+1];

        /*  check for existence of inputfilename */
        if((input=fopen(*inputfilename, "r")) != NULL)
        {
            /*  check for writability of outputfilename
                (file might only be writeable by certain users)
            */
            if((output=fopen(*outputfilename, "w")) != NULL)
            {
                fclose(input);
            }
            else
            {
                printf("sortnames: cannot open output file: %s\n", *outputfilename);
                fclose(input);
				exit(1);
            }
        }
        else
        {
            printf("sortnames: cannot open input file: %s\n", *inputfilename);
            exit(1);
        }
    }
    /*  if there aren't enough filenames */
    else
    {
        printf("sortnames: wrong number of input or output files\n");
        exit(1);
    }
}
