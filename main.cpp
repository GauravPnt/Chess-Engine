#include"chess.h"

const std::string fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";

int main(int argc, char const *argv[]) {
  initHash();
  initBoard();

  BOARD *pos = new BOARD;
  MOVE_LIST *m = new MOVE_LIST;

  Parse_Fen(pos, fen);
  test(5, pos);
}
