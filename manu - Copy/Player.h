#ifndef PLAYER_H
#define PLAYER_H

#include "Maze.h"
using namespace std;

class Player
{
private:
    Maze &maze;
    vector<vector<char>> &grid;
    int x, y;
    int moves;

public:
    Player(Maze &m);
    void play();
    void playWithTimer(int timeLimit);
    int getMoves() const { return moves; }
};

#endif
