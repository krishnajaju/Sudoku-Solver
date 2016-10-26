
#include<iostream>
#include <cstdio>
using namespace std;
#include<math.h>


#define MAX 25

//Function to get input from user as unsolved Sudoku Board
//Returns the size of board as per users choice
int takeInput(int sudoku[MAX][MAX])
{
	int size = 0;
	do
	{
		cout << "Choose the size of board from\nEnter 1 for 9 X 9\nEnter 2 for 16 X 16\nEnter 3 for 25 X 25\n";
		cout << "Your Selection:\t";
		cin >> size;
		switch (size)
		{
		case 1:
			size = 9;
			break;
		case 2:
			size = 16;
			break;
		case 3:
			size = 25;
			break;
		default:
			cout << "Invalid Selection" << endl;
			break;
		}
	} while (!size); //until valid board size is selected

	cout << "Enter the Initial " << size << " X " << size << " Sudoku Board:" << endl;
	cout << "Instruction: Enter 0 for blank" << endl;
	for (int i = 0; i<size; i++)
		for (int j = 0; j<size; j++)
			cin >> sudoku[i][j];

	return size;
}

//Function to display solved Sudoku Board
void displaySolution(int sudoku[MAX][MAX], int size)
{
	for (int i = 0; i<size; i++)
	{
		for (int j = 0; j<size; j++)
			printf("%4d", sudoku[i][j]);
		cout << endl;
	}
	cout << "\n\n*************************************************\n\n";
}

// Function to check if board is solved now i. e. it has no vacancies
// If the board is full then it is solved correctly
bool isFull(int sudoku[MAX][MAX], int size)
{
	int i, j;
	for (i = 0; i<size; i++)
		for (j = 0; j<size; j++)
			if (!sudoku[i][j])
				return false;
	return true;
}

//Function to find various possible values at position (r, c)
//Returns no. of possible values at that position and those values in array a[]
int findPossibleValues(int sudoku[MAX][MAX], int size, int a[], int r, int c)
{
	int n = 0;
	int i, j;
	int s = (int)(sqrt(size));
	int b[MAX + 1] = { 0 };

	//Note no.s appeared in current row
	for (i = 0; i<size; i++)
		b[sudoku[r][i]] = 1;

	//Note no.s appeared in current column
	for (i = 0; i<size; i++)
		b[sudoku[i][c]] = 1;

	//Note no.s appeared in current block
	r = (r / s)*s, c = (c / s)*s;
	for (i = r; i<r + s; i++)
		for (j = c; j<c + s; j++)
			b[sudoku[i][j]] = 1;

	//Fill array a[] with no.s unappeared in current row, column and block
	for (i = 1; i <= size; i++)
		if (!b[i])
			a[n++] = i;

	return n;
}

//Function to solve the sudoku board
//Gives solved_flag as true if at least one solution is possible, false otherwise
//Gives multiple solutions with corresponding soultion no.
//Returns when user does not want more solutions

void SolveSudoku(int sudoku[MAX][MAX], int size, int &solution_num, bool &solved_flag, bool &enough)
{
	int i, j, a[MAX + 1] = { 0 }, n = 0;

	if (enough) //true if user does not want more solutions
		return;

	if (isFull(sudoku, size))    //true if now sudoku board is solved completely
	{

		if (!solved_flag)
			cout << "Sudoku Solved Successfully!" << endl;
		solved_flag = 1;

		//show the solution
		cout << "\n\nSolution no. " << (solution_num++) << endl;
		displaySolution(sudoku, size);

		//users' choice
		char more;
		cout << "Do you want more solutions?" << endl;
		cout << "Press 1 for 'YES', anything OTHERWISE:\t";
		cin >> more;
		cout << "\n\n*************************************************\n\n";

		if (more != '1')
			enough = true;
		return;
	}

	//Find first vacant place/position
	int break_flag = 0;
	for (i = 0; i<size; i++)
	{
		for (j = 0; j<size; j++)
			if (!sudoku[i][j])
			{
				break_flag = 1;
				break;
			}
		if (break_flag)
			break;
	}

	//check possibilities at that vacant place
	n = findPossibleValues(sudoku, size, a, i, j);
	for (int l = 0; l<n; l++)
	{
		//put value at vacant place
		sudoku[i][j] = a[l];
		//now solve the updated board
		SolveSudoku(sudoku, size, solution_num, solved_flag, enough);
	}

	// We come at this position when we have already checked all possible values at sudoku[i][j] and we couldn't find the solution
	// Put any value does not solve our board implies that we must have made wrong choice earlier
	// so we make this sudoku[i][j] again a vacant cell and try to correct our previous guesses/choices.
	sudoku[i][j] = 0;
}

//Starting point
int main()
{
	//Input
	int sudoku[MAX][MAX] = { 0 }, size;
	size = takeInput(sudoku);

	int solution_num = 1;
	bool solved_flag = 0;
	bool enough = false;

	//Processing
	cout << "Finding Solutions!\n\n" << endl;
	SolveSudoku(sudoku, size, solution_num, solved_flag, enough);

	//Exit
	if (!solved_flag)
		cout << "Invalid Board!" << endl;

	cout << "Exiting!\n\n" << endl;

	return 0;
}
