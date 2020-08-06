#include"validate.hpp"

bool onBoard(const int sq) {
  return FilesBrd[sq] != OFF_BOARD;
}

bool sideValid(const int side) {
  return (side == WHITE || side == BLACK);
}

bool FRValid(const int fr) {
  return (fr >= 0 && fr <= 7);
}

bool pceValidEmpty(const int pce) {
  return (pce >= EMPTY && pce <= bK);
}

bool pceValid(const int pce) {
  return (pce >= wP && pce <= bK);
}