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
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <unistd.h>
#include <pthread.h>
#include "robots.h"
#include "mazes.h"
#include "t1.h"
#include "t2.h"

using namespace std;

struct thread_data{
    int thread_id;
    Robots robot;
    Mazes this_maze;
    string hello;
};

void checkuserinput(int argc, char *argv[], string *mazefile,
                     vector<int> *robot_numbers);

// void *PrintHello(void *threadid)
// {
//    long tid;
//    tid = (long)threadid;
//    cout << "Hello World! Thread ID, " << tid << endl;
//    pthread_exit(NULL);
// }

void *PrintRobot(void *threadarg)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;

//    my_data->robot.exit_search(my_data->robot, my_data->this_maze);

    cout << "Thread ID : " << my_data->thread_id << endl;

    int bla = pthread_self();
    cout << bla << endl;

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    string one_row;
    vector<string> mazefile_lines;
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
            mazefile_lines.push_back(one_row);
        }
    } else {
        cout << "invalid file name" << endl;
        exit(EXIT_FAILURE);
    }
    mazefile.close();

    //  create an instance of mazes
    Mazes mymaze;
    /*  the v_maze vector is equal to the vector v_maze here in main
		Can move this to a method in mazes, but this is not a priority
	*/
    mymaze.v_maze = mazefile_lines;

	mymaze.find_entrance(mymaze.v_maze);

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

	mymaze.traverse_robots(mymaze);

    cout << "Our current maze:\n";
    for(unsigned int i=0; i<mymaze.v_maze.size(); i++)
    {
        cout << mymaze.v_maze[i] << endl;
    }

//	mymaze.dummy_function_for_printing();
	pthread_exit(NULL);

    return 0;
}

/*	create a node for the list (called "list_element")
	and put the robot into the "a_robot_in_a_list" part of the struct
*/
void Mazes::add_robot(Robots *a_robot, Mazes maze)
{
	robot_list.push_back (a_robot);
	a_robot->v = maze.entrance[0];
	a_robot->h = maze.entrance[1];
	a_robot->direction = maze.startposition;
}

void Mazes::traverse_robots(Mazes mymaze)
{
    int count = 1;
    int rc;
    // int num_threads = robot_numbers.size();
    pthread_t threads[3];
    struct thread_data td[3];
    int temp_arg[3];
    Robots *a_robot;

	for(vector<Robots*>::iterator i=robot_list.begin();
		  i != robot_list.end(); i++)
	{
		// a_robot->exit_search(*a_robot, mymaze);
        // a_robot->PrintRobot(*a_robot, mymaze);
        a_robot = *i;

        cout << "robot x: " << a_robot->v << endl;

        count++;
	}

        temp_arg[count] = count;

        td[count].robot = *a_robot;
        // td[count].this_maze = mymaze;
        td[count].hello = "hello";

        cout << "main() : creating thread, " << count << endl;
        rc = pthread_create(&threads[count], NULL,
                          PrintRobot,  static_cast<void*>(&temp_arg[count]));

        int bla = pthread_self();
        cout << bla << endl;

        if (rc!=0){
             cout << "Error:unable to create thread," << rc << endl;
             exit(-1);
        }


}

void Robots::exit_search(Robots robot, Mazes this_maze)
{
	cout << "This robot is looking for an exit" << endl;
}

/*    function that makes a robot step forward
    (direction in which it steps is dependend on direction it is facing)
*/

Robots Robots::step_forward(Robots robot)
{
    if (robot.direction == 'n')
    {
        robot.v--;
    }
    else
    if (robot.direction == 'w')
    {
        robot.h--;
    }
    else
    if (robot.direction == 's')
    {
        robot.v++;
    }
    else
    if (robot.direction == 'e')
    {
        robot.h++;
    }
    /*  message for debugging -- TODO: remove later on */
    else cout << "something went wrong (func Robots::step_forward)" << endl;

    return (robot);
}

/*
    function that makes a robot turn to its left
*/

char Robots::turn_left(Robots robot)
{
	switch(robot.direction)
	{
		case 'n': return ('w');
		break;
		case 'w': return ('s');
		break;
		case 's': return ('e');
		break;
		case 'e': return ('n');
		break;
	}
return 'x';
}

char Robots::turn_right(Robots robot)
{
	switch(robot.direction)
	{
		case 'n': return ('w');
		break;
		case 'w': return ('n');
		break;
		case 's': return ('w');
		break;
		case 'e': return ('s');
		break;
	}
return 'x';
}

