#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <math.h>
using namespace std;
#define BEGINNER 0
#define INTERMEDIATE 1
#define ADVANCED 2
#define MAXMINES 99
#define MAXSIDE 25
#define MOVESIZE 526 // 625-99 (MAXSIDE*MAXSIDE)-MAXMINES

int sides ; // side length of the board
int noOfMines ; // number of mines on the board
// A Function to get the user move
void makeYourMove(int *x, int *y)
{
    cout<<"Enter your move, (row and column) ->"<<endl;
    scanf("%d %d", x, y);
}

//To check if cell is valid or not
bool isCellValid(int row, int col)
{
    return (row >= 0) && (row < sides) &&
        (col >= 0) && (col < sides);
}

//To check if there is a mine or not
bool isMine (int row, int col, char board[][MAXSIDE])
{
    if (board[row][col] == '*')
        return (true);
    else
        return (false);
}

// A Function to print the current gameplay board
void printYourBoard(char gameBoard[][MAXSIDE])
{
    int i, j;

    cout<<" ";

    for (i=0; i<sides; i++){
        cout<<i;
		}
        cout<<endl;
		 
     for (i=0; i<sides; i++)
    {
        cout<<i;
        for (j=0; j<sides; j++){
            cout<<gameBoard[i][j];
        }
        cout<<endl;
    }
}

// to count the number of adjacent cells especially for corner cases.
int countAdjacentMines(int row, int col, int mines[][2],
                    char mineBoard[][MAXSIDE])
{

    int i;
    int count = 0;

    
        if (isCellValid (row-1, col) == true)
        {
            if (isMine (row-1, col, mineBoard) == true)
            count++;
        }


        if (isCellValid (row+1, col) == true)
        {
            if (isMine (row+1, col, mineBoard) == true)
            count++;
        }


        if (isCellValid (row, col+1) == true)
        {
            if (isMine (row, col+1, mineBoard) == true)
            count++;
        }


        if (isCellValid (row, col-1) == true)
        {
            if (isMine (row, col-1, mineBoard) == true)
            count++;
        }


        if (isCellValid (row-1, col+1) == true)
        {
            if (isMine (row-1, col+1, mineBoard) == true)
            count++;
        }


        if (isCellValid (row-1, col-1) == true)
        {
            if (isMine (row-1, col-1, mineBoard) == true)
            count++;
        }


        if (isCellValid (row+1, col+1) == true)
        {
            if (isMine (row+1, col+1, mineBoard) == true)
            count++;
        }


        if (isCellValid (row+1, col-1) == true)
        {
            if (isMine (row+1, col-1, mineBoard) == true)
            count++;
        }

    return count;
}

//This is the function that regulates the game.
bool playMinesweeperMain(char gameBoard[][MAXSIDE], char mineBoard[][MAXSIDE],
            int mines[][2], int row, int col, int *movesLeft)
{
    if (gameBoard[row][col] != '-')
        return false;

    int i, j;

    //You have clicked on mine and will lose the game now.
    if (mineBoard[row][col] == '*')
    {
        gameBoard[row][col]='*';

        for (i=0; i<noOfMines; i++)
            gameBoard[mines[i][0]][mines[i][1]]='*';

        printYourBoard (gameBoard);
        cout<<"You lost the game!"<<endl;
        return true ;
    }

    else
    {
        // if you did not click the mine then you display adjacent mines.
         int count = countAdjacentMines(row, col, mines, mineBoard);
        (*movesLeft)--;

        gameBoard[row][col] = count + '0';

        if (!count)
        {
            if (isCellValid (row-1, col) == true)
            {
                if (isMine (row-1, col, mineBoard) == false)
                playMinesweeperMain(gameBoard, mineBoard, mines, row-1, col, movesLeft);
            }

            
            if (isCellValid (row+1, col) == true)
            {
                if (isMine (row+1, col, mineBoard) == false)
                    playMinesweeperMain(gameBoard, mineBoard, mines, row+1, col, movesLeft);
            }

            if (isCellValid (row, col+1) == true)
            {
                if (isMine (row, col+1, mineBoard) == false)
                    playMinesweeperMain(gameBoard, mineBoard, mines, row, col+1, movesLeft);
            }

            if (isCellValid (row, col-1) == true)
            {
                if (isMine (row, col-1, mineBoard) == false)
                    playMinesweeperMain(gameBoard, mineBoard, mines, row, col-1, movesLeft);
            }

            if (isCellValid (row-1, col+1) == true)
            {
                if (isMine (row-1, col+1, mineBoard) == false)
                    playMinesweeperMain(gameBoard, mineBoard, mines, row-1, col+1, movesLeft);
            }

            if (isCellValid (row-1, col-1) == true)
            {
                if (isMine (row-1, col-1, mineBoard) == false)
                    playMinesweeperMain(gameBoard, mineBoard, mines, row-1, col-1, movesLeft);
            }

            if (isCellValid (row+1, col+1) == true)
            {
                if (isMine (row+1, col+1, mineBoard) == false)
                    playMinesweeperMain(gameBoard, mineBoard, mines, row+1, col+1, movesLeft);
            }

            if (isCellValid (row+1, col-1) == true)
            {
                if (isMine (row+1, col-1, mineBoard) == false)
                    playMinesweeperMain(gameBoard, mineBoard, mines, row+1, col-1, movesLeft);
            }
        }

        return false;
    }
}

