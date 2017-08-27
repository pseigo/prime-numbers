#include <iostream>
#include <map>
#include <vector>
#include <cstdlib> // atoi

using namespace std;

void fill(map<int, bool>&, int);
void setPrimes(vector<int>&, map<int, bool>&, int);
void print(const vector<int>&);

void printSyntaxError();
void getPrimesUpTo(int n);
int getInt(int, int);


int main(int argc, char *argv[])
{
    // Decide how to execute program based on command line arguments (or a lack of)
    if (argc == 1) // menu interface
    {
        getPrimesUpTo(getInt(1, 10000000));
    }
    else if (argc == 2) // given a single argument
    {
        /*
         * int 'argument' is initialized to 0. If atoi() is unable to find a number
         * from argv[1], 'argument' will remain as 0. We can utilize this to tell
         * when the user gives an invalid number (anything less than 1 or no number
         * at all).
        */

        int argument = 0;
        argument = atoi(argv[1]); // convert any numbers (as a string) from the argument to an int

        if (argument < 1 || argument > 10000000) {
            printSyntaxError();
            return 1;
        }

        getPrimesUpTo(argument);
    }
    else if (argc > 1) // syntax error, every other case
    {
        printSyntaxError();
        return 1;
    }

    return 0;
}

/* ============== Prime Functions ============== */
// Fill map with numbers [2, upperBound]; assume all numbers are prime
void fill(map<int, bool>& isPrime, int upperBound)
{
    for (int i = 2; i <= upperBound; ++i)
        isPrime[i] = true;
}

// Pushes primes to vector using values from isPrime up to upperBound
void setPrimes(vector<int>& primes, map<int, bool>& isPrime, int upperBound)
{
    for (int i = 2; i*i <= upperBound; i++) {

        if (isPrime[i]) {
            primes.push_back(i);

            // factors of i starting at i*i are composite
            for (int j = i*i; j <= upperBound; j += i)
                isPrime[j] = false;
        }

    }

    for (int i = 2; i <= upperBound; ++i) {
        if (isPrime[i])
            primes.push_back(i);
    }
}

void print(const vector<int>& vec)
{
    for (int i : vec)
        cout << i << '\n';
}

/* ============== Interface Functions ============== */
void printSyntaxError()
{
    cerr << "Usage: primesto.exe [1 ... 10000000] \n"
        << "\tCalculates all prime numbers up to a given number." << endl;
}

void getPrimesUpTo(int n)
{
    if (n < 0) {
        cerr << "ERROR: Must be a number and greater than 0!" << endl;
        return;
    }

    map<int, bool> isPrime;
    vector<int> primes;

    fill(isPrime, n);
    setPrimes(primes, isPrime, n);
    print(primes);

    return;
}

int getInt(int min, int max)
{
    int number;

    do {
        cout << "Enter a positive number: ";
        cin >> number;

        if (!cin.good() || number < min || number > max) {
            cout << "ERROR: Must be a number and greater than 0! \n" << endl;
            cin.clear();
            cin.ignore(128, '\n');
        } else {
            break;
        }
    } while (true);

    return number;
}
