#include <iostream>
using namespace std;

//checks whether the suduko is completely filled or not
int isfilled(int suduko[][9], int r, int c)
{
    int i, j, count = 0;
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            if (suduko[i][j] != 0)
                count++;
        }
    }
    //if suduko is comoletely filled count 81 will be returned
    return count;
}


//checks whether suduko is valid or not
bool isvalid(int suduko[][9], int r, int c)
{
    if (suduko[r][c] != 0)
    {
        for (int x = 0; x < 9; x++)
        {
            if (x != c)
            { //if any number is same in row ,return false
                if (suduko[r][x] == suduko[r][c])
                    return false;
            }
        }
        for (int x = 0; x < 9; x++)
        {
            if (x != r)
            { //if any number is same in column ,return false
                if (suduko[x][c] == suduko[r][c])
                    return false;
            }
        }
        int Start_Row = r - r % 3;
        int Start_Column = c - c % 3;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            { //if any number is same is 3*3 grid, return false
                if ((i + Start_Row) != r && (j + Start_Column) != c)
                {
                    if (suduko[i + Start_Row][j + Start_Column] == suduko[r][c])
                        return false;
                }
            }
        }
    }
    //if number is not same is row, column and 3*3 grid means it is valid suduko and then return true
    return true;
}


//checks whether the number which is to be put in a particular position(given row and column) is safe or not
bool safe(int suduko[][9], int r, int c, int n)
{
    for (int x = 0; x < 9; x++)
    {
        //checks whether the same number exist in the same row, return false
        if (suduko[r][x] == n)
            return false;
    }
    for (int x = 0; x < 9; x++)
    {
        //checks whether the same number exist in the same column, return false
        if (suduko[x][c] == n)
            return false;
    }
    //checks whether the number exists in 3*3 matrix, return false
    int Start_Row = r - r % 3;
    int Start_Column = c - c % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (suduko[i + Start_Row][j + Start_Column] == n)
                return false;
        }
    }
    //if none of the above conditions are executed then it returns true i.e,. it's safe to put number in given row and column
    return true;
}


//solves the suduko
bool solving_suduko(int suduko[][9], int r, int c)
{
    //checks whether we have reached to final row and column,return false to stop execution of this function.
    if (r == 8 && c == 9)
        return true;
    //checks if we reached to last column, increase row by 1 and make column again 0
    if (c == 9)
    {
        r++;
        c = 0;
    }
    //checks if the current position is already occupying number, we move to next column
    if (suduko[r][c] > 0)
        return solving_suduko(suduko, r, c + 1);
    for (int n = 1; n <= 9; n++)
    {
        if (safe(suduko, r, c, n))
        { //if safe function return true means it is safe to put the number in position
            suduko[r][c] = n;
            if (solving_suduko(suduko, r, c + 1))
                return true;
        }
        //if our number is wrong in sudoku, we checks with other numbers
        suduko[r][c] = 0;
    }
    return false;
}





//main program or driver program
int main()
{
    cout << "********************WELCOME TO SUDUKO SOLVER*********************" << endl
         << endl;
    int ele, j, n, i, c = 0;
    int suduko[9][9] = {0};
    cout << "This is 9*9 suduko solver\n\nHow many elements you want to enter" << endl;
    cin >> n;
    cout << "\nEnter position of  ith row separated by space jth column and then separated by space  enter value to be put" << endl;
    //taking input from user
    for (int x = 0; x < n; x++)
    { //enter first row then space column then space number
        cin >> i >> j;
        cin >> ele;
        suduko[i][j] = ele;
    }
    cout << "Intial suduko" << endl;
    for (int m = 0; m < 9; m++)
    {
        for (int n = 0; n < 9; n++)
        {
            if (suduko[m][n] == 0)
                cout << "_"
                     << "  ";
            else
                cout << suduko[m][n] << "  ";
        }
        cout << endl;
    }
    cout << endl;
    int k;
    //checks is the suduko is completely filled(k=81) or not(k!=81)
    k = isfilled(suduko, 9, 9);
    if (k == 81)
        cout << "suduko is completely filled" << endl;
    //if not compeletely filled then check for validation
    else
    {
        for (i = 0; i < 9; i++)
        {
            for (j = 0; j < 9; j++)
            { //checks for valids or not
                if (isvalid(suduko, i, j))
                    continue;
                else
                {
                    c = 1;
                    break;
                }
            }
        }
        if (c == 1)
            cout << "\ninvalid suduko";
        //if not valid solve the suduko
        else
        {
            if (solving_suduko(suduko, 0, 0))
            {
                cout << "solved suduko" << endl;
                for (int i = 0; i < 9; i++)
                {

                    for (int j = 0; j < 9; j++)
                    {
                        cout << suduko[i][j] << "   ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
            else
            {
                cout << "not solvable";
            }
        }
    }
    return 0;
}