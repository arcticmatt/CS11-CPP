#include "maze.hh"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

Maze genMaze(int numRows, int numCols);
void addDirectionOptions(const Maze &maze, const Location &current,
                         vector<Direction> &options);
void addDirectionOption(const Maze &maze, const Location &current,
                        Direction dir, vector<Direction> &v);


/*
 * From a current location, adds all neighboring directions which have
 * not yet been visited to a vector.
 */
void addDirectionOptions(const Maze &maze, const Location &current,
                         vector<Direction> &options) {
    if (current.row > 0) { // We can move up a row
        addDirectionOption(maze, current, Direction::NORTH, options);
    }

    if (current.row < maze.getNumRows() - 1) { // We can move down a row
        addDirectionOption(maze, current, Direction::SOUTH, options);
    }

    if (current.col > 0) { // We can move left a column
        addDirectionOption(maze, current, Direction::WEST, options);
    }

    if (current.col < maze.getNumCols() - 1) { // We can move right a column
        addDirectionOption(maze, current, Direction::EAST, options);
    }
 }


/*
 * Checks the neighbor in direction >dir< of current and, if it has
 * not been visited, add the direction to the vector of direction options.
 */
void addDirectionOption(const Maze &maze, const Location &current,
                        Direction dir, vector<Direction> &v) {
    Location loc = maze.getNeighborCell(current.row, current.col, dir);
    MazeCell neighbor = maze.getCell(loc.row, loc.col);
    assert(neighbor != MazeCell::WALL);
    if (neighbor != MazeCell::VISITED) {
        v.push_back(dir);
    }
}

/*
 * Generates a maze of size numRows x numCols.
 */
Maze genMaze(int numRows, int numCols) {
    Maze maze(numRows, numCols);
    vector<Location> path;

    // Set initial state of maze (fill walls, start top left, end bottom right)
    maze.setAllWalls();

    // Set maze start to VISITED and push it onto the path
    Location start = maze.getStart();
    maze.setCell(start.row, start.col, MazeCell::VISITED);
    path.push_back(start);

    // DFS algorithm to generate path through maze
    while (!path.empty()) {
        Location current = path.back();

        if (current == maze.getEnd()) {
            path.pop_back();
            continue;
        }

        // Vector of possible directions that can be taken from the current loc
        vector<Direction> options;
        addDirectionOptions(maze, current, options);

        if (options.empty()) {
            // All neighbors have been visited => backtrack.
            path.pop_back();
            continue;
        }

        // Choose a random direction. Then, clear the wall in that direction
        // and move into the next cell.
        int randIndex = rand() % options.size();
        Direction randDirection = options[randIndex];
        maze.clearWall(current.row, current.col, randDirection);
        Location nextLocation = maze.getNeighborCell(current.row, current.col,
                                                     randDirection);
        maze.setCell(nextLocation.row, nextLocation.col, MazeCell::VISITED);
        path.push_back(nextLocation);
    }

    return maze;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "usage: ./numRows numCols" << endl;
        exit(1);
    }

    int numRows = atoi(argv[1]);
    int numCols = atoi(argv[2]);

    if (numRows <= 0) {
        cout << "input error: numRows = " << numRows << " is <= 0" << endl;
        exit(1);
    }

    if (numCols <= 0) {
        cout << "input error: numCols = " << numCols << " is <= 0" << endl;
        exit(1);
    }

    Maze m = genMaze(numRows, numCols);
    m.print(std::cout);
}
