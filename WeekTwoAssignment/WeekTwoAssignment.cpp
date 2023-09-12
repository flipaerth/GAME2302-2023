/* * * * * * * * * * * *
 * Week Two Assignment *
 * Austin Ozan         *
 * 9/6/2023            *
 * * * * * * * * * * * */


 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  * OBJECTIVES:                                                                         *
  *                                                                                     *
  * 1) a function that outputs all numbers from 0 to 1000 that are                      *
  *    divisible by two different numbers, which should be passed into the function.    *
  *                                                                                     *
  * 2) a function to reverse the letters in a string ("hello world" => "dlrow olleh").  *
  *                                                                                     *
  * 3) a function that returns a string with the vowels removed.                        *
  *    ("the cake is a lie" => "th ck s  l")                                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   * SIDE NOTE: for the first function, I wasn't sure what the parameters were *
   * for the two different numbers, so I just chose 2 and 3 to keep it simple. *
   * Otherwise, I would've tried to make a random number generator for the two *
   * and that would've just turned into a whole mess.                          *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <iostream>
#include <string>

using namespace std;

// Overloading the Functions
void fOne();
void fTwo();
void fThree();

int main()
{
    // Variable: selection will act as an index for the user input
    int selection = 0;

    // Menu Display
    cout << "1) Output all numbers from 0 to 1000 that are divisible by two and three." << endl;
    cout << "2) Reverse the letters in a string." << endl;
    cout << "3) Return a string with the vowels removed." << endl;
    cout << "Please enter 1, 2, or 3 to select a function to run: ";
    cin >> selection;
    cout << endl;

    // Input Validation
    while (selection >= 4 || selection <= 0) {
        cout << "Please enter 1, 2, or 3 to select a function to run: ";
        cin >> selection;
        cout << endl;
    }

    // Input Confirmation
    cout << "You have entered: " << selection << endl << endl;

    // Function Activation
    switch (selection) {

        // Function One
    case 1:
        fOne();
        break;

        // Function Two
    case 2:
        fTwo();
        break;

        // Function Three
    case 3:
        fThree();
        break;

        // Default Case
    default:
        cout << "I don't know what I should put here, so... STUFF!" << endl;
        break;
    }
}

// Function One
// 1) a function that outputs all numbers from 0 to 1000 that are divisible by two different numbers, which should be passed into the function.
// SIDE NOTE: I'm sure there's a better, cleaner way to do this, but this is what I've got.
void fOne() {

    // Boolean Variables
    bool twoDivisible = false;
    bool threeDivisible = false;

    // Display
    cout << "Here is a list of every number from 0 to 1000 that is divisible by two and three:" << endl;

    // A loop to step through every number between 0 and 1000
    for (int i = 0; i <= 1000; i++) {

        // Variables
        int dividend = i;

        // Check if divisible by 2
        int numberTwo = 2;
        int divisorTwo = numberTwo;
        int quotientTwo = dividend / divisorTwo;
        int remainderTwo = dividend % divisorTwo;
        if (remainderTwo >= 1 || quotientTwo == 0) {
            twoDivisible = false;
        }
        else if (remainderTwo == 0) {
            twoDivisible = true;
        }

        // Check if divisible by 3
        int numberThree = 3;
        int divisorThree = numberThree;
        int quotientThree = dividend / divisorThree;
        int remainderThree = dividend % divisorThree;
        if (remainderThree >= 1 || quotientThree == 0) {
            threeDivisible = false;
        }
        else if (remainderTwo == 0) {
            threeDivisible = true;
        }

        // Output number if divisible by both 2 and 3
        if (twoDivisible == true && threeDivisible == true) {
            cout << i << endl;
        }
    }
}

// Function Two
// 2) a function to reverse the letters in a string ("hello world" => "dlrow olleh").
// SIDE NOTE: I'd really like to see your solution for this one. I wasn't sure on how to tackle it.
void fTwo() {

    // String Variables
    string input;

    // Display
    cout << "Enter a string to reverse: ";

    // Buffer
    cin.ignore();

    // Allow user to input a string, including the whitespaces
    getline(cin, input);
    cout << endl;

    // Variables
    int x = input.length();
    int n = x - 1;

    // Loop through each element of the string
    for (int i = 0; i < (x / 2); i++) {

        // Swaps each index
        swap(input[i], input[n]);
        n = n - 1;
    }

    // Output
    cout << input << endl;
}

// Function Three
// 3) a function that returns a string with the vowels removed ("the cake is a lie" => "th ck s  l").
void fThree() {

    // String Variables
    string input;

    // Array Variables
    char vowels[] = { 'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U' };

    // Display
    cout << "Enter a string to have its vowels removed: ";

    // Buffer
    cin.ignore();

    // Allow user to input a string, including the whitespaces
    getline(cin, input);
    cout << endl;

    // Variables
    int x = input.length();

    // Loop to step through the string
    for (int i = 0; i < x; i++) {

        // Loop to step through the vowels array and compare to the string index
        for (int j = 0; j < sizeof(vowels); j++) {

            // If the element in the string is the same as an element from the array,
            // it's replaced with whitespace to 'remove' the vowel from the string.
            if (input[i] == vowels[j]) {
                input[i] = ' ';
            }
        }

        // Output
        cout << input[i];
    }

}