/*
    Search function for robots of type 2 (called when user enters -t2
    as an option). Takes an instance of Robots and an instance of Mazes as
    arguments and calls the functions Mazes::is_wall, Robots::turn_left
    and Robots::step_forward.

    The robot checks if there is a wall in front of it. If there is,
    it turns left and recursively calls the function again. If there isn't,
    it moves one step forward. The robot also saves the number of steps
    it has already taken.
*/
void t2::exit_search(Robots robot, Mazes this_maze)
{
    int step_count = 0;
    /*  coordinates of the robot are directly accessible since they're
        stored in Robots (or t2)
    */

//    bool stop = false;

    int t = 23;

	while (t > 0)
	{
		/*
			As long as there is no wall in front and a wall on the left,
			keep going; also keep going if this was the very first step
			because then we treat the entrance as a wall
		*/
		if(
			(!(this_maze.is_wall(robot.v, robot.h, robot.direction, this_maze.v_maze)) )
			&&
			( (this_maze.wall_left(robot.v, robot.h, robot.direction, this_maze.v_maze))
					||
			  (step_count == 1)
		    )
		   )
		{
			robot = step_forward(robot);
			step_count++;
			cout << "V: " << robot.v << ", H: " << robot.h << endl;
		}
		else
		{
			cout << robot.direction << endl;
			// if there's a wall on the left, turn right
			if (this_maze.wall_left(robot.v, robot.h, robot.direction, this_maze.v_maze))
			{
				robot.direction = turn_right(robot);
				cout << "V again: " << robot.v << ", H again: " << robot.h << endl;

			}
			// if there is no wall on the left, turn left
			else
			{
				robot.direction = turn_left(robot);
			}
			// in both cases, leave the loop
		}
		t--;
	}
	cout << "Steps: " << step_count << endl;
}

/*
    Search function for robots of type 1.
    Type 1 robots try to find their way through the maze
    by always turning right.
*/

void t1::exit_search(Robots thisrobot, Mazes thismaze)
{
    string wall = "#";
    thisrobot.step_counter = 0;

    // thisrobot.h // x coordinate;
    // thisrobot.v // y coordinate;
    // thisrobot.direction // direction the robot is currently facing;

    cout << endl << "X: " << thisrobot.h << " Y: " << thisrobot.v << endl << endl
    << "facing: " << thisrobot.direction << endl << endl;

// thismaze.wall_check(thisrobot.v, thisrobot.h, thisrobot.direction)
    if(" " == wall)
    {
        cout << "wall!" << endl;
    }
    else
    {
        cout << "empty!" << endl;
    }

}

/*
    Method in mazes that checks whether the robot has a wall in front of
    itself (what "in front of" mean depends on which way the robot is
    facing (=char direction). Returns TRUE if there is a wall and FALSE
    is there isn't
*/

