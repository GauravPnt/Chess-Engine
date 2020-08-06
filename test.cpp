#include"test.hpp"

static U64 leafnodes;

static void test_util(int depth, std::shared_ptr<BOARD> pos) {

#ifdef DEBUG
  assert(CheckBoard(pos));
#endif

//  Get a count of all the leaf nodes
  if(depth == 0) {
    ++leafnodes;
    return;
  }

  std::shared_ptr<MOVE_LIST> list(new MOVE_LIST);
//  Generate move list
  GenerateAllMoves(pos, list);

  int moveNum = 0;
//  Loop through all the moves in the move list
  for(moveNum = 0; moveNum < list->count; ++moveNum) {
//    If move results in a check than continue, else make the move
    if(!makeMove(pos, list->moves[moveNum].move))
      continue;
    test_util(depth - 1, pos);
//    Take back the move
    takeMove(pos);
//    std::cout << "Take move" << std::endl;
  }
}

void test(int depth, std::shared_ptr<BOARD> pos) {

  unsigned U64 start = GetTime();
  assert(("Error before test", CheckBoard(pos)));

//  printBoard(pos);
  std::cout << "Starting test to depth: " << depth <<'\n';
  leafnodes = 0;

  std::shared_ptr<MOVE_LIST> list(new MOVE_LIST);
//  Generate move list
  GenerateAllMoves(pos, list);

  int move = 0;
  int moveNum = 0;
//  Iterate through the moves in move list
  for(moveNum = 0; moveNum < list->count; ++moveNum) {
    move = list->moves[moveNum].move;
//    If move results in a check than continue, else make the move
    if(!makeMove(pos, move))
      continue;
    long cumnodes = leafnodes;
    test_util(depth - 1, pos);
//    Take back the move
    takeMove(pos);
    long oldnodes = leafnodes - cumnodes;
    std::cout << "Move " << std::setw(3) << moveNum + 1 << " : " << PrMove(move) << " : " << oldnodes << '\n';
  }
  unsigned U64 end = GetTime();
  std::cout << "\nTest complete : " << "nodes visited : " << leafnodes << std::endl;
  std::cout << "Time taken : " << end - start << "ms" << std::endl;
}