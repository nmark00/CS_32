// #include <iostream>
// #include <string>
// #include <vector>

// using namespace std;

// class Domain
// {
//   public:
//     Domain(string lbl) : m_label(lbl) {}
//     string label() const { return m_label; }
//     const vector<Domain*>& subdomains() const { return m_subdomains; }
//     void add(Domain* d) { m_subdomains.push_back(d); }
//     ~Domain();
//   private:
//     string m_label;
//     vector<Domain*> m_subdomains;
// };

// Domain::~Domain()
// {
//     for (size_t k = 0; k < m_subdomains.size(); k++)
//         delete m_subdomains[k];
// }

void listAll(const Domain* d, string path) // two-parameter overload
{
    if (d->subdomains().size() == 0 && path == d->label())
    {
        cout << path << endl;
        return;
    }
    if (d->subdomains().size() == 0)
    {
        cout << d->label()  + path << endl;
        return;
    }

    vector<Domain*>::const_iterator it;
    for (it = d->subdomains().begin(); it != d->subdomains().end(); it++)
    {
        if (path != d->label())
        {
            listAll(*it, "." + d->label() +  path);
        }
        else if(path != "")
        {
            listAll(*it, "." + d->label());
        }
        else
            listAll(*it, d->label());
    }
}

// void listAll(const Domain* d)  // one-parameter overload
// {
//     if (d != nullptr)
//         listAll(d, d->label());
// }

// int main()
// {
//     Domain* d1 = new Domain("ucla");
//     d1->add(new Domain("cs"));
//     d1->add(new Domain("ee"));
//     d1->add(new Domain("math"));
//     Domain* d2 = new Domain("caltech");
//     d2->add(new Domain("math"));
//     d2->add(new Domain("cs"));
//     Domain* d3 = new Domain("edu");
//     d3->add(d1);
//     d3->add(d2);
//     Domain* d4 = new Domain("com");
//     d4->add(new Domain("microsoft"));
//     d4->add(new Domain("apple"));
//     Domain* d5 = new Domain("biz");
//     Domain* root = new Domain("");
//     root->add(d3);
//     root->add(d4);
//     root->add(d5);
//     listAll(root);
//     cout << "====" << endl;
//     listAll(d2);
//     cout << "====" << endl;
//     listAll(d5);
//     delete root;
// }
