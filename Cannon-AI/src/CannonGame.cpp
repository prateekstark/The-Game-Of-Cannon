#include "../include/CannonGame.h"

CannonGame::CannonGame(int player, int n, int m){
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

        // coefficients.push_back(0); // number of townhall, 1
        // coefficients.push_back(-29); // number of townhall, 2
        // coefficients.push_back(0); // number of cannon, 1
        // coefficients.push_back(0); //numberOfCannon, 2
        // coefficients.push_back(0); //closenessFactor. 1
        // coefficients.push_back(0); //closenessFactor 2
        // coefficients.push_back(0); // numberOfTownHallCanBeAttacked, 1
        // coefficients.push_back(0); // numberOfTownHallCanBeAttacked, 2
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

int CannonGame::closenessFactor(int player, vector<vector<int> > myState){
    int count = 0;
    int n = myState.size();
    int m = myState[0].size();
    if(player == 1){
        for(int i=0;i<myState.size();i++){
            for(int j=0;j<myState.size();j++){
                if(myState.at(i).at(j) == player){
                    count = count + j;
                }
            }
        }
    }
    if(player == 2){
        for(int i=0;i<myState.size();i++){
            for(int j=0;j<myState.at(0).size();j++){
                if(myState.at(i).at(j) == player){
                    count = count + (m-j-1);
                }
            }
        }
    }
    return count;
}

int CannonGame::evaluationFunction(vector<vector<int> > myState){
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

bool CannonGame::areTwoMatrixEqual(vector<vector<int> > v1, vector<vector<int> > v2){
    if(v1.size() != v2.size() || v1[0].size() != v2[0].size()){
        return false;
    }
    for(int i=0;i<v1.size();i++){
        for(int j=0;j<v1[0].size();j++){
            if(v1[i][j] != v2[i][j]){
                return false;
            }
        }
    }
    return true;
}

vector<string> CannonGame::convertStringToVector(string str){
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

vector<vector<int> > CannonGame::executeMove(vector<string> moveVector, vector<vector<int> > myState){
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

bool CannonGame::doesSpaceContainPlane(vector<vector<vector<int> > > space, vector<vector<int> > plane){
    for(int i=0;i<space.size();i++){
        if(areTwoMatrixEqual(space[i], plane)){
            return true;
        }
    }
    return false;
}

vector<vector<vector<int> > > CannonGame::generateSteps(vector<string> &genStringMoves, int player, vector<vector<int> > myState){
    vector<vector<vector<int> > > allStates;
    vector<vector<int> > child;
    vector<string> possibleMoves1 = validMoves(player, myState);
    vector<string> possibleMoves2 = validCannonMoves(player, myState);
    for(int i=0;i<possibleMoves2.size();i++){
        child = executeMove(convertStringToVector(possibleMoves2[i]), myState);
        allStates.push_back(child);
        genStringMoves.push_back(possibleMoves2[i]);
        child.clear();
    }
    for(int i=0;i<possibleMoves1.size();i++){
        child = executeMove(convertStringToVector(possibleMoves1[i]), myState);
        allStates.push_back(child);
        genStringMoves.push_back(possibleMoves1[i]);
        child.clear();
    }

    return allStates;
}

bool CannonGame::canSoldierBeAttacked(int x, int y, int player, vector<vector<int> > myStateVector){
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

bool CannonGame::isSoldierAdjacentAttacked(int x, int y, int player, vector<vector<int> > myState){
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

int CannonGame::numberOfSoldierCanbeAttacked(int player, vector<vector<int> > myState){
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

int CannonGame::numberOfSoldiers(int player, vector<vector<int> > myState){
    int count = 0;
    for(int i=0;i<myState.size();i++){
        for(int j=0;j<myState.at(0).size();j++){
            if(myState.at(i).at(j) == player){
                count++;
            }
        }
    }
    return count;
}

int CannonGame::numberOfTownHall(int player, vector<vector<int> > myState){
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

int CannonGame::numberOfCannon(int player, vector<vector<int> > myState){
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


bool CannonGame::canTownHallCanBeAttacked(int x, int y, int player, vector<vector<int> > myStateVector){
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

int CannonGame::numberOfTownHallCanBeAttacked(int player, vector<vector<int> > myState){
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



bool CannonGame::isSoldierLeadOfCannon(int x, int y, int player, vector<vector<int> > myState){
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

vector<string> CannonGame::validMoves(int player, vector<vector<int> > myState){
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
            }
        }
    }
    return moves;
}

vector<string> CannonGame::validCannonMoves(int player, vector<vector<int> > myState){
    vector<string> moves;
    int n = myState.size();
    int m = myState[0].size();
    string move = "";
    if(player == 1){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
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

    if(player == 2){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
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
                            // cout<<"sona7"<<endl;
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
                            // cout<<"sona9"<<endl;
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
    return moves;
}

int CannonGame::Max_Val(int &x,vector<vector<int> > curState, int d, int alpha, int beta, int player){
	if(d == 0 || gameWinner(curState)){
        return evaluationFunction(curState);
	}
	int c, ma = INT_MIN;
    vector<string> gs;
	vector<vector<vector<int> > > nextMoves = generateSteps(gs, player, curState);
	for(int i=0; i<nextMoves.size(); i++){
        int y;
		c = Min_Val(y, nextMoves[i], d-1, alpha, beta, otherPlayer(player));
        alpha = max(alpha,c);

		if(c > ma){
			ma = c;
            x = i;
		}

        if(alpha >= beta){
			return c;
		}

	}
    return ma;
}

int CannonGame::Min_Val(int &x,vector<vector<int> > curState, int d, int alpha, int beta, int player){
	if(d == 0 || gameWinner(curState)){
		return evaluationFunction(curState);
	}

	int c, mi = INT_MAX;
    vector<string> gs;
	vector<vector<vector<int> > > nextMoves = generateSteps(gs, player, curState);
	for(int i=0; i<nextMoves.size() ;i++){
        int y;
		c = Max_Val(y,nextMoves[i], d-1, alpha, beta, otherPlayer(player));
		beta = min(beta, c);

		if(c < mi){
			mi = c;
            x = i;
		}
        if(alpha >= beta){
			return c;
		}
	}
	return mi;
}

void CannonGame::nextMove(string &retString, vector<vector<int> > &curState, int depth, int alpha, int beta, int player){
    int y;
	int c = Max_Val(y, curState, depth, alpha, beta, player);
	vector<string> gs;
	vector<vector<vector<int> > > nextMoves = generateSteps(gs, player, curState);
    retString = gs[y];
    curState = nextMoves[y];

	return;
}
int CannonGame::gameWinner(vector<vector<int> > myState){
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


