#ifndef TEST_H
#define TEST_H

#include"board.hpp"
#include"move.hpp"

static void test_util(int depth, std::shared_ptr<BOARD> pos);
extern void test(int depth, std::shared_ptr<BOARD> pos);

#endif