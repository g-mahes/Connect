#include "support.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Scaffold;

bool diagonalRight(Scaffold* s, int level, int column, int N, int color) {
	for (int i = 1; i < level +1; i++) {
		for (int j = 1; j < column +1; j++) {
			int t = s->checkerAt(j, i); // find color at specified level and column
			if (color == t) { // if paramter color is equal to color found at level and column
				int g;
				for (g = 1; g < N; g++) {
					if (t != s->checkerAt(j + g, i + g)) // check diagonal right case (down to the right)
						break; // break once we have found a checker that does not match the parameter color
				}
				if (N == g)
					return true; // return true if count matches same number as number of checkers needed to win
			}		
		}
	}
	return false; // game not won
}

bool diagonalLeft(Scaffold* s, int level, int column, int N, int color) {
	for (int i = 1; i < level + 1; i++) {
		for (int j = 1; j < column +1; j++) {
			int t = s->checkerAt(j, i);// find color at specified level and column
			if (t == color) {// if paramter color is equal to color found at level and column
				int g;
				for (g = 1; g < N; g++) {
					if (t != s->checkerAt(j + g, i - g))// check diagonal left case (up to the right)
						break;// break once we have found a checker that does not match the parameter color
				}
				if (N == g)
					return true; // return true if count matches same number as number of checkers needed to win
			}
		}
	}
	return false; // game not won
}

bool vertical(Scaffold* s, int level, int column, int N, int color) {
	// check vertical positions for  checker
	for (int i = 1; i < column + 1; i++) {
		for (int j = 1; j < level +1; j++) {
			int t = s->checkerAt(i,j);// find color at specified level and column
			if (t == color) {// if paramter color is equal to color found at level and column
				int g;
				for (g = 1; g < N; g++) {
					if (t != s->checkerAt(i, j - g)) // check vertical case (checks going up)
						break;// break once we have found a checker that does not match the parameter color
				}
				if (N == g) {
					return true; // return true if count matches same number as number of checkers needed to win
				}
			}
		}
	}
	return false; // game not won
}

bool horizontal(Scaffold* s, int level, int column, int N, int color) {
	// check horizontal positions for  checker
	for (int i = 1; i < column + 1; i++) {
		for (int j = 1; j < level+1; j++) {
			int t = s->checkerAt(i, j);// find color at specified level and column
			if (t == color) {// if paramter color is equal to color found at level and column
				int g;
				for (g = 1; g < N; g++) {
					if (t != s->checkerAt(i+g, j)) // check horizontal case (checks going to the right)
						break;// break once we have found a checker that does not match the parameter color
				}
				if (N == g) {
					return true; // return true if count matches same number as number of checkers needed to win
				}
			}
		}
	}
	return false; // game not won
}



int rate(Scaffold* s, int color, int N, int d)
{
	if (s->numberEmpty() == 0)
		return 0; // no move can be made (tie game)
	
	
	// check if move has resulted in win for color
	if (horizontal(s, s->levels(), s->cols(), N, color) || vertical(s, s->levels(), s->cols(), N, color) || diagonalRight(s, s->levels(), s->cols(), N, color) || diagonalLeft(s, s->levels(), s->cols(), N, color)) {
		return 1; // direct win 
	}

	return -1; // loss

}
