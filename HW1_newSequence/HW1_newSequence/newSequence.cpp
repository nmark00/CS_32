
#include "newSequence.h"

//new Constructor
Sequence::Sequence(int max)
{
    if (max <0) {
        exit(1);
    }
    m_size =0;
    max_size=max;
    m_sequence = new ItemType[max_size];
}
//Destructor
Sequence::~Sequence()
{
    delete[] m_sequence;
}

//Copy Constructor
Sequence::Sequence(const Sequence& other)
{
    m_size= other.m_size;
    max_size= other.max_size;
    m_sequence= other.m_sequence;
    for (int i=0; i<m_size; i++) {
        m_sequence[i] = other.m_sequence[i];
    }
}

//Assignment Operator
Sequence& Sequence::operator=(const Sequence& rhs)
{
    if (this != &rhs) {
        Sequence temp(rhs);
        swap(temp);
    }
    return *this;
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
    if (pos >= 0 && pos <=size() && size()< max_size) {
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
    //swap m_sequence
    ItemType *temp_sequence = m_sequence;
    m_sequence = other.m_sequence;
    other.m_sequence = temp_sequence;
    
    //swap m_size;
    int temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
    
    //swap max_size
    int temp_max = max_size;
    max_size = other.max_size;
    other.max_size = temp_max;
     
}

