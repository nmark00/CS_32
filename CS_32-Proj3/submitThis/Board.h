#ifndef Board_h
#define Board_h
#include <iostream>
#include <string>
#include <vector>
#include "Side.h"
using namespace std;
class Board
{
public:
	Board(int nHoles, int nInitialBeansPerHole);//constructor

	Board(const Board& other);//copy constructor
	Board& operator=(const Board& other);//assignment operator

	int holes() const;

	int beans(Side s, int hole) const;

	int beansInPlay(Side s) const;

	int totalBeans() const;

	bool sow(Side s, int hole, Side& endSide, int& endHole);

	bool moveToPot(Side s, int hole, Side potOwner);

	bool setBeans(Side s, int hole, int beans);

private:
	int m_nHoles, m_nInitialBeansPerHole;
	vector<int> north_holes;
	vector<int> south_holes;
};

#endif
