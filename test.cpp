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
  printBoard(pos);

  int moveNum = 0;
  for(moveNum = 0; moveNum < list.count; ++moveNum) {
    // std::cout << "depth : " << depth << ' ' << leafnodes <<'\n' << PrMove(list.moves[moveNum].move) << '\n';
    if(!makeMove(pos, list.moves[moveNum].move))
      continue;
    test_util(depth - 1, pos);
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
    // std::cout << PrMove(move) << '\n';
    if(!makeMove(pos, move))
      continue;
    long cumnodes = leafnodes;
    test_util(depth - 1, pos);
    takeMove(pos);
    long oldnodes = leafnodes - cumnodes;
    std::cout << "Move " << std::setw(3) << moveNum + 1 << " : " << PrMove(move) << " : " << oldnodes << '\n';
  }
  std::cout << "\nTest complete : " << "nodes visited : " << leafnodes << '\n';
}