#include"hash.h"
#include"move.h"

const std::string START_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

void Parse_Fen(BOARD* pos, const std::string Fen) {
  int count = 0;
  int rank = RANK_8;
  int file = FILE_A;
  int idx = 0;
  int sq64 = 0;

  ResetBoard(pos);

  for(auto i : Fen) {
    ++idx;

    if(sq64 >= 64)
      break;

    count = 1;

    switch(i) {
      case 'r' : pos->pieces[FR2SQ(file, rank)] = bR; break;
      case 'n' : pos->pieces[FR2SQ(file, rank)] = bN; break;
      case 'b' : pos->pieces[FR2SQ(file, rank)] = bB; break;
      case 'q' : pos->pieces[FR2SQ(file, rank)] = bQ; break;
      case 'k' : pos->pieces[FR2SQ(file, rank)] = bK; break;
      case 'p' : pos->pieces[FR2SQ(file, rank)] = bP; break;
      case 'R' : pos->pieces[FR2SQ(file, rank)] = wR; break;
      case 'N' : pos->pieces[FR2SQ(file, rank)] = wN; break;
      case 'B' : pos->pieces[FR2SQ(file, rank)] = wB; break;
      case 'Q' : pos->pieces[FR2SQ(file, rank)] = wQ; break;
      case 'K' : pos->pieces[FR2SQ(file, rank)] = wK; break;
      case 'P' : pos->pieces[FR2SQ(file, rank)] = wP; break;

      case '1' : 
      case '2' : 
      case '3' : 
      case '4' : 
      case '5' : 
      case '6' : 
      case '7' : 
      case '8' :
                 count = i - '0'; 
                 pos->pieces[FR2SQ(file, rank)] = EMPTY;
                 break;

      case '/' : 
      case ' ' :
                 file = FILE_A, --rank;
                 continue;
      default  : std::cerr << "Invalid FEN\n";
    }

    for(int i = 0; i < count; ++i)
      ++sq64, ++file; 
  }

  pos->side = ( Fen[idx] == 'w' ? WHITE : BLACK );
  
  idx += 2;
  while(Fen[idx] != ' ') {
    switch(Fen[idx]) {
      case 'K' : pos->castlePerm |= WKCA; break;
      case 'Q' : pos->castlePerm |= WQCA; break;
      case 'k' : pos->castlePerm |= BKCA; break;
      case 'q' : pos->castlePerm |= BQCA; break;
      default  : break;
    }
    ++idx;
  }

  if(Fen[++idx] != '-') {
    int file = Fen[idx] - 'a';
    int rank = Fen[++idx] - '1';
    pos->enPas = FR2SQ(file, rank);
  }

  ++idx;
  pos->fifty_move = Fen[++idx] - '0';
  
  ++idx;
  pos->ply = Fen[++idx] - '0';

  pos->key = GeneratePosKey(pos);

  UpdateListMaterial(pos);
}

std::string PrSq(const int sq) {
  int file = FilesBrd[sq];
  int rank = RanksBrd[sq];
  std::string res = {char(file + 'a'), char(rank + '1')};
  return res;
}

std::string PrMove(const int move) {
  int ff = FilesBrd[FROMSQ(move)];
  int ft = FilesBrd[TOSQ(move)];
  int rf = RanksBrd[FROMSQ(move)];
  int rt = RanksBrd[TOSQ(move)];

  int promoted = PROMOTED(move);

  std::string res = {(char)(ff + 'a'), (char)(rf + '1'), (char)(ft + 'a'), (char)(rt + '1')};
  if (promoted) {
    char pchar = 'q';
    if (isN(promoted))
      pchar = 'n';
    else if (isR(promoted))
      pchar = 'r';
    else if (isB(promoted))
      pchar = 'b';
    res += pchar;
  }

  return res;
}