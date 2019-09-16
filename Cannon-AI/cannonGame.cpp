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


class CannonGame{
public:
    vector<vector<int> > board;
    vector<int> coefficients;
    CannonGame(){
        vector<int> tempVector1({1, 10, 1, 10, 1, 10, 1, 10});
        vector<int> tempVector2({1, 0, 1, 0, 1, 0, 1, 0});
        vector<int> tempVector3({0, 0, 0, 0, 0, 0, 0, 0});
        vector<int> tempVector4({20, 2, 20, 2, 20, 2, 20, 2});
        vector<int> tempVector5({0, 2, 0, 2, 0, 2, 0, 2});
        vector<int> tempVector6({2, 2, 2, 0, 0, 0, 0, 10});
        vector<int> tempVector7({20, 0, 0, 0, 0, 1, 1, 1});

        for(int i=0;i<4;i++){
            board.push_back(tempVector7);
            board.push_back(tempVector6);
        }
        for(int i=0;i<6;i++){
            coefficients.push_back(1);
            coefficients.push_back(-1);
        }
    }

    bool areTwoMatrixEqual(vector<vector<int> > v1, vector<vector<int> > v2){
        if(v1.size() != v2.size() || v1.at(0).size() != v2.at(0).size()){
            return false;
        }
        for(int i=0;i<v1.size();i++){
            for(int j=0;j<v1.at(0).size();j++){
                if(v1.at(i).at(j) != v2.at(i).at(j)){
                    return false;
                }
            }
        }
        return true;
    }

    vector<string> convertStringToVector(string str){
        vector<string> answer;
        istringstream ss(str);
        do{
            string word;
            ss >> word;
            answer.push_back(word);
        }while(ss);
        answer.pop_back();
        return answer;
    }
    vector<vector<int> > executeMove(vector<string> moveVector, vector<vector<int> > myState){
        string S_string = "S";
        string M_string = "M";
        string B_string = "B";
        vector<vector<int> > tempState(myState);
        if(moveVector.size() == 6){
            if(moveVector.at(0).compare(S_string) == 0){
                if(moveVector.at(3).compare(M_string) == 0){
                    int ini_pos_x = stoi(moveVector.at(1));
                    int ini_pos_y = stoi(moveVector.at(2));
                    int fin_pos_x = stoi(moveVector.at(4));
                    int fin_pos_y = stoi(moveVector.at(5));
                    tempState.at(fin_pos_x).at(fin_pos_y) = tempState.at(ini_pos_x).at(ini_pos_y);
                    tempState.at(ini_pos_x).at(ini_pos_y) = 0;
                }
                if(moveVector.at(3).compare(B_string) == 0){
                    int fin_pos_x = stoi(moveVector.at(4));
                    int fin_pos_y = stoi(moveVector.at(5));
                    tempState.at(fin_pos_x).at(fin_pos_y) = 0;
                }
            }
        }
        else{
            cerr<<"Wrong State";
        }
        // printState(tempState);
        return tempState;
    }

    bool doesSpaceContainPlane(vector<vector<vector<int> > > space, vector<vector<int> > plane){
        for(int i=0;i<space.size();i++){
            if(areTwoMatrixEqual(space.at(i), plane)){
                return true;
            }
        }
        return false;
    }

    vector<vector<vector<int> > > generateSteps(vector<string> &genStringMoves, int player, vector<vector<int> > myState){
        // cout<<"ghusa>"<<endl;
        vector<vector<vector<int> > > allStates;
        // cout<<"ghusa1"<<endl;
        vector<vector<int> > child;
        vector<string> possibleMoves1 = validMoves(player, myState);
        // cout<<"ghusa2"<<endl;
        for(int i=0;i<possibleMoves1.size();i++){
            // cout<<"ghusa3"<<endl;
            child = executeMove(convertStringToVector(possibleMoves1.at(i)), myState);
            // cout<<"ghusa4"<<endl;
            if(!doesSpaceContainPlane(allStates, child)){
                // cout<<"ghusa5"<<endl;
                allStates.push_back(child);
                genStringMoves.push_back(possibleMoves1.at(i));
            }
            // cout<<"ghusa6"<<endl;
            child.clear();
        }

        // return allStates;
        // cout<<"pkmkb1"<<endl;
        vector<string> possibleMoves2 = validCannonMoves(player, myState);
        // cout<<"pkmkb2"<<endl;
        for(int i=0;i<possibleMoves2.size();i++){
            // cout<<"pkmkb3"<<endl;
            child = executeMove(convertStringToVector(possibleMoves2.at(i)), myState);
            // cout<<"pkmkb4"<<endl;
            if(!doesSpaceContainPlane(allStates, child)){
                // cout<<"pkmkb5"<<endl;
                allStates.push_back(child);
                genStringMoves.push_back(possibleMoves2.at(i));
            }
            child.clear();
            // cout<<"pkmkb6"<<endl;
        }
        return allStates;
    }

