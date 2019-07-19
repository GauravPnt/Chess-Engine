#ifndef MOVES_H
#define MOVES_H

#include "board.h"

#define isP(pce) ((pce) == wP || (pce) == bP)
#define isN(pce) ((pce) == wN || (pce) == bN)
#define isB(pce) ((pce) == wB || (pce) == bB)
#define isR(pce) ((pce) == wR || (pce) == bR)
#define isQ(pce) ((pce) == wQ || (pce) == bQ)
#define isK(pce) ((pce) == wK || (pce) == bK)

#define FRFLAG 0x3F
#define TOFLAG 0x3F80
#define CPFLAG 0x3C000
#define PRFLAG 0xF00000
#define EPFLAG 0x40000
#define PSFLAG 0x80000
#define CSFLAG 0x1000000

#define MAXPOSITIONMOVES 256

#define FROMSQ(m)   ((m) & 0x3F)
#define TOSQ(m)     (((m) >> 7) & 0x3F)
#define CAPTURED(m) (((m) >> 14) & 0xF)
#define PROMOTED(m) (((m) >> 20) & 0xF)

typedef struct {
  int move;
  int score;
} MOVE;

typedef struct {
  MOVE moves[MAXPOSITIONMOVES];
  int count;
} MOVE_LIST;

extern const std::string START_FEN;

const extern int PMov[2];
const extern int Pattack[4];

const extern int NMov[8]; 
const extern int BMov[4];
const extern int RMov[4];
const extern int KMov[8];

extern bool isSqAttacked(const int sq, const int side, const BOARD* pos);
extern std::string PrMove(const int sq);
extern std::string PrMove(const int move);

#endif