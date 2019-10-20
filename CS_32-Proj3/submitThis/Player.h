#ifndef Player_h
#define Player_h
#include <iostream>
#include <string>
#include <vector>
#include<algorithm>// for max and min
#include <cstdlib>// for random
#include "Board.h"
#include "Side.h"
using namespace std;

class Player
{
public:
	Player(std::string name);
	//Create a Player with the indicated name.
	std::string name() const;
	//Return the name of the player.
	virtual bool isInteractive() const;
	//Return false if the player is a computer player. Return true if the player is human. 
	//Most kinds of players will be computer players.
	virtual int chooseMove(const Board& b, Side s) const = 0;
	//Every concrete class derived from this class must implement this function so that 
	//if the player were to be playing side s and had to make a move given board b, 
	//the function returns the move the player would choose. If no move is possible, 
	//return −1.
	virtual ~Player();
	//Since this class is designed as a base class, it should have a virtual destructor.
private:
	string m_name;
protected:
	bool isValid(const Board& b, Side s, int hole) const;
};

class HumanPlayer: public Player
{
public:
	HumanPlayer(string name): Player(name){};

	virtual bool isInteractive() const;

	virtual int chooseMove(const Board& b, Side s) const;
};

class BadPlayer: public Player
{
public:
	BadPlayer(string name): Player(name){};

	virtual int chooseMove(const Board& b, Side s) const;
};

class SmartPlayer: public Player
{
public:
	SmartPlayer(string name): Player(name), maxDepth(10)
	{
		turnCounter = 0;
	};
	virtual int chooseMove(const Board& b, Side s) const;
	
private:
	bool gameOver(const Board& b, int& value) const;
 	mutable int turnCounter;
 	void assignSides(Side s) const;
 	mutable Side s_side;
 	mutable Side n_side;

 	const int maxDepth;

	int chooseMove(const Board& b, int& value) const;
	void oppChooseMove(const Board& b, int& value) const;
};
#endif
