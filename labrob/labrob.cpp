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


    TODOS / ISSUES:
    - need to free the allocated space again, right now program
    doesn't do this at all
    - exit_search function in t2 isn't working; need to pay attention to
    what the recursion actually does
    - made everything in the classes public, remember to put everything
    that doesn't need to be public back to private later, but only after
    we're done with the whole program
    - maybe also use "const" (which can be used for making something in
    a class visible but read-only from outside)
    - for efficiency's sake, maybe find entrance and exit right when
    reading in the file?
	- add_robot needing a Mazes argument is a bit awkward; works tho
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
#include "t2.h"
#include "checkuserinput.cpp"
#include "mazes_findentrance.cpp"
#include "mazes_dummyprint.cpp"
#include "mazes_iswall.cpp"
#include "robots_stepforward.cpp"
#include "robots_turnleft.cpp"

#include "t2_exitsearch.cpp"

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

    /* print robots numbers for debugging -- TODO: remove later on
		Note: only remove the print statement, not the loop!
	*/
    int robot_number;
    cout << endl << "robot_numbers: ";
    for(vector<int>::iterator i=robot_numbers.begin();
        i != robot_numbers.end(); i++)
    {
        robot_number = *i;
        cout << robot_number << " ";
        /* adding all the robots to the vector; right now with 1 and 2
		*/
        if (robot_number == 1)
        {
			mymaze.add_robot(new t1(), mymaze);
		}
		else
		if (robot_number == 2)
        {
			mymaze.add_robot(new t2(), mymaze);
		}
		else
		{
			mymaze.add_robot(new Robots(), mymaze);
		}
    }
    cout << endl;

	mymaze.print_robots(mymaze);

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
	a_robot->h = maze.entrance[1];
	a_robot->direction = maze.startposition;
}


void t1::exit_search()
{
	cout << "Robot of type 1 is looking for an exit" << endl;
}

void Mazes::print_robots(Mazes mymaze)
{
	for(std::vector<Robots*>::iterator i=robot_list.begin();
		  i != robot_list.end(); i++)
	{
		Robots* a_robot = *i;
		a_robot->exit_search(*a_robot, mymaze);
	}
}

void Robots::exit_search(Robots robot, Mazes this_maze)
{
	cout << "This robot is looking for an exit" << endl;
}

