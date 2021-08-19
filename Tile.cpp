#include "Tile.h"

Tile::Tile()
{
    state = State::empty;
    graphic = ' ';
    label = 0;
    hidden = true;
    x = 0;
    y = 0;
    flagged = false;
}

Tile::Tile(State s, char g)
{
    state = s;
    graphic = g;
    label = 0;
    hidden = true;
    x = 0;
    y = 0;
    flagged = false;
}

void Tile::setState(State s)
{
    state = s;
}
void Tile::setGraphic(char g)
{
    graphic = g;
}
void Tile::setLabel(int l)
{
    label = l;
}

void Tile::hide()
{
    hidden = true;
}
void Tile::reveal()
{
    hidden = false;
}
void Tile::setX(int X)
{
    x = X;
}
void Tile::setY(int Y)
{
    y = Y;
}
void Tile::flag()
{
    if (flagged == true)
        flagged = false;
    else
        flagged = true;
}