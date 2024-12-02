/*******************************************************************************
* Name : unique.cpp
* Author : Michael Buzzetta
* Date : Sep 27, 20234
* Description : Determining uniqueness of chars with int as bit vector.
* Pledge : I pledge my honor that I have abided by the Stevens Honor System.
******************************************************************************/
#include <iostream>
#include <cctype>
using namespace std;
bool is_all_lowercase(const string &s) 
{
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    for(auto lower = s.begin(); lower != s.end(); ++lower) 
    {
        if (!islower(*lower)) 
        {
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) 
{
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You MUST use only single unsigned integers and work with bitwise
    // and bitshifting operators only. Using any other kind of solution
    // will automatically result in a grade of ZERO for the whole assignment.
    int set=0;

    for(auto val = s.begin(); val != s.end(); ++val)
    {
        int setter=1<<(*val-'a');
        
        if(setter & set)
        {
            return false;
        }

        set|=setter;

    }
    return true;
}

int main(int argc, char * const argv[]) 
{
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    if (argc == 1) {
        cout << "Usage: ./unique <string>" << endl;
        return 1;
    }

    if (argc > 2) {
        cout << "Usage: ./unique <string>" << endl;
        return 1;
    }

    string input = argv[1];

    if (!is_all_lowercase(input)) 
    {
        cout << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    if (!all_unique_letters(input)) 
    {
        cout << "Duplicate letters found." << endl;
        return 1;
    }

    cout << "All letters are unique." << endl;
    return 0;

}
