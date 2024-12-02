/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Michael Buzzetta
 * Version     : 1.0
 * Date        : Nov 1, 2023
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the stevens honor system
 ******************************************************************************/
//Recieved help from CA Daniel Kim,  Jessica Sabatino, Adam El-Sawaf
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time using two nested loops.
 */
long count_inversions_slow(int array[], int length) 
{
    // TODO
    long c=0;
    for(int i=0; i<length-1; i++)
    {
        for(int x=i+1; x<length;x++)
        {
            if(array[i]>array[x])
            {
                c++;
            }
        }
    }
    return c;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) 
{
    // TODO
    // Hint: Use mergesort!
    
    int *temp=new int[length];

    long track=mergesort(array, temp, 0, length-1);
    delete[] temp;
    return track;

}

long helper(int array[], int scratch[], int low, int high, int mid)
{
    long low1 = low;
    long mid1 = mid + 1;
    long low2 = low;
    long tracker = 0;
    while(low1 <= mid && mid1 <= high) 
    {
        if(array[low1] <= array[mid1]) {
            scratch[low2++] = array[low1++];
        } 
        else 
        {
            scratch[low2++] = array[mid1++];
            tracker += mid - low1 + 1;
        }
    }

    while(low1 <= mid) 
    {
        scratch[low2++] = array[low1++];
    }

    while(mid1 <= high) 
    {
        scratch[low2++] = array[mid1++];
    }

    for(long x = low; x <= high; x++) 
    {
        array[x] = scratch[x];
    }

    return tracker;
}

static long mergesort(int array[], int scratch[], int low, int high) 
{
    // TODO
    long track=0;
    long mid=0;
    if(low<high)
    {
        mid=(low+high)/2;
        track+=mergesort(array, scratch, low, mid) 
        + mergesort(array, scratch, mid + 1, high)
        + helper(array, scratch, low, high, mid);

        // cout << track << endl;
   
        int x=low;
        int y=mid+1;
    
    
        for(int i=low; i<high; i++)
        {
            if(x<=mid&&(y>high||array[x]<=array[y]))
            {
                scratch[i]=array[x];
                x++;
            }
            else
            {
                scratch[i]=array[y];
                y++;
            }
        }
    }
    
    return track;
}



int main(int argc, char *argv[]) 
{
    // TODO: parse command-line argument
    if (argc > 2) 
    {
        cout << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }

    if (argc == 2) 
    {
        string compare = argv[1];
        if (compare.compare("slow") != 0) 
        {
            cout << "Error: Unrecognized option '" << compare << "'." << endl;
            return 1;
        }
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
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
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    if (argc > 2) 
    {
        cout << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }

    if (argc == 2) 
    {
        string compare = argv[1];
        if (compare.compare("slow") != 0) 
        {
            cout << "Error: Unrecognized option '" << compare << "'." << endl;
            return 1;
        }
    }
    int size=values.size();
    if (size == 0) 
    {
        cout << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    string output="Number of inversions ";

    if(size==0)
    {
        cout<<output << "0"<<endl;
        return 0;
    }
    int *val=&values[0];

    bool check=false;
    if(argc==2)
        check=true;

    
    if(check)
    {
        cout<<output<<"(slow): "<<count_inversions_slow(val, size)<<endl;
        return 0;
    }
    else
    {
        cout<<output<<"(fast): "<<count_inversions_fast(val, size)<<endl;
        return 0;
    }
}
