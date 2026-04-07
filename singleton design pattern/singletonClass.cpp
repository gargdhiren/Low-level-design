#include <bits/stdc++.h>
using namespace std;

class Singleton
{
private:
    static Singleton *instance;
    Singleton()
    {
        cout << "Creating a singleton class" << endl;
    }

public:
    static Singleton *getInstance()
    {
        return instance;
    }
};

Singleton *Singleton::instance = new Singleton();

int main()
{
    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();
    cout << "Is the s1 and s2 same class" << ((s1 == s2)?" True":" False" )<< endl;
    return 0;
}