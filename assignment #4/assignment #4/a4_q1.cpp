//
// Student names: Esther Xin, Sydney LeBlanc
//
// SYDE 121 assignment: 4
// file name: a4_q1.cpp
//
// I hereby declare that this code, submitted for credit for the course
// SYDE121, is a product of my own efforts.  This coded solution has
// not been plagiarized from other sources and has not been knowingly
// plagiarized by others.
//
// Project: Tic Tac Toe Simulation
// Purpose: to simulate a game of 4 x 4 Tic Tac Toe between X player and O player
//
// Due date: November 6, 2020
//***************************************************

/* TESTING CONDITIONS
 1. Wins
    - horizontal win
    - vertical win
    - diagonal win
    - tie game
 2. Invalid Entry
    - inputted an number that was below 1
    - input a number above 16
    - input a number that is already taken
 3. Play Again
    - tested 'yes/Y/y' to see if the gameboard clears and the game restarts
    - test 'no' to see if the game ends, and the stats are ouputted
 4. Statistics (play multiple games)
    - if x wins more times
    - if y wins more times
 5. Switch Player
    - played multiple games to see if the players switched
*/

/* BOUNDS
 User Bounds: can only input between numbers 1 - 16
 Assume user will only enter integer numbers for board positions
 */


#include <iostream>
#include <string>
using namespace std;

void initialize_game(string (&board)[4][4], int size);
//PURPOSE: initalize the game board and resets board back to numbers 1 to 16 when the user indicates to play again
//INPUT: board[4][4] – string array with corresponding values, size– size of string array
//OUTPUT: nothing; passes values by reference
bool is_valid_entry (string board[][4], int size, int board_position);
//PURPOSE: identifies when the player inputs an invalid number (outside the bounds of 1-16
//      or a spot that is already taken) and prompts the user to re-enter a number
//INPUT: board[][4] – string array with corresponding values, size- size of array,
//      board_position: corresponding integer value
//OUTPUT: returns true if entered board position is valid, false if not
void input_move(string (&board)[4][4], int size, string player);
//PURPOSE: Prompts user for board position and saves correpsonding X or O into game board
//INPUT: board[][4] – string array with corresponding values, size- size of array,
//      player– corresponding string of "X" or "O"
//OUTPUT: nothing; values are passed by reference
void display_output(string board[][4], int size);
//PURPOSE: to display the game board as ut updates
//INPUT: board[4][4] – string array with corresponding values, size– size of string array
//OUTPUT: nothing
bool is_tie(string board[][4], int size);
//PURPOSE: to determine if there is a tie on the game board
//INPUT: board[4][4] – string array with corresponding values, size– size of string array
//OUTPUT: Returns true if there is a tie, returns false if there is a position that is not an X nor an O
bool is_winner(string board[][4], int size);
//PURPOSE: Determines if there is a winning combination on the rows, columns and diagonals
//INPUT: board[4][4] – string array with corresponding values, size– size of string array
//OUTPUT: returns true if there is a winner, false if not
void update_stats(string player, string board[][4], int size, int& player_x_wins, int& player_o_wins, int& ties);
//PURPOSE: Updates the stats after a win or tie
//INPUT: board[4][4] – string array with corresponding values,
//      size, player_x_wins, player_o_wins, ties – corresponding integer values
//OUTPUT: nothing; values are passed by reference
void output_stats(int player_x_wins, int player_o_wins, int ties);
//PURPOSE: output board with position numbers and updated board each turn with X or O
//INPUT: player_x_wins, player_o_wins, ties – corresponding integer values
//OUTPUT: nothing

void initialize_game(string (&board)[4][4], int size){
    // Step1. Set board to integers values  1 to 16 and convert into strings
    int count = 1;
    for (int index1 = 0; index1 < 4; index1++) {
        for (int index2 = 0; index2 < 4; index2++) {
            board[index1][index2] = to_string(count++);
        }
    }
}

bool is_valid_entry (string board[][4], int size, int board_position){
    // Step1. Determine position of the entered value
    int columns = board_position % 4;
    int rows = board_position / 4;
    string current_value = board[rows][columns - 1];
    
    //Step2. If the positon is an X or O, it is an invalid entry, user must enter again
    if (current_value == "X" || current_value == "O") {
        cout << "Sorry. Invalid entry.";
        return false;
    }
    else if(board_position < 1 || board_position > 16){
        cout << "Sorry. Invalid entry. ";
        return false;
    }
    else {
        return true;
    }
}

