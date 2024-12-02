/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Sahil Virani and Michael Buzzetta
 * Date        : 10/17/23
 * Description : Program to solve the famous water jug puzzle using breadth-first search.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    vector<string> directions;
    //This instantiates a state with a vector<string> directions
    State(int _a, int _b, int _c, vector<string> _directions) : a(_a), b(_b), c(_c), directions(_directions) { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
    void print_directions(){
        for (size_t i = 0; i < directions.size(); i++){
            cout << directions[i] << endl;
        }
    }
};

//This function creates a 2D boolean array
bool** makeMatrix(int a, int b) {
    bool ** map = new bool*[a];
    for (int i = 0; i < a; i++){
        map[i] = new bool[b];
        fill(map[i], map[i] + b,false);
    }
    return map;
}
//This function deletes a previously made 2D boolean array 
//Needed for valgrind and memory leaks
void clearMatrix(bool **map, int size){
    for (int i = 0; i < size; i++){
        delete [] map[i];
    }
    delete [] map;
}
//This function takes in an integer and returns a string.
//Used in main, for printing which jug.
string jug(int i){
    if (i == 1 || i == 4){
        return "A.";
    }
    else if (i == 2 || i == 5){
        return "B.";
    }
    else {
        return "C.";
    }
}

//This function returns the goal state with the directions for the solution, or a state with "No solution." as its direction.
State bfs(State curr, State cap, State goal, bool ** map){
    queue<State> q;
    map[curr.a][curr.b] = true;
    //I push back the initial state before the while loop to ensure it only gets pushed one time.
    curr.directions.push_back("Initial state. " + curr.to_string());
    q.push(curr);
    //while the q is not empty exhuasts all possible solutions with BFS.
    //if the q is empty then there is no solution
    while (!q.empty()){
        curr = q.front();
        q.pop();
        //check to see if the current state is the goal state.
        if (curr.a == goal.a && curr.b == goal.b && curr.c == goal.c){
            return curr;
        }//checks if C can pour into A
        if ((cap.a - curr.a) > 0 && curr.c > 0){
            //created a temporary variable to do each pour on without changing the current state.
            State temp = curr;
            int pour = cap.a - temp.a;
            if (pour >= temp.c){
                temp.a += curr.c;
                temp.c = 0;
            }
            else {
                temp.c -= pour;
                temp.a = cap.a;
            }
            //Check to see if the state has been visited before
            if (map[temp.a][temp.b] == false){
                //if the state has not been visited we change it to visited and then continue.
                map[temp.a][temp.b] = true;
                if (pour == 1 || curr.c == 1){
                    //add the directions to the directions vector<string> before pushing the State onto the q
                    temp.directions.push_back("Pour 1 gallon from C to A. " + temp.to_string());
                    //pushing the temp State onto the q, which includeds the vector<string> directions part of the temp state.
                    q.push(temp);
                }
                else{
                    temp.directions.push_back("Pour " + std::to_string(min(pour, curr.c)) + " gallons from C to A. " + temp.to_string());
                    q.push(temp);
                }
            }
        }//checks if B can pour into A
        if ((cap.a - curr.a) > 0 && curr.b > 0){
            State temp = curr;
            int pour = cap.a - temp.a;
            if (pour >= temp.b){
                temp.a += temp.b;
                temp.b = 0;
            }
            else {
                temp.b -= pour;
                temp.a = cap.a;
            }
            if (map[temp.a][temp.b] == false){
                map[temp.a][temp.b] = true;
                if (pour == 1 || curr.b == 1){
                    temp.directions.push_back("Pour 1 gallon from B to A. " + temp.to_string());
                    q.push(temp);
                }
                else{
                    temp.directions.push_back("Pour " + std::to_string(min(pour, curr.b)) + " gallons from B to A. " + temp.to_string());
                    q.push(temp);
                }
            }
        }//checks if C can pour into B
        if ((cap.b - curr.b) > 0 && curr.c > 0){
            State temp = curr;
            int pour = cap.b - temp.b;
            if (pour >= temp.c){
                temp.b += temp.c;
                temp.c = 0;
            }
            else {
                temp.c -= pour;
                temp.b = cap.b;
            }
            if (map[temp.a][temp.b] == false){
                map[temp.a][temp.b] = true;
                if (pour == 1 || curr.c == 1){
                    temp.directions.push_back("Pour 1 gallon from C to B. " + temp.to_string());
                    q.push(temp);
                }
                else{
                    temp.directions.push_back("Pour " + std::to_string(min(pour, curr.c)) + " gallons from C to B. " + temp.to_string());
                    q.push(temp);
                }
            }
        }//checks if A can pour into B
        if ((cap.b - curr.b) > 0 && curr.a > 0){
            State temp = curr;
            int pour = cap.b - temp.b;
            if (pour >= temp.a){
                temp.b += temp.a;
                temp.a = 0;
            }
            else {
                temp.a -= pour;
                temp.b = cap.b;
            }
            if (map[temp.a][temp.b] == false){
                map[temp.a][temp.b] = true;
                if (pour == 1 || curr.a == 1){
                    temp.directions.push_back("Pour 1 gallon from A to B. " + temp.to_string());
                    q.push(temp);
                }
                else{
                    temp.directions.push_back("Pour " + std::to_string(min(pour, curr.a)) + " gallons from A to B. " + temp.to_string());
                    q.push(temp);
                }
            }
        }//check if B can pour into C
        if ((cap.c - curr.c) > 0 && curr.b > 0){
            State temp = curr;
            int pour = cap.c - temp.c;
            if (pour >= temp.b){
                temp.c += temp.b;
                temp.b = 0;
            }
            else {
                temp.b -= pour;
                temp.c = cap.c;
            }
            if (map[temp.a][temp.b] == false){
                map[temp.a][temp.b] = true;
                if (pour == 1 || curr.b == 1){
                    temp.directions.push_back("Pour 1 gallon from B to C. " + temp.to_string());
                    q.push(temp);
                }
                else{
                    temp.directions.push_back("Pour " + std::to_string(min(pour, curr.b)) + " gallons from B to C. " + temp.to_string());
                    q.push(temp);
                }
            }
        }//check if A can pour into C
        if ((cap.c - curr.c) > 0 && curr.a > 0){
            State temp = curr;
            int pour = cap.c - temp.c;
            if (pour >= temp.a){
                temp.c += temp.a;
                temp.a = 0;
            }
            else {
                temp.a -= pour;
                temp.c = cap.c;
            }
            if (map[temp.a][temp.b] == false){
                map[temp.a][temp.b] = true;
                if (pour == 1 || curr.a == 1){
                    temp.directions.push_back("Pour 1 gallon from A to C. " + temp.to_string());
                    q.push(temp);
                }
                else{
                    temp.directions.push_back("Pour " + std::to_string(min(pour, curr.a)) + " gallons from A to C. " + temp.to_string());
                    q.push(temp);
                }
            }
        }
    }
    //if the code reaches this point there is no solution.
    //clear the vector<string> of a State variable and push back "No solution." then return the State.
    curr.directions.clear();
    curr.directions.push_back("No solution.");
    return curr;
}

