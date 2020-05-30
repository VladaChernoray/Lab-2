#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct PJegalkin
{    
    vector<vector<int>> items{};
    bool a00{};
    int imax{-1};

    bool execute( const vector<bool>& input )
    {
        bool res = a00;

        for(auto& item : items)
        {
            bool v = true;

            for(int i : item)
            {
                if(i < 0 || i >= input.size())
                    throw "Jegalkin execution error!";
                
                //v &= input[imax - i]; // just to be able to compare with WIKI
                v &= input[i];
            }
            
            res ^= v;
        }

        return res;
    }
};

istream& operator >> ( istream& in, PJegalkin& poly )
{
    poly.items.clear();
    poly.a00 = false;
    string str;

    while(getline( in, str ))
    {
        stringstream sstream{str};

        vector<int> item{};
        int i;

        while(sstream >> i)
        {
            if(i < 0)
            {
                poly.a00 = true;
                break;
            }

            if(i > poly.imax)
                poly.imax = i;

            item.push_back(i);
        }

        poly.items.push_back(item);
    }

    return in;
}

bool increase( vector<bool>& arg )
{    
    int i = 0;
    while(i < arg.size())
    {
        if(arg[i])
        {
            arg[i] = 0;
            i++;
        }
        else
        {
            arg[i] = 1;
            return false;
        }
    }
    return true;
}

void printValueTable( PJegalkin& poly )
{
    vector<bool> arg;
    arg.resize(poly.imax + 1);
   
    do
    {
        bool r = poly.execute(arg);
        for(bool b : arg)
            cout<<b;
        cout<<"\t:\t"<<r<<endl;
        
    }while( !increase( arg ) );    
}

int main()
{
    ifstream in("in.txt");

    PJegalkin poly;
    in>>poly;
    printValueTable(poly);
    
    cin.get();
    return 0;
}

