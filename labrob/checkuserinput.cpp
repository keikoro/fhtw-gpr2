#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>

using namespace std;


void checkuserinput (int argc, char *argv[]) {

    string programname = argv[0];
    string helpmsg = "To send a robot through the labyrinth, \nplease "
                        "enter the filename of the maze you'd like to use\n"
                        "as well as the shortcut of the robot (t1 to t3), "
                        "like so:";

    int getflags;
    string *robot = new string();
    string *maze = new string();

    // print all arguments
    // std::cout << "argc: " << argc << std::endl;
    // for (int i = 0; i < argc; ++i)
    //     std::cout << "argv: "<< argv[i] << std::endl;

    while ((getflags = getopt(argc, (char **)argv, "t:h")) != -1) {

        switch(getflags) {
            case 'h':
                cout << helpmsg << endl; // prints help message
                exit(EXIT_FAILURE);
                break;
            case 't':
                    *robot = optarg;
                    // print number of robot
                    // cout << "the robot number is " << *robot << endl;
                break;
        }
    }

    *maze = argv[optind];
    // print name of maze
    // cout << "the maze name is " << *maze << endl;
}
