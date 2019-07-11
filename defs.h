#ifndef DEFS_H
#define DEFS_H

#define U64 long long
#define BRDSQ_120 120
#define MAX_MOVES 2048
#define FR2SQ(f, r) ( ( 21 + (f) ) + (r) * 10 )
#define SQ64(sq120) Sq4ToSq120[sq120]

#include<string>
#include<algorithm>
#include<iostream>

enum { WHITE, BLACK, BOTH };

enum {
  A1 = 21, B1, C1, D1, E1, F1, G1, H1,
  A2 = 32, B2, C2, D2, E2, F2, G2, H2,
  A3 = 43, B3, C3, D3, E3, F3, G3, H3,
  A4 = 54, B4, C4, D4, E4, F4, G4, H4,
  A5 = 65, B5, C5, D5, E5, F5, G5, H5,
  A6 = 76, B6, C6, D6, E6, F6, G6, H6,
  A7 = 87, B7, C7, D7, E7, F7, G7, H7,
  A8 = 98, B8, C8, D8, E8, F8, G8, H8
};

enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8 };
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H };
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8};

typedef struct {
  int move;
  int castlePerm;
  int enPas;
  U64 key;
} UNDO;

typedef struct {
  int pieces[BRDSQ_120];

  int side;
  int castlePerm;
  int enPas;

  int ply;
  int fiftymove;
  U64 key;

  UNDO history[MAX_MOVES];

  int pList[13][10];
} BOARD;

extern int Sq120ToSq64[BRDSQ_120];
extern int Sq64ToSq120[64];

extern void initBoard();
extern void Parse_Fen(BOARD* pos, std::string Fen);

#endif