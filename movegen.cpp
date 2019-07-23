#include"moves.h"
#include"hash.h"

static void clearPiece(const int sq, BOARD *pos) {
  assert(onBoard(sq));

  int pce = pos->pieces[sq];

  assert(pceValid(pce));

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
  assert(onBoard(sq));
  assert(pceValid(pce));

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

  assert(pceValid(pce));

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

#ifdef DEBUG
  assert(CheckBoard(pos));
#endif

  int from = FROMSQ(move);
  int to = TOSQ(move);
  int side = pos->side;

  assert(from != OFF_BOARD);
  assert(to != OFF_BOARD);
  assert(sideValid(side));
  assert(onBoard(from));

  pos->history[pos->hisPly].key = pos->key;
  pos->history[pos->hisPly].move = move;
  pos->history[pos->hisPly].fiftymove = pos->fiftymove;
  pos->history[pos->hisPly].enPas = pos->enPas;
  pos->history[pos->hisPly].castlePerm = pos->castlePerm;

  if(move & EPFLAG) {
    if(side == WHITE)
      clearPiece(to - 10, pos);
    else
      clearPiece(to + 10, pos);
  } else if(move & CSFLAG) {
    switch(to) {
      case C1 :  movePiece(A1, D1, pos);  break;
      case C8 :  movePiece(A8, D8, pos);  break;
      case G1 :  movePiece(H1, F1, pos);  break;
      case G8 :  movePiece(H8, F8, pos);  break;
      default :  assert(false); break;
    } 
  } else if(move & PSFLAG) {
      if(side == WHITE)
        pos->enPas = to - 10;
      else
        pos->enPas = to + 10;
  }

  if(pos->enPas != NO_SQ) pos->key ^= PieceKeys[EMPTY][pos->enPas];
  pos->key ^= CastleKeys[pos->castlePerm];
  
  pos->castlePerm &= castlePerm(from);
  pos->castlePerm &= castlePerm(to);
  
  pos->key ^= CastleKeys[pos->castlePerm];

  int captured = CAPTURED(move);
  ++pos->fiftymove;

  if(captured != EMPTY) {
    assert(pceValid(captured));
    clearPiece(to, pos);
    pos->fiftymove = 0;
  }

  ++pos->hisPly;
  ++pos->ply;

  if(piecePwn[from]) {
    pos->fiftymove = 0;
    if(move & PSFLAG) {
      if(side == WHITE) {
        pos->enPas = from + 10;
        assert(RanksBrd[pos->enPas] == RANK_3);
      } else {
        pos->enPas = from - 10;
        assert(RanksBrd[pos->enPas] == RANK_7);
      }
      pos->key ^= PieceKeys[EMPTY][pos->enPas];
    }
  }

  movePiece(from, to, pos);

  int prPce = PROMOTED(move);
  if(prPce != EMPTY) {
    assert(pceValid(prPce));
    clearPiece(to, pos);
    addPiece(to, pos, prPce);
  }

  if(isK(pos->pieces[to]))
    pos->KingSq[pos->side] = to;
  
  pos->side ^= 1;
  pos->key ^= SideKey;

  if(isSqAttacked(pos->KingSq[side], pos->side, pos)) {
    takeMove(pos);
    return false;
  }

  return true;
}

void takeMove(BOARD *pos) {

#ifdef DEBUG
  assert(CheckBoard(pos));
#endif

  --pos->hisPly, --pos->ply;

  int move = pos->history[pos->hisPly].move;
  pos->fiftymove = pos->history[pos->hisPly].fiftymove;
  pos->castlePerm = pos->history[pos->hisPly].castlePerm;
  pos->enPas = pos->history[pos->hisPly].enPas;
  int from = FROMSQ(move);
  int to = TOSQ(move);

  assert(onBoard(from));
  assert(onBoard(to));

  pos->side ^= 1;

  if(move & EPFLAG) {
    if(pos->side == WHITE)
      addPiece(to - 10, pos, bP);
    else
      addPiece(to + 10, pos, wP);
  } else if(CSFLAG & move) {
    switch(to) {
      case C1 :  movePiece(D1, A1, pos);  break;
      case C8 :  movePiece(D8, A8, pos);  break;
      case G1 :  movePiece(F1, H1, pos);  break;
      case G8 :  movePiece(F8, H8, pos);  break;
      default :  assert(false); break;
    }
  }

  movePiece(to, from, pos);

  if(isK(pos->pieces[from]))
    pos->KingSq[pos->side] = from;
  
  int captured = CAPTURED(move);
  if(captured != EMPTY) {
    assert(pceValid(captured));
    addPiece(to, pos, captured);
  }

  int prPce = PROMOTED(move);
  if(prPce != EMPTY) {
    assert(pceValid(prPce) && !piecePwn[prPce]);
    clearPiece(from, pos);
    addPiece(from, pos, pieceCol[prPce] == WHITE ? wP : wB);
  }

  pos->key = pos->history[pos->hisPly].key;

#ifdef DEBUG
  assert(CheckBoard(pos));
#endif
}