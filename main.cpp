#include"chess.hpp"

const std::string fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";

int main(int argc, char const *argv[]) {

//  PVTABLE p;
  std::shared_ptr<BOARD> b(new BOARD);

  ParseFen(b, START_FEN);
  PrintBoard(b);

//  Test(3,b);

  while(true) {
    std::cout << "Enter a move > ";
    std::string input;
    std::cin >> input;
    if(input == "q")
      break;
    else if(input == "t") {
      TakeMove(b);
      PrintBoard(b);
    }
    else if(input == "p") {
      int count = GetPvLine(4, b);
      for(int idx = 0; idx < count; ++idx) {
        int move = b->PvArray[idx];
        std::cout << PrMove(move) << ' ';
      }
      std::cout << std::endl;
    } else {
      int move = ParseMove(b, input);
      if (move == NOMOVE) {
        std::cout << "Invalid move" << std::endl;
        continue;
      } else {
        StorePvMove(b, move);
        if(!MakeMove(b, move)) {
          std::cout << "Infeasible move" << std::endl;
          continue;
        }
      }
      StorePvMove(b, move);
      PrintBoard(b);
    }
  }
}
