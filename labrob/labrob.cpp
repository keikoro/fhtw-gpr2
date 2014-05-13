/*  labrob program
    labrob.cpp

    GPR2 UE5

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    Small programm for reading mazes into a C++ vector
    and then printing that vector.

*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <getopt.h>
#include "mazes.h"
#include "robots.h"
#include "checkuserinput.cpp"

using namespace std;

void checkuserinput (int argc, char argv[]);


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
	mymaze.v_maze = v_maze; //the v_maze vector is equal toe the vector v_maze here in main

    checkuserinput(argc, argv);

    cout << "Our current maze:\n";
    for(unsigned int i=0; i<mymaze.v_maze.size(); i++)
        cout << mymaze.v_maze[i] << endl;

    return 0;
}
