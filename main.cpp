#include <iostream>
#include "Board.h"
#include "Tile.h"

using namespace std;

void printBoard(const Board&);

int main(){

    int width = 6;
    int height = width;
    int numberOfMines = 9;
    // Create a 6 x 6 square board with 9 mines
    Board newBoard(width, height, numberOfMines);

    // Search the board for the first empty space and reveal it
    for (int i = 1; i < newBoard.getRows() - 1; i++)
    {
        for (int j = 1; j < newBoard.getCols() - 1; j++)
        {
            if (newBoard.getGrid()[i][j].getState() == State::empty)
            {
                newBoard.chainReveal(i, j);
                i = newBoard.getRows() - 1;
                break;
            }
        }
    }

    int x, y, cnt = 0;

    do
    {
        printBoard(newBoard);
        
        cin >> x >> y;  // Get input form user


        // If the tile you revealed is empty reveal everything around it
        // if it's a mine you lose the game
        // if it's a number tile reveal only that
        if (newBoard.getGrid()[x][y].getState() == State::empty)
        {
            newBoard.chainReveal(x, y);
        }
        else if (newBoard.getGrid()[x][y].getState() == State::mine)
        {
            newBoard.getGrid()[x][y].reveal();
            printBoard(newBoard);
            cout << endl << "Game over :c" << endl;
            break;
        }
        else
        {
            newBoard.getGrid()[x][y].reveal();
        }


        // Win condition
        // count how many tiles are hidden
        for (int i = 1; i < newBoard.getRows() - 1; i++)
        {
            for (int j = 1; j < newBoard.getCols() - 1; j++)
            {
                if (!newBoard.getGrid()[i][j].isHidden())
                {
                    cnt++;
                }
            }
        }
        // If the number of hidden tiles is the number of all tiles minus how many mines there are you win
        if (cnt == width * height - numberOfMines)
        {
            printBoard(newBoard);
            cout << "You win! :D" << endl;
            break;
        }

        cnt = 0;

    } while (true);
}

void printBoard(const Board& board)
{

    cout << "     ";
    for (int i = 1; i <= board.getRows() - 2; i++)
    {
        cout << i << "   ";
    }
    cout << endl;

    for (int i = 1; i < board.getRows() - 1; i++)
    {
        if (i < 10)
            cout << " " << i << " ";
        else
            cout << i << " ";

        for (int j = 1; j < board.getCols() - 1; j++)
        {

            if (board.getGrid()[i][j].getState() == State::outerLayer)
                continue;

            if (board.getGrid()[i][j].isHidden())
            {
                cout << "| X ";
            }
            else if (board.getGrid()[i][j].isFlagged())
            {
                cout << "| F ";
            }
            else
            {
                cout << "| " << board.getGrid()[i][j].getGraphic() << " ";
            }

            if (j == board.getCols() - 2)
            {
                cout << "|";
            }
        }

        cout << endl;
    }
}