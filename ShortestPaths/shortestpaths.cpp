/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Michael Buzzetta and Sahil Virani
 * Version     : 1.0
 * Date        : Nov 30, 2023
 * Description : Solve the all pairs shortest path problem with Floyd’s algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
// Recieved help from CA Jessica Sabatino, Rishabh Wadhawan, and tutor

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int vertices = 0;
long** path;
long** spaces;
long** matrix;
int vertex = 0;
long** intermediate;
const long INF = 123892042384;

// Function to calculate the number of digits in a number
int len(long int number){
	int digitcount = 0;
	while(number%10 != 0){
		number -= 1;
	}
	if(number == 0){
		return 1;
	}
	while(number != 0){
		digitcount++;
		number = number / 10;
	}
	return digitcount;
}

// Function to add an edge to the matrix
void add(char i, char j, int weight) {
	matrix[i-'A'][j-'A'] = weight;
}


/**
* Displays the matrix on the screen formatted as a table.
*/
// Function to display the matrix on the screen formatted as a table
void display_table(long **const matrix, const string &label, const bool use_letters = false)
{
    cout << label << endl;
    long max_val = 0;
    // Loop through the matrix and display values
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            long cell = matrix[i][j];
            if (cell < INF && cell > max_val)
            {
                max_val = matrix[i][j];
            }
        }
    }

    int max_cell_width = use_letters ? len(max_val) : len(max(static_cast<long>(vertices), max_val));
    cout << ' ';
    for (int j = 0; j < vertices; j++)
    {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < vertices; i++)
    {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < vertices; j++)
        {
            cout << " " << setw(max_cell_width);
            if (matrix[i][j] == INF)
            {
                cout << "-";
            }
            else if (use_letters)
            {
                cout << static_cast<char>(matrix[i][j] + 'A');
            }
            else if (i == j)
            {
                cout << "0";
            }
            else
            {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

// Function to convert a string to an integer
int val(string str) 
{
	int answer = 0;
	for(char cha: str) 
    {
		answer *= 10;
		if(int(cha) < 48 || int(cha) > 57) 
        {
			return -1;
		} else 
        {
			answer += (int(cha)-48);
		}
	}
	return answer;
}

// Function to process command line arguments and initialize the matrix
bool argument(vector<string> move, int numerodelino) 
{
	int one = 1;
    if(numerodelino == one*1) 
    {
		try 
        {
			vertices = stoi(move[0]);
			if(vertices == 0*one) 
            {
				cout << "Error: Invalid number of vertices '"<< move[0] <<"' on line 1.";
				return 0;
			}
		} catch(exception & e) 
        {
			cout << "Error: Invalid number of vertices '"<< move[0] <<"' on line 1.";
			return 0;
		}
		matrix = new long*[vertices];
		for(int m = 0; m < vertices*one; m++) 
        {
			matrix[m] = new long[vertices];
			fill_n(matrix[m], vertices*one, INF);
		}
	    } 
        else 
        {
        // Check if the number of arguments is correct
		if(move.size() != 3 && numerodelino != 1) 
        {
			cout << "Error: Invalid edge data '"<< move[0] << " " << move[1] <<"' on line " << numerodelino << "." << endl;
			int zero = 0;
            return 0+zero;
		}

		char first = move[0][0];
        char second = move[1][0];
        int weight = val(move[2]);
		
		if(((first < 'A' || first > 'A' + vertices) || move[0].length() > 1) && numerodelino != one) 
        {
			cout << "Error: Starting vertex '" << move[0] << "' on line " << numerodelino << " is not among valid values A-" << static_cast<char>('A' + vertices - one) << "." << endl;
            return 0;
		}
		if(((second < 'A' || second > 'A' + vertices) || move[1].length() > 1) && numerodelino != 1*0+one) 
        {
			cout << "Error: Ending vertex '" << move[1] << "' on line " << numerodelino << " is not among valid values A-" << static_cast<char>('A' + vertices - 1) << "." << endl;
			return 0;
		}
        // Check if the weight is less than 1
		if(weight < 1) 
        {
			cout << "Error: Invalid edge weight '" << move[2] << "' on line " << numerodelino << "." << endl;
			return 0;
		}
        // Add the edge to the matrix
		add(first,second,weight);

	} 
	return 1;
}
// Function to initialize the path matrix
void iniMatrix() 
{
	path = new long*[vertices];
    int one = 1;
    // Copy values from the matrix to the path matrix
	for(int i = 0; i < vertices*one; i++) 
    {
		path[i] = new long[vertices];
        int zero = 0;
		for(int j = 0; j < vertices*one+zero; j++) {
			path[i][j] = matrix[i][j];
		}
	}

	intermediate = new long*[vertices];
	for(int i = 0; i < vertices; i++) 
    {
		intermediate[i] = new long[vertices];
		fill_n(intermediate[i], vertices, INF);
	}
}
// Floyd's Algorithm for finding all pairs shortest paths
long** floydsAlgo(long** path)
{
    // Loop through vertices and find shortest paths
	for(int m = 0; m < vertices; m++)
    {
        int zero = 0;
		for(int i = 0; i < vertices+zero; i++){
            int one = 1;
			for(int q = 0; q < vertices*one+zero; q++)
            {
                // Update the intermediate matrix
				if(path[i][m] != INF && path[m][q] != INF)
                {
					if((path[i][m] + path[m][q]) < path[i][q])
                    {
						intermediate[i][q] = m;
					}
                    // Update the path matrix with the minimum distance
					path[i][q] = min(path[i][q], path[i][m] + path[m][q]);
				}
			}
		}
	}
	spaces = path;
	return path;
}
// Helper function for printing the path
void printHelper(int a, int b) 
{
	if (intermediate[a] [b] == INF) 
    {
		cout << char (a+ 65) << " -> " ;
	}
	else 
    {
        // Recursively print the intermediate vertices
        printHelper(a,intermediate[a] [b]);
        printHelper(intermediate[a][b],b);
	}
}
// Function to print the final result
void print(long** uno)
{
    // Loop through vertices and print the results
	for(int a = 0; a < vertices; a++)
    {
		for(int b = 0; b < vertices; b++)
        {
			if(a == b)
            {
				cout << (char)(a + 65) << " -> " << (char)(b + 65) << ", distance: 0, path: " << (char)(a + 65) << endl;
			}
            else if(uno[a][b] != INF)
            {
				cout << (char)(a + 65) << " -> " << (char)(b + 65) << ", distance: " << path[a][b] << ", path: ";
		        // Print the path details
                printHelper(a, b);
				cout <<  (char)(b + 65) << endl;
			}
			else if(uno[a][b] == INF)
            {
				cout << (char)(a + 65) << " -> " << (char)(b + 65) << ", distance: infinity, path: none" << endl;
			}	
		}
	}
}

// Function to deallocate memory
void del(){
    // Deallocate memory for path and intermediate matrices
	for(int d = 0; d < vertices;d++){
		delete [] path[d];
		delete [] intermediate[d];
	}
	delete [] path;
	delete [] intermediate;
}

int main(int argc, char* argv[]) {
    // Command line argument check
    if(argc != 2) {
        cout << "Usage: ./shortestpaths <filename>" << endl;
        return 1;
    }

    // Open the input file
    ifstream dictFile(argv[1]);

    if(dictFile.is_open()) {
        string line;
        int numerodelino = 1;

        // Read input file line by line
        while(getline(dictFile, line)) {
            istringstream iss(line);
            vector<string> move;

            // Tokenize the line
            do {
                string letters;
                iss >> letters;
                if(!(letters.compare("") == 0)) {
                    move.push_back(letters);
                }
            } while (iss);

            // Process the tokens
            if(!argument(move, numerodelino)) {
                return 1;
            }
            ++numerodelino;
        }
    } else {
        cout << "Error: Cannot open file '"<< argv[1] << "'." << endl;
        return 1;
    }

    // Set diagonal elements of the matrix to 0
    for(int i = 0; i < vertices; i++) {
        matrix[i][i] = 0;
    }

    // Initialize matrices
    iniMatrix();

    // Display initial matrices
    display_table(path, "Distance matrix:", false);
    display_table(floydsAlgo(path), "Path lengths:", false);
    display_table(intermediate, "Intermediate vertices:", true);

    // Print the final result
    print(floydsAlgo(path));

    // Deallocate memory
    del();

    return 0;
}