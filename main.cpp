#include"chess.h"

const std::string fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";

int main(int argc, char const *argv[]) {
  initHash();
  initBoard();
  
  BOARD *board = new BOARD;
  MOVE_LIST *list = new MOVE_LIST;

  // Parse_Fen(board, fen);
  // GenerateAllMoves(board, list);

  // printBoard(board);
  // getchar();
  
  // for(int moveNum = 0; moveNum < list->count; ++moveNum) {
  //   int move = list->moves[moveNum].move;

  //   if(!makeMove(board, move))
  //     continue;
    
  //   std::cout << PrMove(move) << '\n';
  //   printBoard(board);

  //   takeMove(board);
  //   std::cout << PrMove(move) << '\n';
  //   printBoard(board);

  //   getchar();
  // }
  Parse_Fen(board, fen);
  GenerateAllMoves(board, list);

  test(3, board);

}
