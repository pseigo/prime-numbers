#include <iostream>
#include <cmath> // sqrt
#include <vector>
#include <cstdlib> // atoi

using namespace std;

void fillVector(vector<pair<int, bool>> &number, int n); // Fill vector with numbers up to n
void setPrimes(vector<pair<int, bool>> &prime, int maxNumber); // Set all primes in vector to 'true' and composites to 'false'
void printPrimes(vector<pair<int, bool>> const &prime); // Print primes by a const reference (can't change value)

void printSyntaxError();
void runPrime(int n); // executes prime functions with n
int askForNumber();


int main(int argc, char *argv[])
{
    // Decide how to execute program based on command line arguments (or a lack of)
    if (argc == 1) // menu interface
    {
        runPrime(askForNumber());
        cout << endl;
    } else if (argc == 2) // given a single argument
    {
        /*
         * int 'argument' is initialized to -1. If atoi() is unable to find a number
         * from argv[1], 'argument' will remain as -1. We can utilize this to tell
         * when the user gives an invalid number (anything less than 1 or no number
         * at all).
        */

        int argument = 0;
        argument = atoi(argv[1]);

        cout << argument << endl;

        if (argument < 1 || argument > 10000000) {
            printSyntaxError(); return 1;
        } else {
            runPrime(argument);
        }
    }
    else if (argc > 1) // syntax error, every other case
    {
        printSyntaxError(); return 1;
    }

    return 0;
}


/* ============== Prime Functions ============== */
// Fill vector with numbers up to n
void fillVector(vector<pair<int, bool>> &number, int n)
{
    // populate vector with numbers from 1-n and set boolean vaues to true
    for (int current = 0; current < n; current++) {
        number.push_back( make_pair((current + 1), true) );
    }
}

// Set all primes in vector to 'true' and composites to 'false'
void setPrimes(vector<pair<int, bool>> &prime, int maxNumber)
{
    // process to mark non-primes (composite numbers) as false
    for (int current = 2; current <= sqrt(maxNumber); current++) {

        // if current number is true, theorem states it is PRIME!
        if (prime[current - 1].second == true) {

            // starting at the square of the current number, go through every number
            // up to maxNumber and if it's a factor of current, mark it as true.
            for (int factor = (current*current); factor <= maxNumber; factor++) {
                if (factor % current == 0) {
                    // the factor of the current number is composite, therefore set to false
                    prime[factor - 1].second = false;
                }
            }

        } // end of prime condition
    }

    return;
}

// Print primes by a const reference (can't change value)
void printPrimes(vector<pair<int, bool>> const &prime)
{
    // print all prime numbers (prime has boolean 'true')
    for (pair<int, bool> current : prime) {
        if (current.second == true)
            cout << current.first << ' ';
    }

    return;
}

/* ============== Interface Functions ============== */
// informs user of syntax
void printSyntaxError()
{
    cerr << "Usage: primesto.exe [1 ... 10000000] \n"
        << "\tCalculates all prime numbers up to a given number. \n" << endl;
}

// finds primes up to parameter n
void runPrime(int n)
{
    if (n > 0) {
        // int refers to number, bool refers to primeness (if true, its prime)
        vector< pair<int,bool> > number;

        fillVector(number, n);
        setPrimes(number, n);
        printPrimes(number);
    } else { // theoretically will never occur but good to have just in case
        cerr << "ERROR: Must be a number and greater than 0!" << endl;
    }

    return;
}

int askForNumber()
{
    int number;

    do {
        cout << "Enter a positive number: ";
        cin >> number;
        // number = atoi(input);

        if (!cin.good() || number < 1 || number > 10000000) {
            cout << "ERROR: Must be a number and greater than 0! \n" << endl;
            cin.clear();
            cin.ignore(128, '\n');
        } else {
            break;
        }
    } while (true);

    return number;
}
