#ifndef MAZES_H
#define MAZES_H

class mazes {
public:
	//~ mazes();
	//~ ~mazes();
    std::vector<std::string> v_maze;
    void add_robot();	// function for adding a new robot into the maze
						// needs to be accessible by objects of class "robots"
};

#endif // MAZES_H
