/*******************************************************************************
 * Name : quickselect.cpp
 * Author : Michael Buzzetta
 * Date : October 26, 2023
 * Description : Implements the quickselect algorithm.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
//assignment completed with CA Jessica Sabatino
//used provided pseudocode
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

size_t lomuto_partition(int array[], size_t left, size_t right) 
{
    // TODO
    // DO NOT change the function header in any way, otherwise you will lose points.
    int temp=array[left];
    size_t size=left;

    //itterates through array and swaps elements smaller than temp with size
    for(size_t i=left+1; i<=right; i++)
    {
        if(array[i]<temp)
        {
            swap(array[++size], array[i]);
        }
    }
    swap(array[left], array[size]);
    return size;
}

int quick_select(int array[], size_t left, size_t right, size_t k) 
{
    // TODO
    // DO NOT change the function header in any way, otherwise you will lose points.

    //checks if the values of left and right are equal to eachother, if they are it returns array at index left
    // if(left==right)
    // {
    //     return array[left];
    // }

    

    size_t size1=lomuto_partition(array, left, right);
    //checks if the temporary variable is equal to 1 less than k, if it is, it returns the array at index temp1
    if(size1==k-1)
    {
        return array[size1];
    }
    if(size1>k-1)
    {
        return quick_select(array, left, size1-1, k);
    }
    //covers all other cases, reruns the function until another return statement is hit
    else
    {
        return quick_select(array, size1+1, right, k);
    }
}

int quick_select(int array[], const size_t length, size_t k) 
{
    return quick_select(array, 0, length - 1, k);
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        cerr << "Usage: " << argv[0] << " <k>" << endl;
        return 1;
    }

    int k;
    istringstream iss;
    iss.str(argv[1]);
    if ( !(iss >> k) || k <= 0 ) 
    {
        cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    iss.clear();
    while (true) 
    {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) 
        {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) 
            {
                break;
            }
            str.clear();
        } 
        else 
        {
            str += c;
        }
    }

    int num_values = values.size();
    if (num_values == 0) 
    {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    // TODO - error checking k against the size of the input
    if (k > num_values) 
    {
        if (num_values == 1) {
            cerr << "Error: Cannot find smallest element " << k << " with only " << num_values << " value." << endl;
        } else {
            cerr << "Error: Cannot find smallest element " << k << " with only " << num_values << " values." << endl;
        }
        return 1;
    }

    // TODO - call the quick_select function and display the result
    int *result = &values[0];  //vector => array to pass into function
    cout << "Smallest element " << k << ": " << quick_select(result, num_values, k);

    return 0;
}
