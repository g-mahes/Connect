#ifndef SUPPORT_INCLUDED
#define SUPPORT_INCLUDED
#include "provided.h"
#include <string>
#include <vector>
#include <stack>


bool diagonalRight(Scaffold* s, int level, int column, int N, int color);

bool diagonalLeft(Scaffold* s, int level, int column, int N, int color);

bool vertical(Scaffold* s, int level, int column, int N, int color);

bool horizontal(Scaffold* s, int level, int column, int N, int color);

int rate(Scaffold* s, int color, int N, int d);
#endif