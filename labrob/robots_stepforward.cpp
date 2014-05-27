/*  labrob program
    robots_stepforward.cpp

    GPR2 UE5 + UE6 + UE7

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    function that makes a robot step forward
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
