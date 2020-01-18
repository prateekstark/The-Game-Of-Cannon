#include<bits/stdc++.h>
#include<chrono>
#include<fstream>
using namespace std::chrono;
using namespace std;

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

class CannonGame{
public:
    vector<vector<int> > board;
    vector<int> coefficients;
    int player;


    CannonGame(int player, int n, int m){
        this->player = player;
        if(n == 8 && m == 8){
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
        }
        if(n == 10 && m == 10){
            vector<int> tempVector1({1, 10, 1, 10, 1, 10, 1, 10, 1, 10});
            vector<int> tempVector2({1, 0, 1, 0, 1, 0, 1, 0, 1, 0});
            vector<int> tempVector3({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
            vector<int> tempVector4({20, 2, 20, 2, 20, 2, 20, 2, 20, 2});
            vector<int> tempVector5({0, 2, 0, 2, 0, 2, 0, 2, 0, 2});
            vector<int> tempVector6({2, 2, 2, 0, 0, 0, 0, 0, 0, 10});
            vector<int> tempVector7({20, 0, 0, 0, 0, 0, 0, 1, 1, 1});

            for(int i=0;i<5;i++){
                board.push_back(tempVector7);
                board.push_back(tempVector6);
            }
        }

        if(n == 8 && m == 10){
            vector<int> tempVector1({1, 10, 1, 10, 1, 10, 1, 10, 1, 10});
            vector<int> tempVector2({1, 0, 1, 0, 1, 0, 1, 0, 1, 0});
            vector<int> tempVector3({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
            vector<int> tempVector4({20, 2, 20, 2, 20, 2, 20, 2, 20, 2});
            vector<int> tempVector5({0, 2, 0, 2, 0, 2, 0, 2, 0, 2});
            vector<int> tempVector6({2, 2, 2, 0, 0, 0, 0, 10});
            vector<int> tempVector7({20, 0, 0, 0, 0, 1, 1, 1});

            for(int i=0;i<5;i++){
                board.push_back(tempVector7);
                board.push_back(tempVector6);
            }
        }

        if(n == 10 && m == 8){
            vector<int> tempVector1({1, 10, 1, 10, 1, 10, 1, 10, 1, 10});
            vector<int> tempVector2({1, 0, 1, 0, 1, 0, 1, 0, 1, 0});
            vector<int> tempVector3({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
            vector<int> tempVector4({20, 2, 20, 2, 20, 2, 20, 2, 20, 2});
            vector<int> tempVector5({0, 2, 0, 2, 0, 2, 0, 2, 0, 2});
            vector<int> tempVector6({2, 2, 2, 0, 0, 0, 0, 0, 0, 10});
            vector<int> tempVector7({20, 0, 0, 0, 0, 0, 0, 1, 1, 1});

            for(int i=0;i<4;i++){
                board.push_back(tempVector7);
                board.push_back(tempVector6);
            }
        }
        if(player == 1){

            coefficients.push_back(-70); //number of soldiers that can be attacked, player 1
            coefficients.push_back(50); //number of soldier that can be attacked, player 2

            coefficients.push_back(250); // number of soldier, 1
            coefficients.push_back(-150); //number of soldier, 2

            coefficients.push_back(500); // number of townhall, 1
            coefficients.push_back(-400); // number of townhall, 2

            coefficients.push_back(80); // number of cannon, 1
            coefficients.push_back(-100); //numberOfCannon, 2

            coefficients.push_back(-10); //closenessFactor. 1
            coefficients.push_back(10); //closenessFactor 2

            coefficients.push_back(-30); // numberOfTownHallCanBeAttacked, 1
            coefficients.push_back(30); // numberOfTownHallCanBeAttacked, 2
        }

        if(player == 2){

            coefficients.push_back(50); //number of soldiers that can be attacked, player 1
            coefficients.push_back(-70); //number of soldier that can be attacked, player 2

            coefficients.push_back(-150); // number of soldier, 1
            coefficients.push_back(250); //number of soldier, 2

            coefficients.push_back(-400); // number of townhall, 1
            coefficients.push_back(500); // number of townhall, 2

            coefficients.push_back(-100); // number of cannon, 1
            coefficients.push_back(80); //numberOfCannon, 2

            coefficients.push_back(10); //closenessFactor. 1
            coefficients.push_back(-10); //closenessFactor 2

            coefficients.push_back(30); // numberOfTownHallCanBeAttacked, 1
            coefficients.push_back(-30); // numberOfTownHallCanBeAttacked, 2
        }

    }

    int evaluationFunction(vector<vector<int> > myState){
        int numberOfSoldierCanbeAttackedPlayer1 = 0, numberOfSoldierCanbeAttackedPlayer2 = 0, numberOfSoldiersPlayer1 = 0, numberOfSoldiersPlayer2 = 0;
        int numberOfTownHallPlayer2 = 0, numberOfTownHallPlayer1 = 0;
        int numberOfCannonPlayer1 = 0, numberOfCannonPlayer2 = 0;
        int numberOfTownHallCanBeAttackedPlayer1 = 0, numberOfTownHallCanBeAttackedPlayer2 = 0;
        int closenessFactorPlayer1 = 0, closenessFactorPlayer2 = 0;
        int tempPlayer;
        int n = myState.size();
        int m = myState[0].size();
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                tempPlayer = myState[i][j];
                if(tempPlayer == 1){
                    numberOfSoldiersPlayer1++;
                    closenessFactorPlayer1 += j;
                    if(canSoldierBeAttacked(i, j, 1, myState)){
                        numberOfSoldierCanbeAttackedPlayer1++;
                    }
                    if(isSoldierLeadOfCannon(i, j, 1, myState)){
                        numberOfCannonPlayer1++;
                    }
                }
                if(tempPlayer == 2){
                    numberOfSoldiersPlayer2++;
                    closenessFactorPlayer2 += (m-j-1);
                    if(canSoldierBeAttacked(i, j, 2, myState)){
                        numberOfSoldierCanbeAttackedPlayer2++;
                    }
                    if(isSoldierLeadOfCannon(i, j, 2, myState)){
                        numberOfCannonPlayer2++;
                    }
                }
                if(tempPlayer == 10){
                    numberOfTownHallPlayer1++;
                    if(canTownHallCanBeAttacked(i, j, 1, myState)){
                        numberOfSoldierCanbeAttackedPlayer1++;
                    }

                }
                if(tempPlayer == 20){
                    numberOfTownHallPlayer2++;
                    if(canTownHallCanBeAttacked(i, j, 2, myState)){
                        numberOfSoldierCanbeAttackedPlayer2++;
                    }
                }
            }
        }

        int answer = coefficients[0]*numberOfSoldierCanbeAttackedPlayer1 + coefficients[1]*numberOfSoldierCanbeAttackedPlayer2 + coefficients[2]*numberOfSoldiersPlayer1 + coefficients[3]*numberOfSoldiersPlayer2;
        answer = answer + coefficients[4]*numberOfTownHallPlayer1 + coefficients[5]*numberOfTownHallPlayer2 + coefficients[6]*numberOfCannonPlayer1 + coefficients[7]*numberOfCannonPlayer2;
        answer = answer + coefficients[8]*closenessFactorPlayer1 + coefficients[9]*closenessFactorPlayer2 + coefficients[10]*numberOfTownHallCanBeAttackedPlayer1 + coefficients[11]*numberOfTownHallCanBeAttackedPlayer2;
        return answer;
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
            if(moveVector[0].compare(S_string) == 0){
                if(moveVector[3].compare(M_string) == 0){
                    int ini_pos_x = stoi(moveVector[1]);
                    int ini_pos_y = stoi(moveVector[2]);
                    int fin_pos_x = stoi(moveVector[4]);
                    int fin_pos_y = stoi(moveVector[5]);
                    tempState[fin_pos_x][fin_pos_y] = tempState[ini_pos_x][ini_pos_y];
                    tempState[ini_pos_x][ini_pos_y] = 0;
                }
                if(moveVector[3].compare(B_string) == 0){
                    int fin_pos_x = stoi(moveVector[4]);
                    int fin_pos_y = stoi(moveVector[5]);
                    tempState[fin_pos_x][fin_pos_y] = 0;
                }
            }
        }
        return tempState;
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

    int gameWinner(vector<vector<int> > myState){
        int n1 = numberOfTownHall(1, myState);
        int n2 = numberOfTownHall(2, myState);
        if(n1-n2 == 2){
            return 1;
        }
        if(n2-n1 == 2){
            return 2;
        }
        return 0;
    }

    bool canSoldierBeAttacked(int x, int y, int player, vector<vector<int> > myStateVector){
        if(myStateVector[x][y] != player){
            return false;
        }
        int n = myStateVector.size();
        int m = myStateVector[0].size();
        int myState[n][m];
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                myState[i][j] = myStateVector[i][j];
            }
        }
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
                if(myState[x-1][y+1] == 1){
                    return true;
                }
            }

            if(x+1 < n){
                if(myState[x+1][y] == 1){
                    return true;
                }
            }

            if(x-1 >= 0){
                if(myState[x-1][y] == 1){
                    return true;
                }
            }

            if(y+4 < m){
                if(myState[x][y+2] == 1 && myState[x][y+3] == 1 && myState[x][y+4] == 1 && myState[x][y+1] == 0){
                    return true;
                }
            }


            if(x+4 < m){
                if(myState[x+2][y] == 1 && myState[x+3][y] == 1 && myState[x+4][y] == 1 && myState[x+1][y] == 0){
                    return true;
                }
            }

            if(x-4 >= 0){
                if(myState[x-2][y] == 1 && myState[x-3][y] == 1 && myState[x-4][y] == 1 && myState[x-1][y] == 0){
                    return true;
                }
            }


            if(y+4 < m){
                if(x+4 < n){
                    if(myState[x+2][y+2] == 1 && myState[x+3][y+3] == 1 && myState[x+4][y+4] == 1 && myState[x+1][y+1] == 0){
                        return true;
                    }       
                }
                if(x-4 >= 0){
                    if(myState[x-2][y+2] == 1 && myState[x-3][y+3] == 1 && myState[x-4][y+4] == 1 && myState[x-1][y+1] == 0){
                        return true;
                    }       
                }
            }


            //Start
            if(y+5 < m){
                if(myState[x][y+3] == 1 && myState[x][y+4] == 1 && myState[x][y+5] == 1 && myState[x][y+1] == 0 && myState[x][y+2] == 0){
                    return true;
                }
            }


            if(x+5 < m){
                if(myState[x+3][y] == 1 && myState[x+4][y] == 1 && myState[x+5][y] == 1 && myState[x+1][y] == 0 && myState[x+2][y] == 0){
                    return true;
                }
            }

            if(x-5 >= 0){
                if(myState[x-3][y] == 1 && myState[x-4][y] == 1 && myState[x-5][y] == 1 && myState[x-1][y] == 0 && myState[x-2][y] == 0){
                    return true;
                }
            }

            if(y+5 < m){
                if(x+5 < n){
                    if(myState[x+3][y+3] == 1 && myState[x+4][y+4] == 1 && myState[x+5][y+5] == 1 && myState[x+1][y+1] == 0 && myState[x+2][y+2] == 0){
                        return true;
                    }       
                }
                if(x-5 >= 0){
                    if(myState[x-3][y+3] == 1 && myState[x-4][y+4] == 1 && myState[x-5][y+5] == 1 && myState[x-1][y+1] == 0 && myState[x-2][y+2] == 0){
                        return true;
                    }       
                }
            }



            if(y-4 >= 0){
                if(myState[x][y-2] == 1 && myState[x][y-3] == 1 && myState[x][y-4] == 1 && myState[x][y-1] == 0){
                    return true;
                }
            }


            if(y-4 >= 0){
                if(x+4 < n){
                    if(myState[x+2][y-2] == 1 && myState[x+3][y-3] == 1 && myState[x+4][y-4] == 1 && myState[x+1][y-1] == 0){
                        return true;
                    }       
                }
                if(x-4 >= 0){
                    if(myState[x-2][y-2] == 1 && myState[x-3][y-3] == 1 && myState[x-4][y-4] == 1 && myState[x-1][y-1] == 0){
                        return true;
                    }       
                }
            }


            //Start
            if(y-5 >= 0){
                if(myState[x][y-3] == 1 && myState[x][y-4] == 1 && myState[x][y-5] == 1 && myState[x][y-1] == 0 && myState[x][y-2] == 0){
                    return true;
                }
            }

            if(y-5 >= 0){
                if(x+5 < n){
                    if(myState[x+3][y-3] == 1 && myState[x+4][y-4] == 1 && myState[x+5][y-5] == 1 && myState[x+1][y-1] == 0 && myState[x+2][y-2] == 0){
                        return true;
                    }       
                }
                if(x-5 >= 0){
                    if(myState[x-3][y-3] == 1 && myState[x-4][y-4] == 1 && myState[x-5][y-5] == 1 && myState[x-1][y-1] == 0 && myState[x-2][y-2] == 0){
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
                if(myState[x-1][y-1] == 2){
                    return true;
                }
            }

            if(x+1 < n){
                if(myState[x+1][y] == 2){
                    return true;
                }
            }

            if(x-1 >= 0){
                if(myState[x-1][y] == 2){
                    return true;
                }
            }

            if(y-4 >= 0){
                if(myState[x][y-2] == 2 && myState[x][y-3] == 2 && myState[x][y-4] == 2 && myState[x][y-1] == 0){
                    return true;
                }
            }


            if(x+4 < m){
                if(myState[x+2][y] == 2 && myState[x+3][y] == 2 && myState[x+4][y] == 2 && myState[x+1][y] == 0){
                    return true;
                }
            }

            if(x-4 >= 0){
                if(myState[x-2][y] == 2 && myState[x-3][y] == 2 && myState[x-4][y] == 2 && myState[x-1][y] == 0){
                    return true;
                }
            }


            if(y-4 >= 0){
                if(x+4 < n){
                    if(myState[x+2][y-2] == 2 && myState[x+3][y-3] == 2 && myState[x+4][y-4] == 2 && myState[x+1][y-1] == 0){
                        return true;
                    }
                }
                if(x-4 >= 0){
                    if(myState[x-2][y-2] == 2 && myState[x-3][y-3] == 2 && myState[x-4][y-4] == 2 && myState[x-1][y-1] == 0){
                        return true;
                    }       
                }
            }


            //Start
            if(y-5 >= 0){
                if(myState[x][y-3] == 2 && myState[x][y-4] == 2 && myState[x][y-5] == 2 && myState[x][y-1] == 0 && myState[x][y-2] == 0){
                    return true;
                }
            }


            if(x+5 < m){
                if(myState[x+3][y] == 2 && myState[x+4][y] == 2 && myState[x+5][y] == 2 && myState[x+1][y] == 0 && myState[x+2][y] == 0){
                    return true;
                }
            }

            if(x-5 >= 0){
                if(myState[x-3][y] == 2 && myState[x-4][y] == 2 && myState[x-5][y] == 2 && myState[x-1][y] == 0 && myState[x-2][y] == 0){
                    return true;
                }
            }

            if(y-5 >= 0){
                if(x+5 < n){
                    if(myState[x+3][y-3] == 2 && myState[x+4][y-4] == 2 && myState[x+5][y-5] == 2 && myState[x+1][y-1] == 0 && myState[x+2][y-2] == 0){
                        return true;
                    }       
                }
                if(x-5 >= 0){
                    if(myState[x-3][y-3] == 2 && myState[x-4][y-4] == 2 && myState[x-5][y-5] == 2 && myState[x-1][y-1] == 0 && myState[x-2][y-2] == 0){
                        return true;
                    }       
                }
            }

            if(y+4 < m){
                if(myState[x][y+2] == 2 && myState[x][y+3] == 2 && myState[x][y+4] == 2 && myState[x][y+1] == 0){
                    return true;
                }
            }

            if(y+4 < m){
                if(x+4 < n){
                    if(myState[x+2][y+2] == 2 && myState[x+3][y+3] == 2 && myState[x+4][y+4] == 2 && myState[x+1][y+1] == 0){
                        return true;
                    }       
                }
                if(x-4 >= 0){
                    if(myState[x-2][y+2] == 2 && myState[x-3][y+3] == 2 && myState[x-4][y+4] == 2 && myState[x-1][y+1] == 0){
                        return true;
                    }       
                }
            }


            //Start
            if(y+5 < m){
                if(myState[x][y+3] == 2 && myState[x][y+4] == 2 && myState[x][y+5] == 2 && myState[x][y+1] == 0 && myState[x][y+2] == 0){
                    return true;
                }
            }

            if(y+5 < m){
                if(x+5 < n){
                    if(myState[x+3][y+3] == 2 && myState[x+4][y+4] == 2 && myState[x+5][y+5] == 2 && myState[x+1][y+1] == 0 && myState[x+2][y+2] == 0){
                        return true;
                    }       
                }
                if(x-5 >= 0){
                    if(myState[x-3][y+3] == 2 && myState[x-4][y+4] == 2 && myState[x-5][y+5] == 2 && myState[x-1][y+1] == 0 && myState[x-2][y+2] == 0){
                        return true;
                    }       
                }
            }
        }
        return false;
    }

    bool isSoldierAdjacentAttacked(int x, int y, int player, vector<vector<int> > myState){
        if(myState[x][y] != player){
            return false;
        }
        int n = myState.size();
        int m = myState[0].size();
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
                if(myState[x-1][y+1] == 1){
                    return true;
                }
            }

            if(x+1 < n){
                if(myState[x+1][y] == 1){
                    return true;
                }
            }

            if(x-1 >= 0){
                if(myState[x-1][y] == 1){
                    return true;
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
                if(myState[x-1][y-1] == 2){
                    return true;
                }
            }

            if(x+1 < n){
                if(myState[x+1][y] == 2){
                    return true;
                }
            }

            if(x-1 >= 0){
                if(myState[x-1][y] == 2){
                    return true;
                }
            }
        }
        return false;
    }

    bool canTownHallCanBeAttacked(int x, int y, int player, vector<vector<int> > myStateVector){
        if(myStateVector[x][y] != player*10){
            return false;
        }
        int n = myStateVector.size();
        int m = myStateVector[0].size();
        int myState[n][m];
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                myState[i][j] = myStateVector[i][j];
            }
        }
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
                if(myState[x-1][y+1] == 1){
                    return true;
                }
            }

            if(x+1 < n){
                if(myState[x+1][y] == 1){
                    return true;
                }
            }

            if(x-1 >= 0){
                if(myState[x-1][y] == 1){
                    return true;
                }
            }

            if(y+4 < m){
                if(myState[x][y+2] == 1 && myState[x][y+3] == 1 && myState[x][y+4] == 1 && myState[x][y+1] == 0){
                    return true;
                }
            }


            if(x+4 < m){
                if(myState[x+2][y] == 1 && myState[x+3][y] == 1 && myState[x+4][y] == 1 && myState[x+1][y] == 0){
                    return true;
                }
            }

            if(x-4 >= 0){
                if(myState[x-2][y] == 1 && myState[x-3][y] == 1 && myState[x-4][y] == 1 && myState[x-1][y] == 0){
                    return true;
                }
            }


            if(y+4 < m){
                if(x+4 < n){
                    if(myState[x+2][y+2] == 1 && myState[x+3][y+3] == 1 && myState[x+4][y+4] == 1 && myState[x+1][y+1] == 0){
                        return true;
                    }       
                }
                if(x-4 >= 0){
                    if(myState[x-2][y+2] == 1 && myState[x-3][y+3] == 1 && myState[x-4][y+4] == 1 && myState[x-1][y+1] == 0){
                        return true;
                    }       
                }
            }


            //Start
            if(y+5 < m){
                if(myState[x][y+3] == 1 && myState[x][y+4] == 1 && myState[x][y+5] == 1 && myState[x][y+1] == 0 && myState[x][y+2] == 0){
                    return true;
                }
            }


            if(x+5 < m){
                if(myState[x+3][y] == 1 && myState[x+4][y] == 1 && myState[x+5][y] == 1 && myState[x+1][y] == 0 && myState[x+2][y] == 0){
                    return true;
                }
            }

            if(x-5 >= 0){
                if(myState[x-3][y] == 1 && myState[x-4][y] == 1 && myState[x-5][y] == 1 && myState[x-1][y] == 0 && myState[x-2][y] == 0){
                    return true;
                }
            }

            if(y+5 < m){
                if(x+5 < n){
                    if(myState[x+3][y+3] == 1 && myState[x+4][y+4] == 1 && myState[x+5][y+5] == 1 && myState[x+1][y+1] == 0 && myState[x+2][y+2] == 0){
                        return true;
                    }       
                }
                if(x-5 >= 0){
                    if(myState[x-3][y+3] == 1 && myState[x-4][y+4] == 1 && myState[x-5][y+5] == 1 && myState[x-1][y+1] == 0 && myState[x-2][y+2] == 0){
                        return true;
                    }       
                }
            }

            if(y-4 >= 0){
                if(myState[x][y-2] == 1 && myState[x][y-3] == 1 && myState[x][y-4] == 1 && myState[x][y-1] == 0){
                    return true;
                }
            }


            if(y-4 >=0){
                if(x+4 < n){
                    if(myState[x+2][y-2] == 1 && myState[x+3][y-3] == 1 && myState[x+4][y-4] == 1 && myState[x+1][y-1] == 0){
                        return true;
                    }       
                }
                if(x-4 >= 0){
                    if(myState[x-2][y-2] == 1 && myState[x-3][y-3] == 1 && myState[x-4][y-4] == 1 && myState[x-1][y-1] == 0){
                        return true;
                    }       
                }
            }


            //Start
            if(y-5 >= 0){
                if(myState[x][y-3] == 1 && myState[x][y-4] == 1 && myState[x][y-5] == 1 && myState[x][y-1] == 0 && myState[x][y-2] == 0){
                    return true;
                }
            }

            if(y-5 >= 0){
                if(x+5 < n){
                    if(myState[x+3][y-3] == 1 && myState[x+4][y-4] == 1 && myState[x+5][y-5] == 1 && myState[x+1][y-1] == 0 && myState[x+2][y-2] == 0){
                        return true;
                    }       
                }
                if(x-5 >= 0){
                    if(myState[x-3][y-3] == 1 && myState[x-4][y-4] == 1 && myState[x-5][y-5] == 1 && myState[x-1][y-1] == 0 && myState[x-2][y-2] == 0){
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
                if(myState[x-1][y-1] == 2){
                    return true;
                }
            }

            if(x+1 < n){
                if(myState[x+1][y] == 2){
                    return true;
                }
            }

            if(x-1 >= 0){
                if(myState[x-1][y] == 2){
                    return true;
                }
            }

            if(y-4 >= m){
                if(myState[x][y-2] == 2 && myState[x][y-3] == 2 && myState[x][y-4] == 2 && myState[x][y-1] == 0){
                    return true;
                }
            }


            if(x+4 < m){
                if(myState[x+2][y] == 2 && myState[x+3][y] == 2 && myState[x+4][y] == 2 && myState[x+1][y] == 0){
                    return true;
                }
            }

            if(x-4 >= 0){
                if(myState[x-2][y] == 2 && myState[x-3][y] == 2 && myState[x-4][y] == 2 && myState[x-1][y] == 0){
                    return true;
                }
            }


            if(y-4 >= m){
                if(x+4 < n){
                    if(myState[x+2][y-2] == 2 && myState[x+3][y-3] == 2 && myState[x+4][y-4] == 2 && myState[x+1][y-1] == 0){
                        return true;
                    }       
                }
                if(x-4 >= 0){
                    if(myState[x-2][y-2] == 2 && myState[x-3][y-3] == 2 && myState[x-4][y-4] == 2 && myState[x-1][y-1] == 0){
                        return true;
                    }       
                }
            }


            //Start
            if(y-5 >= m){
                if(myState[x][y-3] == 2 && myState[x][y-4] == 2 && myState[x][y-5] == 2 && myState[x][y-1] == 0 && myState[x][y-2] == 0){
                    return true;
                }
            }


            if(x+5 < m){
                if(myState[x+3][y] == 2 && myState[x+4][y] == 2 && myState[x+5][y] == 2 && myState[x+1][y] == 0 && myState[x+2][y] == 0){
                    return true;
                }
            }

            if(x-5 >= 0){
                if(myState[x-3][y] == 2 && myState[x-4][y] == 2 && myState[x-5][y] == 2 && myState[x-1][y] == 0 && myState[x-2][y] == 0){
                    return true;
                }
            }

            if(y-5 >= 0){
                if(x+5 < n){
                    if(myState[x+3][y-3] == 2 && myState[x+4][y-4] == 2 && myState[x+5][y-5] == 2 && myState[x+1][y-1] == 0 && myState[x+2][y-2] == 0){
                        return true;
                    }       
                }
                if(x-5 >= 0){
                    if(myState[x-3][y-3] == 2 && myState[x-4][y-4] == 2 && myState[x-5][y-5] == 2 && myState[x-1][y-1] == 0 && myState[x-2][y-2] == 0){
                        return true;
                    }       
                }
            }


            //--------------------------


            if(y+4 < m){
                if(myState[x][y+2] == 2 && myState[x][y+3] == 2 && myState[x][y+4] == 2 && myState[x][y+1] == 0){
                    return true;
                }
            }

            if(y+4 < m){
                if(x+4 < n){
                    if(myState[x+2][y+2] == 2 && myState[x+3][y+3] == 2 && myState[x+4][y+4] == 2 && myState[x+1][y+1] == 0){
                        return true;
                    }       
                }
                if(x-4 >= 0){
                    if(myState[x-2][y+2] == 2 && myState[x-3][y+3] == 2 && myState[x-4][y+4] == 2 && myState[x-1][y+1] == 0){
                        return true;
                    }       
                }
            }


            //Start
            if(y+5 < m){
                if(myState[x][y+3] == 2 && myState[x][y+4] == 2 && myState[x][y+5] == 2 && myState[x][y+1] == 0 && myState[x][y+2] == 0){
                    return true;
                }
            }

            if(y+5 < m){
                if(x+5 < n){
                    if(myState[x+3][y+3] == 2 && myState[x+4][y+4] == 2 && myState[x+5][y+5] == 2 && myState[x+1][y+1] == 0 && myState[x+2][y+2] == 0){
                        return true;
                    }       
                }
                if(x-5 >= 0){
                    if(myState[x-3][y+3] == 2 && myState[x-4][y+4] == 2 && myState[x-5][y+5] == 2 && myState[x-1][y+1] == 0 && myState[x-2][y+2] == 0){
                        return true;
                    }       
                }
            }
        }
        return false;
    }

    bool isSoldierLeadOfCannon(int x, int y, int player, vector<vector<int> > myState){
        int n = myState.size();
        int m = myState[0].size();
        if(myState[x][y] == player){
            if(player == 2){
                if(y-2 >= 0){
                    if(myState[x][y-1] == 2 && myState[x][y-2] == 2){
                        return true;
                    }
                    if(x-2 >= 0){
                        if(myState[x-1][y-1] == 2 && myState[x-2][y-2] == 2){
                            return true;
                        }
                    }
                    if(x+2 < n){
                        if(myState[x+1][y-1] == 2 && myState[x+2][y-2] == 2){
                            return true;
                        }
                    }
                }
                if(x-2 >= 0){
                    if(myState[x-1][y] == 2 && myState[x-2][y] == 2){
                        return true;
                    }
                }
            }
            if(player == 1){
                if(y+2 < m){
                    if(myState[x][y+1] == 1 && myState[x][y+2] == 1){
                        return true;
                    }
                    if(x-2 >= 0){
                        if(myState[x-1][y+1] == 1 && myState[x-2][y+2] == 1){
                            return true;
                        }
                    }
                    if(x+2 < n){
                        if(myState[x+1][y+1] == 1 && myState[x+2][y+2] == 1){
                            return true;
                        }
                    }
                }
                if(x-2 >= 0){
                    if(myState[x-1][y] == 1 && myState[x-2][y] == 1){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    vector<string> generateSteps(int player, vector<vector<int> > myState){
        vector<string> moves;
        int n = myState.size();
        int m = myState[0].size();
        bool soldierCondition;
        string move;
        if(player == 2){
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    if(myState[i][j] == 2){
                        soldierCondition = isSoldierAdjacentAttacked(i, j, 2, myState);
                        if(soldierCondition){
                            if(j-2 >= 0){
                                if(myState[i][j-2] != 2 && myState[i][j-2] != 20){
                                    move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j-2);
                                    if(find(moves.begin(),moves.end(),move) == moves.end()){
                                        moves.push_back(move);
                                    }
                                    
                                }
                                if(i-2 >= 0){
                                    if(myState[i-2][j-2] != 2 && myState[i-2][j-2] != 20){
                                        move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-2) + " " + to_string(j-2);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }

                                    }
                                }
                                if(i+2 < n){
                                    if(myState[i+2][j-2] != 2 && myState[i+2][j-2] != 20){
                                        move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+2) + " " + to_string(j-2);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }

                                    }
                                }
                            }
                        }
                        if(i+1 < n){
                            if(myState[i+1][j] == 1 || myState[i+1][j] == 10){
                                move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j);
                                if(find(moves.begin(),moves.end(),move) == moves.end()){
                                    moves.push_back(move);
                                }
                            }
                            if(j+1 < m){
                                if(myState[i+1][j+1] != 2 && myState[i+1][j+1] != 20){
                                    move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j+1);
                                    if(find(moves.begin(),moves.end(),move) == moves.end()){
                                        moves.push_back(move);
                                    }
                                }
                            }
                        }
                        if(i-1 >= 0){
                            if(myState[i-1][j] == 1 || myState[i-1][j] == 10){
                                move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-1) + " " + to_string(j);
                                if(find(moves.begin(),moves.end(),move) == moves.end()){
                                    moves.push_back(move);
                                }
                            }
                            if(j+1 < m){
                                if(myState[i-1][j+1] != 2 && myState[i-1][j+1] != 20){
                                    move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-1) + " " + to_string(j+1);
                                    if(find(moves.begin(),moves.end(),move) == moves.end()){
                                        moves.push_back(move);
                                    }
                                }
                            }
                        }
                        if(j+1 < m){
                            if(myState[i][j+1] != 2 && myState[i][j+1] != 20){
                                move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j+1);
                                if(find(moves.begin(),moves.end(),move) == moves.end()){
                                    moves.push_back(move);
                                }
                            }
                        }
                    }
                    if(isSoldierLeadOfCannon(i, j, 2, myState)){
                        if(j-2 >= 0){
                            if(myState[i][j-1] == 2 && myState[i][j-2] == 2){
                                if(j-3 >= 0){
                                    if(myState[i][j-3] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j-3);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }
                                
                                if(j+1 < m){
                                    if(myState[i][j+1] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j-2) + " M " + to_string(i) + " " + to_string(j+1);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }

                                if(j+2 < m){
                                    if(myState[i][j+2] != player && myState[i][j+2] != player*10 && myState[i][j+1] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+2);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }

                                if(j+3 < m){
                                    if(myState[i][j+3] != player && myState[i][j+3] != player*10 && myState[i][j+1] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+3);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }

                                if(j-4 >= 0){
                                    if(myState[i][j-4] != player && myState[i][j-4] != player*10 && myState[i][j-3] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-4);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }

                                if(j-5 >= 0){
                                    if(myState[i][j-5] != player && myState[i][j-5] != player*10 && myState[i][j-3] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-5);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }
                            }
                            if(i-2 >= 0 && j-2 >= 0){
                                if(myState[i-1][j-1] == 2 && myState[i-2][j-2] == 2){
                                    if(i-3 >= 0 && j-3 >= 0){
                                        if(myState[i-3][j-3] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-3) + " " + to_string(j-3);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                    // cout<<"sona11"<<endl;
                                    if(i+1 < n && j+1 < m){
                                        if(myState[i+1][j+1] == 0){
                                            move = "S " + to_string(i-2) + " " + to_string(j-2) + " M " + to_string(i+1) + " " + to_string(j+1);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                    // cout<<"sona12"<<endl;
                                    if(j+2 < m && i+2 < n){
                                        if(myState[i+2][j+2] != player && myState[i+2][j+2] != player*10 && myState[i+1][j+1] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+2) + " " + to_string(j+2);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                    // cout<<"sona13"<<endl;
                                    if(j+3 < m && i+3 < n){
                                        if(myState[i+3][j+3] != player && myState[i+1][j+1] == 0 && myState[i+3][j+3] != player*10){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+3) + " " + to_string(j+3);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                    // cout<<"sona14"<<endl;
                                    if(j-4 >= 0 && i-4 >= 0){
                                        if(myState[i-4][j-4] != player && myState[i-4][j-4] != player*10 && myState[i-3][j-3] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-4) + " " + to_string(j-4);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }

                                    if(j-5 >= 0 && i-5 >= 0){
                                        if(myState[i-5][j-5] != player && myState[i-5][j-5] != player*10 && myState[i-3][j-3] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-5) + " " + to_string(j-5);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                }
                            }

                            if(i+2 < n && j-2 >= 0){
                                if(myState[i+1][j-1] == 2 && myState[i+2][j-2] == 2){
                                    if(i+3 < n && j-3 >= 0){
                                        if(myState[i+3][j-3] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+3) + " " + to_string(j-3);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }

                                    if(i-1 >= 0 && j+1 < m){
                                        if(myState[i-1][j+1] == 0){
                                            move = "S " + to_string(i+2) + " " + to_string(j-2) + " M " + to_string(i-1) + " " + to_string(j+1);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }

                                    if(j+2 < m && i-2 >= 0){
                                        if(myState[i-2][j+2] != player && myState[i-2][j+2] != player*10 && myState[i-1][j+1] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-2) + " " + to_string(j+2);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                    if(j+3 < m && i-3 >= 0){
                                        if(myState[i-3][j+3] != player && myState[i-3][j+3] != player*10 && myState[i-1][j+1] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-3) + " " + to_string(j+3);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }

                                    }
                                    if(i+4<n && j-4 >= 0){
                                        if(myState[i+4][j-4] != player && myState[i+4][j-4] != player*10 && myState[i+3][j-3] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+4) + " " + to_string(j-4);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                    if(j-5 >= 0 && i+5 < n){
                                        if(myState[i+5][j-5] != player && myState[i+3][j-3] == 0 && myState[i+5][j-5] != player*10){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+5) + " " + to_string(j-5);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(i - 2 >= 0){
                            if(myState[i-1][j] == 2 && myState[i-2][j] == 2){
                                if(i-3 >= 0){
                                    if(myState[i-3][j] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-3) + " " + to_string(j);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }
                                if(i+1 < n){
                                    if(myState[i+1][j] == 0){
                                        move = "S " + to_string(i-2) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }

                                if(i+2 < n){
                                    if(myState[i+2][j] != player && myState[i+2][j] != player*10 && myState[i+1][j] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+2) + " " + to_string(j);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }
                                if(i+3 < n){
                                    if(myState[i+3][j] != player && myState[i+3][j] != player*10 && myState[i+1][j] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+3) + " " + to_string(j);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }
                                if(i-4 >= 0){
                                    if(myState[i-4][j] != player && myState[i-4][j] != player*10 && myState[i-3][j] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-4) + " " + to_string(j);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }                                   
                                }
                                if(i-5 >= 0){
                                    if(myState[i-5][j] != player && myState[i-5][j] != player*10 && myState[i-3][j] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-5) + " " + to_string(j);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
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

        if(player == 1){
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    if(myState[i][j] == 1){
                        // cout<<"baweja"<<endl;
                        soldierCondition = isSoldierAdjacentAttacked(i, j, 1, myState);
                        // cout<<"baweja1"<<endl;
                        if(soldierCondition){
                            if(j+2 <m){
                                // cout<<"baweja2"<<endl;
                                if(myState[i][j+2] != 1 && myState[i][j+2] != 10){
                                    move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j+2);
                                    if(find(moves.begin(),moves.end(),move) == moves.end()){
                                        moves.push_back(move);
                                    }
                                }
                                if(i-2 >= 0){
                                    // cout<<"baweja3"<<endl;
                                    if(myState[i-2][j+2] != 1 && myState[i-2][j+2] != 10){
                                        move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-2) + " " + to_string(j+2);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }
                                if(i+2 < n){
                                    // cout<<"baweja4"<<endl;
                                    if(myState[i+2][j+2] != 1 && myState[i+2][j+2] != 10){
                                        move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+2) + " " + to_string(j+2);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }
                            }
                        }
                        if(i+1 < n){
                            // cout<<"baweja5"<<endl;
                            if(myState[i+1][j] == 2 || myState[i+1][j] == 20){
                                move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j);
                                if(find(moves.begin(),moves.end(),move) == moves.end()){
                                    moves.push_back(move);
                                }
                            }
                            if(j-1 >= 0){
                                // cout<<"baweja6"<<endl;
                                if(myState[i+1][j-1] != 1 && myState[i+1][j-1] != 10){
                                    move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j-1);
                                    if(find(moves.begin(),moves.end(),move) == moves.end()){
                                        moves.push_back(move);
                                    }
                                }
                            }
                        }
                        if(i-1 >= 0){
                            // cout<<"baweja7"<<endl;
                            if(myState[i-1][j] == 2 || myState[i-1][j] == 20){
                                move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-1) + " " + to_string(j);
                                if(find(moves.begin(),moves.end(),move) == moves.end()){
                                    moves.push_back(move);
                                }
                            }
                            if(j-1 >= 0){
                                // cout<<"baweja8"<<endl;
                                if(myState[i-1][j-1] != 1 && myState[i-1][j] == 10){    
                                    move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-1) + " " + to_string(j-1);
                                    if(find(moves.begin(),moves.end(),move) == moves.end()){
                                        moves.push_back(move);
                                    }
                                }
                            }
                        }
                        if(j-1 >= 0){
                            if(myState[i][j-1] != 1 && myState[i][j-1] != 10){
                                move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j-1);
                                if(find(moves.begin(),moves.end(),move) == moves.end()){
                                    moves.push_back(move);
                                }
                            }
                        }
                    }
                    if(isSoldierLeadOfCannon(i, j, 1, myState)){
                        if(j+2 < m){
                            if(myState[i][j+1] == 1 && myState[i][j+2] == 1){
                                if(j+3 < m){
                                    if(myState[i][j+3] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j+3);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                           moves.push_back(move);
                                        }
                                    }
                                }
                                if(j-1 >= 0){
                                    if(myState[i][j-1] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j+2) + " M " + to_string(i) + " " + to_string(j-1);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                           moves.push_back(move);
                                        }
                                    }
                                }
                                if(j-2 >= 0){
                                    if(myState[i][j-2] != player && myState[i][j-2] != player*10 && myState[i][j-1] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-2);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                           moves.push_back(move);
                                        }
                                    }
                                }
                                if(j-3 >= 0){
                                    if(myState[i][j-3] != player && myState[i][j-3] != player*10 && myState[i][j-1] == 0 && myState[i][j-2] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-3);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                           moves.push_back(move);
                                        }
                                    }
                                }
                                if(j+4 < m){
                                    if(myState[i][j+4] != player && myState[i][j+4] != player*10 && myState[i][j+3] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+4);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                           moves.push_back(move);
                                        }
                                    }
                                }
                                if(j+5 < m){
                                    if(myState[i][j+5] != player && myState[i][j+5] != player*10 && myState[i][j+3] == 0 && myState[i][j+4] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+5);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                           moves.push_back(move);
                                        }
                                    }
                                }
                            }
                        }
                        if(i-2 >= 0){
                            if(j+2 < m){
                                if(myState[i-1][j+1] == 1 && myState[i-2][j+2] == 1){
                                    if(i-3 >= 0 && j+3 < m){
                                        if(myState[i-3][j+3] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-3) + " " + to_string(j+3);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                    if(i+1 < n && j-1 >= 0){
                                        if(myState[i+1][j-1] == 0){
                                            move = "S " + to_string(i-2) + " " + to_string(j+2) + " M " + to_string(i+1) + " " + to_string(j-1);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                    if(j-2 >= 0 && i+2 < n){
                                        if(myState[i+2][j-2] != player && myState[i+2][j-2] != player*10 && myState[i+1][j-1] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+2) + " " + to_string(j-2);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                    if(j-3 >= 0 && i+3 < n){
                                        if(myState[i+3][j-3] != player && myState[i+3][j-3] != player*10 && myState[i+1][j-1] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+3) + " " + to_string(j-3);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                    if(j+4 < m && i-4 >= 0){
                                        if(myState[i-4][j+4] != player && myState[i-4][j+4] != player*10 && myState[i-3][j+3] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-4) + " " + to_string(j+4);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }                                        
                                    }
                                    if(j+5 < m && i-5 >= 0){
                                        if(myState[i-5][j+5] != player && myState[i-5][j+5] != player*10 && myState[i-3][j+3] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-5) + " " + to_string(j+5);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                }
                            }
                            if(i-2 >= 0){
                                if(myState[i-1][j] == 1 && myState[i-2][j] == 1){
                                    if(i-3 >= 0){
                                        if(myState[i-3][j] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-3) + " " + to_string(j);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                    if(i+1 < n){
                                        if(myState[i+1][j] == 0){
                                            move = "S " + to_string(i-2) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }

                                    if(i+2 < n){
                                        if(myState[i+2][j] != player && myState[i+2][j] != player*10 && myState[i+1][j] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+2) + " " + to_string(j);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                    if(i+3 < n){
                                        if(myState[i+3][j] != player && myState[i+3][j] != player*10 && myState[i+1][j] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+3) + " " + to_string(j);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                    if(i-4 >= 0){
                                        if(myState[i-4][j] != player && myState[i-4][j] != player*10 && myState[i-3][j] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-4) + " " + to_string(j);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                    if(i-5 >= 0){
                                        if(myState[i-5][j] != player && myState[i-5][j] != player*10 && myState[i-3][j] == 0){
                                            move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-5) + " " + to_string(j);
                                            if(find(moves.begin(),moves.end(),move) == moves.end()){
                                                moves.push_back(move);
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        if(i+2 < n && j+2 < m){
                            if(myState[i+1][j+1] == 1 && myState[i+2][j+2] == 1){
                                if(i+3 < n && j+3 <m){
                                    if(myState[i+3][j+3] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+3) + " " + to_string(j+3);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }
                                if(i-1 >= 0 && j-1 >= 0){
                                    if(myState[i-1][j-1] == 0){
                                        move = "S " + to_string(i+2) + " " + to_string(j+2) + " M " + to_string(i-1) + " " + to_string(j-1);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }
                                if(j-2 >= 0 && i-2 >= 0){
                                    if(myState[i-2][j-2] != player && myState[i-2][j-2] != player*10 && myState[i-1][j-1] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-2) + " " + to_string(j-2);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }
                                if(j-3 >= 0 && i-3 >= 0){
                                    if(myState[i-3][j-3] != player && myState[i-3][j-3] != player*10 && myState[i-1][j-1] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i-3) + " " + to_string(j-3);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }
                                if(j+4 < m && i+4 < n){
                                    if(myState[i+4][j+4] != player && myState[i+4][j+4] != player*10 && myState[i+3][j+3] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+4) + " " + to_string(j+4);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
                                            moves.push_back(move);
                                        }
                                    }
                                }
                                if(j+5 < m && i+5 < n){
                                    if(myState[i+5][j+5] != player && myState[i+5][j+5] != player*10 && myState[i+3][j+3] == 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i+5) + " " + to_string(j+5);
                                        if(find(moves.begin(),moves.end(),move) == moves.end()){
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

    int Max_Val(int &x,vector<vector<int> > curState, int d, int alpha, int beta, int player){
        // auto start = high_resolution_clock::now();
        
        if(d == 0 || gameWinner(curState)){
            return evaluationFunction(curState);
        }
        int c, ma = INT_MIN;
        vector<string> nextMoves = generateSteps(player, curState);
        // if(d==4)
        // cout<<"Size of children :   " << nextMoves.size() << endl;
        for(int i=0; i<nextMoves.size(); i++){
            int y;
            vector<vector<int> > child = executeMove(convertStringToVector(nextMoves[i]), curState);
            c = Min_Val(y, child, d-1, alpha, beta, otherPlayer(player));
            alpha = max(alpha,c);
            // if(d==4){
            //     cout<<" alpha is "<< i << " : " << alpha << endl;
            //     cout<<" c is "<< i << " : " << c << endl;
            //     cout<<" beta is "<< i << " : " << beta << endl;
            // }
            if(c > ma){
                ma = c;
                x = i;
            }

            if(alpha >= beta){
                // auto stop = high_resolution_clock::now();
                // auto duration = duration_cast<milliseconds>(stop - start);
                // float timed=(float)duration.count() / 1000;
                // if(d>2)
                // cout<<" lol " << i <<" Time taken by Max_Val with depth   " << d <<"   :   " << timed << endl;
                // cout<<"Max : " << d << endl;
                return c;
            }

        }

        // auto stop = high_resolution_clock::now();
        // auto duration = duration_cast<milliseconds>(stop - start);
        // float timed=(float)duration.count() / 1000;
        // if(d>2)
        // cout<<" end Time taken by Max_Val with depth   " << d <<"   :   " << timed << endl;
        return ma;
    }

    int Min_Val(int &x,vector<vector<int> > curState, int d, int alpha, int beta, int player){
        // auto start = high_resolution_clock::now();

        if(d == 0 || gameWinner(curState)){
            return evaluationFunction(curState);
        }

        int c, mi = INT_MAX;
        vector<string> nextMoves = generateSteps(player, curState);
        for(int i=0; i<nextMoves.size() ;i++){
            int y;
            vector<vector<int> > child = executeMove(convertStringToVector(nextMoves[i]), curState);
            c = Max_Val(y, child, d-1, alpha, beta, otherPlayer(player));
            beta = min(beta, c);

            if(c < mi){
                mi = c;
                x = i;
            }
            if(alpha >= beta){
                // auto stop = high_resolution_clock::now();
                // auto duration = duration_cast<milliseconds>(stop - start);
                // float timed=(float)duration.count() / 1000;
                // if(d>2)
                // cout<<" Time taken by Min_Val with depth   " << d <<"   :   " << timed << endl;
                // cout<<"Min : " << d << endl;
                return c;
            }
        }

        // auto stop = high_resolution_clock::now();
        // auto duration = duration_cast<milliseconds>(stop - start);
        // float timed=(float)duration.count() / 1000;
        // if(d>2)
        // cout<<" Time taken by Min_Val with depth   " << d <<"   :   " << timed << endl;

        return mi;
    }

    void nextMove(string &retString, vector<vector<int> > &curState, int depth, int alpha, int beta, int player){
        int y;
        int c = Max_Val(y, curState, depth, alpha, beta, player);
        vector<string> nextMoves = generateSteps(player, curState);
        retString = nextMoves[y];
        curState = executeMove(convertStringToVector(retString), curState);
        return;
    }

};

int main(){
    int n, m, identity, time;
    cin >> identity >> n >> m >> time;
    string a;
    string opponentMove;
    vector<string> abc;
    int player = identity;
    CannonGame *game = new CannonGame(player, n, m);
    if(identity == 1){
        auto start = high_resolution_clock::now();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);
        int timed=(int)duration.count();
        while(timed < time){
            int d;
            if(timed < time/3){
                d = 4;
            }else if(timed < 5*time/6){
                d = 4;
            }else{
                d = 4;
            }

            string s = "";
            game->nextMove(s, game->board, d, INT_MIN, INT_MAX, player);
            cout<<s<<endl;
            opponentMove = "";
            for(int i=0;i<6;i++){
                cin>>a;
                abc.push_back(a);
            }
            game->board = game->executeMove(abc, game->board);
            abc.clear();
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
            int d;
            if(timed < time/3){
                d = 4;
            }else if(timed < 5*time/6){
                d = 4;
            }else{
                d = 4;
            }
            opponentMove = "";
            for(int i=0;i<6;i++){
                cin>>a;
                abc.push_back(a);
            }
            game->board = game->executeMove(abc, game->board);
            abc.clear();
            string s = "";
            game->nextMove(s, game->board, d, INT_MIN, INT_MAX, player);
            cout<<s<<endl;
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<seconds>(stop - start);
            int timed=(int)duration.count();
        }
    }
    return 0;
}
