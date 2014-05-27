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
