/*  labrob program
    robots.h

    GPR2 UE5 + UE6 + UE7

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    class for robots that will be sent through the maze
*/

#ifndef ROBOTS_H
#define ROBOTS_H

class robots {
public:
	//~ robots();
	//~ ~robots();
	char robotcharacter;	// character the robot draws on the labyrinth,
	int x,y;				// integers for saving the
							// coordinates of the robot
protected:
	void exit_search(); // function that will contain the search algorithm
};

#endif // ROBOTS_H
