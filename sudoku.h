class Sudoku {
  private:
    int** board;
    int numRows;
    int numCols;
    int boxSideLen;
    bool isSolved;

  public:
    Sudoku();
    Sudoku(int[9][9]);
    ~Sudoku();

    void printBoard();
    bool isSafe(int, int);
    bool solveRecurse(int, int);
    bool solve();
};
