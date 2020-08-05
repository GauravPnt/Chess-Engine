#include"chess.h"

const std::string fen = "n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - - 0 1";

int main(int argc, char const *argv[]) {
  initHash();
  initBoard();

  BOARD *pos = new BOARD;
  MOVE_LIST *m = new MOVE_LIST;

  Parse_Fen(pos, fen);
  test(4, pos);
}
