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

using namespace std;

//NOTE: No longer get a stack overflow, but no output at all.

// TODO: remove later, überbleibsel of original function
// void checkuserinput(int argc, char *argv[], char **inputfile);

class mazes {
public:
    void checkuserinput(char**);
    vector<string> createmaze(char**){}; // function for read
//private:
    string one_row;
    vector<string> v_maze;
};

std::vector<string> createmaze (char** inputfile)
{
    string one_row;
    vector<string> v_maze;

    std::ifstream mazefile;
    mazefile.open(*inputfile);

    if (mazefile.is_open())
    {
        while ( getline (mazefile,one_row) )
        {
            v_maze.push_back (one_row);
        }
    }
    mazefile.close();

    return (v_maze);
}

class robot{
public:
private:
};


int main(int argc, char *argv[])
{

    char *filename = argv[1];
    mazes* mymaze = new mazes();


    cout << "Our current maze:\n";
    for(int i=0; i < mymaze->v_maze.size(); i++)
        cout << mymaze->v_maze[i] << endl;

    delete mymaze;

    return 0;
}
