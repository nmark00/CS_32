#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole)
{
	if (nHoles<=0)
		m_nHoles = 1;
	if (nInitialBeansPerHole<0)
		m_nInitialBeansPerHole = 0;

	m_nHoles = nHoles;
	m_nInitialBeansPerHole = nInitialBeansPerHole;

	for (int i = 0; i <= m_nHoles; i++)
	{
		north_holes.push_back(m_nInitialBeansPerHole);
		south_holes.push_back(m_nInitialBeansPerHole);
	}
	//set pot to 0
	north_holes[POT] = 0;
	south_holes[POT] = 0;
}
//copy constructor
Board::Board(const Board& other):
    north_holes(other.north_holes), 
    south_holes(other.south_holes)
{
	m_nHoles = other.m_nHoles;
	m_nInitialBeansPerHole = other.m_nInitialBeansPerHole;
}
//assignment operator
Board& Board::operator=(const Board& other)
{
    north_holes.clear();
    south_holes.clear();
    for (int i = 0; i <= other.m_nHoles; i++)
    {
        north_holes.push_back(other.north_holes[i]);
        south_holes.push_back(other.north_holes[i]);
    }
   m_nHoles = other.m_nHoles;
   m_nInitialBeansPerHole = other.m_nInitialBeansPerHole;
   return *this;
}

int Board::holes() const
{
	return m_nHoles;
}

int Board::beans(Side s, int hole) const
{
	if (hole<0 || hole > m_nHoles)
		return -1;
	if (s == NORTH)
		return north_holes[hole];
	else
		return south_holes[hole];
}

int Board::beansInPlay(Side s) const
{
    // cerr<<"North holes size: "<<north_holes.size()<<endl;
	int sum=0;
	if (s == NORTH)
	{
		for (int i = 1; i < north_holes.size(); i++)
			sum+=north_holes[i];
	}
	if (s == SOUTH)
	{
		for (int i = 1; i < south_holes.size(); i++)
			sum+=south_holes[i];
	}

	return sum;
}

int Board::totalBeans() const
{
	int total=0;
	for (int i = 0; i <= m_nHoles; i++)
	{
		total += north_holes[i];
		total += south_holes[i];
	}
	return total;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	if (hole<=0 || hole > m_nHoles)//check invalid hole
		return false;

	int numbeans = beans(s, hole);
	if (numbeans <= 0)//hole is empty
		return false;

	Side currentSide;
	int iterator;
	if (s == SOUTH)
	{	//numbeans is positive
		iterator = hole+1;//add bean to next hole
        currentSide = SOUTH;
		south_holes[hole] = 0;//take all beans
		while (numbeans != 0)
		{
			currentSide = SOUTH;//starts on south side
			while (iterator < south_holes.size() && numbeans !=0)
			{
				south_holes[iterator]++;
				iterator++;
				numbeans--;
			}
			iterator--;
			if (numbeans == 0)//no more beans- did not reach south pot
			{
				break;
			}

			south_holes[POT]++; //otherwise add to one to pot
			numbeans--; 
			if (numbeans == 0)//last bean spent on south pot
			{
				iterator = 0;
				break;
			}

			//if still beans left over, Enter North side
			currentSide = NORTH;// set to side to NORTH
			while (iterator > 0 && numbeans != 0)
			{
				north_holes[iterator]++;
				iterator--;
				numbeans--;
			}
			iterator++;//breaks loop with 1 hole below
		}
	}//end of if (s == SOUTH)
	else// if (s == NORTH)
	{
		iterator = hole -1;//add bean to previous hole
        currentSide = NORTH;
		north_holes[hole]=0;//take all beans
		while (numbeans != 0)
		{
			currentSide = NORTH;
			while (iterator >= 0 && numbeans != 0)
			{
				north_holes[iterator]++;
				iterator--;
				numbeans--;
			}
			iterator++;
			if (numbeans == 0)//no more beans- either doens't matter where
			{
				break;
			}
			iterator++;// set iterator to 1 when entering south side
			while (iterator < south_holes.size() && numbeans !=0)
			{
				currentSide = SOUTH;
				south_holes[iterator]++;
				iterator++;
				numbeans--;
			}
			iterator--;
			if (numbeans == 0)//no more beans
				break;
		}
	}//end of if (s == NORTH)

	endSide = currentSide;
	endHole = iterator;
	return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	if (hole<=0 || hole > m_nHoles)
		return false;

	 setBeans(potOwner, POT, beans(potOwner, POT) + beans(s, hole));
	 // replaces number of beans in pot with existing number + beans in hole
	 setBeans(s, hole, 0);
	 return true;

	// if (s == NORTH)
	// {
	// 	if (potOwner == NORTH)
	// 		north_holes[POT] += north_holes[hole];
	// 	if (potOwner == SOUTH)
	// 		south_holes[POT] += north_holes[hole];
	// 	north_holes[hole] = 0;
	// }
	// if (s == SOUTH)
	// {
	// 	if (potOwner == NORTH)
	// 		north_holes[POT] += south_holes[hole];
	// 	if (potOwner == SOUTH)
	// 		south_holes[POT] += south_holes[hole];
	// 	south_holes[hole] = 0;
	// }
	// return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{
	if (hole<0 || hole > m_nHoles || beans < 0)
		return false;
	if (s == NORTH)
		north_holes[hole] = beans;
	if (s == SOUTH)
		south_holes[hole] = beans;
	return true;
}
