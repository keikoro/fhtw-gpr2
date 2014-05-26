/*  labrob program
    mazes.h

    GPR2 UE5 + UE6 + UE7

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    class for mazes
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
	
	// A vector that saves pointers to instances of robots
	std::vector<Robots*> robot_list;
	
	// function for adding new robots to the vector
	void add_robot (Robots *a_robot);
	
	// function for printing out the list of all robots
	void print_robots();	
};

#endif // MAZES_H
