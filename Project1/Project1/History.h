//
//  History.hpp
//  Project1
//
//  Created by Nicholas Mark on 4/3/19.
//  Copyright © 2019 Nicholas Mark. All rights reserved.
//

#ifndef History_hpp
#define History_hpp

#include <stdio.h>
#include "globals.h"
//class Arena;

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    
    int m_grid[MAXROWS][MAXCOLS];
    int m_rows;
    int m_cols;

};
#endif /* History_hpp */
