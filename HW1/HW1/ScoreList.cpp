#include "ScoreList.h"

ScoreList::ScoreList():  m_sequence()
{}

bool ScoreList::add(unsigned long score)
{
    if (score <= 100 )
    {
        m_sequence.insert(score);
        return true;
    }
    return false;
}

bool ScoreList::remove(unsigned long score)
{
    if (m_sequence.find(score) != -1)
    {
        m_sequence.erase(m_sequence.find(score));
        return true;
    }
    return false;
}

int ScoreList::size() const
{
    return m_sequence.size();
}

unsigned long ScoreList::minimum() const
{
    unsigned long min = NO_SCORE;
    unsigned long temp = 0;
    
    if (size() > 0) {
        for (int i = 0; i< size(); i++) {
            m_sequence.get(i, temp);
            if (temp < min) {
                min = temp;
            }
        }
    }

    return min;
}

unsigned long ScoreList::maximum() const
{
    unsigned long max = -1 * NO_SCORE;
    unsigned long temp = 0;
    
    if (size() > 0) {
        for (int i = 0; i< size(); i++) {
            m_sequence.get(i, temp);
            if (temp > max) {
                max = temp;
            }
        }
    }
    else
        max = NO_SCORE;
    return max;
}

