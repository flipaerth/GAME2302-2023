
#include <iostream>
#include <cstdlib>

using namespace std;

class TicTacToe
{
public:
    // TTT board, empty by default
    char board[3][3] =
    {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    // used for keeping track what's in each space, and what value each player has
    enum Entry
    {
        EMPTY = ' ',
        PLAYER_ONE = 'x',
        PLAYER_TWO = 'o'
    };

    // has the board been completely filled?
    bool isFull()
    {
        bool result = true;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == Entry::EMPTY)
                    result = false;
            }
        }

        return result;
    }

    // has someone won?
    bool isVictory(Entry e)
    {
        for (int i = 0; i < 3; i++) {
            // Row
            if (board[i][0] == (char)e && board[i][1] == (char)e && board[i][2] == (char)e) {
                return true;
            }
            // Column
            if (board[0][i] == (char)e && board[1][i] == (char)e && board[2][i] == (char)e) {
                return true;
            }
        }

        // diagonal 1
        if (board[0][0] == (char)e && board[1][1] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // diagonal 2
        if (board[0][2] == (char)e && board[1][1] == (char)e && board[2][0] == (char)e)
        {
            return true;
        }

        /*
        // first col
        if (board[0][0] == (char)e && board[0][1] == (char)e && board[0][2] == (char)e)
        {
            return true;
        }

        // second col
        else if (board[1][0] == (char)e && board[1][1] == (char)e && board[1][2] == (char)e)
        {
            return true;
        }

        // third col
        else if (board[2][0] == (char)e && board[2][1] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // first row
        else if (board[0][0] == (char)e && board[1][0] == (char)e && board[2][0] == (char)e)
        {
            return true;
        }

        // second row
        else if (board[0][1] == (char)e && board[1][1] == (char)e && board[2][1] == (char)e)
        {
            return true;
        }

        // third row
        else if (board[0][2] == (char)e && board[1][2] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // diagonal 1
        else if (board[0][0] == (char)e && board[1][1] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // diagonal 2
        else if (board[0][2] == (char)e && board[1][1] == (char)e && board[2][0] == (char)e)
        {
            return true;
        }
        */

        return false;
    }

    // return size of the board; mostly just in case I wanted to make the board expandable
    int getSize()
    {
        return 3;
    }


    void dump()
    {
        cout << "----------------------------------------" << endl << endl;
        for (int i = 0; i < getSize(); i++)
        {
            for (int j = 0; j < getSize(); j++)
            {
                cout << " | " << board[i][j] << " | ";
            }

            cout << endl;
        }
        cout << "----------------------------------------" << endl << endl;
    }

};

