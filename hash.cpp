#include"hash.h"

U64 PieceKeys[13][120];
U64 SideKey;
U64 CastleKeys[16];

void initHash() {
  for(int piece = EMPTY; piece <= bK; ++piece)
    for(int pos = 0; pos < BRDSQ_120; ++pos)
      PieceKeys[piece][pos] = RAND_64;

  SideKey = RAND_64;

  for(int key = 0; key < 16; ++key)
    CastleKeys[key] = RAND_64;  
}

U64 GeneratePosKey(BOARD* pos){
  U64 FinalKey = 0;
  
  for(int sq = 0; sq < BRDSQ_120; ++sq){
    int piece = pos->pieces[sq];
    if(piece != EMPTY)
      FinalKey ^= PieceKeys[piece][sq];
  }

  if(pos->side == WHITE)
    FinalKey ^= SideKey;
  
  if(pos->enPas != NO_SQ)
    FinalKey ^= PieceKeys[EMPTY][pos->enPas];

  FinalKey ^= CastleKeys[pos->castlePerm];

  return FinalKey; 
}