    bool canSoldierBeAttacked(int x, int y, int player, vector<vector<int> > myState){
        if(myState.at(x).at(y) != player){
            // cerr<<"Wrong player!"<<endl;
            return false;
        }
        int n = myState.size();
        int m = myState.at(0).size();
        //board is a 2D vector of size n*m
        if(player == 2){
            if(y+1 < m){
                if(myState[x][y+1] == 1){
                    return true;
                }
            }

            if(x+1 < n && y+1 < m){
                if(myState[x+1][y+1] == 1){
                    return true;
                }
            }

            if(x-1 >= 0 && y+1 < m){
                if(myState.at(x-1).at(y+1) == 1){
    				return true;
    			}
            }

            if(x+1 < n){
                if(myState.at(x+1).at(y) == 1){
    				return true;
    			}
            }

            if(x-1 >= 0){
                if(myState.at(x-1).at(y) == 1){
    				return true;
    			}
            }

            if(y+3<m){
                if(isSoldierLeadOfCannon(x, y+3, 1, myState)){
                    return true;
                }
                if(x+3 < n){
                    if(isSoldierLeadOfCannon(x+3, y+3, 1, myState)){
                        return true;
                    }
                }
                if(x-3 >= 0){
                    if(isSoldierLeadOfCannon(x-3, y+3, 1, myState)){
                        return true;
                    }
                }
            }
            if(y+2<m){
                if(isSoldierLeadOfCannon(x, y+2, 1, myState)){
                    return true;
                }
                if(x+2 < n){
                    if(isSoldierLeadOfCannon(x+2, y+2, 1, myState)){
                        return true;
                    }
                }
                if(x-2 >= 0){
                    if(isSoldierLeadOfCannon(x-2, y+2, 1, myState)){
                        return true;
                    }
                }
            }
            if(y-3 >= 0){
                if(isSoldierLeadOfCannon(x, y-3, 1, myState)){
                    return true;
                }
                if(x+3 < n){
                    if(isSoldierLeadOfCannon(x+3, y-3, 1, myState)){
                        return true;
                    }
                }
                if(x-3 >= 0){
                    if(isSoldierLeadOfCannon(x-3, y-3, 1, myState)){
                        return true;
                    }
                }
            }
            if(y-2 >= 0){
                if(isSoldierLeadOfCannon(x, y-2, 1, myState)){
                    return true;
                }
                if(x+2 < n){
                    if(isSoldierLeadOfCannon(x+2, y-2, 1, myState)){
                        return true;
                    }
                }
                if(x-2 >= 0){
                    if(isSoldierLeadOfCannon(x-2, y-2, 1, myState)){
                        return true;
                    }
                }
            }
        }
        if(player == 1){
            if(y-1 >= 0){
                if(myState[x][y-1] == 2){
                    return true;
                }
            }

            if(x+1 < n && y-1 >= 0){
                if(myState[x+1][y-1] == 2){
                    return true;
                }
            }

            if(x-1 >= 0 && y-1 >= 0){
                if(myState.at(x-1).at(y-1) == 2){
                    return true;
                }
            }

            if(x+1 < n){
                if(myState.at(x+1).at(y) == 2){
                    return true;
                }
            }

            if(x-1 >= 0){
                if(myState.at(x-1).at(y) == 2){
                    return true;
                }
            }

            if(y+3<m){
                if(isSoldierLeadOfCannon(x, y+3, 2, myState)){
                    return true;
                }
                if(x+3 < n){
                    if(isSoldierLeadOfCannon(x+3, y+3, 2, myState)){
                        return true;
                    }
                }
                if(x-3 >= 0){
                    if(isSoldierLeadOfCannon(x-3, y+3, 2, myState)){
                        return true;
                    }
                }
            }
            if(y+2<m){
                if(isSoldierLeadOfCannon(x, y+2, 2, myState)){
                    return true;
                }
                if(x+2 < n){
                    if(isSoldierLeadOfCannon(x+2, y+2, 2, myState)){
                        return true;
                    }
                }
                if(x-2 >= 0){
                    if(isSoldierLeadOfCannon(x-2, y+2, 2, myState)){
                        return true;
                    }
                }
            }
            if(y-3 >= 0){
                if(isSoldierLeadOfCannon(x, y-3, 2, myState)){
                    return true;
                }
                if(x+3 < n){
                    if(isSoldierLeadOfCannon(x+3, y-3, 2, myState)){
                        return true;
                    }
                }
                if(x-3 >= 0){
                    if(isSoldierLeadOfCannon(x-3, y-3, 2, myState)){
                        return true;
                    }
                }
            }
            if(y-2 >= 0){
                if(isSoldierLeadOfCannon(x, y-2, 2, myState)){
                    return true;
                }
                if(x+2 < n){
                    if(isSoldierLeadOfCannon(x+2, y-2, 2, myState)){
                        return true;
                    }
                }
                if(x-2 >= 0){
                    if(isSoldierLeadOfCannon(x-2, y-2, 2, myState)){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    int numberOfSoldierCanbeAttacked(int player, vector<vector<int> > myState){
        int n = myState.size();
        int m = myState.at(0).size();
        int count = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(canSoldierBeAttacked(i, j, player, myState)){
                    count++;
                }
            }
        }
        return count;
    }

    int numberOfSoldiers(int player, vector<vector<int> > myState){
        int count = 0;
        for(int i=0;i<myState.size();i++){
            for(int j=0;j<myState.at(0).size();j++){
                if(myState.at(i).at(j) == player){
                    count++;
                }
            }
        }
    }

    int numberOfTownHall(int player, vector<vector<int> > myState){
        int count = 0;
        for(int i=0;i<myState.size();i++){
            for(int j=0;j<myState.at(0).size();j++){
                if(myState.at(i).at(j) == player*10){
                    count++;
                }
            }
        }
        return count;
    }

    int numberOfCannon(int player, vector<vector<int> > myState){
        int count = 0;
        for(int i=0;i<myState.size();i++){
            for(int j=0;j<myState.at(0).size();j++){
                if(isSoldierLeadOfCannon(i, j, player, myState)){
                    count++;
                }
            }
        }
        return count;
    }

    int closenessFactor(int player, vector<vector<int> > myState){
        int count = 0;
        int n = myState.size();
        if(player == 1){
            for(int i=0;i<myState.size();i++){
                for(int j=0;j<myState.size();j++){
                    if(myState.at(i).at(j) == player){
                        count = count + i;
                    }
                }
            }
        }
        if(player == 2){
            for(int i=0;i<myState.size();i++){
                for(int j=0;j<myState.at(0).size();j++){
                    if(myState.at(i).at(j) == player){
                        count = count + (n-i-1);
                    }
                }
            }
        }
        return count;
    }

    bool canTownHallCanBeAttacked(int x, int y, int player, vector<vector<int> > myState){
        if(myState.at(x).at(y) != player*10){
            return false;
        }
        int n = myState.size();
        int m = myState.at(0).size();
        if(player == 2){
            if(y+1 < m){
                if(myState[x][y+1] == 1){
                    return true;
                }
            }

            if(x+1 < n && y+1 < m){
                if(myState[x+1][y+1] == 1){
                    return true;
                }
            }

            if(x-1 >= 0 && y+1 < m){
                if(myState.at(x-1).at(y+1) == 1){
                    return true;
                }
            }

            if(x+1 < n){
                if(myState.at(x+1).at(y) == 1){
                    return true;
                }
            }

            if(x-1 >= 0){
                if(myState.at(x-1).at(y) == 1){
                    return true;
                }
            }

            if(y+3<m){
                if(isSoldierLeadOfCannon(x, y+3, 1, myState)){
                    return true;
                }
                if(x+3 < n){
                    if(isSoldierLeadOfCannon(x+3, y+3, 1, myState)){
                        return true;
                    }
                }
                if(x-3 >= 0){
                    if(isSoldierLeadOfCannon(x-3, y+3, 1, myState)){
                        return true;
                    }
                }
            }
            if(y+2<m){
                if(isSoldierLeadOfCannon(x, y+2, 1, myState)){
                    return true;
                }
                if(x+2 < n){
                    if(isSoldierLeadOfCannon(x+2, y+2, 1, myState)){
                        return true;
                    }
                }
                if(x-2 >= 0){
                    if(isSoldierLeadOfCannon(x-2, y+2, 1, myState)){
                        return true;
                    }
                }
            }
            if(y-3 >= 0){
                if(isSoldierLeadOfCannon(x, y-3, 1, myState)){
                    return true;
                }
                if(x+3 < n){
                    if(isSoldierLeadOfCannon(x+3, y-3, 1, myState)){
                        return true;
                    }
                }
                if(x-3 >= 0){
                    if(isSoldierLeadOfCannon(x-3, y-3, 1, myState)){
                        return true;
                    }
                }
            }
            if(y-2 >= 0){
                if(isSoldierLeadOfCannon(x, y-2, 1, myState)){
                    return true;
                }
                if(x+2 < n){
                    if(isSoldierLeadOfCannon(x+2, y-2, 1, myState)){
                        return true;
                    }
                }
                if(x-2 >= 0){
                    if(isSoldierLeadOfCannon(x-2, y-2, 1, myState)){
                        return true;
                    }
                }
            }
        }
        if(player == 1){
            if(y-1 >= 0){
                if(myState[x][y-1] == 2){
                    return true;
                }
            }

            if(x+1 < n && y-1 >= 0){
                if(myState[x+1][y-1] == 2){
                    return true;
                }
            }

            if(x-1 >= 0 && y-1 >= 0){
                if(myState.at(x-1).at(y-1) == 2){
                    return true;
                }
            }

            if(x+1 < n){
                if(myState.at(x+1).at(y) == 2){
                    return true;
                }
            }

            if(x-1 >= 0){
                if(myState.at(x-1).at(y) == 2){
                    return true;
                }
            }

            if(y+3<m){
                if(isSoldierLeadOfCannon(x, y+3, 2, myState)){
                    return true;
                }
                if(x+3 < n){
                    if(isSoldierLeadOfCannon(x+3, y+3, 2, myState)){
                        return true;
                    }
                }
                if(x-3 >= 0){
                    if(isSoldierLeadOfCannon(x-3, y+3, 2, myState)){
                        return true;
                    }
                }
            }
            if(y+2<m){
                if(isSoldierLeadOfCannon(x, y+2, 2, myState)){
                    return true;
                }
                if(x+2 < n){
                    if(isSoldierLeadOfCannon(x+2, y+2, 2, myState)){
                        return true;
                    }
                }
                if(x-2 >= 0){
                    if(isSoldierLeadOfCannon(x-2, y+2, 2, myState)){
                        return true;
                    }
                }
            }
            if(y-3 >= 0){
                if(isSoldierLeadOfCannon(x, y-3, 2, myState)){
                    return true;
                }
                if(x+3 < n){
                    if(isSoldierLeadOfCannon(x+3, y-3, 2, myState)){
                        return true;
                    }
                }
                if(x-3 >= 0){
                    if(isSoldierLeadOfCannon(x-3, y-3, 2, myState)){
                        return true;
                    }
                }
            }
            if(y-2 >= 0){
                if(isSoldierLeadOfCannon(x, y-2, 2, myState)){
                    return true;
                }
                if(x+2 < n){
                    if(isSoldierLeadOfCannon(x+2, y-2, 2, myState)){
                        return true;
                    }
                }
                if(x-2 >= 0){
                    if(isSoldierLeadOfCannon(x-2, y-2, 2, myState)){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    int numberOfTownHallCanBeAttacked(int player, vector<vector<int> > myState){
        int count = 0;
        for(int i=0;i<myState.size();i++){
            for(int j=0;j<myState.size();j++){
                if(canTownHallCanBeAttacked(i, j, player, myState)){
                    count++;
                }
            }
        }
        return count;
    }

    int evaluationFunction(vector<vector<int> > myState){
        int answer = coefficients.at(0)*numberOfSoldierCanbeAttacked(1, myState) + coefficients.at(1)*numberOfSoldierCanbeAttacked(2, myState) + coefficients.at(2)*numberOfSoldiers(1, myState) + coefficients.at(3)*numberOfSoldiers(2, myState);
        answer = answer + coefficients.at(4)*numberOfTownHall(1, myState) + coefficients.at(5)*numberOfTownHall(2, myState) + coefficients.at(6)*numberOfCannon(1, myState) + coefficients.at(7)*numberOfCannon(2, myState);
        answer = answer + coefficients.at(8)*closenessFactor(1, myState) + coefficients.at(9)*closenessFactor(2, myState) + coefficients.at(10)*numberOfTownHallCanBeAttacked(1, myState) + coefficients.at(11)*numberOfTownHallCanBeAttacked(2, myState);
        return answer;
    }

    bool isSoldierLeadOfCannon(int x, int y, int player, vector<vector<int> > myState){
        int n = myState.size();
        int m = myState.at(0).size();
        if(myState.at(x).at(y) == player){
            if(player == 2){
                if(y-2 >= 0){
                    if(myState.at(x).at(y-1) == 2 && myState.at(x).at(y-2) == 2){
    					return true;
    				}
                    if(x-2 >= 0){
                        if(myState.at(x-1).at(y-1) == 2 && myState.at(x-2).at(y-2) == 2){
        					return true;
        				}
                    }
                    if(x+2 < n){
                        if(myState.at(x+1).at(y-1) == 2 && myState.at(x+2).at(y-2) == 2){
        					return true;
        				}
                    }
                }
            }
            if(player == 1){
                if(y+2 < m){
                    if(myState.at(x).at(y+1) == 1 && myState.at(x).at(y+2) == 1){
    					return true;
    				}
                    if(x-2 >= 0){
                        if(myState.at(x-1).at(y+1) == 1 && myState.at(x-2).at(y+2) == 1){
        					return true;
        				}
                    }
                    if(x+2 < n){
                        if(myState.at(x+1).at(y+1) == 1 && myState.at(x+2).at(y+2) == 1){
        					return true;
        				}
                    }
                }
            }
        }
        return false;
    }


    vector<string> validMoves(int player, vector<vector<int> > myState){
        vector<string> moves;
        int n = myState.size();
        int m = myState.at(0).size();
        bool soldierCondition;
        string move;

        if(player == 2){
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    if(myState.at(i).at(j) == 2){
                        soldierCondition = canSoldierBeAttacked(i, j, 2, myState);
                        if(soldierCondition){
                            if(j-2 >= 0){
                                if(myState.at(i).at(j-2) != 2 && myState.at(i).at(j-2) != 20){
    								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j-2);
    								moves.push_back(move);
    							}
                                if(i-2 >= 0){
                                    if(myState.at(i-2).at(j-2) != 2 && myState.at(i-2).at(j-2) != 20){
        								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-2) + " " + to_string(j-2);
        								moves.push_back(move);
        							}
                                }
                                if(i+2 < n){
                                    if(myState.at(i+2).at(j-2) != 2 && myState.at(i+2).at(j-2) != 20){
        								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+2) + " " + to_string(j-2);
        								moves.push_back(move);
        							}
                                }
                            }
                        }
                        if(i+1 < n){
                            if(myState.at(i+1).at(j) == 1 || myState.at(i+1).at(j) == 10){
    							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j);
    							moves.push_back(move);
    						}
                            if(j+1 < m){
                                if(myState.at(i+1).at(j+1) != 2 && myState.at(i+1).at(j+1) != 20){
        							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j+1);
        							moves.push_back(move);
        						}
                            }
                        }
                        if(i-1 >= 0){
                            if(myState.at(i-1).at(j) == 1 || myState.at(i-1).at(j) == 10){
    							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-1) + " " + to_string(j);
    							moves.push_back(move);
    						}
                            if(j+1 < m){
                                if(myState.at(i-1).at(j+1) != 2 && myState.at(i-1).at(j+1) != 20){
        							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-1) + " " + to_string(j+1);
        							moves.push_back(move);
        						}
                            }
                        }
                        if(j+1 < m){
                            if(myState.at(i).at(j+1) != 2 && myState.at(i).at(j+1) != 20){
    							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j+1);
    							moves.push_back(move);
    						}
                        }
                    }
                }
            }
        }

        if(player == 1){
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    if(myState.at(i).at(j) == 1){
                        // cout<<"baweja"<<endl;
                        soldierCondition = canSoldierBeAttacked(i, j, 1, myState);
                        // cout<<"baweja1"<<endl;
                        if(soldierCondition){
                            if(j+2 <m){
                                // cout<<"baweja2"<<endl;
                                if(myState.at(i).at(j+2) != 1 && myState.at(i).at(j+2) != 10){
    								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j+2);
    								moves.push_back(move);
    							}
                                if(i-2 >= 0){
                                    // cout<<"baweja3"<<endl;
                                    if(myState.at(i-2).at(j+2) != 1 && myState.at(i-2).at(j+2) != 10){
        								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-2) + " " + to_string(j+2);
        								moves.push_back(move);
        							}
                                }
                                if(i+2 < n){
                                    // cout<<"baweja4"<<endl;
                                    if(myState.at(i+2).at(j+2) != 1 && myState.at(i+2).at(j+2) != 10){
        								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+2) + " " + to_string(j+2);
        								moves.push_back(move);
        							}
                                }
                            }
                        }
                        if(i+1 < n){
                            // cout<<"baweja5"<<endl;
                            if(myState.at(i+1).at(j) == 2 || myState.at(i+1).at(j) == 20){
    							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j);
    							moves.push_back(move);
    						}
                            if(j-1 >= 0){
                                // cout<<"baweja6"<<endl;
                                if(myState.at(i+1).at(j-1) != 1 && myState.at(i+1).at(j-1) != 10){
        							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j-1);
        							moves.push_back(move);
        						}
                            }
                        }
                        if(i-1 >= 0){
                            // cout<<"baweja7"<<endl;
                            if(myState.at(i-1).at(j) == 2 || myState.at(i-1).at(j) == 20){
    							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-1) + " " + to_string(j);
    							moves.push_back(move);
    						}
                            if(j-1 < m){
                                // cout<<"baweja8"<<endl;
        							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-1) + " " + to_string(j-1);
                                    if(myState.at(i-1).at(j-1) != 1 && myState.at(i-1).at(j) == 10){
        							moves.push_back(move);
        						}
                            }
                        }
                        if(j-1 < m){
                            // cout<<"baweja9"<<endl;
                            if(myState.at(i).at(j-1) != 1 && myState.at(i).at(j-1) != 10){
    							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j-1);
    							moves.push_back(move);
    						}
                        }
                    }
                }
            }
        }
        return moves;
    }

    vector<string> validCannonMoves(int player, vector<vector<int> > myState){
        vector<string> moves;
        int n = myState.size();
        int m = myState.at(0).size();
        string move = "";
        if(player == 1){
            // cout<<"sona100"<<endl;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    // cout<<"sona1"<<endl;
                    if(isSoldierLeadOfCannon(i, j, 1, myState)){
                        // cout<<"sona2"<<endl;
                        if(j+2 < m){
                            // cout<<"sona3"<<endl;
                            if(myState.at(i).at(j+1) == 1 && myState.at(i).at(j+2) == 1){
                                // cout<<"sona4"<<endl;
                                if(j+3 < m){
                                    if(myState.at(i).at(j+3) == 0){
        								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j+3);
        								moves.push_back(move);
        							}
                                }
                                // cout<<"sona5"<<endl;
                                if(j-1 >= 0){
                                    if(myState.at(i).at(j-1) == 0){
        								move = "S " + to_string(i) + " " + to_string(j+2) + " M " + to_string(i) + " " + to_string(j-1);
        								moves.push_back(move);
        							}
                                }
                                // cout<<"sona6"<<endl;
                                if(j-2 >= 0){
                                    if(myState.at(i).at(j-2) != player){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-2);
            							moves.push_back(move);
                                    }
                                }
                                if(j-3 >= 0){
                                    if(myState.at(i).at(j-3) != player){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-3);
            							moves.push_back(move);
                                    }
                                }
                                if(j+4 < m){
                                    if(myState.at(i).at(j+4) != player){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+4);
            							moves.push_back(move);
                                    }
                                }
                                if(j+5 < m){
                                    if(myState.at(i).at(j+5)){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+5);
            							moves.push_back(move);
                                    }
                                }
                            }

                            if(i-2 >= 0 && j+2 < m){
                                if(myState.at(i-1).at(j+1) == 1 && myState.at(i-2).at(j+2) == 1){
                                    if(i-3 >= 0 && j+3 < m){
                                        if(myState.at(i-3).at(j+3) == 0){
            								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-3) + " " + to_string(j+3);
            								moves.push_back(move);
            							}
                                    }
                                    if(i+1 < n && j-1 >= 0){
                                        if(myState.at(i+1).at(j-1) == 0){
            								move = "S " + to_string(i-2) + " " + to_string(j+2) + " M " + to_string(i+1) + " " + to_string(j-1);
            								moves.push_back(move);
            							}
                                    }
                                    if(j-2 >= 0 && i+2 < n){
                                        if(myState.at(i+2).at(j-2) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+2) + " " + to_string(j-2);
                							moves.push_back(move);
                                        }
                                    }
                                    if(j-3 >= 0 && i+3 < n){
                                        if(myState.at(i+3).at(j-3) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+3) + " " + to_string(j-3);
                							moves.push_back(move);
                                        }
                                    }
                                    if(j+4 < m && i-4 >= 0){
                                        if(myState.at(i-4).at(j+4) != player)
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-4) + " " + to_string(j+4);
            							moves.push_back(move);
                                    }
                                    if(j+5 < m && i-5 >= 0){
                                        if(myState.at(i-5).at(j+5) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-5) + " " + to_string(j+5);
                							moves.push_back(move);
                                        }
                                    }
                                }
                            }
                            if(i+2 < n && j+2 < m){
                                if(myState.at(i+1).at(j+1) == 1 && myState.at(i+2).at(j+2) == 1){
                                    if(i+3 < n && j+3 <m){
                                        if(myState.at(i+3).at(j+3) == 0){
            								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+3) + " " + to_string(j+3);
            								moves.push_back(move);
            							}
                                    }
                                    if(i-1 >= 0 && j-1 >= 0){
                                        if(myState.at(i-1).at(j-1) == 0){
            								move = "S " + to_string(i+2) + " " + to_string(j+2) + " M " + to_string(i-1) + " " + to_string(j-1);
            								moves.push_back(move);
            							}
                                    }
                                    if(j-2 >= 0 && i-2 >= 0){
                                        if(myState.at(i-2).at(j-2) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-2) + " " + to_string(j-2);
                							moves.push_back(move);
                                        }
                                    }
                                    if(j-3 >= 0 && i-3 >= 0){
                                        if(myState.at(i-3).at(j-3) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-3) + " " + to_string(j-3);
                							moves.push_back(move);
                                        }
                                    }
                                    if(j+4 < m && i+4 < n){
                                        if(myState.at(i+4).at(j+4) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+4) + " " + to_string(j+4);
                							moves.push_back(move);
                                        }
                                    }
                                    if(j+5 < m && i+5 < n){
                                        if(myState.at(i+5).at(j+5) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+5) + " " + to_string(j+5);
                							moves.push_back(move);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if(player == 2){
            // cout<<"sona101"<<endl;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    // cout<<"sona2"<<endl;
                    if(isSoldierLeadOfCannon(i, j, 2, myState)){
                        // cout<<"sona3"<<endl;
                        if(j-2 >= 0){
                            // cout<<"sona4"<<endl;
                            if(myState.at(i).at(j-1) == 2 && myState.at(i).at(j-2) == 2){
                                if(j-3 >= 0){
                                    if(myState.at(i).at(j-3) == 0){
        								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j-3);
        								moves.push_back(move);
        							}
                                }
                                // cout<<"sona5"<<endl;
                                if(j+1 < m){
                                    if(myState.at(i).at(j+1) == 0){
        								move = "S " + to_string(i) + " " + to_string(j-2) + " M " + to_string(i) + " " + to_string(j+1);
        								moves.push_back(move);
        							}
                                }
                                // cout<<"sona6"<<endl;
                                if(j+2 < m){
                                    if(myState.at(i).at(j+2) != player){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+2);
            							moves.push_back(move);
                                    }
                                }
                                // cout<<"sona7"<<endl;
                                if(j+3 < m){
                                    if(myState.at(i).at(j+3) != player){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+3);
            							moves.push_back(move);
                                    }
                                }
                                // cout<<"sona8"<<endl;
                                if(j-4 >= 0){
                                    if(myState.at(i).at(j-4) != player){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-4);
            							moves.push_back(move);
                                    }
                                }
                                // cout<<"sona9"<<endl;
                                if(j-5 >= 0){
                                    if(myState.at(i).at(j-5) != player){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-5);
            							moves.push_back(move);
                                    }
                                }
                            }
                            // cout<<"sona10"<<endl;
                            if(i-2 >= 0 && j-2 >= 0){
                                if(myState.at(i-1).at(j-1) == 2 && myState.at(i-2).at(j-2) == 2){
                                    if(i-3 >= 0 && j-3 >= 0){
                                        if(myState.at(i-3).at(j-3) == 0){
            								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-3) + " " + to_string(j-3);
            								moves.push_back(move);
            							}
                                    }
                                    // cout<<"sona11"<<endl;
                                    if(i+1 < n && j+1 < m){
                                        if(myState.at(i+1).at(j+1) == 0){
            								move = "S " + to_string(i-2) + " " + to_string(j-2) + " M " + to_string(i+1) + " " + to_string(j+1);
            								moves.push_back(move);
            							}
                                    }
                                    // cout<<"sona12"<<endl;
                                    if(j+2 < m && i+2 < n){
                                        if(myState.at(i+2).at(j+2) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+2) + " " + to_string(j+2);
                							moves.push_back(move);
                                        }
                                    }
                                    // cout<<"sona13"<<endl;
                                    if(j+3 < m && i+3 < n){
                                        if(myState.at(i+3).at(j+3) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+3) + " " + to_string(j+3);
                							moves.push_back(move);
                                        }
                                    }
                                    // cout<<"sona14"<<endl;
                                    if(j-4 >= 0 && i-4 >= 0){
                                        if(myState.at(i-4).at(j-4) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-4) + " " + to_string(j-4);
                							moves.push_back(move);
                                        }
                                    }
                                    // cout<<"sona15"<<endl;
                                    if(j-5 >= 0 && i-5 >= 0){
                                        if(myState.at(i-5).at(j-5) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-5) + " " + to_string(j-5);
                							moves.push_back(move);
                                        }
                                    }
                                }
                            }
                            if(i+2 < n && j-2 >= 0){
                                if(myState.at(i+1).at(j-1) == 2 && myState.at(i+2).at(j-2) == 2){
                                    if(i+3 < n && j-3 >= 0){
                                        if(myState.at(i+3).at(j-3) == 0){
            								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+3) + " " + to_string(j-3);
            								moves.push_back(move);
            							}
                                    }
                                    if(i-1 >= 0 && j+1 < m){
                                        if(myState.at(i-1).at(j+1) == 0){
            								move = "S " + to_string(i+2) + " " + to_string(j-2) + " M " + to_string(i-1) + " " + to_string(j+1);
            								moves.push_back(move);
            							}
                                    }
                                    if(j+2 < m && i-2 >= 0){
                                        if(myState.at(i-2).at(j+2) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-2) + " " + to_string(j+2);
                							moves.push_back(move);
                                        }
                                    }
                                    if(j+3 < m && i-3 >= 0){
                                        if(myState.at(i-3).at(j+3) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-3) + " " + to_string(j+3);
                							moves.push_back(move);
                                        }

                                    }
                                    if(i+4<n && j-4 >= 0){
                                        if(myState.at(i).at(j-4) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+4) + " " + to_string(j-4);
                							moves.push_back(move);
                                        }
                                    }
                                    if(j-5 >= 0 && i+5 < n){
                                        if(myState.at(i+5).at(j-5) != player){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+5) + " " + to_string(j-5);
                							moves.push_back(move);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return moves;
    }

    int Max_Val(vector<vector<int> > &ret, int &x, int cx, vector<vector<int> > curState, int d, int alpha, int beta, int player){

    	if(d == 0){
    		ret = curState;
            x = cx;
    		// return evaluationFunction(curState);
            return 0;
    	}
    	int c, ma = INT_MIN;
        vector<string> gs;
        // cout<<"hello1"<<endl;
    	vector<vector<vector<int> > > nextMoves = generateSteps(gs, player, curState);
        // cout<<"hello2"<<endl;
        cout<<nextMoves.size()<<endl;

    	for(int i=0; i<nextMoves.size(); i++){
    		vector<vector<int> > r;
            int y;
            // cout<<"hello3"<<endl;
            // cout<<i<<endl;
    		c = Min_Val(r, y, i, nextMoves[i], d-1, alpha, beta, otherPlayer(player));

            // cout<<"hello4"<<endl;
            alpha = max(alpha,c);
            // cout<<"hello5"<<endl;
    		if(alpha >= beta){
    			ret = r;
                x = y;
    			return c;
    		}
            // cout<<"hello6"<<endl;

    		if(c > ma){
    			ma = c;
    			ret = r;
                x = y;
    		}
            // cout<<"hello7"<<endl;
    	}
        // cout<<"madafaqa"<<endl;
    	return ma;
    }

    int Min_Val(vector<vector<int> > &ret, int &x, int cx, vector<vector<int> > curState, int d, int alpha, int beta, int player){
    	if(d == 0){
            // cout<<"hello8"<<endl;
    		ret = curState;
            x = cx;
    		return evaluationFunction(curState);
    	}
        // cout<<"hello9"<<endl;


    	int c,mi = INT_MAX;
        // cout<<"hello10"<<endl;
        vector<string> gs;
        // cout<<"pkmkb100"<<endl;
        // cout<<player<<endl;
        // printState(curState);
        // cout<<"pkmkb1"<<endl;
    	vector<vector<vector<int> > > nextMoves = generateSteps(gs, player, curState);
        // cout<<"hello11"<<endl;
    	for(int i=0; i<nextMoves.size() ;i++){
            // cout<<"hello12"<<endl;
    		vector<vector<int> > r;
            int y;
    		c = Max_Val(r,y,i,nextMoves[i],d-1,alpha,beta, otherPlayer(player));
            // cout<<"hello13"<<endl;
    		beta = min(beta, c);
            // cout<<"hello14"<<endl;
    		if(alpha >= beta){
    			ret = r;
                x = y;
    			return c;
    		}
            // cout<<"hello15"<<endl;

    		if(c < mi){
    			mi = c;
    			ret = r;
                x = y;
                // cout<<"hello16"<<endl;
    		}
            // cout<<"hello17"<<endl;
    	}
    	return mi;
    }

    void nextMove(string &retString, vector<vector<int> > &curState, int depth, int alpha, int beta, int player){
    	vector<vector<int> > ret;
        int y;
    	int c = Max_Val(ret, y, 0, curState, depth, alpha, beta, player);

        // printState(ret);
        // return;

        curState = ret;
        vector<string> gs;

        vector<vector<vector<int> > > nextMoves = generateSteps(gs, player, curState);
        retString = gs[y];
    	return;
    }
    int gameWinner(vector<vector<int> > myState){
        int n1 = numberOfTownHall(1, myState);
        int n2 = numberOfTownHall(2, myState);
        if(n1-n2 == 2){
            return 1;
        }
        if(n2-n1 == 1){
            return 2;
        }
        return 0;
    }
};



