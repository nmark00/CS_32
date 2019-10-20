#ifndef Game_h
#define Game_h
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Board.h"
#include "Side.h"
using namespace std;

class Game
{
public:
	Game(const Board& b, Player* south, Player* north);
	void display() const;
	void status(bool& over, bool& hasWinner, Side& winner) const;
	bool move();
	void play();
	int beans(Side s, int hole) const;
private:
	Board m_board;
	Player* m_south;
	Player* m_north;
	bool m_over, m_hasWinner;
	Side m_winner;
	int turn;//toggle between turns
	// used for Board::sow
	int m_hole, endHole;
	Side endSide;
	void capture(int side);
	void sweep();
};
#endif