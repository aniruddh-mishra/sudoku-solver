#include <iostream>
#include <math.h>
#include "sudoku.h"

Sudoku::Sudoku() {
  this->numRows = 9;
  this->numCols = 9;
  this->boxSideLen = 3;
  this->isSolved = false;
  this->board = new int*[numRows];

  for (int i = 0; i < this->numRows; i++) {
    this->board[i] = new int[numCols];
  }

  for (int i = 0; i < this->numRows; i++) {
    for (int j = 0; j < this->numCols; j++) {
      this->board[i][j] = 0;
    }
  }
}

Sudoku::Sudoku(int board[9][9]) {
  this->numRows = 9;
  this->numCols = 9;
  this->boxSideLen = 3;
  this->isSolved = false;
  this->board = new int*[numRows];

  for (int i = 0; i < this->numRows; i++) {
    this->board[i] = new int[numCols];
  }

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      this->board[i][j] = board[i][j];
    }
  }
}

Sudoku::~Sudoku() {
  for (int i = 0; i < numRows; i++) {
    delete [] board[i];
  }
  delete [] board;
}

void Sudoku::printBoard() {
  if (!isSolved) {
    std::cout << "Original Sudoku: " << std::endl;
  }
  else {
    std::cout << "Solved Sudoku: " << std::endl; 
  }
  for (int i = 0; i < numRows; i++) {
    std::cout << "| ";
    for (int j = 0; j < numCols; j++) {
      std::cout << board[i][j];
      if (j < numCols - 1) {
        std::cout << " | ";
      }
    }
    std::cout << " |" << std::endl;
  }
  std::cout << std::endl;
}

bool Sudoku::isSafe(int row, int col) {
  int value = board[row][col];
  for (int i = 0; i < numCols; i++) {
    if (i != col && value == board[row][i]) return false;
  }

  for (int i = 0; i < numRows; i++) {
    if (i != row && value == board[i][col]) return false;
  }

  int boxStartRow = row/3 * 3;
  int boxStartCol = col/3 * 3;
  for (int i = 0; i < numRows; i++) {
    int currentRow = boxStartRow + (i / 3);
    int currentCol = boxStartCol + (i % 3);

    if (currentCol != col && currentRow != row && board[currentRow][currentCol] == value) return false;
  }

  return true;
}

bool Sudoku::solveRecurse(int row, int col) {
  if (row == numRows - 1 && col == numCols) {
    return true;
  }

  if (col == numCols) {
    col = 0;
    row ++;
  }

  if (board[row][col] != 0) return solveRecurse(row, col + 1);

  for (int i = 1; i <= numRows; i++) {
    this->board[row][col] = i;
    if (isSafe(row, col)) {
      if (solveRecurse(row, col+1)) return true;
    }
    this->board[row][col] = 0;
  }

  return false;
}

bool Sudoku::solve() {
  isSolved = this->solveRecurse(0, 0);
  return isSolved;
}
