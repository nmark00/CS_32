// #include <iostream>
// #include <queue>
// #include <stdio.h>
// #include <string>
// using namespace std;
// class Coord
// {
// public:
//     Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
//     int r() const { return m_r; }
//     int c() const { return m_c; }
// private:
//     int m_r;
//     int m_c;
// };

bool pathExists(char maze[10][10], int sr, int sc, int er, int ec);

// If the start location is equal to the ending location, then we've
//         solved the maze, so return true.
//     Mark the start location as visted.
//     For each of the four directions,
//         If the location one step in that direction (from the start
//             location) is unvisited,
//                 then call pathExists starting from that location (and
//                             ending at the same ending location as in the
//                             current call).
//                      If that returned true,
//                          then return true.
//     Return false.


bool pathExists(char maze[10][10], int sr, int sc, int er, int ec)
{       
    if (sr == er && sc == ec)//if we reached the end, return true
        return true;
    maze[sr][sc] = '@';

    if (maze[sr+1][sc] == '.')//move to the south
        if (pathExists(maze, sr+1, sc, er, ec))
            return true;
    if (maze[sr][sc-1] == '.')//move to the west
        if (pathExists(maze, sr, sc-1, er, ec))
            return true;
    if (maze[sr-1][sc] == '.')//move to the north
        if (pathExists(maze, sr-1, sc, er, ec))
            return true;
    if (maze[sr][sc+1] == '.')//move to the east
        if (pathExists(maze, sr, sc+1, er, ec))
            return true;

    return false;
}

// int main()
// {
//     char maze[10][10] = {
//         { 'X','X','X','X','X','X','X','X','X','X' },
//         { 'X','.','.','.','.','X','.','.','.','X' },
//         { 'X','.','X','X','.','X','X','X','.','X' },
//         { 'X','X','X','.','.','.','.','X','.','X' },
//         { 'X','.','X','X','X','.','X','X','X','X' },
//         { 'X','.','X','.','.','.','X','.','.','X' },
//         { 'X','.','.','.','X','.','X','.','.','X' },
//         { 'X','X','X','X','X','.','X','.','X','X' },
//         { 'X','.','.','.','.','.','.','.','.','X' },
//         { 'X','X','X','X','X','X','X','X','X','X' }
//     };
    
//     if (pathExists(maze, 3,5, 8,8))
//         cout << "Solvable!" << endl;
//     else
//         cout << "Out of luck!" << endl;
//     return 0;
// }
