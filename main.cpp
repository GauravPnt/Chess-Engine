#include"chess.h"

const std::string FEN1 = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
const std::string FEN2 = "5k2/1n6/4n3/6N1/8/3N4/8/5K2 b - - 0 1";
const std::string FEN3 = "rnbqkbnr/p1p1p3/3p3p/1p1p4/2P1Pp2/8/PP1P1PpP/RNBQKB1R b KQkq e3 0 1";
const std::string FEN4 = "6k1/8/5r2/8/1nQ5/5N2/8/6K1 w KQkq - 0 1";
const std::string CAST = "4k3/8/8/8/6r1/8/8/R3K2R w KQkq - 0 1";

int main(int argc, char const *argv[]) {
  initHash();
  initBoard();
  
  BOARD *board = new BOARD;
  MOVE_LIST *list = new MOVE_LIST;

  Parse_Fen(board, START_FEN);
  GenerateAllMoves(board, list);

  printBoard(board);
  getchar();
  
  for(int moveNum = 0; moveNum < list->count; ++moveNum) {
    int move = list->moves[moveNum].move;

    if(!makeMove(board, move))
      continue;
    
    std::cout << PrMove(move) << '\n';
    printBoard(board);

    takeMove(board);
    std::cout << PrMove(move) << '\n';
    printBoard(board);

    getchar();
  }
}
