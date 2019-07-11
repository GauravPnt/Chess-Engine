#include"chess.h"

void printBoard() {
  
  for (int i = 0; i < BRDSQ_120; ++i) {
    if (i % 10 == 0) 
      std::cout << '\n';
    std::cout << std::setw(5) << Sq120ToSq64[i];
  }

  std::cout << '\n' << '\n';

  for(int i = 0; i < 64; ++i){
    if(i % 8 == 0)
      std::cout << '\n';
    std::cout << std::setw(5) << Sq64ToSq120[i];
  }

  std::cout << '\n' << '\n';
  
}