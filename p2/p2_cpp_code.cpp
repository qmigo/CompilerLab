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
    ifstream myFile("p2_automata_txt.txt");
    string myText;
    vector<vector<int>> arr;
    while(getline(myFile, myText))
    {   
        arr.push_back(lineCleaner(myText));
    }
    
    return arr;
}

vector<int> MEALEY(vector<vector<int>> &arr, string &inp)
{
    int initState = arr[0][0];
    int cols = arr[1].size();
    int rows = arr.size();
    vector<vector<int>> transit(rows-1, vector<int> (cols/2,0)), outputs(rows-1, vector<int>(cols/2, 0));

    for(int i=1;i<rows;i++)
    {   
        int k=0, l=0;
        for(int j=0;j<cols;j++)
        {   
            if(j%2==0)
            transit[i-1][k++] = arr[i][j];
            else 
            outputs[i-1][l++] = arr[i][j];
        }
    } 

    int currState = initState;
    vector<int> res;
    cout<<"S1 ---(val)--- S2 ==> Output\n";
    for(int i=0;i<inp.size();i++)
    {
        if(currState==-1 || inp[i]-'0'>=transit[0].size() || outputs[currState][inp[i]-'0']==-1)break;
        cout<<currState<<" ---( "<<inp[i]<<" )---";
        int temp = outputs[currState][inp[i]-'0'];
        currState = transit[currState][inp[i]-'0'];
        cout<<currState<<" ==> "<<temp<<"\n";
    }
    return res;
}

int main()
{   
    vector<vector<int>> dfa = fileParser();
    while(1)
    {   
        cout<<"Enter String to run DFA on :\t";
        string inp;
        cin>>inp;
        
        vector<int> ans = MEALEY(dfa, inp);
        for(int j=0;j<ans.size();j++)cout<<ans[j]<<" ";
        cout<<"\n";
    }
}