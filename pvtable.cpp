#include "board.hpp"
#include "move.hpp"

const int PvSize = 0x100000 * 2;

PVTABLE::PVTABLE(const int PvSize) {
  numEntries = PvSize / sizeof(PVENTRY);
  numEntries -= 2;
  PvTable = std::unique_ptr<PVENTRY[]>(new PVENTRY[numEntries * sizeof(PVENTRY)]);
  std::cout << "PV Table initialized with : " << numEntries << std::endl;
}

void StorePvMove(std::shared_ptr<BOARD> pos, const int move) {
  int idx = pos->key % pos->PvTable->numEntries;
  assert(idx >= 0 && idx < pos->PvTable->numEntries);
  pos->PvTable->PvTable[idx].move = move;
  pos->PvTable->PvTable[idx].key = pos->key;
}

int ProbePvTable(std::shared_ptr<const BOARD> pos) {
  int idx = pos->key % pos->PvTable->numEntries;
  assert(idx >= 0 && idx < pos->PvTable->numEntries);
  if(pos->PvTable->PvTable[idx].key == pos->key)
    return pos->PvTable->PvTable[idx].move;
  return NOMOVE;
}