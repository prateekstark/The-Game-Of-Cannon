#include<bits/stdc++.h>
#include<chrono>
#include<fstream>
using namespace std::chrono;
using namespace std;

int otherPlayer(int player){
    if(player == 1){
        return 2;
    }
    return 1;
}

void printState(vector<vector<int> > myState){
    for(int i=0;i<myState.size();i++){
        for(int j=0;j<myState.at(0).size();j++){
            cout<<myState.at(i).at(j)<<" ";
        }
        cout<<endl;
    }
}

string string_to_good_string(string bad){
    vector<string> result;
    string s = bad;
    istringstream iss(s);
    for(string s; iss >> s;){
        result.push_back(s);
    }
    string a;
    a = result.at(1);
    result[1] = result[2];
    result[2] = a;
    a = result.at(4);
    result.at(4) = result.at(5);
    result.at(5) = a;
    string answer = result[0] + " " + result[1] + " " + result[2] + " " + result[3] + " " + result[4] + " " + result[5];
    return answer;
}
