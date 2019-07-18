#include"chess.h"

const std::string FEN1 = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
const std::string FEN2 = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";
const std::string FEN3 = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2";

int main(int argc, char const *argv[]) {
  initHash();
  initBoard();
  BOARD board;

  Parse_Fen(&board, START_FEN);
  printBoard(&board);
  Parse_Fen(&board, FEN1);
  printBoard(&board);
  Parse_Fen(&board, FEN2);
  printBoard(&board);
  Parse_Fen(&board, FEN3);
  printBoard(&board);
}
