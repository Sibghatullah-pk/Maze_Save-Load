#include "Player.h"
#include <iostream>
#include <chrono>
using namespace std;

Player::Player(Maze &m) : maze(m), grid(m.getGrid()), x(1), y(1), moves(0) {}

void Player::play()
{
    char input;
    while (true)
    {
        maze.display();
        cout << "Use WASD to move or press 'q' to quit: ";
        cin >> input;

        if (input == 'q')
        {
            cout << "Game Over. You chose to quit.\n";
            break;
        }

        int nx = x, ny = y;
        if (input == 'w')
            nx--;
        else if (input == 's')
            nx++;
        else if (input == 'a')
            ny--;
        else if (input == 'd')
            ny++;

        if (grid[nx][ny] == PATH || grid[nx][ny] == END)
        {
            grid[x][y] = PATH;
            x = nx, y = ny;
            grid[x][y] = START;

            if (grid[x][y] == END)
            {
                cout << "You reached the end! Congratulations!\n";
                break;
            }
        }
        moves++;
    }
    cout << "Total moves: " << moves << endl;
}

void Player::playWithTimer(int timeLimit)
{
    auto start = chrono::steady_clock::now();
    char input;

    while (true)
    {
        maze.display();
        cout << "Use WASD to move or press 'q' to quit: ";
        cin >> input;

        if (input == 'q')
        {
            cout << "Game Over. You chose to quit.\n";
            break;
        }

        int nx = x, ny = y;
        if (input == 'w')
            nx--;
        else if (input == 's')
            nx++;
        else if (input == 'a')
            ny--;
        else if (input == 'd')
            ny++;

        if (grid[nx][ny] == PATH || grid[nx][ny] == END)
        {
            grid[x][y] = PATH;
            x = nx, y = ny;
            grid[x][y] = START;

            if (grid[x][y] == END)
            {
                cout << "You reached the end! Congratulations!\n";
                break;
            }
        }

        auto current = chrono::steady_clock::now();
        int elapsed = chrono::duration_cast<chrono::seconds>(current - start).count();
        if (elapsed > timeLimit)
        {
            cout << "Time's up! You lost.\n";
            break;
        }
        moves++;
    }
}
