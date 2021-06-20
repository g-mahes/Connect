// Game.cpp

#include "provided.h"
#include "support.h"
#include <iostream>
using namespace std;
class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black); 
    bool completed(int& winner) const; 
    bool takeTurn(); 
    void play(); 
    int checkerAt(int c, int r) const;
    ~GameImpl();
private:
    int nWin;
    int l;
    int c;
    Player* r;
    Player* b;
    Scaffold* s;
    int m_winner;
    int nTurn;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
    : l(nLevels),c(nColumns),r(red),b(black),nWin(N),nTurn(1) // initialize private variables
{
    s = new Scaffold(nColumns,nLevels); // construct new scaffold object and assign pointer
}

bool GameImpl::completed(int& winner) const
{
    if (1 == nTurn)
        return false; // no one has played a turn yet
    // check left diagonal for red checker
    if (diagonalLeft(s, l, c, nWin, RED)) {
        winner = RED; // assign winner
        return true;
    }

    // check left diagonal for black checker
    if (diagonalLeft(s, l, c, nWin, BLACK)) {
        winner = BLACK;// assign winner
        return true;
    }

    // check right diagonal for red checker
    if (diagonalRight(s, l, c, nWin, RED)) {
        winner = RED;// assign winner
        return true;
    }

    // check right diagonal for black checker
    if (diagonalRight(s, l, c, nWin, BLACK)) {
        winner = BLACK;// assign winner
        return true;
    }

    // check vertical positions for red checker
    if (vertical(s, l, c, nWin, RED)) {
        winner = RED;// assign winner
        return true;
    }

    // check vertical positions for black checker
    if (vertical(s, l, c, nWin, BLACK)) {
        winner = BLACK;
        return true;
    }

    // check horizontal positions for red checker
    if (horizontal(s, l, c, nWin, RED)) {
        winner = RED;// assign winner
        return true;
    }

    // check horizontal positions for black checker
    if (horizontal(s, l, c, nWin, BLACK)) {
        winner = BLACK;// assign winner
        return true;
    }

    // tie situation
    if (s->numberEmpty() == 0)
    {
        winner = TIE_GAME; // tie game is winner
        return true;
    }
    return false;  // game not completed
}

bool GameImpl::takeTurn()
{
    if (completed(m_winner))
        return false; // game is already over

    //first player turn (red)
    if (1 == nTurn % 2) {
        int c = r->chooseMove(*s, nWin, RED);
        s->makeMove(c, RED); // make move for red checker
    }

    // second player turn (black)
    if (0 == nTurn % 2) {
        int c = b->chooseMove(*s, nWin, BLACK);
        s->makeMove(c, BLACK); // make move to black checker
    }
    nTurn++; // increment number of turns
    return true; // turn has taken place
}

void GameImpl::play()
{
    s->display();
    
    if (r->isInteractive() || b->isInteractive()) // one player is interactive
    {
        while (!completed(m_winner)) { // keep looping until game is over
            takeTurn(); // take turn for each player
            s->display(); // display after each turn
            cout << endl; 
        }
    }
    if (!r->isInteractive() && !b->isInteractive()) { // two computer plays playing the game
        while (!completed(m_winner)) {
            cout << "Press enter for next turn." << endl;
            cin.ignore(10000, '\n'); // take input
            takeTurn(); // take turn for player
            s->display(); // display after each turn
            cout << endl;
        }
    }
    if (m_winner == BLACK) { // black checker won
        cout << b->name() << " won!" <<  endl; 
    }
    if (m_winner == RED) { // red checker won
        cout << r->name() << " won!" << endl;
    }
    if (m_winner == TIE_GAME) { // no winner
        cout << "Tie Game." << endl;
    }
}

int GameImpl::checkerAt(int c, int r) const
{
    return s->checkerAt(c, r); // return checkerAt function from scaffold
} 

GameImpl::~GameImpl() {
    delete s; // delete dynamically allocated scaffold object
}

//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code. 

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
