#ifndef BOARD_H
#define BOARD_H

//  Convert from given file, rank to 120 board
#define FR2SQ(f, r) ( ( 21 + (f) ) + (r) * 10 )
//  Convert from 120 board to 64 board
#define SQ64(sq120) (Sq120ToSq64[(sq120)])
//  Convert from 64 board to 120 board
#define SQ120(sq64) (Sq64ToSq120[(sq64)])

#include"defs.h"
#include<string>
#include<algorithm>
#include<iostream>

extern int Sq120ToSq64[BRDSQ_120];
extern int Sq64ToSq120[64];

extern void initBoard();
extern void ResetBoard(BOARD* pos);
extern void Parse_Fen(BOARD* pos, std::string Fen);

#endif