/*  labrob program
    robots.h

    GPR2 UE5 + UE6 + UE7

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    class for robots that will be sent through the maze
*/

#ifndef ROBOTS_H
#define ROBOTS_H

// TODO: put things back to private/protected (commented out for testing)

class Robots {
	public:
//private:
	// character the robot draws on the labyrinth:
	char robotcharacter;
	// integers for saving the coordinates of the robot
	int v, h;
//protected:
	// function that will contain the search algorithm
	virtual void exit_search();
	
	/* saving which way the robot is facing; should contain 
	   'n', 'e', 's', 'w'
	*/
	char direction;
	
	void turn_left();
	void turn_right();
	void step_forward();
};

#endif // ROBOTS_H
