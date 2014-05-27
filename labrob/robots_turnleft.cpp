/*  labrob program
    robots_turnleft.cpp

    GPR2 UE5 + UE6 + UE7

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    function that makes a robot turn to its left
*/

char Robots::turn_left(Robots robot)
{
    if (robot.direction == 'n')
    {
        robot.direction = 'w';
    }
    else
    if (robot.direction == 'w')
    {
        robot.direction = 's';
    }
    else
    if (robot.direction == 's')
    {
        robot.direction = 'e';
    }
    else robot.direction = 'n';

    return (robot.direction);
}



char Robots::turn_right(Robots robot)
{
    if (robot.direction == 'n')
    {
        robot.direction = 'e';
    }
    else
    if (robot.direction == 'w')
    {
        robot.direction = 'n';
    }
    else
    if (robot.direction == 's')
    {
        robot.direction = 'w';
    }
    else robot.direction = 's';

    return (robot.direction);
}
