/*
User is supposed to enter names for an input file (needs to exist) and an output file, which may or may not exist.

If the output file does not exist yet, create a new file with the given name. If it already exists: use it and overwrite it.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define NAMENSLAENGE 256


int readfiles(int argc, char *argv[])
{
    int i = 0;

    /*  not enough arguments given at program start
        (argc always includes program name as well!)
    */
    if (argc < 3)
    {
        printf("sortnames: wrong number of input or output files\n");
        return 1;
    }
    else
    {
        for(; i<argc; i++)
        {
            printf("argv is %s\n", argv[i]);
        }
        return 0;
    }

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
