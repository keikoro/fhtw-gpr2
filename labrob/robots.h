#ifndef ROBOTS_H
#define ROBOTS_H


class robots{
public:	
	robots();
	~robots();
	char robotcharacter;	// character the robot draws on the labyrinth,
							// has to be accessible from outside
protected:
	void exit_search(); // function that will contain the search algorithm
};
// dummy function for exit search
//~ void exit_search(){
	//~ if (mazes.v_maze[0][0] == '#')
		//~ mazes.v_maze[0][0] = 'a';
//~ };
#endif // ROBOTS_H
