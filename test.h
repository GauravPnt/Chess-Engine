#ifndef TEST_H
#define TEST_H

#include"board.h"
#include"moves.h"

static U64 leafnodes;
extern void test_util(int depth, BOARD *pos);
extern void test(int depth, BOARD *pos);

#endif