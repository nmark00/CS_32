#include "Board.h"
#include "Side.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <cassert>
using namespace std;

void doBoardTests()
{
    Board b(3, 2);
    assert(b.holes() == 3);
    assert(b.totalBeans() == 12); 
    assert(b.beans(SOUTH, POT) == 0);
    assert(b.beansInPlay(SOUTH) == 6);
    b.setBeans(SOUTH, 1, 1);
    b.moveToPot(SOUTH, 2, SOUTH);
    //cout<<"pass first set"<<endl;
    assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  &&
                b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
		b.beansInPlay(SOUTH) == 3);
	// test sow:
    Side es;
    int eh;
    b.sow(SOUTH, 3, es, eh);
    assert(es == NORTH); 
	assert(eh == 3);

   	assert(b.beans(SOUTH, 3) == 0);                
	assert(b.beans(NORTH, 3) == 3);
	assert(b.beans(SOUTH, POT) == 3 );
	assert(b.beansInPlay(SOUTH) == 1);
	assert(b.beansInPlay(NORTH) == 7);
}
void doPlayerTests()
{
    HumanPlayer hp("Marge");
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    BadPlayer bp("Homer");
    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
    SmartPlayer sp("Lisa");
    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    Board b(3, 2);
    b.setBeans(SOUTH, 2, 0);
    int n;
//    cout << "=========" << endl;
//    n = hp.chooseMove(b, SOUTH);
//    cout << "=========" << endl;
//    assert(n == 1  ||  n == 3);
    n = bp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
    n = sp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
}
void doGameTests()
{
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board b(3, 0);
    b.setBeans(SOUTH, 1, 2);
    b.setBeans(NORTH, 2, 1);
    b.setBeans(NORTH, 3, 2);
    Game g(b, &bp1, &bp2);
    bool over;
    bool hasWinner;
    Side winner;
    cout<<"SOUTH hole: 1, beans: "<<b.beans(SOUTH, 1)<<endl;
    cout<<"NORTH hole: 2, beans: "<<b.beans(NORTH, 2)<<endl;
    cout<<"NORTH hole: 3, beans: "<<b.beans(NORTH, 3)<<endl;
    g.display();
      //    Homer
      //   0  1  2
      // 0         0
      //   2  0  0
      //    Bart
    g.status(over, hasWinner, winner);
    assert(!over);
    assert(g.beans(NORTH, POT) == 0);
    assert(g.beans(SOUTH, POT) == 0) ;
    assert(g.beans(NORTH, 1) == 0);
    assert(g.beans(NORTH, 2) == 1);
    assert(g.beans(NORTH, 3) == 2);
    assert(g.beans(SOUTH, 1) == 2);
    assert(g.beans(SOUTH, 2) == 0);
    assert(g.beans(SOUTH, 3) == 0);

    g.move();
    //Bart chose 1
      //   0  1  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over);
    assert(g.beans(NORTH, POT) == 0 );
    assert(g.beans(SOUTH, POT) == 3 );
    assert(g.beans(NORTH, 1) == 0 );
    assert(g.beans(NORTH, 2) == 1 );
    assert(g.beans(NORTH, 3) == 0);
    assert(g.beans(SOUTH, 1) == 0 );
    assert(g.beans(SOUTH, 2) == 1);
    assert(g.beans(SOUTH, 3) == 0);

    g.move();
    //Homer Chose 2
      //   1  0  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over);
    assert(g.beans(NORTH, POT) == 0 );
    assert(g.beans(SOUTH, POT) == 3);
    assert(g.beans(NORTH, 1) == 1);
    assert(g.beans(NORTH, 2) == 0 );
    assert(g.beans(NORTH, 3) == 0);
    assert(g.beans(SOUTH, 1) == 0 );
    assert(g.beans(SOUTH, 2) == 1);
    assert(g.beans(SOUTH, 3) == 0);

    g.move();
    //Bart chose 2
      //   1  0  0
      // 0         3
      //   0  0  1
    g.status(over, hasWinner, winner);
    assert(!over);
    assert(g.beans(NORTH, POT) == 0);
    assert(g.beans(SOUTH, POT) == 3);
    assert(g.beans(NORTH, 1) == 1);
    assert(g.beans(NORTH, 2) == 0);
    assert(g.beans(NORTH, 3) == 0);
    assert(g.beans(SOUTH, 1) == 0 );
    assert(g.beans(SOUTH, 2) == 0);
    assert(g.beans(SOUTH, 3) == 1);

    g.move();
    //Homer chose 1
      //   0  0  0
      // 1         4
      //   0  0  0
    g.status(over, hasWinner, winner);
    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
	g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
	g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    assert(hasWinner && winner == SOUTH);
}
void printBoard()
{
	Board b(9,2);
	BadPlayer north("NORTH");
	BadPlayer south("SOUTH");
	Game g(b, &south, &north);
	g.display();
}
void playGame()
{
	HumanPlayer hp("Marge");
	BadPlayer bp("Homer");
	Board b(3, 2);
	Game g(b, &hp, &bp);
	g.play();
}
void computerGame()
{
	BadPlayer hp("Marge");
	BadPlayer bp("Homer");
	Board b(7, 3);
	Game g(b, &hp, &bp);
	g.play();
}
void humanGame()
{
	HumanPlayer hp("Marge");
	HumanPlayer bp("Homer");
	Board b(3, 2);
	Game g(b, &hp, &bp);
	g.play();
}
void testSmartPlayer()//tests the smartplayer algorithm
{
    cout<<endl<<"===== testSmartPlayer ====="<<endl;
    SmartPlayer sp1("South");
    SmartPlayer sp2("North");
    Board b(6,0);

    b.setBeans(SOUTH, 0, 2);
    b.setBeans(SOUTH, 2, 2);
    b.setBeans(SOUTH, 3, 2);
    b.setBeans(SOUTH, 4, 2);
    b.setBeans(SOUTH, 5, 2);
    b.setBeans(NORTH, 1, 2);
    b.setBeans(NORTH, 3, 2);
    b.setBeans(NORTH, 4, 2);
    Game g(b, &sp1, &sp2);
    g.display();
    //   2  0  2  2  0  0
    // 0                  2
    //   0  2  2  2  2  0 
    
    cout<<"SOUTH picks: "<< sp1.chooseMove(b, SOUTH)<<endl;//could make a move to the pot or avoid capture

    cout<<"NORTH picks: "<< sp2.chooseMove(b, NORTH)<<endl;//should capture for max

    Board b2(3,0);
    b2.setBeans(SOUTH, 0, 1);
    b2.setBeans(SOUTH, 1, 1);
    b2.setBeans(SOUTH, 3, 3);

    b2.setBeans(NORTH, 1, 2);
    b2.setBeans(NORTH, 2, 2);
    Game g2(b2, &sp1, &sp2);

    //   1  2  0
    // 0         1
    //   1  0  3
    g2.display();
    cout<< "SOUTH picks: "<<sp1.chooseMove(b2, SOUTH)<<endl;//should capture for best move
    
    cout<<"NORTH picks:" <<sp2.chooseMove(b2, NORTH)<<endl;// no choice

}
void SmartGameS()//manually test human and smartplayer. manually assess smartplayer's move
{
    HumanPlayer hp("Marge");
    SmartPlayer bp("Homer");
    Board b(5, 2);
    Game g(b, &hp, &bp);
    g.play();
}
void SmartGameN()//manually test human and smartplayer. make sure smart player can play as SOUTH
{
    HumanPlayer hp("Marge");
    SmartPlayer bp("Homer");
    Board b(5, 2);
    Game g(b, &bp, &hp);
    g.play();
}
void SmartVSGame()//make sure smartplayer can play against another smartplayer
{
    SmartPlayer hp("Marge");
    SmartPlayer bp("Homer");
    Board b(5, 2);
    Game g(b, &hp, &bp);
    g.play();
}
int main()
{
	// printBoard();
    //doBoardTests();
    //doPlayerTests();
    //doGameTests();
    //testSmartPlayer();
    //cout << endl<< "Passed all tests" << endl;

    //playGame();
    //computerGame();
    //humanGame();
    SmartGameS();
}
