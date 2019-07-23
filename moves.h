#ifndef MOVES_H
#define MOVES_H

#include"board.h"
#include"validate.h"

#define isP(pce) ((pce) == wP || (pce) == bP)
#define isN(pce) ((pce) == wN || (pce) == bN)
#define isB(pce) ((pce) == wB || (pce) == bB)
#define isR(pce) ((pce) == wR || (pce) == bR)
#define isQ(pce) ((pce) == wQ || (pce) == bQ)
#define isK(pce) ((pce) == wK || (pce) == bK)

#define FRFLAG 0x7F
#define TOFLAG 0x3F80
#define CPFLAG 0x3C000
#define PRFLAG 0xF00000
#define EPFLAG 0x40000
#define PSFLAG 0x80000
#define CSFLAG 0x1000000

#define MAXPOSITIONMOVES 256

#define MOVE(f, t, ca, pro, flag) ( (f) | ((t) << 7) | ((ca) << 14) | ((pro) << 20) | (flag))
#define SQOFFBOARD(sq) (FilesBrd[(sq)] == OFF_BOARD)

#define FROMSQ(m)   ((m) & 0x7F)
#define TOSQ(m)     (((m) >> 7) & 0x7F)
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

extern const int PMov[2][2];
extern const int Pattack[2][2];

extern const int NMov[8]; 
extern const int BMov[4];
extern const int RMov[4];
extern const int KMov[8];

extern const int Mov[13][8];
extern const int SlidePieces[2][3];
extern const int NonSlidePce[2][2];

extern bool isSqAttacked(const int sq, const int side, const BOARD* pos);
extern std::string PrSq(const int sq);
extern std::string PrMove(const int move);
void PrintMoveList(MOVE_LIST *list);
static void AddQuietMove(const BOARD* pos, int move, MOVE_LIST* list);
static void AddCaptureMove(const BOARD* pos, int move, MOVE_LIST* list);
static void AddEnPassantMove(const BOARD* pos, int move, MOVE_LIST* list);
static void AddPawnMove(const BOARD *pos, const int from, const int to, 
                  const int cap, const int side, MOVE_LIST *list);
static void AddPawnMove(const BOARD *pos, const int from, const int to, 
                  const int side, MOVE_LIST *list);
extern void GenerateAllMoves(const BOARD* pos, MOVE_LIST* list);

//  Clear the piece, update key, material, minPce, majPce, bigPce,
//  pList, pieces, pceNum
static void clearPiece(const int sq, BOARD *pos);

//  add piece, update key, material, majPce, minPce, bigPce,
//  pList, pieces, pceNum
static void addPiece(const int sq, BOARD *pos, const int pce);

// move piece, update key, pList, pieces
static void movePiece(const int from, const int to, BOARD *pos);

// values of castlePerm for each sq
static int castlePerm(int sq);

// takes move and updates the board structure
extern bool makeMove(BOARD *pos, int move);

// undo a move
extern void takeMove(BOARD *pos);

#endif