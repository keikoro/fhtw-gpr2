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

void checkstdin(int argc, char *argv[], char **inputfile);

class mazes {
public:
    string one_row;
    vector<string> v_maze;
    // include a function that includes/refers to checkstdin (= getopt func)
    // ... ??
};


int main(int argc, char *argv[])
{

    string one_row;
    vector<string> v_maze;

    // create an instance of mazes
    // mazes mazefile;

    // move the below from main to checkstdin
    std::ifstream mazefile (argv[1], std::ifstream::in);

    if (mazefile.is_open())
    {
        while ( getline (mazefile,one_row) )
        {
            v_maze.push_back (one_row);
        }
    }
    mazefile.close();

    // Prints the v_maze:
    cout << "Out current v_maze:\n";
    for(int i=0; i<v_maze.size(); i++)
        cout << v_maze[i] << endl;

    return 0;
}


void checkstdin(int argc, char *argv[], char **inputfile) {

    // std::ifstream mazefile (argv[1], std::ifstream::in);

    // getopt blabla...
    // copy-pasted from gridserver program
    // needs adaption....

    // int c;
    // int error=0;
    // char *x_axis=NULL;
    // char *y_axis=NULL;
    // program_name=argv[0];

    // while( (c = getopt(argc, argv, "x:y:")) != EOF )
    // {
    //     switch( c )
    //     {
    //         case 'x':
    //             if (x_axis!=NULL) /* Argument used more than once */
    //             {
    //               error=1;
    //               break;
    //             }
    //             x_axis=optarg;
    //             printf("%s: parsing option x, argument: %s\n",inputfile,x_axis);
    //             break;
    //         case 'y':
    //             if (y_axis!=NULL)
    //             {
    //               error=1;
    //               break;
    //             }
    //             y_axis=optarg;
    //             // following printf to be deleted later, but useful for debugging
    //             printf("%s: parsing option y, argument: %s\n",inputfile,y_axis);
    //             break;
    //         case '?':
    //             error=1;
    //             break;
    //         default:
    //             assert( 0 );
    //     }
    // }
}

