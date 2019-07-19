#include"moves.h"

const int PMov[2] = {-10, +10};
const int Pattack[4] = {-9, -11, 9, 11};

const int NMov[8] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int BMov[4] = {-9, -11, 11, 9};
const int RMov[4] = {-1, -10, 1, 10};
const int KMov[8] = {-1, -10, 1, 10, -9, -11, 11, 9};

bool isSqAttacked(const int sq, const int side, const BOARD* pos){

  //  pawns
  for(int idx = 0; idx < 4; ++idx) {
    int pce = pos->pieces[sq + Pattack[idx]];
    if(isP(pce) && pieceCol[pce] == side)
      return true;
  }

  //  knights
  for(int idx = 0; idx < 8; ++idx) {
    int pce = pos->pieces[sq + NMov[idx]];
    if(isN(pce) && pieceCol[pce] == side)
      return true;
  }

  //  bishops and queens
  for(int idx = 0; idx < 4; ++idx) {
    int t_sq = sq + BMov[idx];
    int pce = pos->pieces[t_sq];
    while(pce != OFF_BOARD) {
      if(pce != EMPTY) {
        if((isB(pce) || isQ(pce)) && pieceCol[pce] == side)
          return true;
        break;
      }
    t_sq += BMov[idx];
    pce = pos->pieces[t_sq];
    }
  }

  //  rooks and queens 
  for(int idx = 0; idx < 4; ++idx) {
    int t_sq = sq + RMov[idx];
    int pce = pos->pieces[t_sq];
    while(pce != OFF_BOARD) {
      if(pce != EMPTY) {
        if((isR(pce) || isQ(pce)) && pieceCol[pce] == side)
          return true;
        break;
      }
    t_sq += RMov[idx];
    pce = pos->pieces[t_sq];
    }
  }

  //  kings
  for(int idx = 0; idx < 8; ++idx) {
    int pce = pos->pieces[sq + KMov[idx]];
    if(isK(pce) && pieceCol[pce] == side)
      return true;
  }

  return false;
}