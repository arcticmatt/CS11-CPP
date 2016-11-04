#include "maze.hh"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
using namespace std;

Maze::Maze(int rows, int cols) {
    this->numRows = rows;
    this->numCols = cols;
    this->setStart(0, 0);
    this->setEnd(rows - 1, cols - 1);
    this->cells = new MazeCell[this->cell2Expanded(rows) * this->cell2Expanded(cols)];
    this->clear();
}


Maze::Maze(const Maze &m) {
    this->numRows = m.numRows;
    this->numCols = m.numCols;
    this->start = m.getStart();
    this->end = m.getEnd();

    // Initialize and copy over MazeCell array
    size_t s = this->cell2Expanded(this->numRows) * this->cell2Expanded(this->numCols);
    this->cells = new MazeCell[s];
    copy(m.cells, m.getCellsEnd(), this->cells);
}


Maze::~Maze() {
    delete[] this->cells;
}


Maze& Maze::operator=(const Maze &m) {
    if (this != &m) {
        this->numRows = m.numRows;
        this->numCols = m.numCols;
        this->start = m.getStart();
        this->end = m.getEnd();

        // Free existing memory, then copy values
        delete[] this->cells;
        size_t s = this->cell2Expanded(this->numRows) * this->cell2Expanded(this->numCols);
        this->cells = new MazeCell[s];
        copy(m.cells, m.getCellsEnd(), this->cells);
    }

    return *this;
}


// == My Helper Functions ==
MazeCell *Maze::getCellsEnd() const {
    size_t s = this->cell2Expanded(this->numRows) * this->cell2Expanded(this->numCols);
    return this->cells + s;
}


int Maze::cell2Expanded(int n) const{
    return 2 * n + 1;
}


Location Maze::adjustLoc(int row, int col, Direction direction) const {
    int nRow = row;
    int nCol = col;
    switch (direction) {
        case Direction::NORTH:
            nRow--;
            break;
        case Direction::SOUTH:
            nRow++;
            break;
        case Direction::EAST:
            nCol++;
            break;
        case Direction::WEST:
            nCol--;
            break;
        default:
            assert(false);
    }

    Location l(nRow, nCol);
    return l;
}


void Maze::setWithDirection(int cellRow, int cellCol, Direction direction,
                            MazeCell val) {
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    int expRow = this->cell2Expanded(cellRow);
    int expCol = this->cell2Expanded(cellCol);
    int expCols = this->cell2Expanded(this->numCols);
    Location n = this->adjustLoc(expRow, expCol, direction);
    this->cells[n.row * expCols + n.col] = val;
}
// ====


int Maze::getNumRows() const {
    return this->numRows;
}


int Maze::getNumCols() const {
    return this->numCols;
}


Location Maze::getStart() const {
    return this->start;
}


void Maze::setStart(int row, int col) {
    assert(row >= 0 && row < this->numRows);
    assert(col >= 0 && col < this->numCols);
    Location s(row, col);
    this->start = s;
}


Location Maze::getEnd() const {
    return this->end;
}


void Maze::setEnd(int row, int col) {
    assert(row >= 0 && row < this->numRows);
    assert(col >= 0 && col < this->numCols);
    Location e(row, col);
    this->end = e;
}


void Maze::clear() {
    fill(this->cells, this->getCellsEnd(), MazeCell::EMPTY);
}


void Maze::setAllWalls() {
    for (int i = 0; i < this->numRows; ++i) {
        for (int j = 0; j < this->numCols; ++j) {
            this->setWall(i, j, Direction::WEST);
            this->setWall(i, j, Direction::NORTH);
            if (j == this->numCols - 1) {
                this->setWall(i, j, Direction::EAST);
            }
            if (i == this->numRows - 1) {
                this->setWall(i, j, Direction::SOUTH);
            }
        }
    }
}


MazeCell Maze::getCell(int cellRow, int cellCol) const {
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    int expRow = this->cell2Expanded(cellRow);
    int expCol = this->cell2Expanded(cellCol);
    int expCols = this->cell2Expanded(this->numCols);
    return this->cells[expRow * expCols + expCol];
}


MazeCell Maze::getCellExp(int expRow, int expCol) const {
    assert(expRow >= 0 && expRow < this->cell2Expanded(this->numRows));
    assert(expCol >= 0 && expCol < this->cell2Expanded(this->numCols));
    int expCols = this->cell2Expanded(this->numCols);
    return this->cells[expRow * expCols + expCol];
}


void Maze::setCell(int cellRow, int cellCol, MazeCell val) {
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    int expRow = this->cell2Expanded(cellRow);
    int expCol = this->cell2Expanded(cellCol);
    int expCols = this->cell2Expanded(this->numCols);
    this->cells[expRow * expCols + expCol] = val;
}


Location Maze::getNeighborCell(int cellRow, int cellCol, Direction direction) const {
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    Location n = this->adjustLoc(cellRow, cellCol, direction);
    assert(n.row >= 0 && n.row < this->cell2Expanded(this->numRows));
    assert(n.col >= 0 && n.col < this->cell2Expanded(this->numCols));

    return n;
}


bool Maze::hasWall(int cellRow, int cellCol, Direction direction) const {
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    int expRow = this->cell2Expanded(cellRow);
    int expCol = this->cell2Expanded(cellCol);
    Location n = this->adjustLoc(expRow, expCol, direction);
    return this->getCellExp(n.row, n.col) == MazeCell::WALL;
}


void Maze::setWall(int cellRow, int cellCol, Direction direction) {
    this->setWithDirection(cellRow, cellCol, direction, MazeCell::WALL);
}


void Maze::clearWall(int cellRow, int cellCol, Direction direction) {
    this->setWithDirection(cellRow, cellCol, direction, MazeCell::EMPTY);
}


bool Maze::isVisited(int cellRow, int cellCol) const {
    assert(cellRow >= 0 && cellRow < this->numRows);
    assert(cellCol >= 0 && cellCol < this->numCols);
    int expRow = this->cell2Expanded(cellRow);
    int expCol = this->cell2Expanded(cellCol);
    return this->getCellExp(expRow, expCol) == MazeCell::VISITED;
}


void Maze::print(ostream &os) const {
    os << this->numRows << " " << this->numCols << endl;
    for (int i = 0; i < this->numRows; ++i) {
        // Output the walls above this row
        for (int j = 0; j < this->numCols; ++j) {
            os << "+";
            if (this->hasWall(i, j, Direction::NORTH)) {
                os << "---";
            } else {
                os << "   ";
            }
        }
        os << "+" << endl;

        // Output the cells/walls in this row
        for (int j = 0; j < this->numCols; ++j) {
            bool wall = false;
            if (this->hasWall(i, j, Direction::WEST)) {
                os << "|";
                wall = true;
            }

            if (!wall) {
                os << " ";
            }

            // Check for start and end
            if (this->start.row == i && this->start.col == j) {
                cout << " S ";
            } else if (this->end.row == i && this->end.col == j) {
                cout << " E ";
            } else {
                cout << "   ";
            }
        }
        if (this->hasWall(i, this->numCols - 1, Direction::EAST)) {
            os << "|" << endl;
        } else {
            os << endl;
        }
    }

    // Output walls below the last row
    for (int j = 0; j < this->numCols; ++j) {
        os << "+";
        if (this->hasWall(this->numRows - 1, j, Direction::SOUTH)) {
            os << "---";
        } else {
            os << "   ";
        }
    }
    os << "+" << endl;
}
