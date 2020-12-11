/*
    Code written and commented by Connor on GitHub (@Rivers-dev/Sudoku-Solver)
*/

#include <iostream>
using namespace std;

int grid[9][9] = 
{
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {}
};

void input() //Gathers user input matrix
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cin >> grid[i][j];
        }
    }
}

void printGrid() //Prints the solved matrix
{
   for (int row = 0; row < 9; row++)
   {
      for (int col = 0; col < 9; col++)
      {
         if (col == 3 || col == 6)
            cout << " | ";
         cout << grid[row][col] <<" ";
      }
      if (row == 2 || row == 5)
      {
         cout << endl;
         for(int i = 0; i < 9; i++)
         {
            cout << "---";
         }
      }
      cout << endl;
   }
}

bool inRow(int row, int n) //Determines whether the given number is in the given row
{
    for (int col = 0; col < 9; col++)
    {
        if (grid[row][col] == n)
            return true;
    }
    return false;
}

bool inCol(int col, int n) //Determines whether the given number is in the given column
{
    for (int row = 0; row < 9; row++)
    {
        if (grid[row][col] == n)
            return true;
    }
    return false;
}

bool inBox(int boxRow, int boxCol, int n) //Determines whether the given number is in the given box (with starting bounds at the top left)
{
    for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++)
         if (grid[row + boxRow][col + boxCol] == n)
            return true;
    return false;
}

bool isEmpty(int &row, int &col) //Determines whether the row has empty spaces
{ 
   for (row = 0; row < 9; row++)
      for (col = 0; col < 9; col++)
         if (grid[row][col] == 0)
            return true;
   return false;
}

bool isValid(int row, int col, int num) //Determines whether the given number would be a valid addition to the grid
{ 
   return (!inRow(row, num) && !inCol(col, num) && !inBox(row - row % 3, col - col % 3, num));
}

bool solve() //Main solving logic
{
   int row, col;
   if (!isEmpty(row, col))
      return true; 
   for (int n = 1; n <= 9; n++)
   { 
      if (isValid(row, col, n))
      { 
         grid[row][col] = n;
         if (solve()) 
            return true;
         grid[row][col] = 0; 
      }
   }
   return false;
}

int main()
{
    input();
    if (solve() == true)
      printGrid();
   else
      cout << "No solution found." << endl;
    return 0;
}

/* EXAMPLE INPUT:
0 0 4 1 7 0 2 9 0
0 0 0 2 0 4 5 0 8 
8 2 7 9 0 5 1 6 0
1 0 0 7 0 3 0 0 0
7 0 0 8 0 0 0 3 0
0 0 2 0 5 6 7 1 9
0 3 0 0 0 0 9 4 7
0 0 9 3 4 0 6 8 1 
0 7 0 6 0 0 3 2 5

EXPECTED RESULT:
5 6 4  | 1 7 8  | 2 9 3 
9 1 3  | 2 6 4  | 5 7 8 
8 2 7  | 9 3 5  | 1 6 4 
---------------------------
1 4 6  | 7 9 3  | 8 5 2 
7 9 5  | 8 1 2  | 4 3 6 
3 8 2  | 4 5 6  | 7 1 9 
---------------------------
6 3 8  | 5 2 1  | 9 4 7 
2 5 9  | 3 4 7  | 6 8 1 
4 7 1  | 6 8 9  | 3 2 5 
*/