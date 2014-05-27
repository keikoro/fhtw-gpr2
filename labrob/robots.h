/*  labrob program
    robots.h

    GPR2 UE5 + UE6 + UE7

    if13b070 - K Kollmann
    if13b076 - Linda Spindler

    class for robots that will be sent through the maze
*/

#ifndef ROBOTS_H
#define ROBOTS_H

class Mazes;

// TODO: put things back to private/protected (commented out for testing)

class Robots {
	public:
//private:
	// character the robot draws on the labyrinth:
	char robotcharacter;

	int step_counter;
	/* integers for saving the coordinates of the robot;
		v is for the y-axis (vertical), h for the x-axis (horizontal)*/
	int v, h;
//protected:
	// function that will contain the search algorithm
    virtual void exit_search(Robots robot, Mazes this_maze);

	/* saving which way the robot is facing; should contain
	   'n', 'e', 's', 'w'
	*/
	char direction;

	/* function for robot movement (started writing them but not
		changing anything in the main function right now;
		the instances of Robots that are called "robot" in the function
		need to come from going through the vector of Robots pointers
		saved through Mazes
	*/
	char turn_left(Robots robot);
	char turn_right(Robots robot);
	Robots step_forward(Robots robot);
};

#endif // ROBOTS_H
