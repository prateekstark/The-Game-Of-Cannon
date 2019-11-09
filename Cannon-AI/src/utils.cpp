#include "../include/utils.h"
int otherPlayer(int player){
    return (3 - player);
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
    string result[6];
    string s = bad;
    istringstream iss(s);
    int i = 0;
    for(string s; iss >> s;){
        result[i] = s;
        i++;
    }
    string a;
    a = result[1];
    result[1] = result[2];
    result[2] = a;
    a = result[4];
    result[4] = result[5];
    result[5] = a;
    string answer = result[0] + " " + result[1] + " " + result[2] + " " + result[3] + " " + result[4] + " " + result[5];
    return answer;
}
