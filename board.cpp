#include"board.h"
#include"hash.h"

int Sq120ToSq64[BRDSQ_120];
int Sq64ToSq120[64];

void initBoard() {
  std::fill(Sq120ToSq64, Sq120ToSq64 + BRDSQ_120, 65);
  std::fill(Sq64ToSq120, Sq64ToSq120 + 64, 120);

  int sq64 = 0;
  for(int rank = RANK_1; rank <= RANK_8; ++ rank) {
    for(int file = FILE_A; file <= FILE_H; ++file) {
      int sq = FR2SQ(file, rank);
      Sq120ToSq64[sq] = sq64;
      Sq64ToSq120[sq64++] = sq;
    }
  }
}

void ResetBoard(BOARD* pos) {
  for(int idx = 0; idx < BRDSQ_120; ++idx)
    pos->pieces[idx] = OFF_BOARD;
  
  for(int idx = 0; idx < 64; ++idx)
    pos->pieces[SQ120(idx)] = EMPTY;
  
  pos->side = BOTH;
  pos->enPas = NO_SQ;
  pos->castlePerm = 0;
  pos->ply = 0;
  pos->hisPly = 0;
  pos->fiftymove = 0;
  pos->key = 0;
}

void Parse_Fen(BOARD* pos, std::string Fen){
  int count = 0;
  int sq64 = 0;
  int idx = 0;

  ResetBoard(pos);

  for(auto i : Fen) {
    ++idx;

    if(sq64 >= 64)
      break;

    count = 1;

    switch(i) {
      case 'r' : pos->pieces[SQ120(sq64)] = bR; break;
      case 'n' : pos->pieces[SQ120(sq64)] = bN; break;
      case 'b' : pos->pieces[SQ120(sq64)] = bB; break;
      case 'q' : pos->pieces[SQ120(sq64)] = bQ; break;
      case 'k' : pos->pieces[SQ120(sq64)] = bK; break;
      case 'p' : pos->pieces[SQ120(sq64)] = bP; break;
      case 'R' : pos->pieces[SQ120(sq64)] = wR; break;
      case 'N' : pos->pieces[SQ120(sq64)] = wN; break;
      case 'B' : pos->pieces[SQ120(sq64)] = wB; break;
      case 'Q' : pos->pieces[SQ120(sq64)] = wQ; break;
      case 'K' : pos->pieces[SQ120(sq64)] = wK; break;
      case 'P' : pos->pieces[SQ120(sq64)] = wP; break;

      case '1' : 
      case '2' : 
      case '3' : 
      case '4' : 
      case '5' : 
      case '6' : 
      case '7' : 
      case '8' :
                 count = i - '0'; 
                 pos->pieces[SQ120(sq64)] = EMPTY;
                 break;

      case '/' : 
      case ' ' :
                 continue;
      default  : std::cerr << "Invalid FEN\n";
    }

    for(int i = 0; i < count; ++i)
      ++sq64; 
  }

  ++idx;
  pos->side = ( Fen[idx] == 'w' ? WHITE : BLACK );
  
  ++idx;
  for(int i = 0; i < 4; ++i) {
    ++idx;
    if(Fen[idx] == ' ')
      break;
    switch(Fen[idx]) {
      case 'K' : pos->castlePerm |= WKCA; break;
      case 'Q' : pos->castlePerm |= WQCA; break;
      case 'k' : pos->castlePerm |= BKCA; break;
      case 'q' : pos->castlePerm |= BQCA; break;
      default  : break;
    }
  }

  ++idx;
  if(Fen[idx] != '-') {
    int file = Fen[idx] - 'a';
    int rank = Fen[++idx] - '1';
    pos->enPas = FR2SQ(file, rank);
  }

  ++idx;
  pos->fiftymove = Fen[++idx] - '0';
  
  ++idx;
  pos->ply = Fen[++idx] - '0';

  pos->key = GeneratePosKey(pos);
}