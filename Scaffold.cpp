// Scaffold.cpp
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "provided.h"
#include "support.h"
using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels); 
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const; 
    void display() const; 
    bool makeMove(int column, int color); 
    int undoMove(); 
 
private:
    int l;
    int c;
    vector<vector<string>> grid;
    stack<int> m_column;
    stack<int> m_color;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    if (nColumns <= 0 || nLevels <= 0) {
        cerr << "Not valid" << endl;
        exit(1); // invalid number of columns or levels
    }
    l = nLevels;
    c = nColumns;
    grid.resize(l+1); // adding levels
    for (int i = 0; i < l+1; i++) {
        grid[i].resize(2*c+1); // adding columns
    }
    for (int i = 0; i < 2 * c + 1; i++) { // construct bottom level with + and -
        if (i % 2 == 1)
            grid[l][i] = "-"; // insert - to every odd position
        if (i % 2 == 0) {
            grid[l][i] = "+"; // insert + to every even position
        }
    }
    for (int i = 0; i < l; i++) { // construct the other levels with "|" and spaces
        for (int j = 0; j < 2 * c + 1; j++) {
            if (j % 2 == 0)
                grid[i][j] = "|"; // insert | to every even position
            if (j % 2 == 1)
                grid[i][j] = " "; // insert space to every odd position
        }
    }
}

int ScaffoldImpl::cols() const
{
    return c; // return number of columns
}

int ScaffoldImpl::levels() const
{
    return l; // return number of levels
}

int ScaffoldImpl::numberEmpty() const
{
    int count = 0;
    for (int i = 0; i < l+1; i++) {
        for (int j = 0; j < 2*c+1; j++) {
            if (grid[i][j] == " ")
                count++; // count number of empty grid spots on scaffold
        }
    }
    return count; // return number of empty grid spots found
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    if (column > cols() || column < 1)
        return VACANT; // off the grid
    if (level > levels() || level < 1)
        return VACANT; // off the grid
    if (grid[levels()-level][2*column - 1] == "R")
        return RED; // red checker
    else if (grid[levels() - level][2*column-1] == "B")
        return BLACK; // black checker
    else {
        return VACANT; // vacant spot on the grid
    }
}

void ScaffoldImpl::display() const
{
    for (int i = 0; i < l+1; i++) {
        for (int j = 0; j < 2 * c + 1; j++) {
            cout << grid[i][j]; // cout every position on the grid
        }
        cout << endl; // new line after every level
    }
}

bool ScaffoldImpl::makeMove(int column, int color)
{

    if (column > 0 && column < cols()+1) {
        for (int i = 1; i < levels()+1; i++) { // loop to check if column has vacant spots
            if (checkerAt(column,i) == VACANT) {
                if (color == RED) {
                    grid[levels()-i][2 * column - 1] = "R"; // spot gets R
                    m_column.push(column); // stack to keep track of moves for undo
                    m_color.push(RED); // stack to keep track of moves for undo
                }
                else if (color == BLACK) {
                    grid[levels()-i][2 * column - 1] = "B"; // spot gets B
                    m_column.push(column); // stack to keep track of moves for undo
                    m_color.push(BLACK); // stack to keep track of moves for undo
                }
                return true; // move has been made
            }
        }
    }
    return false; // invalid column
}

int ScaffoldImpl::undoMove()
{
    if (m_color.empty() || m_column.empty())
        return 0; // no undo;
    int tempColumn = m_column.top(); // keep track of last column move made was on
    int color = m_color.top(); // keep track of last color that made a move
    string t;
    if (color == RED)
        t = "R"; // RED made last move
    else
        t = "B"; // BLACK made last move
    for (int i = l-1; i >= 0; i--) {
        if (i > 0) { // column is not full case
            if (grid[i][2*tempColumn-1] == t) // we found the right color
                if (grid[i - 1][2 * tempColumn - 1] == " ") { // next spot is vacant
                    grid[i][2 * tempColumn - 1] = " "; // undo the move and make the spot " "
                    if (!m_column.empty())
                        m_column.pop(); // pop the stack
                    if (!m_color.empty())
                        m_color.pop(); // pop the stack
                    return tempColumn; // return column where undo took place
                }        
        }
        else if (i == 0) { // column is full
            if (grid[i][2 * tempColumn - 1] == t) { // we found the right color
                grid[i][2 * tempColumn - 1] = " "; // undo move and make spot " "
                if(!m_column.empty())
                    m_column.pop();  // pop the stack
                if(!m_color.empty())
                    m_color.pop();  // pop the stack
                return tempColumn; // return column where undo took place
            }
        }
    }
    return 0; // nothing to undo
}

//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.
//  You probably don't want to change any of this code. 

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
