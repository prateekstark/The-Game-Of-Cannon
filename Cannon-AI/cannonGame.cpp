#include<iostream>
#include<vector>

using namespace std;

class CannonGame{
public:
    vector<vector<int> > board;
    Board(){
        vector<int> tempVector1({1, 10, 1, 10, 1, 10, 1, 10});
        vector<int> tempVector2({1, 0, 1, 0, 1, 0, 1, 0});
        vector<int> tempVector3({0, 0, 0, 0, 0, 0, 0, 0});
        vector<int> tempVector4({20, 2, 20, 2, 20, 2, 20, 2});
        vector<int> tempVector5({0, 2, 0, 2, 0, 2, 0, 2});
        board.push_back(tempVector4);
        board.push_back(tempVector5);
        board.push_back(tempVector5);
        board.push_back(tempVector3);
        board.push_back(tempVector3);
        board.push_back(tempVector2);
        board.push_back(tempVector2);
        board.push_back(tempVector1);
    }

    bool canSoldierBeAttacked(int x, int y, int player, vector<vector<int> > myState){
        if(myState.at(x).at(y) != player){
            cerr<<"Wrong player!"<<endl;
            return false;
        }
        int n = board.size();
        int m = board.at(0).size();
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

    void printState(vector<vector<int> > myState){
        for(int i=0;i<myState.size();i++){
            for(int j=0;j<myState.at(0).size();j++){
                cout<<myState.at(i).at(j)<<" ";
            }
            cout<<endl;
        }
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
                                if(myState.at(i).at(j-2) == 0 && myState.at(i).at(j-1) == 0){
    								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j-2);
    								moves.push_back(move);
    							}
                                if(i-2 >= 0){
                                    if(myState.at(i-2).at(j-2) == 0 && myState.at(i-1).at(j-1) == 0){
        								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-2) + " " + to_string(j-2);
        								moves.push_back(move);
        							}
                                }
                                if(i+2 < n){
                                    if(myState.at(i+2).at(j-2) == 0 && myState.at(i+1).at(j-1) == 0){
        								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+2) + " " + to_string(j-2);
        								moves.push_back(move);
        							}
                                }
                            }
                        }
                        if(i+1 < n){
                            if(myState.at(i+1).at(j) == 1){
    							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j);
    							moves.push_back(move);
    						}
                            if(j+1 < m){
                                if(myState.at(i+1).at(j+1) != 2){
        							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j+1);
        							moves.push_back(move);
        						}
                            }
                        }
                        if(i-1 >= 0){
                            if(myState.at(i-1).at(j) == 1){
    							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-1) + " " + to_string(j);
    							moves.push_back(move);
    						}
                            if(j+1 < m){
                                if(myState.at(i-1).at(j+1) != 2){
        							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-1) + " " + to_string(j+1);
        							moves.push_back(move);
        						}
                            }
                        }
                        if(j+1 < m){
                            if(myState.at(i).at(j+1) != 2){
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
                        soldierCondition = canSoldierBeAttacked(i, j, 1, myState);
                        if(soldierCondition){
                            if(j+2 >= 0){
                                if(myState.at(i).at(j+2) == 0 && myState.at(i).at(j+1) == 0){
    								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j+2);
    								moves.push_back(move);
    							}
                                if(i-2 >= 0){
                                    if(myState.at(i-2).at(j+2) == 0 && myState.at(i-1).at(j+1) == 0){
        								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-2) + " " + to_string(j+2);
        								moves.push_back(move);
        							}
                                }
                                if(i+2 < n){
                                    if(myState.at(i+2).at(j+2) == 0 && myState.at(i+1).at(j+1) == 0){
        								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+2) + " " + to_string(j+2);
        								moves.push_back(move);
        							}
                                }
                            }
                        }
                        if(i+1 < n){
                            if(myState.at(i+1).at(j) == 1){
    							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j);
    							moves.push_back(move);
    						}
                            if(j-1 < m){
                                if(myState.at(i+1).at(j-1) != 2){
        							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j-1);
        							moves.push_back(move);
        						}
                            }
                        }
                        if(i-1 >= 0){
                            if(myState.at(i-1).at(j) == 1){
    							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-1) + " " + to_string(j);
    							moves.push_back(move);
    						}
                            if(j-1 < m){
                                if(myState.at(i-1).at(j-1) != 2){
        							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-1) + " " + to_string(j-1);
        							moves.push_back(move);
        						}
                            }
                        }
                        if(j-1 < m){
                            if(myState.at(i).at(j-1) != 2){
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

    vector<string> validCannonMovesNonCapture(int player, vector<vector<int> > myState){
        vector<string> moves;
        int n = myState.size();
        int m = myState.at(0).size();
        if(player == 1){
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){
                    if(isSoldierLeadOfCannon(i, j, 1, myState)){
                        if(j+2 < m){
                            if(myState.at(i).at(j+1) == 1 && myState.at(i).at(j+2) == 1){
                                if(j+3 < m){
                                    if(myState.at(i).at(j+3) == 0){
        								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j+3);
        								moves.push_back(move);
        							}
                                }
                                if(j-1 >= 0){
                                    if(myState.at(i).at(j-1) == 0){
        								move = "S " + to_string(i) + " " + to_string(j+2) + " M " + to_string(i) + " " + to_string(j-1);
        								moves.push_back(move);
        							}
                                }
                                if(j-2 >= 0){
                                    move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-2);
        							moves.push_back(move);
                                }
                                if(j-3 >= 0){
                                    move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-3);
        							moves.push_back(move);
                                }
                                if(j+4 < m){
                                    move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+4);
        							moves.push_back(move);
                                }
                                if(j+5 < m){
                                    move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+5);
        							moves.push_back(move);
                                }
                            }
                            if(i-2 >= 0){
                                if(myState.at(i-1).at(j+1) == 1 && myState.at(i-2).at(j+2) == 1){
                                    if(i-3 >= 0 && j+3 < m){
                                        if(myState.at(i-3).at(j+3) == 0){
            								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-3) + " " + to_string(j+3);
            								moves.push_back(move);
            							}
                                    }
                                    if(i+1 <= n && j-1 >= 0){
                                        if(myState.at(i+1).at(j-1) == 0){
            								move = "S " + to_string(i-2) + " " + to_string(j+2) + " M " + to_string(i+1) + " " + to_string(j-1);
            								moves.push_back(move);
            							}
                                    }
                                    if(j-2 >= 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-2);
            							moves.push_back(move);
                                    }
                                    if(j-3 >= 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-3);
            							moves.push_back(move);
                                    }
                                    if(j+4 < m){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+4);
            							moves.push_back(move);
                                    }
                                    if(j+5 < m){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+5);
            							moves.push_back(move);
                                    }
                                }
                            }
                            if(i+2 < n){
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
                                    if(j-2 >= 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-2);
            							moves.push_back(move);
                                    }
                                    if(j-3 >= 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-3);
            							moves.push_back(move);
                                    }
                                    if(j+4 < m){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+4);
            							moves.push_back(move);
                                    }
                                    if(j+5 < m){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+5);
            							moves.push_back(move);
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
                            if(myState.at(i).at(j-1) == 2 && myState.at(i).at(j-2) == 2){
                                if(j-3 >= 0){
                                    if(myState.at(i).at(j-3) == 0){
        								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j-3);
        								moves.push_back(move);
        							}
                                }
                                if(j+1 < m){
                                    if(myState.at(i).at(j+1) == 0){
        								move = "S " + to_string(i) + " " + to_string(j-2) + " M " + to_string(i) + " " + to_string(j+1);
        								moves.push_back(move);
        							}
                                }
                                if(j+2 < m){
                                    move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+2);
        							moves.push_back(move);
                                }
                                if(j+3 < m){
                                    move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+3);
        							moves.push_back(move);
                                }
                                if(j-4 >= 0){
                                    move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-4);
        							moves.push_back(move);
                                }
                                if(j-5 >= 0){
                                    move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-5);
        							moves.push_back(move);
                                }
                            }
                            if(i-2 >= 0){
                                if(myState.at(i-1).at(j-1) == 2 && myState.at(i-2).at(j-2) == 2){
                                    if(i-3 >= 0 && j-3 >= 0){
                                        if(myState.at(i-3).at(j-3) == 0){
            								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-3) + " " + to_string(j-3);
            								moves.push_back(move);
            							}
                                    }
                                    if(i+1 <= n && j+1 < m){
                                        if(myState.at(i+1).at(j+1) == 0){
            								move = "S " + to_string(i-2) + " " + to_string(j-2) + " M " + to_string(i+1) + " " + to_string(j+1);
            								moves.push_back(move);
            							}
                                    }
                                    if(j+2 < m){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+2);
            							moves.push_back(move);
                                    }
                                    if(j+3 < m){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+3);
            							moves.push_back(move);
                                    }
                                    if(j-4 >= 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-4);
            							moves.push_back(move);
                                    }
                                    if(j-5 >= 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-5);
            							moves.push_back(move);
                                    }
                                }
                            }
                            if(i+2 < n){
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
                                    if(j+2 < m){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+2);
            							moves.push_back(move);
                                    }
                                    if(j+3 < m){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j+3);
            							moves.push_back(move);
                                    }
                                    if(j-4 >= 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-4);
            							moves.push_back(move);
                                    }
                                    if(j-5 >= 0){
                                        move = "S " + to_string(i) + " " + to_string(j) + " B " + to_string(i) + " " + to_string(j-5);
            							moves.push_back(move);
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
};
