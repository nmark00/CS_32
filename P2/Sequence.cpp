
#include "Sequence.h"

//new Constructor
Sequence::Sequence()
{
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}
//Destructor
Sequence::~Sequence()
{
    if (head == nullptr)
        return;
    if (head->next == nullptr) {
        delete head;
        return;
    }
  
    Node *n = head, *k;
    while(n != nullptr)
    {
        k = n;
        n = n->next;
        delete k;
        /* delete killMe;
        killMe = n;
        n = n->next; */
    }
    
}

//Copy Constructor
Sequence::Sequence(const Sequence& other)
{
    m_size = other.m_size;
    if (other.head == nullptr)
    {
        head = nullptr;
        head-> prev = nullptr;
    }
    else
    {
        head = new Node; //creates the head Node
        head ->m_value = other.head-> m_value; //sets value
        head -> prev = nullptr; //makes prev point to null
    }
    
    Node *p = head;
    Node *n = other.head->next;
    
    while(n != nullptr)
    {
        p -> next = new Node; //creates new Node to store the next item
        p -> next -> prev = p; //links the next Node's prev to current Node
        p = p-> next; //now pointing to the newly made Node
        p->m_value = n->m_value; //Sets the value
        n = n->next;// advances other
    }
    tail = p; //makes tail point to last Node
    p->next = nullptr; //marks end of list
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
    if (pos == 0)
    {
        if (head == nullptr)
        {
            cerr << "Seqeunce is empty" << endl;
            head = new Node;
            head->prev = (head->next = nullptr);
            m_size++;
            head->m_value = value;
            return pos;
        }
    
        cerr << "Inserting element " << value << " at beginning of array" << endl;
        Node* p = new Node; //creates the inserted item
        p-> m_value = value; //add values
        p-> prev = nullptr;
        p-> next = head;
        head->prev = p;//set next to current head
        head = p; //make p the new head
        m_size++; //increase size
        return pos; 
    }
    else if (pos > 0 && pos < size() )
    {
        cerr << "Inserting element " << value << " in middle of array" << endl;
        Node* p = head;
        for (int i = 0; i < pos; i++)
            p = p->next;
        
        Node* n = new Node; //creates the inserted item
        n->m_value = value; //adding values
        n->prev = p;
        n->next = p->next;
        m_size++;
        return pos;
    }
    else if (pos == size())
    {
        cerr << "Inserting element " << value << " at end of array" << endl;
        Node* p = new Node; //creates the inserted item
        p-> m_value = value;
        p-> prev = tail;
        p-> next = nullptr;
        tail->next = p;
        tail = p;
        m_size++;
        return pos;
    }
    else
        return -1;
}

int Sequence::insert(const ItemType& value)
{
    int pos=0;
    Node* p = head;
    while( pos < size() )
    {
        if (p -> m_value > value)
        {
            break; // if valid value is spotted
        }
        pos++;
        p = p->next;
    }
    
    return insert(pos, value);
}

bool Sequence::erase(int pos)
{
    if (head == nullptr) {
        return false;
    }
    if ( pos == 0 && head -> next == nullptr)
    {
        head = nullptr;
        m_size--;
        return true;
    }
    else if (pos == 0)
    {
        Node *killMe = head; //removing head
        head = killMe -> next;
        head -> prev = nullptr;
        delete killMe;
        m_size--;
        return true;
    }
    else if (pos >0 && pos < size()-1 )
    {
        Node *killMe = head;
        for (int i = 0; i < pos; ++i)
        {
            killMe = killMe -> next;
        }
        killMe->prev = killMe -> next; //remove middle node
        delete killMe;
        m_size--;
        return true;
    }
    else if (pos == size()-1)
    {
        Node *killMe = tail;
        tail = killMe -> prev;
        tail -> next = nullptr;// remove tail
        delete killMe;
        m_size--;
        return true;
    }
    else
        return false;
}

int Sequence::remove(const ItemType& value)
{
    int count = 0;
    int pos=0;
    Node *p = head;
    while(pos<size())
    {
        if (p->m_value == value)
        {
            erase(pos);
            pos--;
            count++;
        }
        p = p->next;
        pos++;
    }
    
    return count;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (head == nullptr)
        return false;
    
    if (pos >=0 && pos < size() - 1)
    {
        Node *p = head;
        for (int i = 0; i < pos; ++i)
            p = p->next;
        if (p == nullptr)
        {
            cerr << "p is nullptr" << endl;
            return false;
        }
        value = p->m_value;
        return true;
    }
    else
        return false;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos >=0 && pos < size() )
    {
        Node *p = head;
        for (int i = 0; i < pos; ++i)
        {
            p = p-> next;
        }
        p->m_value = value;
        return true;
    }
    else
        return false;
}

int Sequence::find(const ItemType& value) const
{
    int pos=-1;
    int m_pos=0;
    Node *p = head;
    while(p->next != nullptr)
    {
        if (p->m_value == value)
        {
            pos = m_pos;
            break;
        }
        m_pos++;
    }
    
    return pos;
}
void Sequence::swap(Sequence& other)
{
    //swap Names of Linked Lists
    Node* p = head;
    Node* n = tail;
    
    head = other.head;
    tail = other.tail;
    other.head = p;
    other.tail = n;
    
    //swap m_size;
    int temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if (seq1.size() == 0 || seq2.size() == 0 || seq1.size() == 1 || seq2.size() == 1)
    {
        return -1;
    }
    ItemType value1, value2;
    for (int i = 0; i < seq2.size()-1; ++i)
    {
        seq1.get(i, value1);
        seq2.get(0, value2);
        if (value1 == value2) {
            for (int j = 0; j < seq1.size()-1; ++j)
            {
                seq1.get(i+j, value1);
                seq2.get(j, value2);
                if (value1 != value2)
                {
                    break;
                }
                if (j == seq2.size()-1) {
                    return i;
                }
            }
        }
            }
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    Sequence r1;
    int p1 = 0;
    int p2 = 0;
    ItemType value1, value2;
    
    if (seq1.size() == 0) //If seq1 is empty return seq2
        r1 = seq2;
    else if (seq2.size() == 0) //If seq2 is empty return seq1
        r1 = seq1;
    else
    {
        while(p1 < seq1.size() || p2 < seq2.size())
        {
            if (p2 < seq2.size())
            {
                seq2.get(p2, value2);
                r1.insert(p2, value2);
                p2++;
            }
            if (p1 < seq1.size())
            {
                seq1.get(p1, value1);
                r1.insert(p1, value1);
                p1++;
            }
        }
    }
    
    result = r1;
}
