#include <iostream>
#include <fstream>
#include "Maze.h"
#include "Player.h"

using namespace std;

// Function prototypes
void saveGame(const Maze &maze, const string &username);
void loadGame(Maze &maze, const string &username);
string login();

int main()
{
    int rows = 21, cols = 21;
    Maze maze(rows, cols);

    cout << "Welcome to the Maze Game!\n";
    string username = login();

    cout << "Choose an option:\n1. Start New Game\n2. Load Game\n";
    int menuChoice;
    cin >> menuChoice;

    if (menuChoice == 2)
    {
        loadGame(maze, username);
    }
    else
    {
        maze.generateMaze();
    }

    cout << "Generated Maze:\n";
    maze.display();

    cout << "Choose mode:\n1. Manual (play with WASD keys)\n2. Automatic (system solves the maze)\n";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        Player player(maze);
        player.play();
        saveGame(maze, username); // Save game after playing
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

    // Save the maze grid
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

    // Load the maze grid from the file
    vector<vector<char>> loadedGrid;
    string line;
    while (getline(inFile, line))
    {
        vector<char> row(line.begin(), line.end());
        loadedGrid.push_back(row);
    }

    maze.setGrid(loadedGrid); // Assuming you add a setGrid method in the Maze class
    cout << "Game loaded successfully.\n";
}
