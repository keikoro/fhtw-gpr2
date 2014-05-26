/*  labrob program
    labrob.cpp

    GPR2 UE5 + UE6 + UE7

    if13b070 - K Kollmann
    if13b076 - Linda Spindler


	TODO (feeback tutorial)
	- have a "step forward" method in robots
    - have a "is_free" method in mazes that checks if what's in
	front of the robot is a wall or not
	- search for the entrance and the exit of the labyrinth with a
    method in mazes; when starting in the upper left corner, the first
    opening in the maze in the outer perimeter is always the entrance,
    the second always the exit
    - have a variable (a char?) in robots that saves the direction the
    robot is currently looking into


    Programm for sending robots through mazes with different search
    algorithms and printing stats about their performance.

    Status:
    - wrote function "add_robots" that saves pointers to robots to a
    vector that is declared in the "mazes" class.
    - the method "exit_search" can be called and generates the
    intended output (different one for robots and t1, so I think the
    add_robots method works as intended)
    - "print_robots" prints the the current list of robots
    (= the robot_list vector); could be used and expanded on later for
    going through the vector in general (to print stats and whatever
    else is needed)
    - added error message when file couldn't be opened

    Issues/other TODOs:
    - with the current char to int conversion, only the last argument
    that has been entered with -tN is converted to int; either write
    an int vector to save them all, or go back to the previous
    version that saved all of them as a string.
    - need to get the numbers for the robot types
    (1, 2, 3, none, which means 1) from checkuserinput() to main()
    - need to free the allocated space again, right now program
    doesn't do this at all
    - made everything in the classes public, remember to put everything
    that doesn't need to be public back to private later, but only after
    we're done with the whole program
    - maybe also use "const" (which can be used for making something in
    a class visible but read-only from outside)
    - opening the file should probably be moved from main to
    checkuserinput; not a priority though, works fine like it is right now

	Next steps:
	- resolve the -tN arguments issue
	- free space
	- start working on actual search algorithms?!!!
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <unistd.h>
#include "robots.h"
#include "mazes.h"
#include "t1.h"

using namespace std;

void checkuserinput(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    string one_row;
    vector<string> v_maze;

    std::ifstream mazefile (argv[1], std::ifstream::in);
    if (mazefile.is_open())
    {
        while ( getline (mazefile,one_row) )
        {
            v_maze.push_back (one_row);
        }
    }
    mazefile.close();

    checkuserinput(argc, argv);

    //make an instance of mazeses called mymaze
    Mazes mymaze;
    /*  the v_maze vector is equal to the vector v_maze here in main
		Can move this to a method in mazes, but this is not a priority
	*/
    mymaze.v_maze = v_maze;

	// add a robot of type 1 to the list
    mymaze.add_robot(new t1());
	//add a robot with no specific type to the list
	mymaze.add_robot(new Robots());

	mymaze.print_robots();

/*
	an int saving the robot type (1,2,3, needs to come from
	the checkuserinput function. 1 is default
	int robot_type = 1;
*/
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
    char *robot_type=NULL;
    std::vector<int> robot_numbers;
	int robot_number;

//    string *robot = new string();
    string *maze = new string();

    // print all arguments
    // std::cout << "argc: " << argc << std::endl;
    // for (int i = 0; i < argc; ++i)
    //     std::cout << "argv: "<< argv[i] << std::endl;

    while ((getflags = getopt(argc, (char **)argv, "t::h")) != -1) {

        switch(getflags) {
            case 'h':
                cout << helpmsg << endl; // prints help message
                exit(EXIT_FAILURE);
                break;
            case 't':
                    robot_type=optarg;
                    // print number of robot
                    cout << "the robot number is " << robot_type << endl;
					if (robot_type != NULL)
					{
						int robot_number = 1;
						sscanf(robot_type, "%d", &robot_number);

						robot_numbers.push_back (robot_number);
					}
					else
					{
						cout << "Option missing" << endl;
						exit(EXIT_FAILURE);
					}					
					
					
					break;
        }
    }
    
	if (argc < optind+1) /* wrong nb of options */
	{
	  cout << "Too few options!" << endl;
	  exit(EXIT_FAILURE);
	}
    
	*maze = argv[optind];


	cout << "All the arguments in an int vector: ";
	for(std::vector<int>::iterator i=robot_numbers.begin();
		i != robot_numbers.end(); i++)
	{
		robot_number = *i;
		cout << robot_number << "   ";
	}
	cout << endl;
}

/*
	create a node for the list (called "list_element")
	and put the robot into the "a_robot_in_a_list" part of the struct
*/
void Mazes::add_robot(Robots *a_robot)
{
	robot_list.push_back (a_robot);
}

void t1::exit_search()
{
	cout << "Robot of type 1 is looking for an exit" << endl;
}

void Robots::exit_search()
{
	cout << "This robot is looking for an exit" << endl;
}

void Mazes::print_robots()
{
	for(std::vector<Robots*>::iterator i=robot_list.begin();
		i != robot_list.end(); i++)
	{
		Robots* a_robot = *i;
		a_robot->exit_search();
	}
}
