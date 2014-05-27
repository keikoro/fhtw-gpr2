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

void t2::exit_search(Robots robot, Mazes this_maze)
{
    step_counter = 0;
    /*  coordinates of the robot are directly accessible since they're
        stored in Robots (or t2)
    */
    while (! ( (robot.v == this_maze.mazeexit[0]) && (robot.h == this_maze.mazeexit[1]) ) )
    {
        cout << "V: " << robot.v << ", H: " << robot.h << endl;
        if (this_maze.is_wall(robot.v, robot.h, robot.direction, this_maze.v_maze))
        {
            /*  if there's a wall, turn left and try again */
            robot.direction = turn_left(robot);
            exit_search(robot, this_maze);
        }
        else
        {
            robot = step_forward(robot);
            step_counter++;
        }
    }
    cout << "Steps taken: " << step_counter << endl;
    cout << "Current position (X,Y): " << robot.h << ", " << robot.v << endl;
}