int main(){
    //One is black, other is white
    int n, m, identity, time;
    cin>> identity >> n >> m >> time;
    CannonGame *game = new CannonGame();
    string a;
    string opponentMove;
    vector<string> abc;
    if(identity == 1){
        auto start = high_resolution_clock::now();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);
        int timed=(int)duration.count();
        ofstream file;
        file.open ("ex.txt");
        while(timed < time){
            opponentMove = "";
            for(int i=0;i<6;i++){
                cin>>a;
                abc.push_back(a);
            }
            game->board = game->executeMove(abc, game->board);
            if(game->gameWinner(game->board) == otherPlayer(identity)){
                cout<<"You lost!"<<endl;
            }
            string s = "";
            game->nextMove(s, game->board, 4, INT_MIN, INT_MAX, identity);
            cout<<string_to_good_string(s)<<endl;
            if(game->gameWinner(game->board) == identity){
                cout<<"You won!!"<<endl;
            }
            // printState(game->board);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<seconds>(stop - start);
            int timed=(int)duration.count();
        }
    }
    if(identity == 2){
        auto start = high_resolution_clock::now();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);
        int timed=(int)duration.count();
        while(timed < time){
            string s = "";
            game->nextMove(s, game->board, 2, INT_MIN, INT_MAX, identity);
            printState(game->board);
            cout<<string_to_good_string(s)<<endl;

            if(game->gameWinner(game->board) == identity){
                cout<<"You won!!"<<endl;
            }
            opponentMove = "";
            for(int i=0;i<6;i++){
                cin>>a;
                abc.push_back(a);
            }
            game->board = game->executeMove(abc, game->board);
            if(game->gameWinner(game->board) == otherPlayer(identity)){
                cout<<"You lost!"<<endl;
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<seconds>(stop - start);
            int timed=(int)duration.count();
        }
    }
    return 0;
}
