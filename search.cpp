#include "search.hpp"

bool isRepetition(std::shared_ptr<const BOARD> pos) {
//  If fifty moves resets then there is no going back since pawns cant go back or capture undone
  for(int idx = pos->hisPly - pos->fifty_move; idx < pos->hisPly - 1; ++idx) {
    assert(idx >= 0 && idx <= MAX_MOVES);
    if(pos->key == pos->history[idx].key)
      return true;
  }
  return false;
}

