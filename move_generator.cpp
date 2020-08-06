#include"move.hpp"

const int SlidePieces[2][3] = {{wB, wR, wQ}, {bB, bR, bQ}};
const int NonSlidePce[2][2] = {{wN, wK}, {bN, bK}};

const int Mov[13][8] = {
  {},
  {},
  {-8, -19, -21, -12, 8, 19, 21, 12},
  {-9, -11, 11, 9},
  {-1, -10, 1, 10},
  {-1, -10, 1, 10, -9, -11, 9, 11},
  {-1, -10, 1, 10, -9, -11, 11, 9},
  {},
  {-8, -19, -21, -12, 8, 19, 21, 12},
  {-9, -11, 11, 9},
  {-1, -10, 1, 10},
  {-1, -10, 1, 10, -9, -11, 9, 11},
  {-1, -10, 1, 10, -9, -11, 11, 9}
};

void PrintMoveList(std::shared_ptr<const MOVE_LIST> list) {
  for(int idx = 0; idx < list->count; ++idx)
    std::cout << "Move: " << idx << " > " << PrMove(list->moves[idx].move) 
              << ' ' << "(score:" << list->moves[idx].score << ')' << '\n';
}

static void AddQuietMove(int move, std::shared_ptr<MOVE_LIST> list) {
  list->moves[list->count].move = move;
  list->moves[list->count].score = 0;
  ++list->count;
}

static void AddCaptureMove(int move, std::shared_ptr<MOVE_LIST> list) {
  list->moves[list->count].move = move;
  list->moves[list->count].score = 0;
  ++list->count;
}

static void AddEnPassantMove(int move, std::shared_ptr<MOVE_LIST> list) {
  list->moves[list->count].move = move;
  list->moves[list->count].score = 0;
  ++list->count;
}

static void AddPawnMove(std::shared_ptr<const BOARD> pos, const int from, const int to, const int cap, const int side,
                        std::shared_ptr<MOVE_LIST> list) {
  assert(sideValid(side));
  assert(onBoard(from));
  assert(onBoard(to));
  assert(pceValidEmpty(cap));

  if(side == WHITE) {
    if(RanksBrd[from] == RANK_7) {
//      Promotion moves
      for(int pro = wQ; pro >= wN; --pro)
        AddCaptureMove(MOVE(from, to, cap, pro, 0), list);
    } else
      AddCaptureMove(MOVE(from, to, cap, EMPTY, 0), list);
  } else {
    if(RanksBrd[from] == RANK_2) {
//      Promotion moves
      for(int pro = bQ; pro >= bN; --pro)
        AddCaptureMove(MOVE(from, to, cap, pro, 0), list);
    } else
      AddCaptureMove(MOVE(from, to, cap, EMPTY, 0), list);
  }
}

static void AddPawnMove(std::shared_ptr<const BOARD> pos, const int from, const int to, const int side,
                        std::shared_ptr<MOVE_LIST> list) {
  assert(sideValid(side));
  assert(onBoard(from));
  assert(onBoard(to));

  if(side == WHITE) {
    if(RanksBrd[from] == RANK_7) {
//      Promotion moves
      for(int pro = wQ; pro >= wN; --pro)
        AddQuietMove(MOVE(from, to, EMPTY, pro, EMPTY), list);
    } else
      AddQuietMove(MOVE(from, to, EMPTY, EMPTY, 0), list);
  } else {
    if(RanksBrd[from] == RANK_2) {
//      Promotion moves
      for(int pro = bQ; pro >= bN; --pro)
        AddQuietMove(MOVE(from, to, EMPTY, pro, EMPTY), list);
    } else
      AddQuietMove(MOVE(from, to, EMPTY, EMPTY, 0), list);
  }
}

