#include "search.hpp"

static bool IsRepetition(std::shared_ptr<const BOARD> pos) {
//  If fifty moves resets then there is no going back since pawns cant go back or capture undone
  for(int idx = pos->hisPly - pos->fifty_move; idx < pos->hisPly - 1; ++idx) {
    assert(idx >= 0 && idx <= MAX_MOVES);
    if(pos->key == pos->history[idx].key)
      return true;
  }
  return false;
}

static void ClearForSearch(std::shared_ptr<BOARD> pos, std::shared_ptr<SEARCH> info) {
  for(int sq = 0; sq < BRDSQ_120; ++sq) {
    for(auto & searchHistory : pos->searchHistory)
      searchHistory[sq] = 0;

    for(auto & searchKiller : pos->searchKillers)
      searchKiller[sq] = 0;
  }

  pos->PvTable = std::make_unique<PVTABLE>(PVTABLE(PvSize));
  pos->ply = 0;

  info->start_time = GetTime();
  info->stop = false;
  info->nodes = 0;
}
