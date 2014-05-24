/*  labrob program
    robots.h

    GPR2 UE5 + UE6 + UE7

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    class for robots that will be sent through the maze
*/

#ifndef ROBOTS_H
#define ROBOTS_H

// TODO: put things back to private (commented out now)

class Robots {
//private:
	// function that will contain the search algorithm
//	void exit_search(); 
	// character the robot draws on the labyrinth,
	char robotcharacter;
	// integers for saving the coordinates of the robot
	int x,y;
protected:
	// function that will contain the search algorithm
	void exit_search(); 
};

#endif // ROBOTS_H
