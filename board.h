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
#include<iomanip>

extern int Sq120ToSq64[BRDSQ_120];
extern int Sq64ToSq120[64];

extern char FilesBrd[BRDSQ_120];
extern int RanksBrd[BRDSQ_120];

//  Conversion array to chars
extern std::string PiceChar;
extern std::string SideChar;

const std::string START_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

//  Initialize the conversion arrays
extern void initBoard();
extern void ResetBoard(BOARD* pos);
extern void Parse_Fen(BOARD* pos, const std::string Fen);
//  Prints the conversion from 64 to 120 and vice versa
extern void printBoard();
//  Print the pieces as present on the board
extern void printBoard(BOARD* pos);

#endif