#include"defs.h"

int Sq120ToSq64[BRDSQ_120];
int Sq64ToSq120[64];

void initBoard() {

  std::fill(Sq120ToSq64, Sq120ToSq64 + BRDSQ_120, 65);
  std::fill(Sq64ToSq120, Sq64ToSq120 + 64, 120);

  int sq64 = 0;
  for(int rank = RANK_1; rank <= RANK_8; ++ rank) {
    for(int file = FILE_A; file <= FILE_H; ++file) {
      int sq = FR2SQ(file, rank);
      Sq120ToSq64[sq] = sq64;
      Sq64ToSq120[sq64++] = sq;
    }
  }

}