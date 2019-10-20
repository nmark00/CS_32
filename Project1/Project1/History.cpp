//
//  History.cpp
//  Project1
//
//  Created by Nicholas Mark on 4/3/19.
//  Copyright © 2019 Nicholas Mark. All rights reserved.
//

#include "History.h"

#include <iostream>


using namespace std;

History::History(int nRows, int nCols){
    m_rows = nRows;
    m_cols = nCols;
    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols;j++){
            m_grid[i][j] = 0;
        }
    }
}

bool History::record(int r, int c){
    //return false if outside the bounds
    if(r <=0 || r > m_rows  ||  c <= 0  ||  c > m_cols)
        return false;
    //increase spot 
    m_grid[r-1][c-1]+=1;
    //cerr<<m_grid[r-1][c-1]<<endl;
    return true;
}

void History::display() const
{
    //assigning each spot
    char displayGrid[MAXROWS][MAXCOLS];
    
    for(int i = 0; i < m_rows; i++){
        for(int j = 0; j < m_cols; j++){
            if (m_grid[i][j] == 0)
                displayGrid[i][j] = '.';
            else if (m_grid[i][j] > 0 && m_grid[i][j] <26)
                displayGrid[i][j] = (char)('A' + m_grid[i][j] - 1);
            else
                displayGrid[i][j] = 'Z';
        }
    }
    //drawing the grid
    clearScreen();
    for (int r = 1; r <= m_rows; r++)
    {
        for (int c = 1; c <= m_cols; c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
}
