#ifndef VALIDATE_H
#define VALIDATE_H

#include"board.h"

extern bool onBoard(const int sq);
extern bool sideValid(const int side);
extern bool FRValid(const int fr);
extern bool pceValidEmpty(const int pce);
extern bool pceValid(const int pce);

#endif