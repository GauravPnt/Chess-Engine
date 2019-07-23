#ifndef BOARD_H
#define BOARD_H

#define U64 long long
#define BRDSQ_120 120
#define MAX_MOVES 2048

//  Convert from given file, rank to 120 board
#define FR2SQ(f, r) ( ( 21 + (f) ) + (r) * 10 )
//  Convert from 120 board to 64 board
#define SQ64(sq120) (Sq120ToSq64[(sq120)])
//  Convert from 64 board to 120 board
#define SQ120(sq64) (Sq64ToSq120[(sq64)])

#include<string>
#include<algorithm>
#include<iostream>
#include<iomanip>

#include<assert.h>

enum { WHITE, BLACK, BOTH };

enum {
  A1 = 21, B1, C1, D1, E1, F1, G1, H1,
  A2 = 31, B2, C2, D2, E2, F2, G2, H2,
  A3 = 41, B3, C3, D3, E3, F3, G3, H3,
  A4 = 51, B4, C4, D4, E4, F4, G4, H4,
  A5 = 61, B5, C5, D5, E5, F5, G5, H5,
  A6 = 71, B6, C6, D6, E6, F6, G6, H6,
  A7 = 81, B7, C7, D7, E7, F7, G7, H7,
  A8 = 91, B8, C8, D8, E8, F8, G8, H8, 
  NO_SQ, OFF_BOARD
};

enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8 };
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H };
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8};

typedef struct {
  int move;
  int castlePerm;
  int fiftymove;
  int enPas;
  unsigned U64 key;
} UNDO;

typedef struct {
  int pieces[BRDSQ_120];

  int side;
  int castlePerm;
  int enPas;

  int ply;
  int hisPly;
  int fiftymove;
  unsigned U64 key;

  //  evaluation improvement sugars

  //  holds King's square
  int KingSq[2];
  //  all below store counts of respective pieces
  int pceNum[13]; //  all
  int bigPce[2];  //  anything not a pawn
  int majPce[2];  //  rook, queen
  int minPce[2];  //  knight, bishop
  int material[2];   

  UNDO history[MAX_MOVES];

  int pList[13][10];
} BOARD;

extern int Sq120ToSq64[BRDSQ_120];
extern int Sq64ToSq120[64];

extern int FilesBrd[BRDSQ_120];
extern int RanksBrd[BRDSQ_120];

extern int pieceBig[13];
extern int pieceMaj[13];
extern int pieceMin[13];
extern int pieceVal[13];
extern int pieceCol[13];
extern int piecePwn[13];

//  Conversion array to chars
extern std::string PiceChar;
extern std::string SideChar;

//  Initialize the conversion arrays
extern void initBoard();

extern void ResetBoard(BOARD* pos);

//  Prints the conversion from 64 to 120 and vice versa
extern void printBoard();

//  Print the pieces as present on the board
extern void printBoard(BOARD* pos);

extern void UpdateListMaterial(BOARD* pos);

// assertion utility
extern bool CheckBoard(const BOARD* pos);

extern void Parse_Fen(BOARD* pos, const std::string Fen);

// convert from 120 to sq (e.g. 21 to A1)
extern std::string PrSq(const int sq);

// print move in format FsqTsqPr
extern std::string PrMove(const int move);

#endif