#include"test.h"

static U64 leafnodes;

static void test_util(int depth, BOARD *pos) {

#ifdef DEBUG
  assert(CheckBoard(pos));
#endif

  if(depth == 0) {
    ++leafnodes;
    return;
  }

  MOVE_LIST list;
  GenerateAllMoves(pos, &list);

  int moveNum = 0;
  for(moveNum = 0; moveNum < list.count; ++moveNum) {
    if(!makeMove(pos, list.moves[moveNum].move))
      continue;
    test(depth + 1, pos);
    takeMove(pos);
  }
}

void test(int depth, BOARD *pos) {
  assert(CheckBoard(pos));

  printBoard(pos);
  std::cout << "Starting test to depth: " << depth <<'\n';
  leafnodes = 0;

  MOVE_LIST list;
  GenerateAllMoves(pos, &list);

  int move = 0;
  int moveNum = 0;
  for(moveNum = 0; moveNum < list.count; ++moveNum) {
    move = list.moves[moveNum].move;
    if(!makeMove(pos, move))
      continue;
    long cumnodes = leafnodes;
    test_util(depth - 1, pos);
    takeMove(pos);
    long oldnodes = leafnodes - cumnodes;
    std::cout << "Move" << moveNum + 1 << " : " << PrMove(move) << " : " << oldnodes;
  }
  std::cout << "\nTest complete : " << "nodes visited : " << leafnodes << '\n';
}