static bool getHumanMove(int maxValue, TicTacToe::Entry human, TicTacToe& t)
{
    // check if player is able to move
    if (t.isVictory(t.PLAYER_ONE) || t.isVictory(t.PLAYER_TWO) || t.isFull())
        return true;

    int rowChoice = 0;
    int colChoice = 0;

    do {

        do {

            cout << "Enter column number (x) : 0 ... 2 : ";
            cin >> colChoice;
            cout << endl;

        } while (colChoice > maxValue || colChoice < 0);

        do {

            cout << "Enter row number (y) : 0 ... 2 : ";
            cin >> rowChoice;
            cout << endl;

        } while (rowChoice > maxValue || rowChoice < 0);


        if (t.board[rowChoice][colChoice] == t.EMPTY)
        {
            t.board[rowChoice][colChoice] = (char)human;

            return false;
        }

        else
        {
            cout << "Not a valid option! Please try again..." << endl;
        }


    } while (t.board[rowChoice][colChoice] != t.EMPTY);

    // move complete
    return false;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * OBJECTIVE:                                                                                  *
 *                                                                                             *
 * Your AI for selecting the computer's move should follow these simple and rules (in order):  *
 *                                                                                             *
 *          a) If the computer can win immediately, it should do so                            *
 *                                                                                             *
 *          b) If the human's next move would result in a victory, the                         *
 *             AI should choose that square to block {DONE - Works 90% of the time}            *
 *                                                                                             *
 *          c) If the center square is open, choose it {DONE}                                  *
 *                                                                                             *
 *          d) If any of the corner squares are open, choose one of them {DONE}                *
 *                                                                                             *
 *          e) Choose any open square at random {DONE - fixed with better random}              *
 *                                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static bool getComputerMove(TicTacToe::Entry computer, TicTacToe::Entry human, TicTacToe& t)
{
    // check if computer is able to move
    if (t.isVictory(t.PLAYER_ONE) || t.isVictory(t.PLAYER_TWO) || t.isFull())
        return true;

    // handle computer's move
    int rowChoice = 0;
    int colChoice = 0;

    // Corner Variables
    int corner[4] = { 0, 1, 2, 3 };
    int cornerSelection;

    corner[0] = t.board[0][0]; // Top left
    corner[1] = t.board[2][0]; // Top right
    corner[2] = t.board[0][2]; // Bottom left
    corner[3] = t.board[2][2]; // Bottom right

    // Seed the random number choice with the current time
    srand(static_cast<unsigned>(time(0)));

    do {

        // Choose middle space if it's empty
        if (t.board[1][1] == t.EMPTY) {
            
            t.board[1][1] = (char)computer;

            return false;
        }

        /***********************************************************************************************************************/
        /* Brute Force Checking to Block Human Victory */
        /***********************************************************************************************************************/

        // first col
        if (t.board[0][0] == (char)human && t.board[0][1] == (char)human && t.board[0][2] == t.EMPTY)
        {
            t.board[0][2] = (char)computer; // Down
            return false;
        }
        else if (t.board[0][2] == (char)human && t.board[0][1] == (char)human && t.board[0][0] == t.EMPTY)
        {
            t.board[0][0] = (char)computer; // Up
            return false;
        }
        else if (t.board[0][0] == (char)human && t.board[0][2] == (char)human && t.board[0][1] == t.EMPTY)
        {
            t.board[0][1] = (char)computer; // Middle
            return false;
        }

        // second col
        else if (t.board[1][0] == (char)human && t.board[1][1] == (char)human && t.board[1][2] == t.EMPTY)
        {
            t.board[1][2] = (char)computer; // Down
            return false;
        }
        else if (t.board[1][2] == (char)human && t.board[1][1] == (char)human && t.board[1][0] == t.EMPTY)
        {
            t.board[1][0] = (char)computer; // Up
            return false;
        }
        else if (t.board[1][0] == (char)human && t.board[1][2] == (char)human && t.board[1][1] == t.EMPTY)
        {
            t.board[1][1] = (char)computer; // Middle
            return false;
        }

        // third col
        else if (t.board[2][0] == (char)human && t.board[2][1] == (char)human && t.board[2][2] == t.EMPTY)
        {
            t.board[2][2] = (char)computer; // Down
            return false;
        }
        else if (t.board[2][2] == (char)human && t.board[2][1] == (char)human && t.board[2][0] == t.EMPTY)
        {
            t.board[2][0] = (char)computer; // Up
            return false;
        }
        else if (t.board[2][0] == (char)human && t.board[2][2] == (char)human && t.board[2][1] == t.EMPTY)
        {
            t.board[2][1] = (char)computer; // Middle
            return false;
        }

        // first row
        else if (t.board[0][0] == (char)human && t.board[1][0] == (char)human && t.board[2][0] == t.EMPTY)
        {
            t.board[2][0] = (char)computer; // Right
            return false;
        }
        else if (t.board[2][0] == (char)human && t.board[1][0] == (char)human && t.board[0][0] == t.EMPTY)
        {
            t.board[0][0] = (char)computer; // Left
            return false;
        }
        else if (t.board[0][0] == (char)human && t.board[0][2] == (char)human && t.board[0][1] == t.EMPTY)
        {
            t.board[0][1] = (char)computer; // Middle
            return false;
        }

        // second row
        else if (t.board[0][1] == (char)human && t.board[1][1] == (char)human && t.board[2][1] == t.EMPTY)
        {
            t.board[2][1] = (char)computer; // Right
            return false;
        }
        else if (t.board[2][1] == (char)human && t.board[1][1] == (char)human && t.board[0][1] == t.EMPTY)
        {
            t.board[0][1] = (char)computer; // Left
            return false;
        }
        else if (t.board[0][1] == (char)human && t.board[2][1] == (char)human && t.board[1][1] == t.EMPTY)
        {
            t.board[1][1] = (char)computer; // Middle
            return false;
        }

        // third row
        else if (t.board[0][2] == (char)human && t.board[1][2] == (char)human && t.board[2][2] == t.EMPTY)
        {
            t.board[2][2] = (char)computer; // Right
            return false;
        }
        else if (t.board[2][2] == (char)human && t.board[1][2] == (char)human && t.board[0][2] == t.EMPTY)
        {
            t.board[0][2] = (char)computer; // Left
            return false;
        }
        else if (t.board[0][2] == (char)human && t.board[2][2] == (char)human && t.board[1][2] == t.EMPTY)
        {
            t.board[1][2] = (char)computer; // Middle
            return false;
        }

        /***********************************************************************************************************************/
        /***********************************************************************************************************************/



        /***********************************************************************************************************************/
        /* ChatGPT Assisted Section {WORKS when uncommented and works better than brute force checking} */
        /* Checks for blocking the human from winning and then selects the space to block */
        /***********************************************************************************************************************/
        /*
        // Check rows
        for (int row = 0; row < 3; ++row) {
            int humanCount = 0; // Count of human's moves in the current row
            int emptyColumn = -1; // Initialize to an invalid value

            for (int col = 0; col < 3; ++col) {
                if (t.board[row][col] == (char)human) {
                    humanCount++;
                }
                else if (t.board[row][col] == t.EMPTY) {
                    // Record the index of the empty column
                    emptyColumn = col;
                }
            }

            // If the human has two moves in this row and there's an empty column, block it
            if (humanCount == 2 && emptyColumn != -1) {
                t.board[row][emptyColumn] = (char)computer;
                return false;
            }
        }

        // Check columns
        for (int col = 0; col < 3; ++col) {
            int humanCount = 0; // Count of human's moves in the current column
            int emptyRow = -1; // Initialize to an invalid value

            for (int row = 0; row < 3; ++row) {
                if (t.board[row][col] == (char)human) {
                    humanCount++;
                }
                else if (t.board[row][col] == t.EMPTY) {
                    // Record the index of the empty row
                    emptyRow = row;
                }
            }

            // If the human has two moves in this column and there's an empty row, block it
            if (humanCount == 2 && emptyRow != -1) {
                t.board[emptyRow][col] = (char)computer;
                return false;
            }
        }
        */
        /***********************************************************************************************************************/
        /***********************************************************************************************************************/



        // Checking for blocking the human from diagonal wins
        if (t.board[1][1] == (char)human) {
            // If the human has the top left corner, computer will pick bottom right corner
            if (t.board[0][0] == (char)human && t.board[2][2] == t.EMPTY) {
                t.board[2][2] = (char)computer;
                return false;
            }
            // If the human has the bottom right corner, computer will pick top left corner
            else if (t.board[2][2] == (char)human && t.board[0][0] == t.EMPTY) {
                t.board[0][0] = (char)computer;
                return false;
            }
            // If the human has the bottom left corner, computer will pick top right corner
            else if (t.board[0][2] == (char)human && t.board[2][0] == t.EMPTY) {
                t.board[2][0] = (char)computer;
                return false;
            }
            // If the human has the top right corner, computer will pick bottom left corner
            else if (t.board[2][0] == (char)human && t.board[0][2] == t.EMPTY) {
                t.board[0][2] = (char)computer;
                return false;
            }
        }
        
        // Choosing a corner space if it's empty
        do {
            // Randomly select a corner
            cornerSelection = rand() % 4;

            // Computer selects a corner
            if (corner[cornerSelection] == t.EMPTY) {
                
                switch (cornerSelection) {
                case 0:
                    // Top left
                    t.board[0][0] = (char)computer;
                    break;
                case 1:
                    // Top right
                    t.board[2][0] = (char)computer;
                    break;
                case 2:
                    // Bottom left
                    t.board[0][2] = (char)computer;
                    break;
                case 3:
                    // Bottom right
                    t.board[2][2] = (char)computer;
                    break;
                }
            }
            return false;
        } while (corner[cornerSelection] != t.EMPTY);

        /***********************************************************************************************************************/
        /* Brute Force Checking for Choosing a Winning Space */
        /* Could just as well do something about this similarly to the blocking section that ChatGPT assisted with */
        /* I like the way it's written out and makes sense, but it's not something I came up with on my own, so I */
        /* have it commented out just to show that I see there's another way to do it */
        /***********************************************************************************************************************/

        // first col
        if (t.board[0][0] == (char)computer && t.board[0][1] == (char)computer && t.board[0][2] == t.EMPTY)
        {
            t.board[0][2] = (char)computer; // Down
            return false;
        }
        else if (t.board[0][2] == (char)computer && t.board[0][1] == (char)computer && t.board[0][0] == t.EMPTY)
        {
            t.board[0][0] = (char)computer; // Up
            return false;
        }
        else if (t.board[0][0] == (char)computer && t.board[0][2] == (char)computer && t.board[0][1] == t.EMPTY)
        {
            t.board[0][1] = (char)computer; // Middle
            return false;
        }

        // second col
        else if (t.board[1][0] == (char)computer && t.board[1][1] == (char)computer && t.board[1][2] == t.EMPTY)
        {
            t.board[1][2] = (char)computer; // Down
            return false;
        }
        else if (t.board[1][2] == (char)computer && t.board[1][1] == (char)computer && t.board[1][0] == t.EMPTY)
        {
            t.board[1][0] = (char)computer; // Up
            return false;
        }
        else if (t.board[1][0] == (char)computer && t.board[1][2] == (char)computer && t.board[1][1] == t.EMPTY)
        {
            t.board[1][1] = (char)computer; // Middle
            return false;
        }

        // third col
        else if (t.board[2][0] == (char)computer && t.board[2][1] == (char)computer && t.board[2][2] == t.EMPTY)
        {
            t.board[2][2] = (char)computer; // Down
            return false;
        }
        else if (t.board[2][2] == (char)computer && t.board[2][1] == (char)computer && t.board[2][0] == t.EMPTY)
        {
            t.board[2][0] = (char)computer; // Up
            return false;
        }
        else if (t.board[2][0] == (char)computer && t.board[2][2] == (char)computer && t.board[2][1] == t.EMPTY)
        {
            t.board[2][1] = (char)computer; // Middle
            return false;
        }

        // first row
        else if (t.board[0][0] == (char)computer && t.board[1][0] == (char)computer && t.board[2][0] == t.EMPTY)
        {
            t.board[2][0] = (char)computer; // Right
            return false;
        }
        else if (t.board[2][0] == (char)computer && t.board[1][0] == (char)computer && t.board[0][0] == t.EMPTY)
        {
            t.board[0][0] = (char)computer; // Left
            return false;
        }
        else if (t.board[0][0] == (char)computer && t.board[0][2] == (char)computer && t.board[0][1] == t.EMPTY)
        {
            t.board[0][1] = (char)computer; // Middle
            return false;
        }

        // second row
        else if (t.board[0][1] == (char)computer && t.board[1][1] == (char)computer && t.board[2][1] == t.EMPTY)
        {
            t.board[2][1] = (char)computer; // Right
            return false;
        }
        else if (t.board[2][1] == (char)computer && t.board[1][1] == (char)computer && t.board[0][1] == t.EMPTY)
        {
            t.board[0][1] = (char)computer; // Left
            return false;
        }
        else if (t.board[0][1] == (char)computer && t.board[2][1] == (char)computer && t.board[1][1] == t.EMPTY)
        {
            t.board[1][1] = (char)computer; // Middle
            return false;
        }

        // third row
        else if (t.board[0][2] == (char)computer && t.board[1][2] == (char)computer && t.board[2][2] == t.EMPTY)
        {
            t.board[2][2] = (char)computer; // Right
            return false;
        }
        else if (t.board[2][2] == (char)computer && t.board[1][2] == (char)computer && t.board[0][2] == t.EMPTY)
        {
            t.board[0][2] = (char)computer; // Left
            return false;
        }
        else if (t.board[0][2] == (char)computer && t.board[2][2] == (char)computer && t.board[1][2] == t.EMPTY)
        {
            t.board[1][2] = (char)computer; // Middle
            return false;
        }

        // Checking for winning diagonally
        if (t.board[1][1] == (char)computer) {
            // If the human has the top left corner, computer will pick bottom right corner
            if (t.board[0][0] == (char)computer && t.board[2][2] == t.EMPTY) {
                t.board[2][2] = (char)computer;
                return false;
            }
            // If the human has the bottom right corner, computer will pick top left corner
            else if (t.board[2][2] == (char)computer && t.board[0][0] == t.EMPTY) {
                t.board[0][0] = (char)computer;
                return false;
            }
            // If the human has the bottom left corner, computer will pick top right corner
            else if (t.board[0][2] == (char)computer && t.board[2][0] == t.EMPTY) {
                t.board[2][0] = (char)computer;
                return false;
            }
            // If the human has the top right corner, computer will pick bottom left corner
            else if (t.board[2][0] == (char)computer && t.board[0][2] == t.EMPTY) {
                t.board[0][2] = (char)computer;
                return false;
            }
        }

        // choose at random until we find a space that's empty
        do {

            rowChoice = rand() % ((t.getSize() - 0) + 1) + 0;

        } while (rowChoice > t.getSize() || rowChoice < 0);

        do {

            colChoice = rand() % ((t.getSize() - 0) + 1) + 0;

        } while (colChoice > t.getSize() || colChoice < 0);


        if (t.board[rowChoice][colChoice] == t.EMPTY)
        {
            t.board[rowChoice][colChoice] = (char)computer;

            return false;
        }

        else
        {
            //cout << "Not a valid option! Please try again..." << endl;
        }


    } while (t.board[rowChoice][colChoice] != t.EMPTY);

    // move complete
    return false;
}

// ----------------------------
// main
// ----------------------------

int main()
{
    TicTacToe t;
    TicTacToe::Entry human = TicTacToe::PLAYER_ONE;
    TicTacToe::Entry computer = TicTacToe::PLAYER_TWO;

    int maxValue = t.getSize();

    cout << "----------------------------------------" << endl;

    cout << "You are '" << (char)human << "', " <<
        "the computer is: '" << (char)computer << "'" << endl;

    cout << "----------------------------------------" << endl << endl;

    // run the game until one player isn't able to go again
    do
    {
        // show board
        t.dump();
    } while (!getHumanMove(maxValue, human, t) && !getComputerMove(computer, human, t));


    t.dump();

    cout << endl;

    if (t.isVictory(human))
        cout << "Human Victory" << endl;

    else if (t.isVictory(computer))
        cout << "Computer Victory" << endl;

    else if (t.isFull())
        cout << "Tie" << endl;

    return(0);
}