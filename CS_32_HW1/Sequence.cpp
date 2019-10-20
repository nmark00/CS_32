//
//  Sequence.cpp
//  HW1
//
//  Created by Nicholas Mark on 4/11/19.
//  Copyright © 2019 Nicholas Mark. All rights reserved.
//

#include "Sequence.h"

Sequence::Sequence(){
    m_size =0;
}

bool Sequence::empty()
{
    if (size()==0) {
        return true;
    }
    return false;
}

int Sequence::size() const
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
{
    if (pos >= 0 && pos <=size() && size()< DEFAULT_MAX_ITEMS) {
        for (int i=size(); i>pos; i--) {
            m_sequence[i] = m_sequence[i-1];
        }
        m_sequence[pos]=value;
        m_size++;
        return pos; //must check fixed-size array
    }
    else
        return -1;
}

int Sequence::insert(const ItemType& value)
{
    int p = size();
    
    for (int i=0; i<size(); i++) {
        if (m_sequence[i] >= value) {
            p=i;
            break;
        }
    }
    
    return insert(p, value);
}

bool Sequence::erase(int pos)
{
    if (pos >=0 && pos < size() ) {
        for (int i=pos; i< size()-1; i++) {
            m_sequence[i]=m_sequence[i+1];
        }
        m_size--;
        return true;
    }
    else
        return false;
}

int Sequence::remove(const ItemType& value)
{
    int count = 0;
    for (int i=0; i<size(); i++) {
        if (m_sequence[i] == value) {
            erase(i);
            count++;
        }
    }
    return count;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos >=0 && pos < size() ) {
        value = m_sequence[pos];
        return true;
    }
    else
        return false;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos >=0 && pos < size() ) {
        m_sequence[pos] = value;
        return true;
    }
    else
        return false;
}

int Sequence::find(const ItemType& value) const
{
    int p=-1;
    for (int i=0; i<size(); i++) {
        if (m_sequence[i] == value) {
            p = i;
            break;
        }
    }
    return p;
}

void Sequence::swap(Sequence& other)
{
    int temp_size = m_size;
    ItemType temp_array[DEFAULT_MAX_ITEMS];
    m_size = other.m_size;
    other.m_size = temp_size;
    
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        temp_array[i] = m_sequence[i];
        m_sequence[i] = other.m_sequence[i];
        other.m_sequence[i] = temp_array[i];
    }
}
