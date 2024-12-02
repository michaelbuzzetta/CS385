/*******************************************************************************
* Filename: sqrt.cpp
* Author: Michael Buzzetta
* Version: 1.0
* Date: September 12, 2023
* Description: This code returns the computed square root of a double using Newton's method.
* Pledge: I pledge my honor that I have abided by the Stevens Honor System.
******************************************************************************/
//Recieved help from CA during office hours
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

double sqrt(double num, double epsilon) 
{
    if (num < 0) {
        return numeric_limits<double>::quiet_NaN();
    } 
    else if ((num == 0) | (num == 1)) 
    {
        return num;
    } 
    else
    {
        double prev_guess = num;
        double next_guess =(prev_guess + num/prev_guess) / 2;
        while (abs(prev_guess - next_guess) > epsilon)
        {
            prev_guess=next_guess;
            next_guess = (prev_guess + num/prev_guess) / 2;
        }
        return next_guess;
    }
}

int main(int argc, char* argv[]) 
{
    double num = 0;
    double epsilon = 1e-7;
    istringstream iss; // input string stream variable
    if(argc != 2 && argc != 3)
    { 
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }
    iss.str(argv[1]);
    if (!(iss >> num)) 
    {
        cout << "Error: Value argument must be a double." << endl;
        return 1;
    }
    if(argc == 2)
    {
        cout << fixed << setprecision(8) << sqrt(num, epsilon) << endl;
    }
    else
    {
        iss.clear();
        iss.str(argv[2]);
        if (!(iss >> epsilon)) 
        {
            cout << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
        else if(epsilon <= 0) 
        {
            cout << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
        cout << fixed << setprecision(8) << sqrt(num, epsilon) << endl;
    }
        return 0;
    
}
