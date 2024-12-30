// main.cpp
#include <iostream>
#include <fstream>
#include "Maze.h"
#include "Player.h"

using namespace std;

// Function prototypes
void saveGame(const Maze &maze, const string &username);
void loadGame(Maze &maze, const string &username);
void multiplayerMode();
string login();

int main()
{
    int rows = 21, cols = 21;
    Maze maze(rows, cols);

    cout << "Welcome to the Maze Game!\n";
    string username = login();

    cout << "Choose an option:\n1. Start New Game\n2. Load Game\n3. Design Maze yourself\n";
    int menuChoice;
    cin >> menuChoice;

    if (menuChoice == 2)
    {
        loadGame(maze, username);
    }
    else if (menuChoice == 3)
    {
        maze.designMaze();
    }
    else
    {
        maze.generateMaze();
    }

    cout << "Generated Maze:\n";
    maze.display();

    cout << "Choose mode:\n1. Manual (play with WASD keys)\n2. Automatic (system solves the maze)\n3. Multiplayer\n";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        cout << "Choose time limit in seconds (0 for no limit): ";
        int timeLimit;
        cin >> timeLimit;
        Player player(maze);
        if (timeLimit > 0)
            player.playWithTimer(timeLimit);
        else
            player.play();
        saveGame(maze, username);
        cout << "Your score: " << 1000 / player.getMoves() << endl; // Example scoring formula
    }
    else if (choice == 2)
    {
        if (maze.solveDFS(1, 1))
        {
            cout << "Maze solved automatically:\n";
            maze.display();
        }
        else
        {
            cout << "No solution found!\n";
        }
    }
    else if (choice == 3)
    {
        multiplayerMode();
    }
    else
    {
        cout << "Invalid choice. Exiting...\n";
    }

    return 0;
}

string login()
{
    cout << "Enter your username: ";
    string username;
    cin >> username;
    cout << "Welcome, " << username << "!\n";
    return username;
}

void saveGame(const Maze &maze, const string &username)
{
    ofstream outFile(username + "_game.txt");

    if (!outFile)
    {
        cout << "Failed to open file for saving.\n";
        return;
    }

    for (const auto &row : maze.getGrid())
    {
        for (char cell : row)
        {
            outFile << cell;
        }
        outFile << endl;
    }

    cout << "Game saved successfully.\n";
}

void loadGame(Maze &maze, const string &username)
{
    ifstream inFile(username + "_game.txt");

    if (!inFile)
    {
        cout << "No saved game found for username: " << username << "\n";
        return;
    }

    vector<vector<char>> loadedGrid;
    string line;
    while (getline(inFile, line))
    {
        vector<char> row(line.begin(), line.end());
        loadedGrid.push_back(row);
    }

    maze.setGrid(loadedGrid);
    cout << "Game loaded successfully.\n";
}

void multiplayerMode()
{
    Maze maze1(21, 21), maze2(21, 21);
    maze1.generateMaze();
    maze2.generateMaze();

    Player player1(maze1), player2(maze2);
    cout << "Player 1's turn:\n";
    player1.play();

    cout << "Player 2's turn:\n";
    player2.play();

    cout << "Game Over. Compare times or moves to decide the winner!\n";
}