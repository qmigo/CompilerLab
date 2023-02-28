#include<bits/stdc++.h>
using namespace std;

map<string, vector<vector<string>>> nfa;
map<vector<string>, vector<vector<string>>> dfa;
string initState;
vector<string> finalStates;
vector<vector<string>> dfaFinalStates;
int inputSize=0;
map<vector<string>, int> vis;

bool isFinal(string &state)
{
    for(auto i:finalStates)if(i==state)return true;
    return false;
}

vector<string> stringToVector(string &res)
{
    vector<string> arr;
    int l=0;
    for(int i=0;i<res.size();i++)
    {
        if(res[i]==' ')
        {
            arr.push_back(res.substr(l,i-l));
            l=i+1;
        }
    }
    int n = res.size();
    arr.push_back(res.substr(l,n-l));
    return arr;
}
vector<vector<string>> splitHandler(string &str, string &key)
{   
    int itr=0;
    while(str[itr++]!=':');
    key = str.substr(0,itr-1);
    vector<vector<string>> big_temp;
    int l=itr;
    str+=" ";
    
    vector<string> small_temp;
    while(itr<str.size())
    {   
        if(str[itr]==',' || str[itr]==' ')
        {
            small_temp.push_back( str.substr(l,itr-l) );
            l=itr+1;
        }
        if(str[itr]==' ')
        {
            big_temp.push_back(small_temp);
            small_temp.clear();
        }
        itr++;
    }
    return big_temp;
}

void dfaConverter()
{
    queue<vector<string>> qu;
    string currState = initState;
    qu.push({currState});
    while(!qu.empty())
    {
        vector<string> stateHead = qu.front();
        qu.pop();
        for(int i=0;i<inputSize;i++)
        {       
            set<string> finalOutputs;
            for(int j=0;j<stateHead.size();j++)
            {
            vector<string> outputs = nfa[stateHead[j]][i];
            for(auto k:outputs)
            finalOutputs.insert(k);
            }
            vector<string> outputs_clean;
            for(auto i:finalOutputs)
            {
                if(i!="-1")outputs_clean.push_back(i);
            }
            if(outputs_clean.size()==0)outputs_clean.push_back("-1");
            dfa[stateHead].push_back(outputs_clean);
            vis[outputs_clean]++;
            if(outputs_clean[0]!="-1" and vis[outputs_clean]==1)
            qu.push(outputs_clean);
        }
    }

    for(auto it:dfa)
    {
        for(auto states:it.first)
        {
            if(isFinal(states))
            {
                dfaFinalStates.push_back(it.first);
                break;
            }
        }
    }
}

void fileReader()
{
    ifstream myFile("input.txt");
    string myText;
    int line = 0;

    while(getline(myFile,myText))
    {   
        if(line==0) initState=myText;
        else if(line==1) finalStates = stringToVector(myText);
        else
        {
            string key;
            vector<vector<string>> transits = splitHandler(myText, key); // key: state1,state2 state1,state2
            inputSize = transits.size();
            nfa[key] = transits;
        }
        line++;
    }
}

void writeDFA()
{   
    ofstream myFile("output.txt");

    myFile<<initState<<"\n";
    for(auto it:dfaFinalStates)
    {   
        
        for(auto j:it)
        myFile<<j;
        myFile<<" ";
    }
    myFile<<"\n";

    for(auto it:dfa)
    {   
        
        for(auto i:it.first)myFile<<i;
        myFile<<": ";
        for(auto i:it.second)
        {   
            
            for(auto j:i)
            myFile<<j;
            myFile<<" ";
        }
    myFile<<"\n";
    }
}

int main()
{
    fileReader();
    dfaConverter();
    writeDFA();
    
    cout<<"final states -> ";
    for(auto it:dfaFinalStates)
    {   
        cout<<"[";
        for(auto j:it)
        cout<<j<<",";
        cout<<"], ";
    }
    cout<<"\n";
    for(auto it:dfa)
    {   
        cout<<"[ ";
        for(auto i:it.first)cout<<i<<", ";
        cout<<"] -> ";
        for(auto i:it.second)
        {   
            cout<<"[";
            for(auto j:i)
            cout<<j<<",";
            cout<<"] ";
        }
    cout<<"\n";
    }
   
}