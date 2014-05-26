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
    - wrote find_entrance method; make it more efficient (less repeated
	code
    - added error message when file couldn't be opened

    Issues/other TODOs:
    - contonie with with find_entrance method (doesn't work right now)
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
    - for efficiency's sake, maybe find entrance and exit right when
		reading in the file?

	Next steps:
	- free space
	- get those t? arguments to main somehow
	- expand the find_entrance method
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

using namespace std;

// void checkuserinput(int argc, char *argv[]);

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
        
        
	mymaze.find_entrance (v_maze);


    return 0;
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


/* function that calculates the coordinates of the entrance,
 right now only if it is in the first line.
 Returns 0 (instead of being declared void) so I can easily leave
 the whole program anytime
 */
int Mazes::find_entrance(std::vector<std::string> v_maze)
{
	
	/* Note: when going through the string vector with v_maze[a][b]
		a is the index on the HEIGHT, b of the LENGTH; this is the 
		opposite of the usual convention that looks at the x-axies first!
	*/
	
	 // lenght of the maze is length of the strings:
	unsigned int maze_length = v_maze[0].length();
	
	// height of the maze is length of the vector:
	unsigned int maze_height = v_maze.size();
	
	bool found_entrance = false;
//	bool found_exit = false;

	// look for entrance at the top
	for (unsigned int i = 1; i < maze_length-1; ++i)
	{
		if(v_maze[0][i] != '#')
		{
			entrance[0] = i;
			entrance[1] = 0;
			// inverse order (x-coordinate first) for the printout
			cout << "Coordinated of the entrance up: X, Y: " <<
				entrance[0] << "," << entrance [1] << endl;		
				found_entrance = true;		
				return 0;
		}
	}
	
	// if the entrance is not in the first row look on the right side
	if (found_entrance == false)
	{
		for (unsigned int i=1; i < maze_height-2; ++i)
		{
			if(v_maze[i][maze_length-1] != '#')
			{
				entrance[0] = v_maze[0].length();
				entrance[1] = i;
				cout << "Coordinated of the entrance right: X, Y: " <<
					entrance[0] << "," << entrance [1] << endl;
					found_entrance = true;
					return 0;
			}		
		}
	}

	// look for entrance at the bottom
	if (found_entrance == false)
	{
		for (unsigned int i = maze_length-1 ; i >= 1 ; --i)
		{
			if(v_maze[maze_height-2][i] != '#')
			{
				entrance[0] = i;
				entrance[1] = maze_height;
				// inverse order (x-coordinate first) for the printout
				cout << "Coordinated of the entrance down: X, Y: " <<
					entrance[0] << "," << entrance [1] << endl;				
					return 0;
			}
		}
	}
	
	// look for entrance on the left
	if (found_entrance == false)
	{
		for (unsigned int i=maze_height-2; i >= 1 ; --i)
		{
			if(v_maze[i][0] != '#')
			{
				entrance[0] = 0;
				entrance[1] = i;
				cout << "Coordinated of the entrance right: X, Y: " <<
					entrance[0] << "," << entrance [1] << endl;
					found_entrance = true;
					return 0;
			}		
		}
	}
	
	return 0;
}