void input_move(string (&board)[4][4], int size, string player){
    // Declare and intialize variables
    int board_position = 0, columns = 0, rows = 0;
    
    //Step1. User inputs board position, check to see if it is a valid entry
    // If it is not valid, user enters again
    do {
        cout << "\nPlayer " << player << " enter your position: ";
        cin >> board_position;
    } while (!is_valid_entry(board, 4, board_position));
    
    //Step2. if it is valid, the board position becomes either X or O
    columns = board_position % 4;
    rows = board_position / 4;
    board[rows][columns - 1] = player;
    
}

void display_output(string board[][4], int size){
    //Step1. Output multidimensional string array in a grid format with position numbers, X, or O
    cout<<"\t\t     |     |     |\n";
    cout<<"\t\t  "<<board[0][0]<<"  |  "<<board[0][1]<<"  |  "<<board[0][2]<<"  |  "<<board[0][3]<<" \n";
    cout<<"\t\t_____|_____|_____|_____\n";
    cout<<"\t\t     |     |     |     \n";
    cout<<"\t\t  "<<board[1][0]<<"  |  "<<board[1][1]<<"  |  "<<board[1][2]<<"  |  "<<board[1][3]<<" \n";
    cout<<"\t\t_____|_____|_____|_____\n";
    cout<<"\t\t     |     |     |     \n";
    cout<<"\t\t  "<<board[2][0]<<"  |  "<<board[2][1]<<" |  "<<board[2][2]<<" |  "<<board[2][3]<<" \n";
    cout<<"\t\t_____|_____|_____|_____\n";
    cout<<"\t\t     |     |     |     \n";
    cout<<"\t\t  "<<board[3][0]<<" |  "<<board[3][1]<<" |  "<<board[3][2]<<" |  "<<board[3][3]<<" \n";
    cout<<"\t\t     |     |     |     \n";
    
}

bool is_tie(string board[][4], int size){
    //Step1. If there is a position that is not an X nor an O, it is not a tie and returns false
    // If all positions are X or O, returns true
    for (int row = 0; row < 4; row++) {
        for (int column = 0; column < 4; column++) {
            if (board[row][column] != "X" && board[row][column] != "O") {
                return false;
            }
        }
    }
    return true;
}

bool is_winner(string board[][4], int size){
    //Step1. Check each row, if all values are equal in a row return true
    for(int row=0; row<4; row++) {
        if(board[row][0] == board[row][1] && board[row][0] == board[row][2] && board[row][0] == board [row][3]) {
            return true;
        }
    }
    //Step2. Check each column, if all values are equal in a column return true
    for(int column=0; column<4; column++){
        if (board[0][column] == board[1][column] && board[0][column] == board[2][column] && board[0][column] == board[3][column]){
           return true;
        }
    }
        
    //Step3. Check both diagonals, if all values are equal in a diagonal return true
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] == board[3][3]){
        return true;
    }
    else if ( board[0][3] == board[1][2] && board[0][3] == board[2][1] && board[0][3] == board[3][0]){
        return true;
    }
    // If not row, column or diagonal are all equal, there is no current winner
    return false;
}


void update_stats(string player, string board[][4], int size, int& player_x_wins, int& player_o_wins, int& ties){
    // Step1. Determine which player won or tied and increase corresponding stat
    if (player == "X" && is_winner(board, 4)) {
        ++player_x_wins;
    }
    else if (player == "O" && is_winner(board, 4)){
        ++player_o_wins;
    }
    else if(is_tie(board, 4)){
        ++ties;
    }
}

void output_stats(int player_x_wins, int player_o_wins, int ties){
    //Step1. Output the overall winner for all games
    if (player_o_wins > player_x_wins){
        cout << "The overall winner is Player O!\n\n";
    }
    else if (player_x_wins > player_o_wins){
        cout << "The overall winner is Player X!\n\n";
    }
    else{
        cout << "There is a tie! Player X and Player O won the same amount of times!\n\n";
    }
    
    // Step2. Output final victories and ties
    cout << "Final game stats:\n";
    cout << "Player X wins:\t" << player_x_wins << "\nPlayer O wins:\t"
        << player_o_wins << "\nTies:\t" << ties;
    // Step3. Output closing statment and indicate simulation is over
    cout << "\n\nThanks for playing! \n";
    
}
 
