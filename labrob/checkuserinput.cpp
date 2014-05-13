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
    int i;
    int robottype = 0;
    // int usagemsg = 0;
    char *programname=argv[0];
    int getflags = 0;
    // char *filename=argv[1];


    while ((getflags = getopt(argc, argv, "th")) != -1)
    {
        /*  suppress auto system error msgs on wrong flags */
        //opterr = 0;
        switch (getflags)
        {
            case 't':
                robottype = optopt;
                printf("Using a robot: %c\n", robottype);
                break;
            case 'h':
                // usagemsg = optopt;
                printf("To send a robot through the labyrinth, \nplease "
                        "enter the filename of the maze you'd like to use\n"
                        "as well as the shortcut of the robot (t1 to t3), "
                        "like so:\n"
                        "%s filename_of_maze -t1\n", programname);
                break;
            /*  if unknown flags were given */
            case '?':
                /*  print out printable flags */
                if (isprint(optopt))
                {
                    fprintf(stderr, "%s: wrong option %c\n", argv[0], optopt);
                }
                /*  for non-printable characters */
                else
                {
                    fprintf(stderr, "%s: wrong option %c\n", argv[0], optopt);
                }
                exit(1);
                break;
        }
    }


    /*  loop through file names */
    for (i = 0; i < argc; i++)
    {
         printf("Argument #%d is: %s\n", i, argv[i]);
    }

    if(err == 1)
    {
        printf("You provided a wrong number of arguments!\n");
    }
    
}

