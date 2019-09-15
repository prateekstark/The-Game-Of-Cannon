#include<iostream>
#include<vector>

using namespace std;


int Min_Val(vector<vector<int> > curState,int d);
int Max_Val(vector<vector<int> > curState,int d);

void nextMove(vector<vector<int> > &curState, int depth, int alpha, int beta){

	vector<vector<int> > ret;
	int c = Max_Val(ret, curState, depth, alpha, beta);

	curState = ret;

	return;
}

int Max_Val(vector<vector<int> > &ret, vector<vector<int> > curState, int d, int alpha, int beta){
	
	if(d == 0){
		ret = curState;
		return evaluationFunction(curState); 
	}

	int c,ma = INT_MIN;

	vector<vector<vector<int> > > nextMoves = possibleMoves(curState);

	for(int i=0; i<nextMoves.size() ;i++){

		vector<vector<int> > r;
		c = Min_val(r,nextMoves[i],d-1,alpha,beta);
		alpha = max(alpha,c);

		if(alpha >= beta){
			ret = r;
			return c;
		}

		if(c > ma){
			ma = c;
			ret = r;
		}
	}

	return ma;
}

int Min_Val(vector<vector<int> > &ret, vector<vector<int> > curState, int d, int alpha, int beta){
	
	if(d == 0){
		ret = curState;
		return evaluationFunction(curState); 
	}

	int c,mi = INT_MAX;

	vector<vector<vector<int> > > nextMoves = possibleMoves(curState);

	for(int i=0; i<nextMoves.size() ;i++){

		vector<vector<int> > r;
		c = Max_val(r,nextMoves[i],d-1,alpha,beta);
		beta = min(beta,c);

		if(alpha >= beta){
			ret = r;
			return c;
		}

		if(c < mi){
			mi = c;
			ret = r;
		}
	}

	return mi;
}

