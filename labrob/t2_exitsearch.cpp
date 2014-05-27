/*  labrob program
    t2_exitsearch.cpp

    GPR2 UE5 + UE6 + UE7
    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    Search function for robots of type 2 (called when user enters -t2
    as an option). Takes an instance of Robots and an instance of Mazes as
    arguments and calls the functions Mazes::is_wall, Robots::turn_left
    and Robots::step_forward.

    The robot checks if there is a wall in front of it. If there is,
    it turns left and recursively calls the function again. If there isn't,
    it moves one step forward. The robot also saves the number of steps
    it has already taken.
*/


/*  labrob program
    mazes_iswall.cpp

    GPR2 UE5 + UE6 + UE7
    if13b070 - K Kollmann
    if13b076 - Linda Spindler
     
    Method in mazes that checks whether the robot has a wall in front of
    itself (what "in front of" mean depends on which way the robot is
    facing (=char direction). Returns TRUE if there is a wall and FALSE
    is there isn't
*/

using namespace std;




void t2::exit_search(Robots robot, Mazes this_maze)
{
    int step_count = 0;
    /*  coordinates of the robot are directly accessible since they're
        stored in Robots (or t2)
    */
    
    bool stop = false;

	while (!stop)
	{
		/*
			As long as there is no wall in front and a wall on the left,
			keep going
		*/
		if  (
			(!(this_maze.is_wall(robot.v, robot.h, robot.direction, this_maze.v_maze)) )
			&&
			(this_maze.wall_left(robot.v, robot.h, robot.direction, this_maze.v_maze))
			)
		{
			robot = step_forward(robot);
			step_count++;
			cout << "V: " << robot.v << ", H: " << robot.h << endl;
		}
		else
		{
			// if there's a wall on the left, turn right
			if (this_maze.wall_left(robot.v, robot.h, robot.direction, this_maze.v_maze))
			{
				robot.direction = turn_right(robot);
			}
			// if there is no wall on the left, turn left
			else
			{
				robot.direction = turn_left(robot);
			}
			// in both cases, leave the loop
			stop = true;
		}
	}
	cout << "Steps: " << step_count << endl;
}
	
	//~ while (! ( (robot.v == this_maze.mazeexit[0]) && (robot.h == this_maze.mazeexit[1]) ) )
	//~ {
		//~ cout << robot.v << " " << robot.h << endl;
		//~ while (! (this_maze.is_wall(robot.v, robot.h, robot.direction, this_maze.v_maze)) )
		//~ {
			//~ if (  !(this_maze.is_wall(robot.v, robot.h, robot.direction, this_maze.v_maze)) )
			//~ {
				//~ robot = step_forward(robot);
				//~ step_count++;
			//~ }
			//~ else break;
		//~ }
		//~ if (this_maze.wall_left(robot.v, robot.h, robot.direction, this_maze.v_maze))
		//~ robot.direction = turn_right(robot);
	//~ }

