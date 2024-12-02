/*******************************************************************************
 * Name        : fastmult.cpp
 * Author      : Michael Buzzetta
 * Version     : 1.0
 * Date        : Nov 13, 2023
 * Description : C++ implementation of Karatsuba algorithm for bit string multiplication.
 * Pledge      : I pledge my honor that I have abided by the stevens honor system
 ******************************************************************************/
#include<iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <time.h>
#include <math.h>



using namespace std;
//this function takes both strings and makse sure that they are both the same length

void equalize(string& s1, string& s2)
{

    int len1 = s1.size();
    int len2 = s2.size();
    if (len1 < len2)
    {
        for (int i = 0; i < len2 - len1; i++)
        {
            s1 = '0' + s1;
        }
    }
    else
    {
        if (len1 > len2)
        {
            for (int i = 0; i < len1 - len2; i++)
            {
                s2 = '0' + s2;
            }

        }
    }
}

void equalize2(string& a, string& b)
{
    string padA;
    string padB;
    int lengthA = a.length();
    int lengthB = b.length();

    int length = pow(2, ceil(log2(max(lengthA, lengthB))));
    padA = string(length - lengthA, '0') + a;
    padB = string(length - lengthB, '0') + b;
    a = padA;
    b = padB;
}

//gets the size of the string
int getSize(string strang)
{
    int sizeOfStrang = strang.size();
    return sizeOfStrang;
}

string add(const string& a, const string& b)
{
    int index = 0;

    string copyA = a;
    string copyB = b;
    equalize(copyA, copyB);

    int trackA = getSize(copyA) - 1 - index;
    int sizeA = getSize(copyA);
    int trackB = getSize(copyB) - 1 - index;
    int sizeB = getSize(copyB);
    int carry = 0;
    string total = "";
 
    //while((index>=sizeA) or (index>=sizeB))
    while (true)
    {

        int intA = (int(copyA[trackA]) - '0');
        int intB = (int(copyB[trackB]) - '0');

        int curr = intA + intB + carry;

        carry = curr / 10;

        total += to_string(curr % 10);
        index++;
        trackA = getSize(copyA) - 1 - index;
        trackB = getSize(copyB) - 1 - index;
        if (index >= sizeA)
        {
            if (index >= sizeB)
            {
                break;
            }
            total += copyB.substr(0, trackB + 1);
            break;
        }
        else
        {
            if (index >= sizeB)
            {
                total += copyA.substr(0, trackA + 1);
                break;
            }
        }
    }

    if (carry)
    {
        total += "1";
    }
    reverse(total.begin(), total.end());
    return total;
}


string subtract(const string& a, const string& b)
{
    int index = 0;

    string copyA = a;
    string copyB = b;
    equalize(copyA, copyB);

    int trackA = getSize(copyA) - 1 - index;
    int sizeA = getSize(copyA);
    int trackB = getSize(copyB) - 1 - index;
    int sizeB = getSize(copyB);
    int carry = 0;
    string total = "";
   
    //while((index>=sizeA) or (index>=sizeB))
    while (true)
    {

        int intA = (carry == 1) ? (int(copyA[trackA]) - '0') - 1 : (int(copyA[trackA]) - '0');
        if (carry == 1)
        {
            carry = 0;
        }
        int intB = (int(copyB[trackB]) - '0');

        int curr = intA - intB - carry;
        if (curr < 0)
        {
            carry = 1;
            int aa = intA += 10;
            curr = aa - intB;
        }
        //carry=curr/10;

        total += to_string(curr);
        index++;
        trackA = getSize(copyA) - 1 - index;
        trackB = getSize(copyB) - 1 - index;
        if (index >= sizeA)
        {
            if (index >= sizeB)
            {
                break;
            }
            total += copyB.substr(0, trackB + 1);
            break;
        }
        else
        {
            if (index >= sizeB)
            {
                total += copyA.substr(0, trackA + 1);
                break;
            }
        }
    }

    reverse(total.begin(), total.end());
    //researched for solution, similar syntax found on geeksforgeeks.
    total.erase(0, min(total.find_first_not_of('0'), total.size() - 1));
    return total;
}

string multiply(const string& a, const string& b)
{
    /*
    string copyA=a;
    string copyB=b;
    int length = equalize(copyA, copyB);
    int trackA = length - 1;
    int trackB = length - 1;
    */
    int trackA = getSize(a);
    int trackB = getSize(b);
    string output(trackA + trackB, '0');
    int carry = 0;

    for (int i = trackA - 1; i >= 0; --i)
    {
        for (int j = trackB - 1; j >= 0; --j)
        {
            int result = (a[i] - '0') * (b[j] - '0') + (output[i + j + 1] - '0') + carry;
            carry = result / 10;
            output[i + j + 1] = result % 10 + '0';
        }
        output[i] += carry;
    }

    // Remove leading zeros
    output.erase(0, min(output.find_first_not_of('0'), output.size() - 1));
    if (output.size() == 0)
    {
        return "0";
    }
    return output;
}

//string input
//size_t
//string*10^size_t

string multiply2(const string& input, size_t exponent)
{
    string copyInput = input;
    int intInput = stoi(copyInput);

    if (exponent == 0)
    {
        return "1";
    }
    string result = to_string(intInput * (static_cast<int>(std::pow(10, exponent))));
    return result;
}

string karatsuba(const string& a, const string& b)
{

    string copyA = a;
    string copyB = b;
    //int length = equalize(copyA, copyB);


    int trackA = getSize(a);
    int trackB = getSize(b);
    equalize2(copyA, copyB);

    if (trackA == 1 || trackB == 1)
    {
        return to_string(stoi(a) * stoi(b));
    }

    
   
    string firstHalfA = copyA.substr(0, copyA.size()/2);
    string secondHalfA = copyA.substr(copyA.size()/2, copyA.size()/2);
    string firstHalfB = copyB.substr(0,copyB.size()/2);
    string secondHalfB = copyB.substr(copyB.size()/2,copyB.size()/2);
    string karatsubaCall1 = karatsuba(secondHalfA, secondHalfB);
    string karatsubaCall2 = karatsuba(firstHalfA, firstHalfB);
    string temp = karatsuba(add(firstHalfA, secondHalfA), add(firstHalfB, secondHalfB));
    string karatsubaCall3 = subtract(temp, add(karatsubaCall1, karatsubaCall2));
    string temp1 = multiply2(karatsubaCall2,copyA.size());
    string temp2 = multiply2(karatsubaCall3,copyA.size()/2);
    return add(add(temp1, temp2), karatsubaCall1);
}


int main(int argc, char* argv[])
{
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer1> <integer2>" << endl;
        return 1;
    }

    string num1 = argv[1];
    string num2 = argv[2];

    std::cout << karatsuba(num1, num2) << std::endl;

    return 0;
}