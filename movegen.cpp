#include"moves.h"
#include"hash.h"

static void clearPiece(const int sq, BOARD *pos) {
  assert(sq != OFF_BOARD);

  int pce = pos->pieces[sq];

  assert(pce != EMPTY && pce != OFF_BOARD);

  int color = pieceCol[pce];
  int t_pceNum = -1;

  pos->key ^= PieceKeys[pce][sq];

  pos->pieces[sq] = EMPTY;
  pos->material[color] -= pieceVal[pce];

  if(pieceBig[pce]) {
    --pos->bigPce[color];
    if(pieceMaj[pce])
      --pos->majPce[color];
    else
      --pos->minPce[color];
  }

  for(int idx = 0; idx < pos->pceNum[pce]; ++idx) {
    if(pos->pList[pce][idx] == sq) {
      t_pceNum = idx;
      break;
    }
  }

  assert(t_pceNum != -1);

  pos->pList[pce][t_pceNum] = pos->pList[pce][pos->pceNum[pce] - 1];
  --pos->pceNum[pce];
}

static void addPiece(const int sq, BOARD *pos, const int pce) {
  assert(sq != OFF_BOARD);
  assert(pce != EMPTY && pce != OFF_BOARD);

  int color = pieceCol[pce];
  int t_pceNum = -1;

  pos->key ^= PieceKeys[pce][sq];

  pos->pieces[sq] = pce;
  pos->material[color] += pieceVal[pce];

  if(pieceBig[pce]) {
    ++pos->bigPce[color];
    if(pieceMaj[pce])
      ++pos->majPce[color];
    else
      ++pos->minPce[color];
  }

  ++pos->pceNum[pce];
  pos->pList[pce][t_pceNum] = pos->pList[pce][pos->pceNum[pce] - 1] = sq;
}

static void movePiece(const int from, const int to, BOARD *pos) {
  assert(from != OFF_BOARD && to != OFF_BOARD);

  int pce = pos->pieces[from];

  assert(pce != EMPTY && pce != OFF_BOARD);

  pos->key ^= PieceKeys[pce][from];
  pos->pieces[from] = EMPTY;

  pos->key ^= PieceKeys[pce][to];
  pos->pieces[to] = pce;

  int t_idx = -1;
  for(int idx = 0; idx < pos->pceNum[pce]; ++idx) {
    if(pos->pList[pce][idx] == from)
      pos->pList[pce][idx] = to;
      t_idx = pos->pList[pce][idx];
  }

  assert(t_idx != -1);
}

static int castlePerm(int sq) {
  switch(sq) {
    case E8 : return 12;
    case E1 : return 3;
    case H8 : return 11;
    case H1 : return 14;
    case A8 : return 13;
    case A1 : return 7;
    default : return 15; 
  }
}

bool makeMove(BOARD *pos, int move) {
  assert(CheckBoard(pos));

  int from = FROMSQ(move);
  int to = TOSQ(move);
  int side = pos->side;

  assert(from != OFF_BOARD);
  assert(to != OFF_BOARD);
  assert(side == WHITE || side == BLACK);
  assert(pos->pieces[from] != OFF_BOARD && pos->pieces[to] != EMPTY);

  pos->history[pos->hisPly].key = pos->key;

  if(move & EPFLAG) {
    if(side == WHITE)
      clearPiece(to - 10, pos);
    else
      clearPiece(to + 10, pos);
  } else if(move & CSFLAG) {
    switch(to) {
      case C1 :  movePiece(from, to, pos);  break;
      case C8 :  movePiece(from, to, pos);  break;
      case G1 :  movePiece(from, to, pos);  break;
      case G8 :  movePiece(from, to, pos);  break;
      default :  assert(false); break;
    }
  }

  if(pos->enPas != NO_SQ) pos->key ^= PieceKeys[NO_SQ][pos->enPas];
  //  HASH_CA

  pos->history[pos->hisPly].move = move;
  pos->history[pos->hisPly].fiftymove = pos->fiftymove;
  pos->history[pos->hisPly].enPas = pos->enPas;
  pos->history[pos->hisPly].castlePerm = pos->castlePerm;
  
}