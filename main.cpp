#include "provided.h"
#include <iostream>
#include <cassert>
using namespace std;

void doGameTests()
{
	BadPlayer bp1("Bart");
	BadPlayer bp2("Homer");
	Game g(2, 2, 2, &bp1, &bp2);
	int winner;
	assert(!g.completed(winner));
	g.takeTurn();  // Red's first move
	assert(!g.completed(winner) &&
		(g.checkerAt(1, 1) == RED || g.checkerAt(2, 1) == RED));
	g.takeTurn();  // Black's first move
	assert(!g.completed(winner));
	g.takeTurn();  // Red's second move; Red must win
	assert(g.completed(winner) && winner == RED);
}

int main()
{
	int r;
	int c;
	int win;
	string t;
	cout << "Please type in how many rows you would like to play with." << endl;
	cin >> r;
	cout << "Please type in how many columns you would like to play with." << endl;
	cin >> c;
	cout << "Please type in how many checkers needed to win." << endl;
	cin >> win;
	cout << "Please type Y if you would like to play against AI, or type N if you would like to play against another human player." << endl;
	cin >> t;
	if (t == "Y")
	{
		HumanPlayer h("Human");
		SmartPlayer s("AI");
		Game g(c, r,win, &h, &s);
		g.play();
	}
	else {
		HumanPlayer h("Human 1");
		HumanPlayer s("Human 2");
		Game g(c, r, win, &h, &s);
		g.play();
	}

}