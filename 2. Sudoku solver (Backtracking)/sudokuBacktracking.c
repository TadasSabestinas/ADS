#include <stdio.h>

#define UNASSIGNED 0
#define N 9

//Paima Sudoku grido masyvą bei jį atspausdina į terminalą.

void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
        printf("%2d", grid[row][col]);
        }
        printf("\n");
    }
}

//Paima Sudoku grido masyva ir suranda sekancia nepriskirta vieta Sudoku gride.
//Funkcija atnaujina eilučių bei stulpelių pointerius, kurie pateikti kaip argumentai pointinantys į nepriskirtą vietą.

int findUnassignedLocation(int grid[N][N], int *row, int *col)
{
    for (*row = 0; *row < N; (*row)++)
    {
        for (*col = 0; *col < N; (*col)++)
        {
            if (grid[*row][*col] == UNASSIGNED)
                return 1;
        }
    }
    return 0;
}

//Patikrina ar Sudoku grido eilutėje skaičius jau buvo panaudotas

int usedInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
    {
        if (grid[row][col] == num)
        {
            return 1;
        }
    }
    return 0;
}

//Patikrina ar Sudoku grido stulpelyje skaičius jau buvo panaudotas.

int usedInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
    {
        if (grid[row][col] == num)
            {
                return 1;
            }
    }
    return 0;
}

//Patikrina ar 3x3 langeliu ir stulpeliu plote skaicius jau buvo panaudotas.

int usedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
    {
         for (int col = 0; col < 3; col++)
         {
             if (grid[row + boxStartRow][col + boxStartCol] == num)
                {
                    return 1;
                }
         }
    }
    return 0;
}

//Patikrina ar galima priskirti skaičių specifiškoje vietoje patikrinant ar tas skaičius jau yra naudotas toje pačioje eilutėje, stulpelyje ar 3x3 plote

int isSafe(int grid[N][N], int row, int col, int num)
{
    return !usedInRow(grid, row, num) && !usedInCol(grid, col, num) &&
           !usedInBox(grid, row - row % 3, col - col % 3, num);
}

//Rekursyviai issprendzia Sudoku puzzle priskiriant skaicius i tuscias Sudoku grido vietas naudojant backtracking algoritma.
//Funckija returns 1 jeigu pateiktame tekstiniame faile Sudoku yra issprendziamas arba returns 0 jeigu neissprendziamas.

int solveSudoku(int grid[N][N])
{
    int row, col;
    if (!findUnassignedLocation(grid, &row, &col))
    {
         return 1;
    }
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;
            if (solveSudoku(grid))
                return 1;
            grid[row][col] = UNASSIGNED;
        }
    }
    return 0;
}

int main()
{
    int grid[N][N];
    char fileName[30];

    printf("Enter the name of text file: ");
    scanf("%s", fileName);

    FILE *fp;
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("File with such name does not exist.\n");
        return 1;
    }
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            fscanf(fp, "%d", &grid[row][col]);
        }
    }
    fclose(fp);

    printf("Input grid: \n\n");
    printGrid(grid);
    printf("\n");

    if (solveSudoku(grid))
    {
        printf("The solved Sudoku grid: \n\n");
        printGrid(grid);
    }
    else
    {
        printf("There isn't a solution for the provided grid.\n");
    }

    return 0;
}
