/*  labrob program
    mazes_iswall.cpp
*/

using namespace std;

bool Mazes::is_wall(int v, int h, char direction,
            std::vector<std::string> v_maze)
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
