#include "../include/MCTS.h"

int xdim=8, ydim=8;

int CannonGame::gameWinnerMCTS(){
    int n1 = numberOfTownHall(1, board);
    int n2 = numberOfTownHall(2, board);
    if(n1-n2 == 2){
        return 1;
    }
    if(n2-n1 == 2){
        return 2;
    }
    vector<string> gs;
    vector<vector<vector<int> > > nextMoves = generateSteps(gs, this->player, board);
    if(nextMoves.size() == 0){
    	return -1;
    }
    nextMoves = generateSteps(gs, 3 - player, board);
    if(nextMoves.size() == 0){
    	return -1;
    }
    return 0;
}



State::State(){
	player = 1;
	board = new CannonGame(player, xdim, ydim);
	visitCount = 0;
	winScore = 0;
}

vector<State> State::possibleStates(vector<string> &ss){
	vector<string> gs;
	int n = board->board.size();
	int m = board->board[0].size();
	vector<vector<vector<int> > > nextMoves = board->generateSteps(gs, player, board->board);
	vector<State> possibleStates;
	ss = gs;
	for(int i=0 ; i<nextMoves.size() ; i++){
		State s = State();
		s.board->board = nextMoves[i];
		s.player = 3 - player;
		s.board->player = s.player;
		possibleStates.push_back(s);
	}
	return possibleStates;
}
void State::randomMove(){
	vector<string> gs;
	vector<vector<vector<int> > > nextMoves = board->generateSteps(gs, player, board->board);
	srand(time(0));
	if(nextMoves.size() == 0){
		cout<< " bada LOL " << endl;
	}
	int r = ((int) rand())%nextMoves.size();
	board->board = nextMoves[r];
}

Node::Node(){
	state = State();
	parent = NULL;
}

Node* Node::getRandomChildNode(){
	srand(time(0));
	int r = ((int) rand())%children.size();
	return children[r];
}

Node* Node::getChildWithMaxScore(string &s){
	int k = -1;
	double t = (double) INT_MIN;
	for(int i=0 ; i<children.size() ; i++){
		if(children[i]->state.visitCount == 0){
			s = schildren[i];
			return children[i];
		}
		if((children[i]->state.winScore / children[i]->state.visitCount) > t){
			t = (children[i]->state.winScore / children[i]->state.visitCount);
			k = i;
		}
	}
	s = schildren[k];
	return children[k];
}

double UCT::uctValue(int totalVisit, double nodeWinScore, int nodeVisit){
	if(nodeVisit == 0){
		return INT_MAX;
	}
	return ((double) nodeWinScore / (double) nodeVisit) + 2 * sqrt(log(totalVisit) / (double) nodeVisit);
}

Node* UCT::findBestNodeWithUCT(Node* node){
	int parentVisit = node->state.visitCount;
	vector<Node*> children = node->children;
	double ma = (double)INT_MIN;
	int k = -1;
	for(int i=0; i<children.size() ; i++){
		double t = uctValue(parentVisit, children[i]->state.winScore, children[i]->state.visitCount);
		if(ma < t){
			ma = t;
			k = i;
		}
	}
	return children[k];
}



Node* getPNode(Node* rootNode){
	Node* node = rootNode;
	UCT uct;
	while(node->children.size() != 0){
		node = uct.findBestNodeWithUCT(node);
	}
	return node;
}

CannonGame* MCTS::playNextMove(CannonGame* board, int player, string &s, int &levels){
	// cout<<"1"<<endl;
	opponent = 3 - player;
	Tree tree = Tree();
	xdim= board->board.size();
	ydim = board->board[0].size();
	tree.root = new Node();
	Node* rootNode = tree.root;
	rootNode->state.board->board = board->board;
	rootNode->state.player = player;
	rootNode->state.board->player = player;

	auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    int timed=(int)duration.count();
    // cout<<"2"<<endl;
    int x = 0;
	while(timed < 3){
		x++;
		Node* pNode = getPNode(rootNode);
		if(pNode->state.board->gameWinnerMCTS() == IN_PROGRESS){
			expandNode(pNode);
		}
		// cout<<"3"<<endl;
		Node* nodeToExplore = pNode;
		if(pNode->children.size() > 0){
			nodeToExplore = pNode->getRandomChildNode();
		}
		// cout<<"4"<<endl;
		int playoutResult = simulateRandomPlayout(nodeToExplore);
		// cout<<"5"<<endl;
		backPropogation(nodeToExplore, playoutResult);
		// cout<<"6"<<endl;
		stop = high_resolution_clock::now();
		duration = duration_cast<seconds>(stop - start);
    	timed=(int)duration.count();
	}
    levels = x;
	// cout<<"7"<<endl;
	Node* winnerNode = rootNode->getChildWithMaxScore(s);
	// cout<<"8"<<endl;
	rootNode = winnerNode;
	return winnerNode->state.board;
}

void MCTS::expandNode(Node* node){
	vector<string> ss;
	vector<State> possibleStates = node->state.possibleStates(ss);
	node->schildren= ss;
	for(int i=0; i<possibleStates.size() ; i++){
		Node* newNode = new Node();
		newNode->state = possibleStates[i];
		newNode->parent = node;
		newNode->state.player = 3 - node->state.player;
		newNode->state.board->player = newNode->state.player;
		node->children.push_back(newNode);
	}
}

void MCTS::backPropogation(Node* nodeToExplore, int player){
	Node* tempNode = nodeToExplore;
	while(tempNode != NULL){
		tempNode->state.visitCount ++;
		if(tempNode->state.player == player){
			tempNode->state.winScore += WIN_SCORE;
		}
		tempNode = tempNode->parent;
	}
}

int MCTS::simulateRandomPlayout(Node* node){
	Node* tempNode = new Node();
	*tempNode = *node;
	State tempState = tempNode->state;
	// cout<<"9"<<endl;
	int boardStatus = tempState.board->gameWinnerMCTS();
	if(boardStatus == opponent){
		// cout<<"10"<<endl;
		tempNode->parent->state.winScore = -WIN_SCORE;
		return boardStatus;
	}
	int x = 0;
	while(boardStatus == IN_PROGRESS){
		x++;
		// cout<<x<<endl;
		tempState.player = 3 - tempState.player;
		tempState.board->player = tempState.player;
		// cout<<"11"<<endl;
		tempState.randomMove();
		boardStatus = tempState.board->gameWinnerMCTS();
	}
	// cout<<"12"<<endl;
	return boardStatus;
}
