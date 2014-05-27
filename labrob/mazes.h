/*  labrob program
    mazes.h

    GPR2 UE5 + UE6 + UE7

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    class for mazes

	IMPORTANT: the maze is saved as a string vector.
	This means that when referencing one character withing the maze like this:
		vector[v][h] (where "vector" is the vector and v and h are ints)
	"v" is the index on the y-axis (vertical), and 
	"h" the index on the x-axix (horizontal)
*/


#ifndef MAZES_H
#define MAZES_H

class Mazes {
public:
/*
 TODO return things to "private" later,
 commented it out now for easier testing
*/
//private:
	// Vector that contains the maze
	std::vector<std::string> v_maze;
	
	/* int arrays for saving the coordinated of entrance and exit of
		the maze, and method for finding the entrance as well as the
		robot start position in the robot; char for saving
		that start position
	*/
	int entrance [2];
	int mazeexit [2];
	int find_entrance(std::vector<std::string> v_maze);
	char startposition;

	void dummy_function_for_printing();
	
	// A vector that saves pointers to instances of robots
	std::vector<Robots*> robot_list;
	
	// function for adding new robots to the vector
	void add_robot (Robots *a_robot, Mazes maze);
	
	// function for printing out the list of all robots
	void print_robots();	
	
	/* function to check whether the char right in front of the 
	   robot is a wall or not */
	bool is_wall(int v, int h, char direction, 
		std::vector<std::string> v_maze);
};

#endif // MAZES_H
