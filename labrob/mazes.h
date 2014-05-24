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
 return things to private later,
 commented in out now for easier testing
*/
//private:
	// Vector that contains the maze
	std::vector<std::string> v_maze;
	
	
	// A stuct for saving pointers to individual instances of robots
	struct node
	{
		Robots *a_robot_in_a_list; // pointer to a robot
		struct node *next;
	};
	// typdef so we don't have to write "struct node" every time
	typedef struct node list;

	/* the function to call when adding a robot
		by default should be of type t1 (TODO)
	*/
	void add_robot (Robots **a_robot); 
	list *head = NULL;
};

#endif // MAZES_H
