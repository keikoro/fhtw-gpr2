/*  labrob program
    labrob.cpp

    GPR2 UE5 (+ UE6, UE7)

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    Small programm for reading mazes into a C++ vector
    and then printing that vector.

*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <getopt.h>
#include <unistd.h>
#include "mazes.h"
#include "robots.h"

using namespace std;

void checkuserinput(int argc, char *argv[]);

int main(int argc, char *argv[])
{

    string one_row;
    vector<string> v_maze;

    // create an instance of mazes
    // mazes mazefile;
    // mazes *mymaze = new mazes();

    // move the below from main to checkuserinput
    std::ifstream mazefile (argv[1], std::ifstream::in);

    if (mazefile.is_open())
    {
        while ( getline (mazefile,one_row) )
        {
            v_maze.push_back (one_row);
        }
    }
    mazefile.close();

    mazes mymaze; //make an instance of mazeses called mymaze
    /*  the v_maze vector is equal toe the vector v_maze here in main */
    mymaze.v_maze = v_maze;

    checkuserinput(argc, argv);

    cout << "Our current maze:\n";
    for(unsigned int i=0; i<mymaze.v_maze.size(); i++)
        cout << mymaze.v_maze[i] << endl;

    return 0;
}

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
