#include"moves.h"

const int PMov[2][2] = {{10, 20}, {-10, -20}};
const int Pattack[2][2] = {{9, 11}, {-9, -11}};

const int NMov[8] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int BMov[4] = {-9, -11, 11, 9};
const int RMov[4] = {-1, -10, 1, 10};
const int KMov[8] = {-1, -10, 1, 10, -9, -11, 11, 9};

bool isSqAttacked(const int sq, const int side, const BOARD* pos) {

  assert(sq != OFF_BOARD);
  assert(side == WHITE || side == BLACK);

#ifdef DEBUG
  assert(CheckBoard(pos));
#endif

  //  pawns
  if(side == WHITE) {
		if(pos->pieces[sq-11] == wP || pos->pieces[sq-9] == wP) {
			return true;
		}
	} else {
		if(pos->pieces[sq+11] == bP || pos->pieces[sq+9] == bP) {
			return true;
		}	
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