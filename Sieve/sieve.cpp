/*******************************************************************************
 * Name : sieve.cpp
 * Author : Michael Buzzetta
 * Date : September 17
 * Description : Sieve of Eratosthenes
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
// Recieved help from CA and tutors
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;
class PrimesSieve
{
public:
    PrimesSieve(int limit);
    ~PrimesSieve()
    {
        delete[] is_prime_;
    }
    void display_primes() const;

private:
    // Instance variables
    bool *const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;
    // Method declarations
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit}
{
    sieve();
}

void PrimesSieve::display_primes() const
{
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    const int max_prime_width = num_digits(max_prime_);
    const int primes_per_row = 80 / (max_prime_width + 1);

    cout << endl;
    cout << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ":" << endl;

    // This variable tracks the number of columns used
    int x = 0;

    for (int i = 2; i < limit_ + 1; i++)
    {

        if (is_prime_[i] == true)
        {
            if (x >= primes_per_row)
            {
                cout << endl;
                x = 0;
            }

            if (x != 0)
            {
                cout << " ";
            }
            if (num_primes_ >primes_per_row)
            {
                cout << setw(max_prime_width);
            }
            cout << i;
            x++;
        }
    }
    cout << endl;
}

void PrimesSieve::sieve()
{
    // TODO: write sieve algorithm
    // All instance variables must be initialized by the end of this method.
    for (int i = 2; i < limit_ + 1; i++)
    {
        is_prime_[i] = true;
    }

    for (int i = 2; i < sqrt(limit_); i++)
    {
        if (is_prime_[i] == true)
        {
            for (int x = i * 2; x < limit_ + 1; x = x + i)
            {
                is_prime_[x] = false;
            }
        }
    }
    num_primes_ = 0;
    for (int y = 2; y < limit_ + 1; y++)
    {
        if (is_prime_[y] == true)
        {
            max_prime_ = y;
            num_primes_++;
        }
    }
}

int PrimesSieve::num_digits(int num)
{
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int c = 1;
    while (num / 10 != 0)
    {
        c++;
        num = num / 10;
    }
    return c;

    return 0;
}
int main()
{
    cout << "**************************** "
         << "Sieve of Eratosthenes"
         << " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;
    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);
    // Check for error.
    if (!(iss >> limit))
    {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2)
    {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve output(limit);
    output.display_primes();
    return 0;
}