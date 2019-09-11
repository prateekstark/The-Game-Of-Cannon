#include<iostream>
#include<vector>

using namespace std;
class Board{
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

	bool canSoldierBeAttacked(int x, int y, iny player, vector<vector<int> > myState){
		if(myState.at(x).at(y) != player){
			cerr<<"Wrong player!"<<endl;
			return false;
		}

		if(player == 2){
			if(myState.at(x).at(y+1) == 1){
				return true;
			}

			if(myState.at(x+1).at(y+1) == 1){
				return true;
			}

			if(myState.at(x-1).at(y+1) == 1){
				return true;
			}

			if(myState.at(x+1).at(y) == 1){
				return true;
			}

			if(myState.at(x-1).at(y) == 1){
				return true;
			}
			if(isSoldierLeadOfCannon(x, y+2, 1, myState) || isSoldierLeadOfCannon(x, y+3, 1, myState)){
				return true;
			}
			if(isSoldierLeadOfCannon(x, y-2, 1, myState) || isSoldierLeadOfCannon(x, y-3, 1, myState)){
				return true;
			}
			if(isSoldierLeadOfCannon(x+2, y+2, 1, myState) || isSoldierLeadOfCannon(x+3, y+3, 1, myState)){
				return true;
			}
			if(isSoldierLeadOfCannon(x-2, y-2, 1, myState) || isSoldierLeadOfCannon(x-3, y-3, 1, myState)){
				return true;
			}

			if(isSoldierLeadOfCannon(x+2, y-2, 1, myState) || isSoldierLeadOfCannon(x+3, y-3, 1, myState)){
				return true;
			}

			if(isSoldierLeadOfCannon(x-2, y+2, 1, myState) || isSoldierLeadOfCannon(x-3, y+3, 1, myState)){
				return true;
			}
		}
		else if(player == 1){
			if(myState.at(x).at(y+1) == 2){
				return true;
			}

			if(myState.at(x+1).at(y+1) == 2){
				return true;
			}

			if(myState.at(x-1).at(y+1) == 2){
				return true;
			}

			if(myState.at(x+1).at(y) == 2){
				return true;
			}

			if(myState.at(x-1).at(y) == 2){
				return true;
			}
			if(isSoldierLeadOfCannon(x, y+2, 2, myState) || isSoldierLeadOfCannon(x, y+3, 2, myState)){
				return true;
			}
			if(isSoldierLeadOfCannon(x, y-2, 2, myState) || isSoldierLeadOfCannon(x, y-3, 2, myState)){
				return true;
			}
			if(isSoldierLeadOfCannon(x+2, y+2, 2, myState) || isSoldierLeadOfCannon(x+3, y+3, 2, myState)){
				return true;
			}
			if(isSoldierLeadOfCannon(x-2, y-2, 2, myState) || isSoldierLeadOfCannon(x-3, y-3, 2, myState)){
				return true;
			}

			if(isSoldierLeadOfCannon(x+2, y-2, 2, myState) || isSoldierLeadOfCannon(x+3, y-3, 2, myState)){
				return true;
			}

			if(isSoldierLeadOfCannon(x-2, y+2, 2, myState) || isSoldierLeadOfCannon(x-3, y+3, 2, myState)){
				return true;
			}	
		}
		return false;
	}

	bool isSoldierLeadOfCannon(int x, int y, int player, vector<vector<int> > myState){
		if(myState.at(x).at(y) == player){
			if(player == 2){
				if(myState.at(x).at(y-1) == 2 && myState.at(x).at(y-2) == 2){
					return true;
				}
				if(myState.at(x-1).at(y-1) == 2 && myState.at(x-2).at(y-2) == 2){
					return true;
				}
				if(myState.at(x+1).at(y-1) == 2 && myState.at(x+2).at(y-2) == 2){
					return true;
				}
			}
			else if(player == 1){
				if(myState.at(x).at(y+1) == 1 && myState.at(x).at(y+2) == 1){
					return true;
				}
				if(myState.at(x-1).at(y+1) == 1 && myState.at(x-2).at(y+2) == 1){
					return true;
				}
				if(myState.at(x+1).at(y+1) == 1 && myState.at(x+2).at(y+2) == 1){
					return true;
				}
			}
		}
		return false;
	}

	void printState(){
		for(int i=0;i<board.size();i++){
			for(int j=0;j<board.at(0).size();j++){
				cout<<board.at(i).at(j)<<" ";
			}
			cout<<endl;
		}
	}

	vector<string> validMovesWithoutCapture(int player, vector<vector<int> > myState){
		vector<string> moves;
		if(player == 2){
			string move;
			for(int i=0;i<myState.size();i++){
				for(int j=0;j<myState.at(0).size(0);j++){
					if(myState.at(i).at(j) == 2){
						bool soldierCondition = canSoldierBeAttacked(i, j, 2, myState);
						if(soldierCondition){
							if(myState.at(i).at(j-2) == 0 && myState.at(i).at(j-1) == 0){
								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j-2);
								moves.push_back(move);
							}
							if(myState.at(i-2).at(j-2) == 0 && myState.at(i-1).at(j-1) == 0){
								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-2) + " " + to_string(j-2);
								moves.push_back(move);
							}
							if(myState.at(i+2).at(j-2) == 0 && myState.at(i+1).at(j-1) == 0){
								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+2) + " " + to_string(j-2);
								moves.push_back(move);
							}
						}
						if(myState.at(i).at(j+1) == 0){
							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j+1);
							moves.push_back(move);
						}
						if(myState.at(i+1).at(j+1) == 0){
							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j+1);
							moves.push_back(move);
						}
						if(myState.at(i-1).at(j+1) == 0){
							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-1) + " " + to_string(j+1);
							moves.push_back(move);
						}
					}
				}
			}
		}
		if(player == 1){
			string move;
			for(int i=0;i<myState.size();i++){
				for(int j=0;j<myState.at(0).size(0);j++){
					if(myState.at(i).at(j) == 1){
						bool soldierCondition = canSoldierBeAttacked(i, j, 1, myState);
						if(soldierCondition){
							if(myState.at(i).at(j+2) == 0 && myState.at(i).at(j+1) == 0){
								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j+2);
								moves.push_back(move);
							}
							if(myState.at(i-2).at(j+2) == 0 && myState.at(i-1).at(j+1) == 0){
								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+2) + " " + to_string(j+2);
								moves.push_back(move);
							}
							if(myState.at(i+2).at(j+2) == 0 && myState.at(i+1).at(j+1) == 0){
								move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+2) + " " + to_string(j+2);
								moves.push_back(move);
							}
						}
						if(myState.at(i).at(j-1) == 0){
							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i) + " " + to_string(j-1);
							moves.push_back(move);
						}
						if(myState.at(i+1).at(j-1) == 0){
							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i+1) + " " + to_string(j-1);
							moves.push_back(move);
						}
						if(myState.at(i-1).at(j-1) == 0){
							move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(i-1) + " " + to_string(j-1);
							moves.push_back(move);
						}
					}
				}
			}
		}
		return moves;
	}


	bool canSoldierAttack

	// vector<string> captureMoves(int player){


	// }






};



int main(){
	Board* newGame = new Board();
	newGame->printState();
	return 0;
}