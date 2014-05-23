/*  labrob program
    mazes.h

    GPR2 UE5 + UE6 + UE7

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    class for mazes
*/


#ifndef MAZES_H
#define MAZES_H

class mazes {
public:
	/*
	 function for adding a new robot into the maze
	 needs to be accessible by objects of class "robots"
	*/
	void add_robot();

private:
	// Vector that contains the maze
	std::vector<std::string> v_maze;
	/* List for saving pointers to the individual instances of robots
	   TODO: define lists (struct nodes)
	*/
//	list<robot*> robots_list;

};

#endif // MAZES_H
