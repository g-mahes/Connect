// Player.cpp

#include "provided.h"
#include "support.h"
#include <string>
#include <iostream>
using namespace std;

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
    int determineAIMove(AlarmClock& ac, Scaffold& s, int& sc, int color, int N, int d);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() == 0)
        return 0; // no move can be made;
    int cl = -1;
    cout << "Choose a column: ";
    cin >> cl; // get column input
    while (cl > s.cols() || cl < 0 || s.checkerAt(cl,s.levels()) != VACANT) // loop if invalid column inputted
    {
        cout << "Choose a valid column: ";
        cin >> cl; // input valid column
    }
    for (int i = 1; i < s.levels()+1; i++) {
        if (s.checkerAt(cl, i) == VACANT)
            return cl; // return column if there is valid position in column
    }
    return 0; // no spot in column
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() == 0)
        return 0; // no move can be made;

    for (int j = 1; j < s.cols()+1; j++) {
        for (int i = 1; i < s.cols() + 1; i++) {
            if (s.checkerAt(i,j) == VACANT) // check if there spot VACANT at specified level,column
                return i; // return column if there is a spot available (will choose left-most column)
        }
    }
    return 0; // no move possible
}

int SmartPlayerImpl::determineAIMove(AlarmClock& ac, Scaffold& s, int& sc, int color, int N, int d) {
    int score;
    int move = 1;
    int othercolor;
    if (color == RED)
        othercolor = BLACK; // find other player's color
    else
        othercolor = RED; // find other player's color
    if (d % 2 == 1) {
        int max = -1000000000;
        for (int i = 1; i < s.cols() + 1; i++) {
            if (s.makeMove(i, color)) {
                if (ac.timedOut()) { // check if alarm has run out
                    s.undoMove(); // undomove if alarmclock has run out
                    move = i; // assign move to column number based on loop
                    return move; // return column number
                }
                // rating
                int rating = max; // initialize rate variable
                int state = rate(&s, color, N, d); // geting rating from move made on that column
                if (1 == state) { // win 
                    rating = 100000000 - d; // BIGNUMBER - depth is assigned to rating
                }
                else if (0 == state) { // tie game
                    rating = 0; // rating is 0
                }
                else {
                    if (ac.timedOut()) { // check if alarm has run out
                        s.undoMove(); // undomove if alarmclock has run out
                        move = i; // assign move to column number based on loop
                        return move; // return column number
                    }
                    else {
                        determineAIMove(ac, s, rating, othercolor, N, d + 1); // alarmclock has not run out yet - call the function again
                    }
                }
                if (rating > max) { 
                    max = rating; // reassign max rating if we found a greater rating
                    move = i; // reassign column number (better column to place item)
                }
                s.undoMove(); // undo move
            }
        }
        sc = max; // set score to max rating
    }
    else if (d % 2 == 0) {
        int min = 1000000000;
        for (int i = 1; i < s.cols() + 1; i++) {
            if (s.makeMove(i, color)) {
                if (ac.timedOut()) { // check if alarm has run out
                    s.undoMove(); // undomove if alarmclock has run out
                    move = i; // assign move to column number based on loop
                    return move; // return column number
                }
                // rating
                int rating = min;
                int state = rate(&s, color, N, d); // find rating value for this column
                if (1 == state) { // win 
                    rating = -100000000 + d;  // low number if move resulted in win
                }
                else if (0 == state) { // tie game
                    rating = 0; // 0 if move resulted in tie
                }
                else {
                    if (ac.timedOut()) { // check if alarm has run out
                        s.undoMove();
                        move = i; // reassign move if alarm run out
                        return move; // return column number
                    }
                    else {
                        determineAIMove(ac, s, rating, othercolor, N, d + 1); // recursive call again if alarm has not run out
                    }                   
                }
                if (rating < min) {
                    min = rating; // reassign minimum value from column if rating is lower than current min
                    move = i; // reassign column number (better move)
                }
                s.undoMove(); // undo move 
            }
        }
        sc = min; // assign parameter score to minimum value
    }

    return move; // return move (column number)
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
   
    if (s.numberEmpty() == 0)
        return 0; // no move can be made;
    Scaffold g(s); // temporary scaffold
    int r; // column that we will return
    int d = 1; // depth (number of recusion calls) is currently 0
    AlarmClock ac(8500);
    int t = determineAIMove(ac,g, r, color, N, d); // stores column into r
    return t;
}


//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code. 

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