//This function takes in the command line arguments and calls BFS and the other functions to find the solution
void find_solution(int cA, int cB, int cC, int A, int B, int C){
    vector<string> dir;
    //needed to create an empty vector<string> dir to instantiate with each State variable.
    State goal(A, B, C, dir);
    
    State initial(0, 0, cC, dir);
    State cap(cA, cB, cC, dir);
    //the matrix is cA+1 and cB+1 to account for indecies starting at 0
    bool ** map = makeMatrix(cA + 1, cB + 1);
    goal = bfs(initial, cap, goal, map);
    goal.print_directions();
    //clears up allocated memory
    clearMatrix(map, cA + 1);
}

int main(int argc, char * const argv[]) {
    vector<int> temp;
    int capA, capB, capC, goalA, goalB, goalC;
    if (argc != 7){
        cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }
    else {
        for (int i = 1; i < 7; i++){
            istringstream iss(argv[i]);
            int ref;
            if (!(iss >> ref)){
                if (i < 4){
                    cout << "Error: Invalid capacity '" << iss.str() << "' for jug ";
                    cout << jug(i) << endl;
                    return 1;
                }
                else {
                    cout << "Error: Invalid goal '" << iss.str() << "' for jug ";
                    cout << jug(i) << endl;
                    return 1;
                }
            }
            else {
                if (i < 4) {
                    if (ref <= 0) {
                        cout << "Error: Invalid capacity '" << iss.str() << "' for jug ";
                        cout << jug(i) << endl;
                        return 1;
                    }
                    else {
                        temp.push_back(ref);
                    }
                }
                else {
                    temp.push_back(ref);
                    if (temp[2] == 0){
                        cout << "Error: Invalid goal '0' for jug C." << endl;
                        return 1;
                    }
                    else if (ref < 0) {
                        cout << "Error: Invalid goal '" << iss.str() << "' for jug ";
                        cout << jug(i) << endl;
                        return 1;
                    }
                    else if (i == 6) {
                        int counter = 0;
                        for (size_t ind = 0; ind < 3; ind++) {
                            size_t ind2 = ind + 3;
                            counter++;
                            if (temp[ind] < temp[ind2]) {
                                cout << "Error: Goal cannot exceed capacity of jug ";
                                cout << jug(counter) << endl;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        capA = temp[0];
        capB = temp[1];
        capC = temp[2];
        goalA = temp[3];
        goalB = temp[4];
        goalC = temp[5];
        if ((goalA + goalB + goalC) != capC){
            cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
            return 1;
        }
        find_solution(capA, capB, capC, goalA, goalB, goalC);
        return 0;
    }
}