void GenerateAllMoves(std::shared_ptr<const BOARD> pos, std::shared_ptr<MOVE_LIST> list) {

#ifdef DEBUG
  assert(CheckBoard(pos));
#endif
  
  list->count = 0;

  int pce = EMPTY;
  int side = pos->side;

  assert(sideValid(side));

  if(side == WHITE) {

//    Loop through all the pawns on the board
    for(int pceNum = 0; pceNum < pos->pceNum[wP]; ++pceNum) {
      int sq = pos->pList[wP][pceNum];
      assert(onBoard(sq));

//      1 step pawn move
      if(pos->pieces[sq + PMov[WHITE][0]] == EMPTY) {
        AddPawnMove(pos, sq, sq + PMov[WHITE][0], WHITE, list);
//        2 step pawn move
        if(RanksBrd[sq] == RANK_2 && pos->pieces[sq + PMov[WHITE][1]] == EMPTY)
          AddQuietMove(MOVE(sq, sq + PMov[WHITE][1], EMPTY, EMPTY, PSFLAG), list);
      }

//      Check captures by pawns
      for(int idx = 0; idx < 2; ++idx) {
        if(!SQOFFBOARD(sq + PAttack[WHITE][idx]) && pieceCol[pos->pieces[sq + PAttack[WHITE][idx]]] == BLACK)
          AddPawnMove(pos, sq, sq + PAttack[WHITE][idx], pos->pieces[sq + PAttack[WHITE][idx]],WHITE, list);
        if(pos->enPas != NO_SQ && sq + PAttack[WHITE][idx] == pos->enPas)
          AddCaptureMove(MOVE(sq, pos->enPas, EMPTY, EMPTY, EPFLAG), list);
      }
    }

//    King side castle
    if(pos->castlePerm & WKCA) {
      if(pos->pieces[F1] == EMPTY && pos->pieces[G1] == EMPTY) {
        if(!isSqAttacked(E1, BLACK, pos) &&
            !isSqAttacked(F1, BLACK, pos) && !isSqAttacked(G1, BLACK, pos))
          AddQuietMove(MOVE(E1, G1, EMPTY, EMPTY, CSFLAG), list);
      }
    }

//    Queen side castle
    if(pos->castlePerm & WQCA) {
      if(pos->pieces[D1] == EMPTY && pos->pieces[C1] == EMPTY && pos->pieces[B1] == EMPTY)
        if(!isSqAttacked(E1, BLACK, pos) && !isSqAttacked(D1, BLACK, pos))
          AddQuietMove(MOVE(E1, C1, EMPTY, EMPTY, CSFLAG), list);
    }

  } else {

//    Loop through all the pawns on the board
    for(int pceNum = 0; pceNum < pos->pceNum[bP]; ++pceNum) {
      int sq = pos->pList[bP][pceNum];
      assert(onBoard(sq));

//      1 step pawn move
      if(pos->pieces[sq + PMov[BLACK][0]] == EMPTY) {
        AddPawnMove(pos, sq, sq + PMov[BLACK][0], BLACK, list);
//        2 step pawn move
        if(RanksBrd[sq] == RANK_7 && pos->pieces[sq + PMov[BLACK][1]] == EMPTY)
          AddQuietMove(MOVE(sq, sq + PMov[BLACK][1], EMPTY, EMPTY, PSFLAG), list);
      }

//      Check captures by pawns
      for(int idx = 0; idx < 2; ++idx) {
        if(!SQOFFBOARD(sq + PAttack[BLACK][idx]) && pieceCol[pos->pieces[sq + PAttack[BLACK][idx]]] == WHITE)
          AddPawnMove(pos, sq, sq + PAttack[BLACK][idx],
                      pos->pieces[sq + PAttack[BLACK][idx]], BLACK, list);
        if(pos->enPas != NO_SQ && sq + PAttack[BLACK][idx] == pos->enPas)
          AddCaptureMove(MOVE(sq, pos->enPas, EMPTY, EMPTY, EPFLAG), list);
      }
    }

//    King side castle
    if(pos->castlePerm & BKCA) {
      if(pos->pieces[F8] == EMPTY && pos->pieces[G8] == EMPTY) {
        if(!isSqAttacked(E8, WHITE, pos) && !isSqAttacked(F8, WHITE, pos))
          AddQuietMove(MOVE(E8, G8, EMPTY, EMPTY, CSFLAG), list);
      }
    }

//    Queen side castle
    if(pos->castlePerm & BQCA) {
      if(pos->pieces[D8] == EMPTY && pos->pieces[C8] == EMPTY && pos->pieces[B8] == EMPTY)
        if(!isSqAttacked(E8, WHITE, pos) && !isSqAttacked(D8, WHITE, pos))
          AddQuietMove(MOVE(E8, C8, EMPTY, EMPTY, CSFLAG), list);
    }
  }

//  Loop through non sliders aka knight and king
  for(int idx = 0; idx < 2; ++idx) {
    int pce = NonSlidePce[side][idx];
    for(int pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum) {
      int sq = pos->pList[pce][pceNum];
      assert(onBoard(sq));
      for(int inc = 0; inc < 8; ++inc) {
        int to = sq + Mov[pce][inc];
        if(SQOFFBOARD(to))
         continue;
        if(pos->pieces[to] == EMPTY)
          AddQuietMove(MOVE(sq, to, EMPTY, EMPTY, EMPTY), list);
        else if(pieceCol[pos->pieces[to]] == side ^ 1)
          AddCaptureMove(MOVE(sq, to, pos->pieces[to], EMPTY, EMPTY), list);
      }
    }
  }

//  Loop through sliders aka queen, rook, bishop
  for(int idx = 0; idx < 3; ++idx) {
    int pce = SlidePieces[side][idx];
    for(int pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum) {
      int sq = pos->pList[pce][pceNum];
      assert(onBoard(sq));
      int limit = 4;
      if(isQ(pce))
        limit = 8;
      for(int inc = 0; inc < limit; ++inc) {
        int dir = Mov[pce][inc];
        int to = sq + dir;
        while(!SQOFFBOARD(to)) {
          if(pos->pieces[to] != EMPTY) {
            if(pieceCol[pos->pieces[to]] == side ^ 1)
              AddCaptureMove(MOVE(sq, to, pos->pieces[to], EMPTY, EMPTY), list);
            break;
          } else
            AddQuietMove(MOVE(sq, to, EMPTY, EMPTY, EMPTY), list);
          to += dir;
        }
      }
    }
  }
}