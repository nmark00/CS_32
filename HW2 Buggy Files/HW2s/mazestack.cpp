#include <iostream>
#include <stack>
#include <stdio.h>
#include <string>
using namespace std;
class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(char maze[10][10], int sr, int sc, int er, int ec);

bool pathExists(char maze[10][10], int sr, int sc, int er, int ec)
{
	stack<Coord> coordStack;//create stack of coords
	coordStack.push(Coord(sr,sc));
	maze[sr][sc] = '.';

	while(!coordStack.empty())
	{
		Coord current = coordStack.top();
		coordStack.pop();
		int row = current.r();//starting coordinate
		int col = current.c();
		
		if (row == er && col == ec)//if we reached the end, return true
		{
			return true;
		}

		if (maze[row-1][col] == '.')//move to the north
		{
			coordStack.push(Coord(row-1,col));
			maze[row-1][col] = '@';// mark as visitied
		}
		if (maze[row+1][col] == '.')//move to the south
		{
			coordStack.push(Coord(row+1,col));
			maze[row+1][col] = '@';// mark as visitied
		}
		if (maze[row][col+1] == '.')//move to the east
		{
			coordStack.push(Coord(row,col+1));
			maze[row][col+1] = '@';// mark as visitied
		}
		if (maze[row][col-1] == '.')//move to the west
		{
			coordStack.push(Coord(row-1,col));
			maze[row][col-1] = '@';// mark as visitied
		}
	}
	return false;
}

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','.','X' },
        { 'X','.','X','X','.','X','X','X','.','X' },
        { 'X','X','X','.','.','.','.','X','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
    return 0;
}