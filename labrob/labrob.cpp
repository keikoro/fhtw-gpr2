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

//NOTE: Current programm causes stack overflow! Uploading it for sharing anyway.
// But previous commit is last functioning programm.

// TODO: remove later, überbleibsel of original function
// void checkuserinput(int argc, char *argv[], char **inputfile);

//class mazes {
//public:
//    void checkuserinput(char**);
//    vector<string> createmaze(char**); // function for read
////private:
//    string one_row;
//    vector<string> v_maze;
//};
//std::vector<string> createmaze (char** inputfile)
//{
//    string one_row;
//    vector<string> v_maze;
//    std::ifstream mazefile (*inputfile, std::ifstream::in);
//
//    if (mazefile.is_open())
//    {
//        while ( getline (mazefile,one_row) )
//        {
//            v_maze.push_back (one_row);
//        }
//    }
//    mazefile.close();
//
//    return v_maze;
//}
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

    std::ifstream mazefile (*inputfile);

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


int main(int argc, char *argv[])
{

//    mazes.checkuserinput(argv[1]);

    // create an instance of mazes
    // mazes mazefile;

    char *filename = argv[1];
    mazes mymaze;
    vector<string> v_maze;
    v_maze = mymaze.createmaze(&filename);


    cout << "Our current maze:\n";
    for(unsigned int i=0; i<v_maze.size(); ++i)
        cout << v_maze[i] << endl;

    return 0;
}

//void mazes::checkuserinput (char *inputfile) {

    // function that includes/refers to checkuserinput (= getopt func)
    // ... ??

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



//}