//this function places mines randomly on the mineBoard before the game starts
void placeMines(int mines[][2], char mineBoard[][MAXSIDE])
{
    bool mark[MAXSIDE*MAXSIDE];

    memset (mark, false, sizeof (mark)); //This function converts the value of a character to unsigned character and copies it into each of first n character of the object pointed by the given str[].
 
    for (int i=0; i<noOfMines; )
    {
        int random = rand() % (sides*sides); //so that it does not generate number out of range
        int x = random / sides;
        int y = random % sides;
 
        if (mark[random] == false)
        {
            mines[i][0]= x;
            mines[i][1] = y;
            mineBoard[mines[i][0]][mines[i][1]] = '*';
            mark[random] = true;
            i++;
        }
    }
}

// A Function to initialise the game
void initialise(char mineBoard[][MAXSIDE], char gameBoard[][MAXSIDE])
{
    srand(time(NULL));
    for (int i=0; i<sides; i++)
    {
        for (int j=0; j<sides; j++)
        {
            gameBoard[i][j] = mineBoard[i][j] = '-'; //initialise all gameBoard as well as mineBoard with null values.
        }
    }
}


void cheatOnMinesweeper (char mineBoard[][MAXSIDE])
{
    cout<<"The mines locations are:"<<endl;
    printYourBoard (mineBoard);
}


void replaceMine (int row, int col, char board[][MAXSIDE])
{
    for (int i=0; i<sides; i++)
    {
        for (int j=0; j<sides; j++)
            {
                if (board[i][j] != '*')
                {
                    board[i][j] = '*';
                    board[row][col] = '-';
                    return;
                }
            }
    }
     
}

void playMinesweeper ()
{
    bool isGameOver = false; //this is intially when the game is not over so false
    char mineBoard[MAXSIDE][MAXSIDE], gameBoard[MAXSIDE][MAXSIDE];

    int movesLeft = sides * sides - noOfMines, x, y;
    int mines[MAXMINES][2]; // stores coordinates of all mines

    initialise (mineBoard, gameBoard);
    placeMines (mines, mineBoard);
    /*uncomment if you want to see the mineBoard
    cheatOnMinesweeper(mineBoard); 
*/
    int currentMoveIndex = 0;
    while (isGameOver == false)
    {
        cout<<"The current status of the Game:"<<endl;
        printYourBoard (gameBoard);
        makeYourMove (&x, &y);

        //first move of the game is safe
        if (currentMoveIndex == 0)
        {
            //if first attempt is mine then mine will be removed for safe play.
            if (isMine (x, y, mineBoard) == true)
                replaceMine (x, y, mineBoard);
        }

        currentMoveIndex ++;

        isGameOver = playMinesweeperMain (gameBoard, mineBoard, mines, x, y, &movesLeft);

        if ((isGameOver == false) && (movesLeft == 0))
        {
            cout<<"You WON the Game!!!"<<endl;
            isGameOver = true;
        }
    }
}



void chooseDifficultyLevel ()
{
    
    int level;
    cout<<"Enter the Difficulty Level for the Game:"<<endl;
    cout<<"Press 0 for BEGINNER LEVEL = 9 * 9 Cells and 10 Mines"<<endl;
    cout<<"Press 1 for INTERMEDIATE LEVEL = 16 * 16 Cells and 40 Mines"<<endl;
    cout<<"Press 2 for ADVANCED LEVEL = 24 * 24 Cells and 99 Mines" <<endl;

    cin>>level;

    if (level == BEGINNER)
    {
        sides = 9;
        noOfMines = 10;
    }

    if (level == INTERMEDIATE)
    {
        sides = 16;
        noOfMines = 40;
    }

    if (level == ADVANCED)
    {
        sides = 24;
        noOfMines = 99;
    }

}


int main()
{
    chooseDifficultyLevel();
    playMinesweeper();
    return 0;
}

