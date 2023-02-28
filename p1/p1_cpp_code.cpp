#include<bits/stdc++.h>
using namespace std;

vector<int> lineCleaner(string str)
{
    int l=0;
    vector<int> res;
    for(int r=0;r<str.size();r++)
    {
        if(str[r]==' ')
        {
            res.push_back(stoi(str.substr(l,r-l)));
            l=r+1;
        }
    }
    res.push_back(stoi(str.substr(l,str.size()-l)));
    return res;
}

vector<vector<int>> fileParser()
{
    ifstream myFile("p1_automata_txt.txt");
    string myText;
    vector<vector<int>> arr;
    while(getline(myFile, myText))
    {   
        arr.push_back(lineCleaner(myText));
    }
    
    return arr;
}

bool DFA(vector<vector<int>> &arr, string &inp)
{
    int initState = arr[0][0];
    vector<int> finalStates = arr[1];
    vector<vector<int>> transits;
    for(int i=2;i<arr.size();i++)transits.push_back(arr[i]);

    int currState = initState;
    for(int i=0;i<inp.size();i++)
    {   
        if(currState==-1 || inp[i]-'0'>=transits[0].size())return 0;
        cout<<currState<<" ---( "<<inp[i]<<" )--- ";
        currState = transits[currState][inp[i]-'0'];
        cout<<currState<<"\n";
    }
    for(int i=0;i<finalStates.size();i++)
    if(finalStates[i]==currState)return 1;
    return 0;
}

int main()
{   
    vector<vector<int>> dfa = fileParser();
    while(1)
    {   
        cout<<"Enter String to run DFA on :\t";
        string inp;
        cin>>inp;
        if(DFA(dfa,inp))
        cout<<"SUCCESS\n";
        else
        cout<<"FAIL\n";
    }
}