#include "Player.h"

Player::Player(std::string name)
{
	m_name = name;
}

string Player::name() const
{
	return m_name;
}

bool Player::isInteractive() const
{
	return false;
}

bool Player::isValid(const Board& b, Side s, int hole) const
{
	if (b.beans(s, hole) <= 0)
		return false;
	return true;
}

Player::~Player()
{}

bool HumanPlayer::isInteractive() const
{
	return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
	int hole = -1;
	while (!isValid(b, s, hole))
	{	//ask if message matters
		cout<<"Select a hole, "<< name() << ": ";
		cin>> hole;
		if (hole <= 0 || hole > b.holes())
		{
			cout<< "The hole number must be from 1 to " << b.holes()<< "."<<endl;
			hole = -1;//makes false
		}
		else if (b.beans(s, hole) == 0)
			cout<< "There are no beans in that hole."<<endl;
	}
	return hole;
}
int BadPlayer::chooseMove(const Board& b, Side s) const
{
	int randomHole = -1;
	while (!isValid(b, s, randomHole))
	{
		randomHole = 1 + rand() % (b.holes());
	}
	cout<< name()<< " chooses hole "<< randomHole;
	return randomHole;
}
//=======================================================================
//============================ SMART PLAYER =============================

bool SmartPlayer::gameOver(const Board& b, int& value) const
{
	if (b.beansInPlay(NORTH) == 0 && b.beansInPlay(SOUTH) == 0)
	{
		if (b.beans(NORTH, POT) > b.beans(SOUTH, POT))//North wins
			value = 9999;
		else if (b.beans(NORTH, POT) < b.beans(SOUTH, POT))//South wins
			value = -9999;
		else
			value = 0;//tie
		return true;
	}
	return false;
}

void SmartPlayer::assignSides(Side s) const
{
	if (s == SOUTH)
		n_side = NORTH;
	else
		n_side = SOUTH;
	s_side = s;
}

int SmartPlayer::chooseMove(const Board& b, int& value) const
{
	if (gameOver(b, value))
		return -1;
	if (turnCounter == maxDepth)//limit number of searches
	{
		value = b.beans(n_side, POT)-b.beans(s_side, POT);
		return -1;
	}
	//variables to keep track of stuff
	int bestValue = 10000;//never select the pot
	int bestHole = -1;
    turnCounter++;
	for (int i = 1; i <= b.holes(); ++i)
	{	//tests out each possible move
		if (isValid(b, s_side, i))
		{
			Board temp_b(b); //give each opp a temp_b to work on
			//for sow function:
			int m_endHole=0;
		    Side m_endSide=s_side;
			temp_b.sow(s_side, i, m_endSide, m_endHole);//make your move
            
			if (gameOver(temp_b, value))//check if value is 999 or -999
                {}
			else
                oppChooseMove(temp_b, value);

			if (value < bestValue)
			{
				bestValue = value;
				bestHole = i;
			}
		}
	}


	while (!isValid(b, s_side, bestHole))
	{
		bestHole = 1 + rand() % (b.holes());//just in case all options are the same
	}
	
	return bestHole;
}
//Super short version of opponent:
// void SmartPlayer::oppChooseMove(const Board& b, int& value) const
// {
// 	if (gameOver(b, value))
// 	{	//gameOver modifies value for you ;)
// 		return;
// 	}
// 	value = b.beans(n_side, POT)-b.beans(s_side, POT);
// }

//Regular version of opponent:
void SmartPlayer::oppChooseMove(const Board& b, int& value) const
{
    // cerr<<"oppChooseMove-nHoles: "<<b.holes()<<endl;
	if (gameOver(b, value))
	{	//gameOver modifies value for you ;)
		return;
	}
	if (turnCounter == maxDepth)//limit number of searches
	{
		value = (b.beans(n_side, POT))-(b.beans(s_side, POT));
		return;//break and just pass back the value
	}
	//variables to keep track of stuff
	int bestValue = -10000;//never select the pot
    turnCounter++;
	for (int i = 1; i <= b.holes(); ++i)
	{	//tests out each possible move
		if (isValid(b, s_side, i))
		{
			Board temp_b(b); //give each opp a temp_b to work on
			//for sow function:
			int m_endHole=0;
		    Side m_endSide=s_side;
			temp_b.sow(n_side, i, m_endSide, m_endHole);//make your move
            
			if (gameOver(temp_b, value))//check if value is 999 or -999
                {}
			else chooseMove(temp_b, value);

			if (value > bestValue)
				bestValue = value;

		}
	}
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	assignSides(s);
    int value;//pass by reference
    turnCounter = 0;//reset each turn
    int chosen = chooseMove(b, value);//call chooseMove once
    cout<< name()<< " chooses hole "<< chosen;
	return chosen;
}
