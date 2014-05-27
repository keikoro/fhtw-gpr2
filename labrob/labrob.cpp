/*  labrob program
    labrob.cpp

    GPR2 UE5 + UE6 + UE7
    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    Program for sending robots through mazes with different kinds of
    search algorithms and printing statistics about the robots' performances.
    (When all robots have found their way from the entrance to the
    labyrinth to its exit, a table containing information on how many
    steps it took each robot to reach the exit is printed out.)

    Usage:
    labrob path_to_maze [-t1] [–t2] [–t3]...[-tN] [-h]

    With:
    -t1-tN being used for the robot type (if no type is specified, t1 is used)
    -h being used for printing a usage message


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
    - wrote find_entrance method (make it more efficient less repeated
	code later if possible, not a priority)
    - added error message when file couldn't be opened
	- add_robot now also adds the start direction and coordinates 

    Issues/other TODOs:
    - need to free the allocated space again, right now program
    doesn't do this at all
    - made everything in the classes public, remember to put everything
    that doesn't need to be public back to private later, but only after
    we're done with the whole program
    - maybe also use "const" (which can be used for making something in
    a class visible but read-only from outside)
    - for efficiency's sake, maybe find entrance and exit right when
		reading in the file?
	- add_robot needing a Mazes argument is a bit awkward; works tho

	Next steps:
	- !! figure out communication between classes: class that is included
		first connot use anything from the classes included bellow it
	- free space
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
#include "checkuserinput.cpp"
#include "mazes_findentrance.cpp"
#include "mazes_dummyprint.cpp"


using namespace std;

// void checkuserinput(int argc, char *argv[], string *mazefile,
//                     vector<int> *robot_numbers);

int main(int argc, char *argv[])
{
    string one_row;
    vector<string> v_maze;
    vector<int> robot_numbers;
    string bla = "";
    string *mazepath = &bla;

    checkuserinput(argc, argv, mazepath, &robot_numbers);

    /*  for reference:
        for strings one would use mazepath.c_str()
        for string pointers it's mazepath->c_str()
    */
    ifstream mazefile(mazepath->c_str(), ifstream::in);
    if (mazefile)
    {
        while (getline(mazefile,one_row))
        {
            v_maze.push_back(one_row);
        }
    } else {
        cout << "invalid file name" << endl;
        exit(EXIT_FAILURE);
    }
    mazefile.close();

    //make an instance of mazes called mymaze
    Mazes mymaze;
    /*  the v_maze vector is equal to the vector v_maze here in main
		Can move this to a method in mazes, but this is not a priority
	*/
    mymaze.v_maze = v_maze;


	mymaze.find_entrance(v_maze);

    /* print robots numbers for debugging -- TODO: remove later on */
    int robot_number;
    cout << endl << "robot_numbers: ";
    for(vector<int>::iterator i=robot_numbers.begin();
        i != robot_numbers.end(); i++)
    {
        robot_number = *i;
        cout << robot_number << " ";
        /* adding all the robots to the vector; later can be expanded
			with robot_number==2 and 3*/
        if (robot_number == 1)
        {
			mymaze.add_robot(new t1(), mymaze);
		}
		else
		{
			mymaze.add_robot(new Robots(), mymaze);
		}
    }
    cout << endl;

	mymaze.print_robots();

    cout << "Our current maze:\n";
    for(unsigned int i=0; i<mymaze.v_maze.size(); i++)
        cout << mymaze.v_maze[i] << endl;

	mymaze.find_entrance (v_maze);
	mymaze.dummy_function_for_printing();

    return 0;
}


/*
	create a node for the list (called "list_element")
	and put the robot into the "a_robot_in_a_list" part of the struct
*/
void Mazes::add_robot(Robots *a_robot, Mazes maze)
{
	robot_list.push_back (a_robot);
	a_robot->v = maze.entrance[0];
	cout << "Vertical: " << a_robot->v << endl;
	a_robot->h = maze.entrance[1];
	cout << "Horizontal: " << a_robot->h << endl;
	a_robot->direction = maze.startposition;
	cout << "Direction: " << a_robot->direction << endl;
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

