#include "CannonGame.h"

const int IN_PROGRESS = 0;
const int WIN_SCORE = 10;


class State{
public:
	CannonGame* board;
	int player;
	int visitCount;
	double winScore;
	State();
	vector<State> possibleStates(vector<string> &ss);
	void randomMove();
};

class Node{
public:	
	State state;
	Node* parent;
	vector<Node*> children;
	vector<string> schildren;

	Node();

	Node* getRandomChildNode();

	Node* getChildWithMaxScore(string &s);
};

class Tree{
public:
	Node* root;
};

class UCT{
public:
	double uctValue(int totalVisit, double nodeWinScore, int nodeVisit);

	Node* findBestNodeWithUCT(Node* node);
};


Node* getPNode(Node* rootNode);

class MCTS{
public:

	int level;
	int opponent;

	CannonGame* playNextMove(CannonGame* board, int player, string &s, int &levels);

	void expandNode(Node* node);

	void backPropogation(Node* nodeToExplore, int player);

	int simulateRandomPlayout(Node* node);

};