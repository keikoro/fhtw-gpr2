/*  labrob program
    t2_exitsearch.cpp
*/

void t2::exit_search(Robots robot, Mazes this_maze)
{
    step_counter = 0;

    /* coordinated of the robot, are directly accessible since they're
        stored in Robots (or t2)

    */
    while (! ( (robot.v == this_maze.mazeexit[0]) && (robot.h == this_maze.mazeexit[1]) ) )
    {
        cout << robot.v << robot.h << endl;
        if (this_maze.is_wall(robot.v, robot.h, robot.direction, this_maze.v_maze))
        {
            // if there's a wall turn left and try again
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
