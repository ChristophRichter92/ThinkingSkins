/*
  ServoPai.h
*/
#ifndef Coord_h
#define Coord_h

#include "Arduino.h"

class Coord
{
  public:
    Coord(int x, int y);
    void incX();
    void incY();
    void decX();
    void decY();
    void setTo(int x, int y);
    void setStandard(int x, int y);
    int getX();
    int getY();
  private:
    int _x;
    int _y;
};

#endif
