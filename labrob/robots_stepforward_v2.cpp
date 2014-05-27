/*  labrob program
    robots_stepforward.cpp

    GPR2 UE5 + UE6 + UE7

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    function that makes a robot step forward
    (direction in which it steps is dependent on direction it is facing)
*/

using namespace std;

/*  return character at given coordinates
    (either empty space or # for a wall)
*/
char Mazes::wall_check(int x, int y, char direction) {
    return v_maze[y-1][x];
}

Robots Robots::step_forward_v2(Robots robot)
{
    return(robot);
}
