#ifndef ROBOTS_H
#define ROBOTS_H


class robots{
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
