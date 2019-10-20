// #include <iostream>
// #include <string>
// using namespace std;

// enum CallType {
//     VOICE, TEXT
// };

//Your declarations and implementations would go here
class Medium
{
public:
    Medium(string id);
    virtual string connect() const=0;
    string id()  const;
    virtual string transmit(string msg) const;
    virtual ~Medium(){}
private:
    string m_id;
};
Medium::Medium(string id): m_id(id)
{}
string Medium::id() const
{return m_id;}
string Medium::transmit(string msg) const
{return "text: "+msg;}
// ============== TwitterAccount ==============
class TwitterAccount: public Medium
{
public:
    TwitterAccount(string id): Medium(id){};
    virtual string connect() const;
    //virtual string transmit(string msg) const;
    virtual ~TwitterAccount();
};
string TwitterAccount::connect() const
{return "Tweet";}
//string TwitterAccount::transmit(string msg) const
//{return "text: "+msg;}
TwitterAccount::~TwitterAccount()
{cout<<"Destroying the Twitter account "<< Medium::id()<<"."<<endl;}
// ================= Phone =================
class Phone: public Medium
{
public:
    Phone(string id, CallType calltype): Medium(id), m_calltype(calltype){};
    virtual string connect() const;
    virtual string transmit(string msg) const;
    virtual ~Phone();
private:
    CallType m_calltype;
};
string Phone::connect() const
{return "Call";}
string Phone::transmit(string msg) const{
    if (m_calltype == VOICE) {
        return "voice: "+msg;
    }
    else
        return Medium::transmit(msg);
}
Phone::~Phone(){
    cout<<"Destroying the phone "<<Medium::id()<<"."<<endl;
}
// ============== EmailAccount ==============
class EmailAccount: public Medium
{
public:
    EmailAccount(string id): Medium(id){};
    virtual string connect() const;
    //virtual string transmit(string msg) const;
    virtual ~EmailAccount();
};
string EmailAccount::connect() const
{return "Email";}
//string EmailAccount::transmit(string msg) const
//{return "text: "+msg;}
EmailAccount::~EmailAccount(){
    cout<<"Destroying the email account "<< Medium::id()<<"."<<endl;
    }

    
// void send(const Medium* m, string msg)
// {
//     cout << m->connect() << " using id " << m->id()
//     << ", sending " << m->transmit(msg) << endl;
// }

// int main()
// {
//     Medium* media[4];
//     media[0] = new TwitterAccount("UCLABruinAlert");
//     // Phone users may prefer messages to be left as voice or text.
//     media[1] = new Phone("(310) 825 3894", VOICE);
//     media[2] = new Phone("(213) 389 9060", TEXT);
//     media[3] = new EmailAccount("jbroon@ucla.edu");
    
//     cout << "Send the message." << endl;
//     for (int k = 0; k < 4; k++)
//         send(media[k], "Major power outage in West L.A.");
    
//     // Clean up the media before exiting
//     cout << "Cleaning up." << endl;
//     for (int k = 0; k < 4; k++)
//         delete media[k];
// }

//Output produced:
//
//Send the message.
//Tweet using id UCLABruinAlert, sending text: Major power outage in West L.A.
//Call using id (310) 825 3894, sending voice: Major power outage in West L.A.
//Call using id (213) 389 9060, sending text: Major power outage in West L.A.
//Email using id jbroon@ucla.edu, sending text: Major power outage in West L.A.
//Cleaning up.
//Destroying the Twitter account UCLABruinAlert.
//Destroying the phone (310) 825 3894.
//Destroying the phone (213) 389 9060.
//Destroying the email account jbroon@ucla.edu.


//You must not declare any struct or class other than Medium, TwitterAccount, Phone, and EmailAccount.
//The Medium class must not have a default constructor. The only constructor you may declare for Medium must have exactly one parameter. That parameter must be of type string, and it must be a useful parameter.
//Although the expression new Phone("(310) 825 3894",VOICE) is fine, the expression new Medium("ethel") must produce a compilation error. (A client can create a particular kind of medium, like a Phone, but is not allowed to create an object that is just a plain Medium.)
//Other than constructors and destructors (which can't be const), all member functions must be const member functions.
//No two functions with non-empty bodies may have the same implementation, or implementations that have the same effect for a caller. For example, there's a better way to deal with the id() function than to have each kind of medium declare and identically implement an id function. (Notice that { return "Shout"; } and { return "Telegraph"; } do not have the same effect, but { return "text"; } and { string s("tex"); return s + 't'; } have the same effect, which is to return "text".
//No implementation of an id() function may call any other function.
//No class may have a data member whose value is identical for every object of a particular class
//All data members must be declared private. You may declare member functions public or private. Your solution must not declare any protected members (which we're not covering in this class). Your solution must not contain the word friend.