bool Mazes::is_wall(int v, int h, char direction,
            vector<string> v_maze)
{
    if (direction == 'n')
    {
        if (v_maze[v-1][h] == '#')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    if (direction == 'w')
    {
        if (v_maze[v][h-1] == '#')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    if (direction == 's')
    {
        if (v_maze[v+1][h] == '#')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    // (direction == 'e')
    {
        if (v_maze[v][h+1] == '#')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}


bool Mazes::wall_left(int v, int h, char direction,
            vector<string> v_maze)
{
    if (direction == 'n')
    {
        if (v_maze[v][h-1] == '#')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    if (direction == 'w')
    {
        if (v_maze[v+1][h] == '#')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    if (direction == 's')
    {
        if (v_maze[v][h+1] == '#')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    // (direction == 'e')
    {
        if (v_maze[v-1][h] == '#')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

int Mazes::find_entrance(std::vector<std::string> v_maze)
{
	 // length of the maze is length of the strings:
	unsigned long maze_length = v_maze[0].length();

	// height of the maze is length of the vector:
	unsigned long maze_height = v_maze.size();
	cout << maze_height << endl;

	bool found_entrance = false;
	bool found_exit = false;

// cout << "Length: " << maze_length << endl; << "Height: " << maze_height <<endl;

	/*	look for entrance/exit in the top row of the maze;
		the corner is irrelevant, so stop at maze_length-2 */
	for (unsigned int i = 1; i < maze_length-1; ++i)
	{
		if(v_maze[0][i] != '#')
		{
			if (found_entrance == false)
			{
				found_entrance = true;
				entrance[0] = 0;
				entrance[1] = i;
				startposition = 's';
				continue; // next iteration of the loop
			}
				else
			{
				found_exit = true;
				mazeexit[0] = 0;
				mazeexit[1] = i;
//				cout << "Exit is at the top" << endl;
				return 0;
			}
		}
	}

	/*	if the entrance/exit is not in the first row,
		look on the right side of the maze */
	if (found_entrance == false || found_exit == false)
	{
		for (unsigned int i=1; i < maze_height-1; ++i)
		{
			if(v_maze[i][maze_length-1] != '#')
			{
				if (found_entrance == false)
				{
					found_entrance = true;
					entrance[0] = i;
					entrance[1] = maze_length-1;
					startposition = 'w';
					continue; // next iteration of the loop
				}
					else
				{
					found_exit = true;
					mazeexit[0] = i;
					mazeexit[1] = maze_length-1;
		//			cout << "Exit is on the right" << endl;
					return 0;
				}
			}
		}
	}

	/*	look for entrance/exit at the bottom */
	if (found_entrance == false || found_exit == false)
	{
		for (unsigned int i = maze_length-2 ; i >= 1 ; --i)
		{
			if(v_maze[maze_height-1][i] != '#')
			{
				if (found_entrance == false)
				{
					found_entrance = true;
					entrance[0] = maze_height-1;
					entrance[1] = i;
					startposition = 'n';
					continue; // next iteration of the loop
				}
					else
				{
					found_exit = true;
					mazeexit[0] = maze_height-1;
					mazeexit[1] = i;
	//				cout << "Exit is at the bottom" << endl;
					return 0;
				}
			}
		}
	}

	/*	look for entrance on the left */
	if (found_entrance == false || found_exit == false)
	{
		for (unsigned int i=maze_height-2; i >= 1 ; --i)
		{
			if(v_maze[i][0] != '#')
			{
				if (found_entrance == false)
				{
					found_entrance = true;
					entrance[0] = i;
					entrance[1] = 0;
					startposition = 'e';
					continue; // next iteration of the loop
				}
					else
				{
					found_exit = true;
					mazeexit[0] = i;
					mazeexit[1] = 0;
					return 0;
				}
			}
		}
	}
	return 0;
}

char Mazes::wall_check(int x, int y, char direction) {
    return v_maze[y-1][x];
}

Robots Robots::step_forward_v2(Robots robot)
{
    return(robot);
}


void checkuserinput (int argc, char *argv[], string *mazefile, vector<int> *robot_numbers) {

    string helpmsg = "Usage: labrob path_to_maze "
                        "[-t1] [–t2] [–t3]...[-tN] [-h]";
    int getflags;
    int thisrobot;
    vector<int> initialrobotnumbers;
    string placeholder = "";
    *mazefile = placeholder;
    // string *maze = NULL;

    /*  use double colon for option argument for the*/
    while ((getflags = getopt(argc, (char **)argv, "t::h")) != -1) {

        switch(getflags) {
            case 'h':
                cout << helpmsg << endl;
                exit(EXIT_FAILURE);
                break;
            case 't':
                /*  if no argument is given, use 1  */
                if (optarg == NULL)
                {
                    /*  check if argument is a number  */
                    thisrobot = 1;
                    robot_numbers->push_back(thisrobot);
                }
                else
                {
                    if (isdigit(*optarg))
                    {
                        sscanf(optarg, "%d", &thisrobot);
                        robot_numbers->push_back(thisrobot);
                        /* below for debugging -- TODO: remove later on */
                        // cout << "robot " << thisrobot << endl;
                    }
                    else
                    {
                        cout << "invalid argument: " << optarg << endl;
                        cout << helpmsg << endl;
                        exit(EXIT_FAILURE);
                    }
                }
                break;
            /*  unknown option used */
            case '?':
                cout << "invalid option: " << optarg << endl
                << helpmsg << endl;
                exit(EXIT_FAILURE);
                break;
        }
    }

    /*  there must be at least 3 argv (program name, -t, file name of maze) */
    if (sizeof(argc) < 3)
    {
        cout << "not enough options provided" << endl << helpmsg << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        if (argv[optind])
        {
            /*  store the name of the maze file
                attn.: validity of file name is not yet confirmed */
            *mazefile = string(argv[optind]);
        }
        else
        {
            cout << "no maze file was provided!" << endl << helpmsg << endl;
        }
    }
}

