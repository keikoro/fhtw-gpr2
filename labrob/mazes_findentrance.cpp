/* function that calculates the coordinates of the entrance,
 right now only if it is in the first line.
 Returns 0 (instead of being declared void) so I can easily leave
 the whole program anytime

 Status:
 - should now find the correct coordinated for entrance and exit
   and prints them.

 */
 
using namespace std;
 
 
int Mazes::find_entrance(std::vector<std::string> v_maze)
{
	
	/* 
	*/
	
	 // lenght of the maze is length of the strings:
	unsigned int maze_length = v_maze[0].length();
	
	// height of the maze is length of the vector:
	unsigned int maze_height = v_maze.size();
	
	bool found_entrance = false;
	bool found_exit = false;

// cout << "Length: " << maze_length << endl; << "Height: " << maze_height <<endl;

	// look for entrance/exit at the top; the corner is irrelavant
	// so stop at maze_length - 2
	for (unsigned int i = 1; i < maze_length-1; ++i)
	{
		if(v_maze[0][i] != '#')
		{
			if (found_entrance == false)
			{
				found_entrance = true;
				entrance[0] = i;
				entrance[1] = 0;
				cout << "Entrance is at the top" << endl;
				continue; // next iteration of the loop
			}
				else
			{
				found_exit = true;
				mazeexit[0] = i;
				mazeexit[1] = 0;
				cout << "Exit is at the top" << endl;
				return 0;
			}
		}
	}
	
	// if the entrance/exit is not in the first row look on the right side
	if (found_entrance == false || found_exit == false)
	{
		for (unsigned int i=1; i <= maze_height-2; ++i)
		{
			if(v_maze[i][maze_length-1] != '#')
			{
				if (found_entrance == false)
				{
					found_entrance = true;
					entrance[0] = v_maze[0].length()-1;
					entrance[1] = i;
					cout << "Entrance is on the right" << endl;
					continue; // next iteration of the loop
				}
					else
				{
					found_exit = true;
					mazeexit[0] = v_maze[0].length()-1;
					mazeexit[1] = i;
					cout << "Exit is on the right" << endl;				
					return 0;
				}
			}
		}
	}

	// look for entrance/exit at the bottom
	if (found_entrance == false || found_exit == false)
	{
		for (unsigned int i = maze_length-2 ; i >= 1 ; --i)
		{
			if(v_maze[maze_height-1][i] != '#')
			{
				if (found_entrance == false)
				{
					found_entrance = true;
					entrance[0] = i;
					entrance[1] = maze_height-1;
					cout << "Entrance is at the bottom" << endl;
					continue; // next iteration of the loop
				}
					else
				{
					found_exit = true;
					mazeexit[0] = i;
					mazeexit[1] = maze_height-1;
					cout << "Exit is at the bottom" << endl;
					return 0;
				}
			}
		}
	}
	
	// look for entrance on the left
	if (found_entrance == false || found_exit == false)
	{
		for (unsigned int i=maze_height-2; i >= 1 ; --i)
		{
			if(v_maze[i][0] != '#')
			{
				if (found_entrance == false)
				{
					found_entrance = true;
					entrance[0] = 0;
					entrance[1] = i;
					cout << "Entrance is on the left" << endl;
					continue; // next iteration of the loop
				}
					else
				{
					found_exit = true;
					mazeexit[0] = 0;
					mazeexit[1] = i;
					return 0;
				}
			}		
		}
	}	
	return 0;
}
