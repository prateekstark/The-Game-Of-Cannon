#include "../include/CannonGame.h"
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
        // ofstream file;sssss
        while(timed < time){
        	int d;
        	if(timed < time/3){
        		d = 3;
        	}else if(timed < 5*time/6){
        		d = 4;
        	}else{
        		d = 2;
        	}

            string s = "";
            game->nextMove(s, game->board, d, INT_MIN, INT_MAX, player);
            // printState(game->board);
            cout<<s<<endl;
            opponentMove = "";
            for(int i=0;i<6;i++){
                cin>>a;
                abc.push_back(a);
            }
            game->board = game->executeMove(abc, game->board);
            // printState(game->board);
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
        		d = 3;
        	}else if(timed < 5*time/6){
        		d = 4;
        	}else{
        		d = 2;
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
