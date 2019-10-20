#include "Game.h"

Game::Game(const Board& b, Player* south, Player* north): m_board(b)
{
	m_south = south;
	m_north = north;
	turn = -1;
	m_over = false;
}

void Game::display() const
{
	cout<<endl;
	//prints north name
	for (int i = 0; i < m_board.holes()/2; ++i)
		cout<< "   ";
	cout<<m_north->name()<< endl; 
	//print north beans
	for (int i = 1; i <= m_board.holes(); ++i)
		cout<<"  "<< beans(NORTH, i);
	//print north pot
	cout<<endl << beans(NORTH, 0);
	//print south pot
	for (int i = 0; i < m_board.holes(); ++i)
		cout<< "   ";
	cout<< beans(SOUTH, 0)<< endl;
	//print south beans
	for (int i = 1; i <= m_board.holes(); ++i)
		cout<<"  "<< beans(SOUTH, i);
	cout<<endl;
	//prints sout name
	for (int i = 0; i < m_board.holes()/2; ++i)
		cout<< "   ";
	cout<<m_south->name()<< endl; 
}
void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
	if (m_board.beansInPlay(NORTH) != 0 && m_board.beansInPlay(SOUTH) != 0)
	// if ((m_board.beansInPlay(NORTH) != 0 && turn == 1)||
	// 	(m_board.beansInPlay(SOUTH) != 0 && turn == -1))
	{
		over = false;
		return;
	}

	over = true;//game over
	if (m_board.beans(NORTH, 0) != m_board.beans(SOUTH, 0))
	{
		hasWinner = true;
		if (m_board.beans(NORTH, 0) > m_board.beans(SOUTH, 0))
			winner = NORTH;
		else
			winner = SOUTH;
	}
	else
		hasWinner = false;
	return;
}
void Game::capture(int side)//captures hole across the board
{
	if (side == -1)//south side- capturing north hole
	{
		if (beans(endSide, endHole) == 1 && endHole != POT
			&& endSide == SOUTH && beans(NORTH, endHole) != 0)
		{
			m_board.moveToPot(SOUTH, endHole, SOUTH);
			m_board.moveToPot(NORTH, endHole, SOUTH);
			endHole = -1;
		}
	}
	if (side == 1)//north side- capturing south hole
	{
		if (beans(endSide, endHole) == 1 && endHole != POT 
			&& endSide == NORTH && beans(SOUTH, endHole) != 0)
		{
			m_board.moveToPot(NORTH, endHole, NORTH);
			m_board.moveToPot(SOUTH, endHole, NORTH);
			endHole = -1;
		}
	}
}
void Game::sweep()//any remaining beans get swept to the respective pot
{
	//sweep remaining beans to respective pot
	if (m_board.beansInPlay(NORTH) == 0 && m_board.beansInPlay(SOUTH) != 0)
	{
		cout << "Sweeping remaining beans into " << m_south->name() <<"'s pot.";
		for (int i = 1; i <= m_board.holes(); i++)
			m_board.moveToPot(SOUTH, i, SOUTH);
		display();
	}
	if (m_board.beansInPlay(SOUTH) == 0 && m_board.beansInPlay(NORTH) != 0)
	{
		cout << "Sweeping remaining beans into " << m_north->name() <<"'s pot.";
		for (int i = 1; i <= m_board.holes(); i++)
			m_board.moveToPot(NORTH, i, NORTH);
		display();
	}
}
bool Game::move()
{
	status(m_over, m_hasWinner, m_winner);
	if (m_over) //game is complete
	{
		return false;
	}

	endHole = 0; //reset endHole to enter while loop at least once
	if (turn == -1)//south's turn
	{
		while (endHole == 0 && !m_over)//lands on pot or first run through
		{
			m_hole = m_south->chooseMove(m_board, SOUTH);//gets hole number
			m_board.sow(SOUTH, m_hole, endSide, endHole);//moves beans
			capture(turn);// check for capture
			display();// show updated game board
			status(m_over, m_hasWinner, m_winner);
			// if (endHole == 0)
			// 	status(m_over, m_hasWinner, m_winner);
			// else
			// {
			// 	turn *= -1;//switch sides before doing status, in case you run out of beans
			// 	status(m_over, m_hasWinner, m_winner);//check status of game
			// 	turn *=-1;//switch back to your turn
			// }
			if (endHole == 0 && !m_over)//check if player gets another turn
				cout<< m_south->name() << " gets another turn."<<endl;
		}

		turn *= -1;//switch turns
	}
	else //north's turn
	{
		while (endHole == 0 && !m_over)
		{
			m_hole = m_north->chooseMove(m_board, NORTH);
			m_board.sow(NORTH, m_hole, endSide, endHole);
			capture(turn);
			display();
			status(m_over, m_hasWinner, m_winner);
			// if (endHole == 0)
			// 	status(m_over, m_hasWinner, m_winner);
			// else
			// {
			// 	turn *= -1;//switch sides before doing status, in case you run out of beans
			// 	status(m_over, m_hasWinner, m_winner);//check status of game
			// 	turn *=-1;//switch back to your turn
			// }
			if (endHole == 0 && !m_over)
				cout<< m_north->name() << " gets another turn."<<endl;
		}

		turn *= -1;//switch turns
	}
	if (m_over) //when game ends, sweep remaining beans
		sweep();
	return true;
}

void Game::play()
{
	display();
	if (m_board.beansInPlay(SOUTH)==0)//south has no beans to start
	{
		for (int i = 1; i <= m_board.holes(); i++)
			m_board.moveToPot(NORTH, i, NORTH);
		status(m_over, m_hasWinner, m_winner);
	}
	// 2 non human players
	else if (!m_south->isInteractive() && !m_north->isInteractive())
	{	
		while (!m_over)
		{	//neither are interactive: ask to continue
			if (move())
			{
				cout<<"Press Enter to continue.";
				cin.ignore(10000, '\n');//enter
			}
			else
				break;
		}	
	}
	else
		while (move())//move returns false if m_over
        {}

	status(m_over, m_hasWinner, m_winner);//reevaluate the winner
	//Announce the winner:
	if (!m_hasWinner)
		cout<< "Tie game."<<endl;
	else if (m_winner == NORTH)
		cout<< "The winner is "<<m_north->name()<<"."<<endl;
	else if (m_winner == SOUTH)
		cout<< "The winner is "<<m_south->name()<<"."<<endl;
}

int Game::beans(Side s, int hole) const
{
	return m_board.beans(s, hole);
}
