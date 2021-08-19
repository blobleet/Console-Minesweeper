#include "Board.h"

Board::Board()
{
    grid = nullptr;
    rows = 0;
    cols = 0;
    mineCnt = 0;
}
Board::Board(int r, int c, int mines)
{
    srand(time(NULL));

    //+2 because we need an extra layer on the grid
    rows = r + 2;
    cols = c + 2;
    mineCnt = mines;

    grid = new Tile * [rows];
    for (int i = 0; i < rows; i++)
    {
        grid[i] = new Tile[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            grid[i][j].setX(i);
            grid[i][j].setY(j);
        }
    }

    // Setting the outer layer
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == 0)
                grid[i][j].setState(State::outerLayer);
            if (i == rows - 1)
                grid[i][j].setState(State::outerLayer);
            if (j == 0)
                grid[i][j].setState(State::outerLayer);
            if (j == cols - 1)
                grid[i][j].setState(State::outerLayer);
        }
    }

    //Generate numbers for where to place mines

    int* mineSpots = new int[mineCnt];
    for (int i = 0; i < mineCnt; i++)
    {

        mineSpots[i] = rand() % (r * c) + 1;

        for (int j = 0; j < i; j++)
        {
            if (mineSpots[i] == mineSpots[j])
            {
                i--;
                break;
            }
        }
    }

    //Place mines on the designated places
    int spot = 1;
    int index = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j].getState() == State::outerLayer)
                continue;

            if (mineSpots[index] == spot)
            {
                grid[i][j].setState(State::mine);
                i = 0;
                j = 0;
                spot = 1;
                index++;
                break;
            }
            spot++;
        }
    }

    //Start placing numbers
    Tile** ajacent = nullptr;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j].getState() == State::outerLayer)
                continue;
            else if (grid[i][j].getState() == State::mine)
                continue;

            ajacent = getAjacent(i, j);

            for (int k = 0; k < 8; k++)
            {

                if (ajacent[k]->getState() == State::mine)
                {
                    grid[i][j].setLabel(grid[i][j].getLabel() + 1);
                    grid[i][j].setState(State::numbered);
                }
            }
        }
    }

    /*
      Checking if it works
    for(int i = 0; i < rows; i++)
    {
      for(int j = 0; j < cols; j++)
      {
        cout << grid[i][j].getLabel();
      }
      cout << endl;
    }
    */

    //Set graphic
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            switch (grid[i][j].getState())
            {
            case State::outerLayer:
                grid[i][j].setGraphic(' ');
                break;
            case State::mine:
                grid[i][j].setGraphic('M');
                break;
            case State::numbered:
                grid[i][j].setGraphic(digitToChar(grid[i][j].getLabel()));
                break;
            case State::empty:
                grid[i][j].setGraphic(' ');
                break;
            default:
                cout << "Set graphic error!" << endl;
                break;
            }
        }
    }


    delete[] mineSpots;
}

Tile** Board::getAjacent(int x, int y)
{
    /*
      This function returns a double pointer
      because I need an array of references
      to the adjacent tiles in order to manipilate
      them directly when it is needed
    */

    Tile** ajacentTiles = new Tile * [8];
    int cnt = 0;

    // I cant use loop here because the
    // value for x and y is always different
    ajacentTiles[cnt] = &grid[x - 1][y];
    cnt++;
    ajacentTiles[cnt] = &grid[x - 1][y + 1];
    cnt++;
    ajacentTiles[cnt] = &grid[x][y + 1];
    cnt++;
    ajacentTiles[cnt] = &grid[x + 1][y + 1];
    cnt++;
    ajacentTiles[cnt] = &grid[x + 1][y];
    cnt++;
    ajacentTiles[cnt] = &grid[x + 1][y - 1];
    cnt++;
    ajacentTiles[cnt] = &grid[x][y - 1];
    cnt++;
    ajacentTiles[cnt] = &grid[x - 1][y - 1];
    cnt++;

    return ajacentTiles;
}

void Board::chainReveal(int x, int y)
{
    Tile** ajacent = getAjacent(x, y);

    grid[x][y].reveal();

    for (int i = 0; i < 8; i++)
    {

        if (ajacent[i]->getState() == State::empty
            && ajacent[i]->isHidden())
        {
            chainReveal(ajacent[i]->getX(), ajacent[i]->getY());
        }

        ajacent[i]->reveal();
    }
}

/*
Board::~Board()
{
  for(int i = 0; i < rows; i++)
  {
    delete[] grid[i];
  }
  delete[] grid;
}
*/

void Board::setRows(int r)
{
    rows = r;
}
void Board::setCols(int c)
{
    cols = c;
}
void Board::setMineCnt(int mines)
{
    mineCnt = mines;
}
void Board::setGrid(Tile** g)
{
    grid = g;
}

char digitToChar(int i)
{
    switch (i)
    {
    case 1:
        return '1';
        break;
    case 2:
        return '2';
        break;
    case 3:
        return '3';
        break;
    case 4:
        return '4';
        break;
    case 5:
        return '5';
        break;
    case 6:
        return '6';
        break;
    case 7:
        return '7';
        break;
    case 8:
        return '8';
        break;
    case 9:
        return '9';
        break;
    default:
        return '0';
        break;
    }
}
