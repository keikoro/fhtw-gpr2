#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <getopt.h>
#include "mazes.h"
#include "robots.h"


void checkuserinput (int argc, char *argv[]) {

    // std::ifstream mazefile (argv[1], std::ifstream::in);
    int c;
    int error = 0;
    int i;
    char *robottype=NULL;
    char *usagemsg=NULL;
    char *programname=argv[0];
    // char *filename=argv[1];

    while((c = getopt(argc, argv, "th")) != EOF)
    {
        switch(c)
        {
            case 't':
                if (robottype!=NULL) /* Argument used more than once */
                {
                  error=1;
                  break;
                }
                robottype=optarg;
                printf("Using a robot: %s\n", robottype);
                break;
            case 'h':
                if (usagemsg!=NULL)
                {
                  error=1;
                  break;
                }
                usagemsg=optarg;
                // following printf to be deleted later, but useful for debugging
                printf("To send a robot through the labyrinth, \nplease "
                        "enter the filename of the maze you'd like to use\n"
                        "as well as the shortcut of the robot (t1 to t3), "
                        "like so:\n"
                        "%s filename_of_maze -t1\n", programname);
                break;
            case '?':
                error=1;
                break;
            default:
                break;
        }
    }


    /*  loop through file names */
    for (i = 0; i < argc; i++)
    {
         printf("Argument #%d is: %s\n", i, argv[i]);
    }

}

