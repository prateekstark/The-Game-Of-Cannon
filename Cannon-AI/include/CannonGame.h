#include "utils.h"
class CannonGame{
public:
    vector<vector<int> > board;
    vector<int> coefficients;
    CannonGame(int player, int n, int m);
    
    int evaluationFunction(vector<vector<int> > myState);

    bool areTwoMatrixEqual(vector<vector<int> > v1, vector<vector<int> > v2);

    vector<string> convertStringToVector(string str);

    vector<vector<int> > executeMove(vector<string> moveVector, vector<vector<int> > myState);

    bool doesSpaceContainPlane(vector<vector<vector<int> > > space, vector<vector<int> > plane);

    vector<vector<vector<int> > > generateSteps(vector<string> &genStringMoves, int player, vector<vector<int> > myState);

    bool canSoldierBeAttacked(int x, int y, int player, vector<vector<int> > myState);

    bool isSoldierAdjacentAttacked(int x, int y, int player, vector<vector<int> > myState);

    int numberOfSoldierCanbeAttacked(int player, vector<vector<int> > myState);

    int numberOfSoldiers(int player, vector<vector<int> > myState);

    int numberOfTownHall(int player, vector<vector<int> > myState);

    int numberOfCannon(int player, vector<vector<int> > myState);

    int closenessFactor(int player, vector<vector<int> > myState);

    bool canTownHallCanBeAttacked(int x, int y, int player, vector<vector<int> > myState);

    int numberOfTownHallCanBeAttacked(int player, vector<vector<int> > myState);

    bool isSoldierLeadOfCannon(int x, int y, int player, vector<vector<int> > myState);

    vector<string> validMoves(int player, vector<vector<int> > myState);

    vector<string> validCannonMoves(int player, vector<vector<int> > myState);

    int Max_Val(int &x,vector<vector<int> > curState, int d, int alpha, int beta, int player);

    int Min_Val(int &x,vector<vector<int> > curState, int d, int alpha, int beta, int player);

    void nextMove(string &retString, vector<vector<int> > &curState, int depth, int alpha, int beta, int player);

    int gameWinner(vector<vector<int> > myState);

};