/*
    labrob program
    mazes_findentrance.cpp

    GPR2 UE5 + UE6 + UE7
    if13b070 - K Kollmann
    if13b076 - Linda Spindler


*/

using namespace std;


// function that prints the exit and entrance coordinates for debugging
void Mazes::dummy_function_for_printing()
{
	cout << "Coordinates of the entrance: X, Y: " <<
		entrance[0] << "," << entrance[1] << endl;
	cout << "Coordinates of the exit: X, Y: " <<
		mazeexit[0] << "," << mazeexit [1] << endl;
//	cout << "The robot enters the labyrinth facing: " << startposition << endl;
}
