
// Andres Gutierrez
// 08-13-2022
// Connect4.cpp

/* programmers note!

    this program will only be visibly usable if your terminal
    is capable of displaying ubuntu terminal color codes 

    
*/

#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

// classes 
class token { 
    private:
        string color, display; 
    public: 
        void setColor(string in);
        string retToken() {
            return display;
        }
        string retColor() {
            return color;
        }
        token();
};

// prototypes
void pgrmGreet();
void pgrmEnd();
void theGame();
void printBoard(token Board[][7], int Rows, int Cols);
void updateBoard(token Board[][7], int Rows, int ColChoice, int PlyrNum);
string checkBoard(token Board[][7]);  

void token::setColor(string in) { 
    color = in;
    if (color == "red") {
        display = "\033[31mO\033[0m";
    }
    else if (color == "blue") {
        display = "\033[34mO\033[0m";
    }
    else {
        display = "O";
    }

} 
token::token(void) {
   setColor("blank"); 
}

int main () {

    pgrmGreet();
    theGame(); 
    pgrmEnd(); 

    return 0;
}

void pgrmGreet() {

    cout << "\n\"\"\"\n"
         << "    Welcome to ConnectFour!\n\n" 
         << "    A program built by Andres Gutierrez\n"
         << "    On 08-13-2022\n"
         << "\"\"\"\n" << endl;
}
void pgrmEnd() {

    cout << "\n\"\"\"\n"
         << "    Thanks for playing!\n\n"
         << "    Enter anything to quit the game\n" 
         << "\"\"\"\n" << endl;
    char a;
    cin >> a;
}

void theGame() {

    const int rows = 6, cols = 7; 

    token board[rows][cols];

    // board set up 
    AGAIN: 
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col ++) {
                token holder;
                board[row][col] = holder;
            }
        }

    //get move 
    cout << "Determing who will go first . . .\n" << endl;
    srand((unsigned) time(0));
    int plyr = (rand() % 2) + 1;
    cout << "Player " << plyr << " will go first.\n\n";

    string trueCond;
    while (true) {

        printBoard(board, rows, cols);
        int colChoice = -1;
        cout << "\nIt is player " << plyr << "\'s turn\n";
        cout << "Please enter the number of the column you wish to fill: ";
        cin >> colChoice;
        cout << "\n"; 
        while ((colChoice < 1 || colChoice > 7) || cin.fail() || board[0][colChoice -1].retToken() != "O") {
            cin.clear();
            cin.ignore(123,'\n');
            cout << "Enter a valid input: ";
            cin >> colChoice;
            cout << "\n";
        }
        colChoice--;
        updateBoard(board, rows, colChoice, plyr);
        if (plyr == 1) {
            plyr++;
        }
        else {
            plyr--;
        }
        string gameCond = checkBoard(board);
        if (gameCond == "red" || gameCond == "blue" || gameCond == "tie") {
            trueCond = gameCond;
            break;
        }
    }
    printBoard(board, rows, cols);
    cout << "\nGame over!\n"; 
    if (trueCond == "red" || trueCond == "blue") {
        cout << "Looks like the " << trueCond << " side won!" << endl;
    }
    else {
        cout << "Looks like it was a " << trueCond << "!" << endl;
    }

    char playAgain; 
    cout << "\nDid you want to play again? (y/n): ";
    ERR:
        cin >> playAgain;
        if (tolower(playAgain) != 'y' && tolower(playAgain) != 'n') {
            cout <<"\nInvalid Input, go again: ";
            cin.clear();
            cin.ignore(10, '\n');
            goto ERR;
        }
    if (tolower(playAgain) == 'y') {
        cout << endl;
        goto AGAIN;
    }

}
void printBoard(token Board[][7], int Rows, int Cols) {

   for (int col = 0; col < Cols; col++) {
        cout <<"  " << col + 1 << " ";
    }
    cout << endl;
    for (int row = 0; row < Rows; row++) {
        for (int col = 0; col < Cols; col ++) {
            cout << " \033[90m[\033[0m" << Board[row][col].retToken() << "\033[90m]\033[0m";
        }
        cout << endl;
    }
    cout << "/___________________________\\" << endl;
}
void updateBoard(token Board[][7], int Rows, int ColChoice, int PlyrNum) {


    for (int rowEnd = 5; rowEnd >= 0; rowEnd--) {
        if (Board[rowEnd][ColChoice].retToken() == "O") {
            if (PlyrNum == 1) {
                Board[rowEnd][ColChoice].setColor("blue");
            }
            else {
                Board[rowEnd][ColChoice].setColor("red");
            }
            break;
        }
    }
}
string checkBoard(token Board[][7]) {

    // horz check 
    for (int row = 0; row < 6; row++) {
        string horzCheck; 
        for (int col = 0; col < 4; col++) {
            horzCheck = Board[row][col].retColor() + Board[row][col + 1].retColor() + Board[row][col + 2].retColor() + Board[row][col + 3].retColor();
            if (horzCheck == "redredredred") {
                return "red";
            }
            else if (horzCheck == "blueblueblueblue") {
                return "blue";
            }
        }
        
    }

    // vert 
    for (int col = 0; col < 7; col++) {
        string vertCheck; 
        for (int row = 0; row < 3; row++) {
            vertCheck = Board[row][col].retColor() + Board[row + 1][col].retColor() + Board[row  + 2][col].retColor() + Board[row + 3][col].retColor();
            if (vertCheck == "redredredred") {
                return "red";
            }
            else if (vertCheck == "blueblueblueblue") {
                return "blue";
            }
        }
        
    }

    // down right check
    for (int col = 0; col < 4; col++) {
        string vertCheck; 
        for (int row = 0; row < 3; row++) {
            vertCheck = Board[row][col].retColor() + Board[row + 1][col + 1].retColor() + Board[row  + 2][col + 2].retColor() + Board[row + 3][col + 3].retColor();
            if (vertCheck == "redredredred") {
                return "red";
            }
            else if (vertCheck == "blueblueblueblue") {
                return "blue";
            }
        }
        
    }

    // dl 
     for (int col = 7; col > 3; col--) {
        string vertCheck; 
        for (int row = 0; row < 3; row++) {
            vertCheck = Board[row][col].retColor() + Board[row + 1][col - 1].retColor() + Board[row  + 2][col - 2].retColor() + Board[row + 3][col - 3].retColor();
            if (vertCheck == "redredredred") {
                return "red";
            }
            else if (vertCheck == "blueblueblueblue") {
                return "blue";
            }
        }
        
    }   

    // tie check sort off
    for (int col = 0; col < 7; col++) {
        if (Board[0][col].retToken() == "O") {
            return "none";
        }
    }

    return "tie";
}