void start_tic_tac_toe_simulation(){
    // [SETUP] declare and intialize variables
    int player_x_wins = 0, player_o_wins = 0, ties = 0;
    string player, play_again;
    string board[4][4] ={};
    bool x_starts = true;

    cout << "Hello! Welcome to 'Tic Tac Toe'\n\n";
    do {
        // Step1. Set or reset the board back to numbers 1-16
        initialize_game(board, 4);
        // Step2. Switch which player starts for each new game
        if (x_starts) {
            player = "X";
        }
        else {
            player = "O";
        }
        // Step3. Indicate who plays first and display board
        cout << "Player " << player << " goes first.\n\n";

        display_output(board, 4);
        
        // Step4. Allow user to input move and update board display
        do {
            input_move(board, 4, player);
            display_output(board, 4);
            
            // Step4.1 If a winner or tie is detected, ouput corresponding statement
            if (is_winner(board, 4)) {
                cout << "Player " << player << " won! Congratulations!\n";
            }
            else if (is_tie(board, 4)) {
                cout << "Tie game. No winner\n";
                
            }
            // Step4.2 update corresponding stats
            update_stats(player, board, 4, player_x_wins, player_o_wins, ties);
            
            // Step4.3 If no winner or tie, alternate between player X and O
            if (player == "X") {
                player = "O";
            }
            else {
                player = "X";
            }
            // Step4.4 If there is no current winner or tie, continue loop
        } while (!is_winner(board, 4) && !is_tie(board, 4));
        
        // Step5. Ask user if they want to play again, if yes, continue loop
        cout << "\nDo you want to play again? Y/N ";
        cin >> play_again;
        cout << endl;
        
        // Step6. switch the starting player
        x_starts = !x_starts;
       
    } while (play_again == "Y" || play_again == "y" || play_again == "yes");
    //Step7. Output all game stats once users have finished all games
    output_stats(player_x_wins, player_o_wins, ties);
}

int main() {
    //Invoke tic tac toe simulation
    start_tic_tac_toe_simulation();
}

/* SAMPLE OUTPUT
 
 Hello! Welcome to 'Tic Tac Toe'

 Player X goes first.

              |     |     |
           1  |  2  |  3  |  4
         _____|_____|_____|_____
              |     |     |
           5  |  6  |  7  |  8
         _____|_____|_____|_____
              |     |     |
           9  |  10 |  11 |  12
         _____|_____|_____|_____
              |     |     |
           13 |  14 |  15 |  16
              |     |     |

 Player X enter your position: 1
              |     |     |
           X  |  2  |  3  |  4
         _____|_____|_____|_____
              |     |     |
           5  |  6  |  7  |  8
         _____|_____|_____|_____
              |     |     |
           9  |  10 |  11 |  12
         _____|_____|_____|_____
              |     |     |
           13 |  14 |  15 |  16
              |     |     |

 Player O enter your position: 5
              |     |     |
           X  |  2  |  3  |  4
         _____|_____|_____|_____
              |     |     |
           O  |  6  |  7  |  8
         _____|_____|_____|_____
              |     |     |
           9  |  10 |  11 |  12
         _____|_____|_____|_____
              |     |     |
           13 |  14 |  15 |  16
              |     |     |

 Player X enter your position: 2
              |     |     |
           X  |  X  |  3  |  4
         _____|_____|_____|_____
              |     |     |
           O  |  6  |  7  |  8
         _____|_____|_____|_____
              |     |     |
           9  |  10 |  11 |  12
         _____|_____|_____|_____
              |     |     |
           13 |  14 |  15 |  16
              |     |     |

 Player O enter your position: 6
              |     |     |
           X  |  X  |  3  |  4
         _____|_____|_____|_____
              |     |     |
           O  |  O  |  7  |  8
         _____|_____|_____|_____
              |     |     |
           9  |  10 |  11 |  12
         _____|_____|_____|_____
              |     |     |
           13 |  14 |  15 |  16
              |     |     |

 Player X enter your position: 3
              |     |     |
           X  |  X  |  X  |  4
         _____|_____|_____|_____
              |     |     |
           O  |  O  |  7  |  8
         _____|_____|_____|_____
              |     |     |
           9  |  10 |  11 |  12
         _____|_____|_____|_____
              |     |     |
           13 |  14 |  15 |  16
              |     |     |

 Player O enter your position: 7
              |     |     |
           X  |  X  |  X  |  4
         _____|_____|_____|_____
              |     |     |
           O  |  O  |  O  |  8
         _____|_____|_____|_____
              |     |     |
           9  |  10 |  11 |  12
         _____|_____|_____|_____
              |     |     |
           13 |  14 |  15 |  16
              |     |     |

 Player X enter your position: 4
              |     |     |
           X  |  X  |  X  |  X
         _____|_____|_____|_____
              |     |     |
           O  |  O  |  O  |  8
         _____|_____|_____|_____
              |     |     |
           9  |  10 |  11 |  12
         _____|_____|_____|_____
              |     |     |
           13 |  14 |  15 |  16
              |     |     |
 Player X won! Congradulations!

 Do you want to play again? Y/N n

 The overall winner is Player X!

 Final game stats:
 Player X wins:    1
 Player O wins:    0
 Ties:    0

 Thanks for playing!
*/
