
/*******************************************************************************
* Name : stairclimber.cpp
* Author : Michael Buzzetta
* Date : October 5, 2023
* Description : Lists the number of ways to climb n stairs.
* Pledge : I pledge my honor that I have abided by the Stevens Honor System.
******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;
int stairs;
vector< vector<int> > get_ways(int num_stairs) 
{
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> answer;

    if(num_stairs<=0)
    {
        answer.push_back(vector<int>());
    }
    else
    {
        for(int i = 1; i < 4; i++)
        {
            if(num_stairs>=i)
            {
                vector<vector<int>> step=get_ways(num_stairs-i);

                for(auto &index : step)
                {
                    index.insert(index.begin(), i);
                }

                answer.insert(answer.end(), step.begin(), step.end());
            }
        }
    }
    return answer;
}

int count(int num)
{
    int c=1;

    while(num/10 !=0)
    {
        c++;
        num=num/10;
    }
    return c;
}

void display_ways(const vector< vector<int> > &ways) 
{
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int answer=ways.size();
    int width=count(answer);

    if(answer>1)
    {
        cout << answer << " ways to climb " << stairs << " stairs." << endl;
    }
    else
    {
        cout << answer << " way to climb " << stairs << " stair." << endl;
    }

    int x=1;

    for (auto &shallow : ways)
    {
        cout << right << setw(width) << x++;
        cout << ". [";

        for (unsigned int i = 0; i < shallow.size() - 1; i++) 
        {
            cout << shallow[i] << ", ";
        }
        cout << shallow[shallow.size() - 1];
        cout << "]" << endl;
    }
}
int main(int argc, char * const argv[]) 
{
    if (argc != 2) 
    {
        cout << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }
    istringstream iss(argv[1]);

    // If the argument is not a valid integer
    if (!(iss >> stairs) || stairs < 1) 
    {
        cout << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    vector<vector<int>> result=get_ways(stairs);
    // for(const auto& row : result)
    // {
    //     for(const auto& element : row)
    //     {
    //         cout << element << " ";
    //     }
    //     cout << "\n";
    // }
    display_ways(get_ways(stairs));
    return 0;
}
