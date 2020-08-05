#ifndef MOVES_H
#define MOVES_H

#include"board.h"
#include"validate.h"

/******************** MOVE INT DEFINITION *******************************
 * 0000 0000 0000 0000 0000 0111 1111 -> From
 * 0000 0000 0000 0011 1111 1000 0000 -> To
 * 0000 0000 0011 1100 0000 0000 0000 -> Captured piece type
 * 0000 0000 0100 0000 0000 0000 0000 -> En Passant capture move
 * 0000 0000 1000 0000 0000 0000 0000 -> Pawn start move, sets en passant
 * 0000 1111 0000 0000 0000 0000 0000 -> Promoted piece type
 * 0001 0000 0000 0000 0000 0000 0000 -> Castle move
 */

//Utility macro for checking the piece type
#define isP(pce) ((pce) == wP || (pce) == bP)
#define isN(pce) ((pce) == wN || (pce) == bN)
#define isB(pce) ((pce) == wB || (pce) == bB)
#define isR(pce) ((pce) == wR || (pce) == bR)
#define isQ(pce) ((pce) == wQ || (pce) == bQ)
#define isK(pce) ((pce) == wK || (pce) == bK)

//Check flags for en passant, pawn start, castling
#define EPFLAG 0x40000
#define PSFLAG 0x80000
#define CSFLAG 0x1000000

#define MAXPOSITIONMOVES 256

//Convert from, to, captured, promoted, flag(above) to move int
#define MOVE(f, t, ca, pro, fl) ((f) | ((t) << 7) | ((ca) << 14) | ((pro) << 20) | (fl))
//Check if the square is off board
#define SQOFFBOARD(sq) (FilesBrd[(sq)] == OFF_BOARD)

//Extract meaning from move int
#define FROMSQ(m)   ((m) & 0x7F)
#define TOSQ(m)     (((m) >> 7) & 0x7F)
#define CAPTURED(m) (((m) >> 14) & 0xF)
#define PROMOTED(m) (((m) >> 20) & 0xF)

//Defines a move for a game
typedef struct {
//  Move int that stores the info of a move
  int move;
//  Move score for move ordering
  int score;
} MOVE;

//List of moves
typedef struct {
//  Array storing the moves
  MOVE moves[MAXPOSITIONMOVES];
//  Count of moves in the array
  int count;
} MOVE_LIST;

//FEN string for the start of the game
extern const std::string START_FEN;

//Allowed non attack moves for white and black pawns
extern const int PMov[2][2];
//Allowed attack moves for white and black pawns
extern const int PAttack[2][2];

//Allowed moves for knight, bishop, rook, king
extern const int NMov[8]; 
extern const int BMov[4];
extern const int RMov[4];
extern const int KMov[8];

extern const int Mov[13][8];
extern const int SlidePieces[2][3];
extern const int NonSlidePce[2][2];

//Convert from 120 to sq (e.g. 21 to A1)
extern std::string PrSq(const int sq);
//Print move in format FsqTsqPr
extern std::string PrMove(const int move);
//Print move list
void PrintMoveList(MOVE_LIST *list);

//Check if the current square is attacked by side
extern bool isSqAttacked(const int sq, const int side, const BOARD* pos);

/****************** MOVE TYPES *******************
 * Quiet
 * Capture
 * En passant
 */

static void AddQuietMove(const BOARD* pos, int move, MOVE_LIST* list);
static void AddCaptureMove(const BOARD* pos, int move, MOVE_LIST* list);
static void AddEnPassantMove(const BOARD* pos, int move, MOVE_LIST* list);

/******************** PAWN MOVES ********************
 *Pawn moves are special due to promotion
 * Quiet
 * Capture
 */

static void AddPawnMove(const BOARD *pos, const int from, const int to, const int cap, const int side, MOVE_LIST *list);
static void AddPawnMove(const BOARD *pos, const int from, const int to, const int side, MOVE_LIST *list);

//Loop all pieces and add all the possible moves corresponding to each to move list
extern void GenerateAllMoves(const BOARD* pos, MOVE_LIST* list);

//Clear the piece, update key, material, minPce, majPce, bigPce, pList, pieces, pceNum
static void clearPiece(const int sq, BOARD *pos);

//Add piece, update key, material, majPce, minPce, bigPce, pList, pieces, pceNum
static void addPiece(const int sq, BOARD *pos, const int pce);

//Move piece, update key, pList, pieces
static void movePiece(const int from, const int to, BOARD *pos);

//Values of castlePerm for each sq
static int castlePerm(int sq);

//Takes move and updates the board structure
extern bool makeMove(BOARD *pos, int move);

//Undo a move
extern void takeMove(BOARD *pos);

#endif
