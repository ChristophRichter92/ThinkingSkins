/*
  Coord.cpp
*/

#include "Arduino.h"
#include "Coord.h"

Coord::Coord(int x, int y)
{
  _x = x;  
  _y = y;
}

int Coord::getX()
{
  return _x;
}

int Coord::getY()
{
  return _y;
}

void Coord::incX()
{
  _x++;
}

void Coord::incY()
{
  _y++;
}

void Coord::decX()
{
  _x--;
}

void Coord::decY()
{
  _y--;
}

void Coord::setX(int x)
{
  _x = x;
}

void Coord::setY(int y)
{
  _y = y;
}

void Coord::setTo(int x, int y)
{
  _x = x;
  _y = y;
}
