/* Small programm for reading mazes (here from "maze1_small.txt" in the
    directory mazes) into a vector and then printing that vector

*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*class maze{
public:




};*/

using namespace std;

int main()

{
    string one_row;
    vector<string> labyrinth;

    ifstream labyrinth_file;
    labyrinth_file.open ("mazes/maze1_small.txt", ios::in);
    if (labyrinth_file.is_open())
    {
        while ( getline (labyrinth_file,one_row) )
        {
            labyrinth.push_back (one_row);
        }
    }
    labyrinth_file.close();


// Prints the labyrinth:
    cout << "Out current Labyrinth:\n";
    for(int i=0; i<labyrinth.size(); i++)
        cout << labyrinth[i] << '\n';
}
