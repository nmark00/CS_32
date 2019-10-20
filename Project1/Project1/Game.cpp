//
//  Game.cpp
//  Project1
//
//  Created by Nicholas Mark on 4/3/19.
//  Copyright © 2019 Nicholas Mark. All rights reserved.
//
#include "Arena.h"
#include "globals.h"
#include "Game.h"
#include "Player.h"
#include "History.h"
Game::Game(int rows, int cols, int nZombies)
{
    if (nZombies < 0)
    {
        cout << "***** Cannot create Game with negative number of zombies!" << endl;
        exit(1);
    }
    if (nZombies > MAXZOMBIES)
    {
        cout << "***** Trying to create Game with " << nZombies
        << " zombies; only " << MAXZOMBIES << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nZombies > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the zombies!" << endl;
        exit(1);
    }
    
    // Create arena
    m_arena = new Arena(rows, cols);
    
    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_arena->addPlayer(rPlayer, cPlayer);
    
    // Populate with zombies
    while (nZombies > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a zombie where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_arena->addZombie(r, c);
        nZombies--;
    }
}

Game::~Game()
{
    delete m_arena;
}

void Game::play()
{
    m_arena->display();
    Player* p = m_arena->player();
    //History h =m_arena->history();
    if (p == nullptr)
        return;
    while ( ! m_arena->player()->isDead()  &&  m_arena->zombieCount() > 0)
    {
        cout << endl;
        cout << "Move (u/d/l/r//h/q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)  // player stands
            p->stand();
        //history add-on
        else if (action == "h"){
            m_arena-> history().display();
            //cout<< "Press enter to continue";
            string enter= "null";
            while (enter != "") {
                cout<< "Press enter to continue";
                getline(cin,enter);
            }
            m_arena->display();
        }
        
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->moveOrAttack(decodeDirection(action[0]));
                    break;
                //case 'h':
                    ////h.record(p->row(), p->col());
                    //h.display();
            }
        }
        if (action!= "h") {
            m_arena->moveZombies();
            m_arena->display();
        }
    }
}
