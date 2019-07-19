#ifndef HASH_H
#define HASH_H

#include<cstdlib>
#include"defs.h"

//  Generates 64 bit random number
#define RAND_64 ( (U64)rand() | \
                  (U64)rand() << 15 | \
                  (U64)rand() << 30 | \
                  (U64)rand() << 45 | \
                  (U64)rand() << 60 )

extern unsigned U64 PieceKeys[13][120];
extern unsigned U64 SideKey;
extern unsigned U64 CastleKeys[16];
//  enPas pos is taken care by PieceKeys[EMPTY][pos->enPas]

extern void initHash();
extern unsigned U64 GeneratePosKey(const BOARD* pos);

#endif