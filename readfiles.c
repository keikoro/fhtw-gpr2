/*
User is supposed to enter names for an input file (needs to exist) and an output file, which may or may not exist.

If the output file does not exist yet, create a new file with the given name. If it already exists: use it and overwrite it.
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

int readfiles(int argc, char *argv[])
{
    int getflags = 0;
    int recursive = 0;
    int flagcount = 0;
    int i = 0;


    while ((getflags = getopt(argc, argv, "r")) != -1)
    {
        switch (getflags)
        {
            case 'r':
                flagcount++;
                recursive = 1;
                break;
            /*  if some other option was given */
            case '?':
                flagcount++;
                /*  print out printable characters */
                if (isprint(optopt))
                {
                    printf("sortnames: wrong option %c\n", optopt);
                }
                /*  non-printable characters */
                else
                {
                    printf("sortnames: wrong option %#x\n", optopt);
                }
                break;
        }

    for (i = optind; i < argc; i++)
    {
         printf ("Non-option argument %s\n", argv[i]);
    }


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
