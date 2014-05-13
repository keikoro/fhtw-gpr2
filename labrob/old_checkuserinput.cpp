#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <getopt.h>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include "mazes.h"
#include "robots.h"


void checkuserinput (int argc, char *argv[]) {

    // std::ifstream mazefile (argv[1], std::ifstream::in);
    int err = 0;
    int i, j = 0;
    int robottype = 0;
    // int usagemsg = 0;
    char *mazename;
    char *programname = argv[0];
    int getflags = 0;
    char helpmessage[] = "To send a robot through the labyrinth, \nplease "
                        "enter the filename of the maze you'd like to use\n"
                        "as well as the shortcut of the robot (t1 to t3), "
                        "like so:\n";
    // char *filename=argv[1];


    while ((getflags = getopt(argc, argv, "th")) != -1)
    {
        /*  suppress auto system error msgs on wrong flags */
        opterr = 0;
        switch (getflags)
        {
            case 't':
                robottype = optopt;
                printf("Using a robot: %c\n", robottype);
                break;
            case 'h':
                // usagemsg = optopt;
                printf("%s %s filename_of_maze -t1\n", helpmessage, programname);
                break;
            /*  if unknown flags were given */
            case '?':
                break;
            default:
                break;
        }
    }


    /*  loop through file names */
    for (i = 0; i < argc; i++)
    {
         j++;
         printf("Argument #%d is: %s\n", i, argv[i]);
    }

    if(err == 1)
    {
                printf("%s %s filename_of_maze -t1\n", helpmessage, programname);
    }

    if (j >= 2)
    {
        mazename = argv[optind];

        printf("Works!\n");
        exit(1);

    }
    /*  if there aren't enough filenames */
    else
    {
        fprintf(stderr, "%s: You must provide a robot name!\n", argv[0]);
        exit(1);
    }

}

