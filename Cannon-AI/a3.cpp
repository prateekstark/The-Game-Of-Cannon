#include<iostream>
#include<fstream>
#include<stdio.h>
#include<sstream>
#include<vector>
#include<time.h>
#include<chrono>
#include<climits>

using namespace std;

class Board{
    
    public:
    vector<vector<int> > game_board;
    vector<pair<int,int> > whites;
    vector<pair<int,int> > blacks;
    string theMove;
    int alpha;
    int beta;
    int cost;
    vector<vector<pair<int,int> > > white_canons;
    vector<vector<pair<int,int> > > black_canons;
    Board(){
        alpha = INT_MIN;
        beta = INT_MAX;
        cost = 0;
        whites.push_back(make_pair(0,1));
        whites.push_back(make_pair(1,1));
        whites.push_back(make_pair(2,1));
        whites.push_back(make_pair(0,3));
        whites.push_back(make_pair(1,3));
        whites.push_back(make_pair(2,3));
        whites.push_back(make_pair(0,5));
        whites.push_back(make_pair(1,5));
        whites.push_back(make_pair(2,5));
        whites.push_back(make_pair(0,7));
        whites.push_back(make_pair(1,7));
        whites.push_back(make_pair(2,7));
        
        blacks.push_back(make_pair(7,0));
        blacks.push_back(make_pair(7,2));
        blacks.push_back(make_pair(7,4));
        blacks.push_back(make_pair(7,6));
        blacks.push_back(make_pair(6,0));
        blacks.push_back(make_pair(6,2));
        blacks.push_back(make_pair(6,4));
        blacks.push_back(make_pair(6,6));
        blacks.push_back(make_pair(5,0));
        blacks.push_back(make_pair(5,2));
        blacks.push_back(make_pair(5,4));
        blacks.push_back(make_pair(5,6));
        
        vector<pair<int,int> > a;
        a.push_back(make_pair(0,1));
        a.push_back(make_pair(1,1));
        a.push_back(make_pair(2,1));
        white_canons.push_back(a);
        vector<pair<int,int> > b;
        b.push_back(make_pair(0,3));
        b.push_back(make_pair(1,3));
        b.push_back(make_pair(2,3));
        white_canons.push_back(b);
        vector<pair<int,int> > c;
        c.push_back(make_pair(0,5));
        c.push_back(make_pair(1,5));
        c.push_back(make_pair(2,5));
        white_canons.push_back(c);
        vector<pair<int,int> > d;
        d.push_back(make_pair(0,7));
        d.push_back(make_pair(1,7));
        d.push_back(make_pair(2,7));
        white_canons.push_back(d);
        
        vector<pair<int,int> > a1;
        a1.push_back(make_pair(7,0));
        a1.push_back(make_pair(6,0));
        a1.push_back(make_pair(5,0));
        black_canons.push_back(a1);
        vector<pair<int,int> > b1;
        b1.push_back(make_pair(7,2));
        b1.push_back(make_pair(6,2));
        b1.push_back(make_pair(5,2));
        black_canons.push_back(b1);
        vector<pair<int,int> > c1;
        c1.push_back(make_pair(7,4));
        c1.push_back(make_pair(6,4));
        c1.push_back(make_pair(5,4));
        black_canons.push_back(c1);
        vector<pair<int,int> > d1;
        d1.push_back(make_pair(7,6));
        d1.push_back(make_pair(6,6));
        d1.push_back(make_pair(5,6));
        black_canons.push_back(d1);
        
        vector<int> x;
        for(int i=0;i<8;i++){
            x.push_back(0);
        }
        for(int i=0;i<8;i++){
            game_board.push_back(x);
        }
        
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(i==0){
                    if(j%2==0){
                        game_board[i][j] = 2;
                    }
                    else{
                        game_board[i][j] = 1;
                        game_board[i+1][j] = 1;
                        game_board[i+2][j] = 1;
                    }
                }
                if(i==1){
                    i=7;
                }
                if(i==7){
                    if(j%2!=0){
                        game_board[i][j] = -2;
                    }
                    else{
                        game_board[i][j] = -1;
                        game_board[i-1][j] = -1;
                        game_board[i-2][j] = -1;
                    }
                }
            }
        }
    }
    
};

int gameBoardCost (Board b,int k)
{   int index_sum_whites = 0;
    int index_sum_blacks = 0;
    int black_soldiers = b.blacks.size();
    int white_soldiers = b.whites.size();
    int black_townhalls = 0;
    int white_townhalls = 0;
    for (int i = 0;i<b.blacks.size();i++)
    {
        index_sum_blacks += (7-b.blacks[i].first);
    }
    
    for (int i = 0;i<b.whites.size();i++)
    {
        index_sum_whites += (b.whites[i].first);
    }
    
    for (int i = 0;i<4;i++)
    {
        if (b.game_board[0][2*i] == 2)
        white_townhalls++;
        if (b.game_board[7][2*i+1] == -2)
        black_townhalls++;
    }
    int cost = 0;
    cost = 5*(white_soldiers-black_soldiers)+50*(white_townhalls)-20*(black_townhalls)+ 2 *index_sum_whites- 3 * index_sum_blacks;
    if(white_townhalls == 4){
        cost = 4 * cost;
    }
    if(white_townhalls == 3){
        cost = 2*cost;
    }
    return (cost);
}


bool compare(vector<pair<int,int> >a,vector<pair<int,int> >b){
    for(int i=0;i<3;i++){
        bool xd = false;
        for(int j=0;j<3;j++){
            if(a[i] == b[j]){
                xd = true;
            }
        }
        if(!xd){
            return false;
        }
    }
    return true;
}


Board newBoardBlack(bool isCanon, pair<int,int> initial, pair<int,int> final, Board b, vector<pair<int,int> > initial_canon, vector<pair<int,int> > final_canon, pair<int, int> killer){
    if(!isCanon){
        
        if(b.game_board[final.first][final.second] == 1){
            for(int i=0;i<b.whites.size();i++){
                if(final == b.whites[i]){
                    b.whites.erase(b.whites.begin() + i);
                    break;
                }
            }
        }
        
        for(int i=0;i<b.white_canons.size();i++){
            for(int j=0;j<3;j++){
                if(b.white_canons[i][j].first == final.first && b.white_canons[i][j].second == final.second){
                    b.white_canons.erase(b.white_canons.begin() + i);
                    i--;
                    j=3;
                }
            }
        }
        
        
        for(int i=0;i<b.blacks.size();i++){
            if(b.blacks[i] == initial){
                b.blacks.erase(b.blacks.begin()+i);
                break;
            }
        }
        
        b.blacks.push_back(final);
        
        for(int i=0;i<b.black_canons.size();i++){
            for(int j=0;j<3;j++){
                if(b.black_canons[i][j].first == initial.first && b.black_canons[i][j].second == initial.second){
                    b.black_canons.erase(b.black_canons.begin() + i);
                    i--;
                    j=3;
                }
            }
        }
        
        b.game_board[initial.first][initial.second] = 0;
        b.game_board[final.first][final.second] = -1;
        
        if(final.second-1>=0 && final.first-1>=0){
            if(b.game_board[final.first-1][final.second-1] == -1){
                if(final.first+1<8 && final.second+1<8){
                    if(b.game_board[final.first+1][final.second+1] == -1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final.first,final.second));
                        as.push_back(make_pair(final.first+1,final.second+1));
                        as.push_back(make_pair(final.first-1,final.second-1));
                        bool sdf = false;
                        for(int i=0;i<b.black_canons.size();i++){
                            if(compare(b.black_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.black_canons.push_back(as);
                        }
                    }
                }
            }
        }
        
        if(final.first-1>=0){
            if(b.game_board[final.first-1][final.second] == -1){
                if(final.first+1<8){
                    if(b.game_board[final.first+1][final.second] == -1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final.first,final.second));
                        as.push_back(make_pair(final.first+1,final.second));
                        as.push_back(make_pair(final.first-1,final.second));
                        bool sdf = false;
                        for(int i=0;i<b.black_canons.size();i++){
                            if(compare(b.black_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.black_canons.push_back(as);
                        }
                    }
                }
            }
        }
        
        if(final.second-1>=0){
            if(b.game_board[final.first][final.second-1] == -1){
                if(final.second+1<8){
                    if(b.game_board[final.first][final.second+1] == -1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final.first,final.second));
                        as.push_back(make_pair(final.first,final.second+1));
                        as.push_back(make_pair(final.first,final.second-1));
                        bool sdf = false;
                        for(int i=0;i<b.black_canons.size();i++){
                            if(compare(b.black_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.black_canons.push_back(as);
                        }
                    }
                }
            }
        }
        
        if(final.second-1>=0 && final.first+1<8){
            if(b.game_board[final.first+1][final.second-1] == -1){
                if(final.first-1>=0 && final.second+1<8){
                    if(b.game_board[final.first-1][final.second+1] == -1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final.first,final.second));
                        as.push_back(make_pair(final.first+1,final.second-1));
                        as.push_back(make_pair(final.first-1,final.second+1));
                        bool sdf = false;
                        for(int i=0;i<b.black_canons.size();i++){
                            if(compare(b.black_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.black_canons.push_back(as);
                        }
                    }
                }
            }
        }
        
        if(final.first-2>=0 && final.second-2>=0){
            if(b.game_board[final.first-1][final.second-1] == -1 && b.game_board[final.first-2][final.second-2] == -1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first-1,final.second-1));
                as.push_back(make_pair(final.first-2,final.second-2));
                bool sdf = false;
                for(int i=0;i<b.black_canons.size();i++){
                    if(compare(b.black_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.black_canons.push_back(as);
                }
            }
        }
        
        if(final.first-2>=0){
            if(b.game_board[final.first-1][final.second] == -1 && b.game_board[final.first-2][final.second] == -1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first-1,final.second));
                as.push_back(make_pair(final.first-2,final.second));
                bool sdf = false;
                for(int i=0;i<b.black_canons.size();i++){
                    if(compare(b.black_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.black_canons.push_back(as);
                }
            }
        }
        
        if(final.first+2<=7){
            if(b.game_board[final.first+1][final.second] == -1 && b.game_board[final.first+2][final.second] == -1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first+1,final.second));
                as.push_back(make_pair(final.first+2,final.second));
                bool sdf = false;
                for(int i=0;i<b.black_canons.size();i++){
                    if(compare(b.black_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.black_canons.push_back(as);
                }
            }
        }
        
        if(final.second-2>=0){
            if(b.game_board[final.first][final.second-1] == -1 && b.game_board[final.first][final.second-2] == -1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first,final.second-1));
                as.push_back(make_pair(final.first,final.second-2));
                bool sdf = false;
                for(int i=0;i<b.black_canons.size();i++){
                    if(compare(b.black_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.black_canons.push_back(as);
                }
            }
        }
        
        if(final.second+2<=7){
            if(b.game_board[final.first][final.second+1] == -1 && b.game_board[final.first][final.second+2] == -1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first,final.second+1));
                as.push_back(make_pair(final.first,final.second+2));
                bool sdf = false;
                for(int i=0;i<b.black_canons.size();i++){
                    if(compare(b.black_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.black_canons.push_back(as);
                }
            }
        }
        
        
        if(final.first+2<=7 && final.second+2<=7){
            if(b.game_board[final.first+1][final.second+1] == -1 && b.game_board[final.first+2][final.second+2] == -1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first+1,final.second+1));
                as.push_back(make_pair(final.first+2,final.second+2));
                bool sdf = false;
                for(int i=0;i<b.black_canons.size();i++){
                    if(compare(b.black_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.black_canons.push_back(as);
                }
            }
        }
        
        if(final.first-2>=0 && final.second+2<=7){
            if(b.game_board[final.first-1][final.second+1] == -1 && b.game_board[final.first-2][final.second+2] == -1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first-1,final.second+1));
                as.push_back(make_pair(final.first-2,final.second+2));
                bool sdf = false;
                for(int i=0;i<b.black_canons.size();i++){
                    if(compare(b.black_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.black_canons.push_back(as);
                }
            }
        }
        
        if(final.first+2<=7 && final.second-2>=0){
            if(b.game_board[final.first+1][final.second-1] == -1 && b.game_board[final.first+2][final.second-2] == -1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first+1,final.second-1));
                as.push_back(make_pair(final.first+2,final.second-2));
                bool sdf = false;
                for(int i=0;i<b.black_canons.size();i++){
                    if(compare(b.black_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.black_canons.push_back(as);
                }
            }
        }
        
    }
    else{
        
        if(killer.first == -1){
            
            for(int i=0;i<b.black_canons.size();i++){
                for(int j=0;j<3;j++){
                    if( (initial_canon[0] == b.black_canons[i][j]) || (initial_canon[1] == b.black_canons[i][j]) || (initial_canon[2] == b.black_canons[i][j]) ){
                        b.black_canons.erase(b.black_canons.begin()+i);
                        i--;
                        j=3;
                    }
                }
            }
            
            for(int i=0;i<b.blacks.size();i++){
                if(b.blacks[i] == initial_canon[0] || b.blacks[i] == initial_canon[1] || b.blacks[i] == initial_canon[2]){
                    b.blacks.erase(b.blacks.begin() + i);
                    i--;
                }
            }
            
            b.blacks.push_back(final_canon[0]);
            b.blacks.push_back(final_canon[1]);
            b.blacks.push_back(final_canon[2]);
            
            b.game_board[initial_canon[0].first][initial_canon[0].second] = 0;
            b.game_board[initial_canon[1].first][initial_canon[1].second] = 0;
            b.game_board[initial_canon[2].first][initial_canon[2].second] = 0;
            
            
            b.game_board[final_canon[0].first][final_canon[0].second] = -1;
            b.game_board[final_canon[1].first][final_canon[1].second] = -1;
            b.game_board[final_canon[2].first][final_canon[2].second] = -1;
            
            for(int i=0;i<3;i++){
                
                if(final_canon[i].second-1>=0 && final_canon[i].first-1>=0){
                    if(b.game_board[final_canon[i].first-1][final_canon[i].second-1] == -1){
                        if(final_canon[i].first+1<8 && final_canon[i].second+1<8){
                            if(b.game_board[final_canon[i].first+1][final_canon[i].second+1] == -1){
                                vector<pair<int,int > > as;
                                as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                                as.push_back(make_pair(final_canon[i].first+1,final_canon[i].second+1));
                                as.push_back(make_pair(final_canon[i].first-1,final_canon[i].second-1));
                                bool sdf = false;
                                for(int i=0;i<b.black_canons.size();i++){
                                    if(compare(b.black_canons[i],as)){
                                        sdf = true;
                                    }
                                }
                                if(!sdf){
                                    b.black_canons.push_back(as);
                                }
                            }
                        }
                    }
                }
                
                if(final_canon[i].first-1>=0){
                    if(b.game_board[final_canon[i].first-1][final_canon[i].second] == -1){
                        if(final_canon[i].first+1<8){
                            if(b.game_board[final_canon[i].first+1][final_canon[i].second] == -1){
                                vector<pair<int,int > > as;
                                as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                                as.push_back(make_pair(final_canon[i].first+1,final_canon[i].second));
                                as.push_back(make_pair(final_canon[i].first-1,final_canon[i].second));
                                bool sdf = false;
                                for(int i=0;i<b.black_canons.size();i++){
                                    if(compare(b.black_canons[i],as)){
                                        sdf = true;
                                    }
                                }
                                if(!sdf){
                                    b.black_canons.push_back(as);
                                }
                            }
                        }
                    }
                }
                
                if(final_canon[i].second-1>=0){
                    if(b.game_board[final_canon[i].first][final_canon[i].second-1] == -1){
                        if(final_canon[i].second+1<8){
                            if(b.game_board[final_canon[i].first][final_canon[i].second+1] == -1){
                                vector<pair<int,int > > as;
                                as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                                as.push_back(make_pair(final_canon[i].first,final_canon[i].second+1));
                                as.push_back(make_pair(final_canon[i].first,final_canon[i].second-1));
                                bool sdf = false;
                                for(int i=0;i<b.black_canons.size();i++){
                                    if(compare(b.black_canons[i],as)){
                                        sdf = true;
                                    }
                                }
                                if(!sdf){
                                    b.black_canons.push_back(as);
                                }
                            }
                        }
                    }
                }
                
                if(final_canon[i].second-1>=0 && final_canon[i].first+1<8){
                    if(b.game_board[final_canon[i].first+1][final_canon[i].second-1] == -1){
                        if(final_canon[i].first-1>=0 && final_canon[i].second+1<8){
                            if(b.game_board[final_canon[i].first-1][final_canon[i].second+1] == -1){
                                vector<pair<int,int > > as;
                                as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                                as.push_back(make_pair(final_canon[i].first+1,final_canon[i].second-1));
                                as.push_back(make_pair(final_canon[i].first-1,final_canon[i].second+1));
                                bool sdf = false;
                                for(int i=0;i<b.black_canons.size();i++){
                                    if(compare(b.black_canons[i],as)){
                                        sdf = true;
                                    }
                                }
                                if(!sdf){
                                    b.black_canons.push_back(as);
                                }
                            }
                        }
                    }
                }
                
                if(final_canon[i].first-2>=0 && final_canon[i].second-2>=0){
                    if(b.game_board[final_canon[i].first-1][final_canon[i].second-1] == -1 && b.game_board[final_canon[i].first-2][final_canon[i].second-2] == -1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first-1,final_canon[i].second-1));
                        as.push_back(make_pair(final_canon[i].first-2,final_canon[i].second-2));
                        bool sdf = false;
                        for(int i=0;i<b.black_canons.size();i++){
                            if(compare(b.black_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.black_canons.push_back(as);
                        }
                    }
                }
                
                if(final_canon[i].first-2>=0){
                    if(b.game_board[final_canon[i].first-1][final_canon[i].second] == -1 && b.game_board[final_canon[i].first-2][final_canon[i].second] == -1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first-1,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first-2,final_canon[i].second));
                        bool sdf = false;
                        for(int i=0;i<b.black_canons.size();i++){
                            if(compare(b.black_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.black_canons.push_back(as);
                        }
                    }
                }
                
                if(final_canon[i].first+2<=7){
                    if(b.game_board[final_canon[i].first+1][final_canon[i].second] == -1 && b.game_board[final_canon[i].first+2][final_canon[i].second] == -1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first+1,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first+2,final_canon[i].second));
                        bool sdf = false;
                        for(int i=0;i<b.black_canons.size();i++){
                            if(compare(b.black_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.black_canons.push_back(as);
                        }
                    }
                }
                
                if(final_canon[i].second-2>=0){
                    if(b.game_board[final_canon[i].first][final_canon[i].second-1] == -1 && b.game_board[final_canon[i].first][final_canon[i].second-2] == -1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second-1));
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second-2));
                        bool sdf = false;
                        for(int i=0;i<b.black_canons.size();i++){
                            if(compare(b.black_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.black_canons.push_back(as);
                        }
                    }
                }
                
                if(final_canon[i].second+2<=7){
                    if(b.game_board[final_canon[i].first][final_canon[i].second+1] == -1 && b.game_board[final_canon[i].first][final_canon[i].second+2] == -1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second+1));
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second+2));
                        bool sdf = false;
                        for(int i=0;i<b.black_canons.size();i++){
                            if(compare(b.black_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.black_canons.push_back(as);
                        }
                    }
                }
                
                if(final_canon[i].first+2<=7 && final_canon[i].second+2<=7){
                    if(b.game_board[final_canon[i].first+1][final_canon[i].second+1] == -1 && b.game_board[final_canon[i].first+2][final_canon[i].second+2] == -1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first+1,final_canon[i].second+1));
                        as.push_back(make_pair(final_canon[i].first+2,final_canon[i].second+2));
                        bool sdf = false;
                        for(int i=0;i<b.black_canons.size();i++){
                            if(compare(b.black_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.black_canons.push_back(as);
                        }
                    }
                }
                
                if(final_canon[i].first-2>=0 && final_canon[i].second+2<=7){
                    if(b.game_board[final_canon[i].first-1][final_canon[i].second+1] == -1 && b.game_board[final_canon[i].first-2][final_canon[i].second+2] == -1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first-1,final_canon[i].second+1));
                        as.push_back(make_pair(final_canon[i].first-2,final_canon[i].second+2));
                        bool sdf = false;
                        for(int i=0;i<b.black_canons.size();i++){
                            if(compare(b.black_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.black_canons.push_back(as);
                        }
                    }
                }
                
                if(final_canon[i].first+2<=7 && final_canon[i].second-2>=0){
                    if(b.game_board[final_canon[i].first+1][final_canon[i].second-1] == -1 && b.game_board[final_canon[i].first+2][final_canon[i].second-2] == -1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first+1,final_canon[i].second-1));
                        as.push_back(make_pair(final_canon[i].first+2,final_canon[i].second-2));
                        bool sdf = false;
                        for(int i=0;i<b.black_canons.size();i++){
                            if(compare(b.black_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.black_canons.push_back(as);
                        }
                    }
                }
                
                
            }
            
        }
        else{
            for(int it=0;it<b.white_canons.size();it++){
                if((b.white_canons[it][0] == killer) || (b.white_canons[it][1] == killer) || (b.white_canons[it][2] == killer)){
                    b.white_canons.erase(b.white_canons.begin()+it);
                    it--;
                }
            }
            
            
            
            
            if(b.game_board[killer.first][killer.second] == 1){
                for(int i=0;i<b.whites.size();i++){
                    if(killer == b.whites[i]){
                        b.whites.erase(b.whites.begin() + i);
                        break;
                    }
                }
            }
            
            b.game_board[killer.first][killer.second] = 0;
        }
    }
    return b;
}







Board newBoardWhite(bool isCanon, pair<int,int> initial, pair<int,int> final, Board b, vector<pair<int,int> > initial_canon, vector<pair<int,int> > final_canon, pair<int, int> killer){
    
    
    if(!isCanon){
        
        if(b.game_board[final.first][final.second] == -1){
            for(int i=0;i<b.blacks.size();i++){
                if(final == b.blacks[i]){
                    b.blacks.erase(b.blacks.begin() + i);
                    break;
                }
            }
        }
        
        
        
        for(int i=0;i<b.black_canons.size();i++){
            for(int j=0;j<3;j++){
                if(b.black_canons[i][j] == final){
                    b.black_canons.erase(b.black_canons.begin() + i);
                    i--;
                    j=3;
                }
            }
        }
        
        
        
        for(int i=0;i<b.whites.size();i++){
            if(b.whites[i] == initial){
                b.whites.erase(b.whites.begin()+i);
                break;
            }
        }
        
        b.whites.push_back(final);
        
        for(int i=0;i<b.white_canons.size();i++){
            for(int j=0;j<3;j++){
                if(b.white_canons[i][j] == initial){
                    b.white_canons.erase(b.white_canons.begin() + i);
                    i--;
                    j=3;
                }
            }
        }
        
        
        b.game_board[initial.first][initial.second] = 0;
        b.game_board[final.first][final.second] = 1;
        
        if(final.second-1>=0 && final.first-1>=0){
            
            if(b.game_board[final.first-1][final.second-1] == 1){
                if(final.first+1<8 && final.second+1<8){
                    if(b.game_board[final.first+1][final.second+1] == 1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final.first,final.second));
                        as.push_back(make_pair(final.first+1,final.second+1));
                        as.push_back(make_pair(final.first-1,final.second-1));
                        bool sdf = false;
                        for(int i=0;i<b.white_canons.size();i++){
                            if(compare(b.white_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.white_canons.push_back(as);
                        }
                    }
                }
            }
        }
        
        
        if(final.first-1>=0){
            if(b.game_board[final.first-1][final.second] == 1){
                if(final.first+1<8){
                    if(b.game_board[final.first+1][final.second] == 1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final.first,final.second));
                        as.push_back(make_pair(final.first+1,final.second));
                        as.push_back(make_pair(final.first-1,final.second));
                        bool sdf = false;
                        for(int i=0;i<b.white_canons.size();i++){
                            if(compare(b.white_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.white_canons.push_back(as);
                        }
                    }
                }
            }
        }
        
        if(final.second-1>=0){
            if(b.game_board[final.first][final.second-1] == 1){
                if(final.second+1<8){
                    if(b.game_board[final.first][final.second+1] == 1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final.first,final.second));
                        as.push_back(make_pair(final.first,final.second+1));
                        as.push_back(make_pair(final.first,final.second-1));
                        bool sdf = false;
                        for(int i=0;i<b.white_canons.size();i++){
                            if(compare(b.white_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.white_canons.push_back(as);
                        }
                    }
                }
            }
        }
        
        if(final.second-1>=0 && final.first+1<8){
            if(b.game_board[final.first+1][final.second-1] == 1){
                if(final.first-1>=0 && final.second+1<8){
                    if(b.game_board[final.first-1][final.second+1] == 1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final.first,final.second));
                        as.push_back(make_pair(final.first+1,final.second-1));
                        as.push_back(make_pair(final.first-1,final.second+1));
                        bool sdf = false;
                        for(int i=0;i<b.white_canons.size();i++){
                            if(compare(b.white_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.white_canons.push_back(as);
                        }
                    }
                }
            }
        }
        
        if(final.first-2>=0 && final.second-2>=0){
            if(b.game_board[final.first-1][final.second-1] == 1 && b.game_board[final.first-2][final.second-2] == 1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first-1,final.second-1));
                as.push_back(make_pair(final.first-2,final.second-2));
                bool sdf = false;
                for(int i=0;i<b.white_canons.size();i++){
                    if(compare(b.white_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.white_canons.push_back(as);
                }
            }
        }
        
        if(final.first-2>=0){
            if(b.game_board[final.first-1][final.second] == 1 && b.game_board[final.first-2][final.second] == 1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first-1,final.second));
                as.push_back(make_pair(final.first-2,final.second));
                bool sdf = false;
                for(int i=0;i<b.white_canons.size();i++){
                    if(compare(b.white_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.white_canons.push_back(as);
                }
            }
        }
        
        if(final.first+2<=7){
            if(b.game_board[final.first+1][final.second] == 1 && b.game_board[final.first+2][final.second] == 1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first+1,final.second));
                as.push_back(make_pair(final.first+2,final.second));
                bool sdf = false;
                for(int i=0;i<b.white_canons.size();i++){
                    if(compare(b.white_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.white_canons.push_back(as);
                }
            }
        }
        
        if(final.second-2>=0){
            if(b.game_board[final.first][final.second-1] == 1 && b.game_board[final.first][final.second-2] == 1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first,final.second-1));
                as.push_back(make_pair(final.first,final.second-2));
                bool sdf = false;
                for(int i=0;i<b.white_canons.size();i++){
                    if(compare(b.white_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.white_canons.push_back(as);
                }
            }
        }
        
        if(final.second+2<=7){
            if(b.game_board[final.first][final.second+1] == 1 && b.game_board[final.first][final.second+2] == 1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first,final.second+1));
                as.push_back(make_pair(final.first,final.second+2));
                bool sdf = false;
                for(int i=0;i<b.white_canons.size();i++){
                    if(compare(b.white_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.white_canons.push_back(as);
                }
            }
        }
        
        if(final.first+2<=7 && final.second+2<=7){
            if(b.game_board[final.first+1][final.second+1] == 1 && b.game_board[final.first+2][final.second+2] == 1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first+1,final.second+1));
                as.push_back(make_pair(final.first+2,final.second+2));
                bool sdf = false;
                for(int i=0;i<b.white_canons.size();i++){
                    if(compare(b.white_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.white_canons.push_back(as);
                }
            }
        }
        
        if(final.first-2>=0 && final.second+2<=7){
            if(b.game_board[final.first-1][final.second+1] == 1 && b.game_board[final.first-2][final.second+2] == 1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first-1,final.second+1));
                as.push_back(make_pair(final.first-2,final.second+2));
                bool sdf = false;
                for(int i=0;i<b.white_canons.size();i++){
                    if(compare(b.white_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.white_canons.push_back(as);
                }
            }
        }
        
        if(final.first+2<=7 && final.second-2>=0){
            if(b.game_board[final.first+1][final.second-1] == 1 && b.game_board[final.first+2][final.second-2] == 1){
                vector<pair<int,int > > as;
                as.push_back(make_pair(final.first,final.second));
                as.push_back(make_pair(final.first+1,final.second-1));
                as.push_back(make_pair(final.first+2,final.second-2));
                bool sdf = false;
                for(int i=0;i<b.white_canons.size();i++){
                    if(compare(b.white_canons[i],as)){
                        sdf = true;
                    }
                }
                if(!sdf){
                    b.white_canons.push_back(as);
                }
            }
        }
        
        
    }
    else{
        
        if(killer.first == -1){
            for(int i=0;i<b.white_canons.size();i++){
                for(int j=0;j<3;j++){
                    if( (initial_canon[0] == b.white_canons[i][j]) || (initial_canon[1] == b.white_canons[i][j]) || (initial_canon[2] == b.white_canons[i][j])){
                        b.white_canons.erase(b.white_canons.begin()+i);
                        i--;
                        j=3;
                    }
                }
            }
            
            for(int i=0;i<b.whites.size();i++){
                if(b.whites[i] == initial_canon[0] || b.whites[i] == initial_canon[1] || b.whites[i] == initial_canon[2]){
                    b.whites.erase(b.whites.begin() + i);
                    i--;
                }
            }
            
            b.whites.push_back(final_canon[0]);
            b.whites.push_back(final_canon[1]);
            b.whites.push_back(final_canon[2]);
            
            b.game_board[initial_canon[0].first][initial_canon[0].second] = 0;
            b.game_board[initial_canon[1].first][initial_canon[1].second] = 0;
            b.game_board[initial_canon[2].first][initial_canon[2].second] = 0;
            
            
            
            
            b.game_board[final_canon[0].first][final_canon[0].second] = 1;
            b.game_board[final_canon[1].first][final_canon[1].second] = 1;
            b.game_board[final_canon[2].first][final_canon[2].second] = 1;
            
            b.white_canons.push_back(final_canon);
            
            for(int i=0;i<3;i++){
                
                if(final_canon[i].second-1>=0 && final_canon[i].first-1>=0){
                    if(b.game_board[final_canon[i].first-1][final_canon[i].second-1] == 1){
                        if(final_canon[i].first+1<8 && final_canon[i].second+1<8){
                            if(b.game_board[final_canon[i].first+1][final_canon[i].second+1] == 1){
                                vector<pair<int,int > > as;
                                as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                                as.push_back(make_pair(final_canon[i].first+1,final_canon[i].second+1));
                                as.push_back(make_pair(final_canon[i].first-1,final_canon[i].second-1));
                                bool sdf = false;
                                for(int i=0;i<b.white_canons.size();i++){
                                    if(compare(b.white_canons[i],as)){
                                        sdf = true;
                                    }
                                }
                                if(!sdf){
                                    b.white_canons.push_back(as);
                                }
                            }
                            
                        }
                    }
                }
                
                if(final_canon[i].first-1>=0){
                    if(b.game_board[final_canon[i].first-1][final_canon[i].second] == 1){
                        if(final_canon[i].first+1<8){
                            if(b.game_board[final_canon[i].first+1][final_canon[i].second] == 1){
                                vector<pair<int,int > > as;
                                as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                                as.push_back(make_pair(final_canon[i].first+1,final_canon[i].second));
                                as.push_back(make_pair(final_canon[i].first-1,final_canon[i].second));
                                bool sdf = false;
                                for(int i=0;i<b.white_canons.size();i++){
                                    if(compare(b.white_canons[i],as)){
                                        sdf = true;
                                    }
                                }
                                if(!sdf){
                                    b.white_canons.push_back(as);
                                }
                                
                            }
                        }
                    }
                }
                
                if(final_canon[i].second-1>=0){
                    if(b.game_board[final_canon[i].first][final_canon[i].second-1] == 1){
                        if(final_canon[i].second+1<8){
                            if(b.game_board[final_canon[i].first][final_canon[i].second+1] == 1){
                                vector<pair<int,int > > as;
                                as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                                as.push_back(make_pair(final_canon[i].first,final_canon[i].second+1));
                                as.push_back(make_pair(final_canon[i].first,final_canon[i].second-1));
                                bool sdf = false;
                                for(int i=0;i<b.white_canons.size();i++){
                                    if(compare(b.white_canons[i],as)){
                                        sdf = true;
                                    }
                                }
                                if(!sdf){
                                    b.white_canons.push_back(as);
                                }
                                
                            }
                        }
                    }
                }
                
                if(final_canon[i].second-1>=0 && final_canon[i].first+1<8){
                    if(b.game_board[final_canon[i].first+1][final_canon[i].second-1] == 1){
                        if(final_canon[i].first-1>=0 && final_canon[i].second+1<8){
                            if(b.game_board[final_canon[i].first-1][final_canon[i].second+1] == 1){
                                vector<pair<int,int > > as;
                                as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                                as.push_back(make_pair(final_canon[i].first+1,final_canon[i].second-1));
                                as.push_back(make_pair(final_canon[i].first-1,final_canon[i].second+1));
                                bool sdf = false;
                                for(int i=0;i<b.white_canons.size();i++){
                                    if(compare(b.white_canons[i],as)){
                                        sdf = true;
                                    }
                                }
                                if(!sdf){
                                    b.white_canons.push_back(as);
                                }
                                
                            }
                        }
                    }
                }
                
                if(final_canon[i].first-2>=0 && final_canon[i].second-2>=0){
                    if(b.game_board[final_canon[i].first-1][final_canon[i].second-1] == 1 && b.game_board[final_canon[i].first-2][final_canon[i].second-2] == 1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first-1,final_canon[i].second-1));
                        as.push_back(make_pair(final_canon[i].first-2,final_canon[i].second-2));
                        bool sdf = false;
                        for(int i=0;i<b.white_canons.size();i++){
                            if(compare(b.white_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.white_canons.push_back(as);
                        }
                        
                    }
                }
                
                if(final_canon[i].first-2>=0){
                    if(b.game_board[final_canon[i].first-1][final_canon[i].second] == 1 && b.game_board[final_canon[i].first-2][final_canon[i].second] == 1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first-1,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first-2,final_canon[i].second));
                        bool sdf = false;
                        for(int i=0;i<b.white_canons.size();i++){
                            if(compare(b.white_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.white_canons.push_back(as);
                        }
                        
                    }
                }
                
                if(final_canon[i].first+2<=7){
                    if(b.game_board[final_canon[i].first+1][final_canon[i].second] == 1 && b.game_board[final_canon[i].first+2][final_canon[i].second] == 1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first+1,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first+2,final_canon[i].second));
                        bool sdf = false;
                        for(int i=0;i<b.white_canons.size();i++){
                            if(compare(b.white_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.white_canons.push_back(as);
                        }
                        
                    }
                }
                
                if(final_canon[i].second-2>=0){
                    if(b.game_board[final_canon[i].first][final_canon[i].second-1] == 1 && b.game_board[final_canon[i].first][final_canon[i].second-2] == 1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second-1));
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second-2));
                        bool sdf = false;
                        for(int i=0;i<b.white_canons.size();i++){
                            if(compare(b.white_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.white_canons.push_back(as);
                        }
                        
                    }
                }
                
                if(final_canon[i].second+2<=7){
                    if(b.game_board[final_canon[i].first][final_canon[i].second+1] == 1 && b.game_board[final_canon[i].first][final_canon[i].second+2] == 1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second+1));
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second+2));
                        bool sdf = false;
                        for(int i=0;i<b.white_canons.size();i++){
                            if(compare(b.white_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.white_canons.push_back(as);
                        }
                        
                    }
                }
                
                if(final_canon[i].first+2<=7 && final_canon[i].second+2<=7){
                    if(b.game_board[final_canon[i].first+1][final_canon[i].second+1] == 1 && b.game_board[final_canon[i].first+2][final_canon[i].second+2] == 1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first+1,final_canon[i].second+1));
                        as.push_back(make_pair(final_canon[i].first+2,final_canon[i].second+2));
                        bool sdf = false;
                        for(int i=0;i<b.white_canons.size();i++){
                            if(compare(b.white_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.white_canons.push_back(as);
                        }
                        
                    }
                }
                
                if(final_canon[i].first-2>=0 && final_canon[i].second+2<=7){
                    if(b.game_board[final_canon[i].first-1][final_canon[i].second+1] == 1 && b.game_board[final_canon[i].first-2][final_canon[i].second+2] == 1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first-1,final_canon[i].second+1));
                        as.push_back(make_pair(final_canon[i].first-2,final_canon[i].second+2));
                        bool sdf = false;
                        for(int i=0;i<b.white_canons.size();i++){
                            if(compare(b.white_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.white_canons.push_back(as);
                        }
                        
                    }
                }
                
                if(final_canon[i].first+2<=7 && final_canon[i].second-2>=0){
                    if(b.game_board[final_canon[i].first+1][final_canon[i].second-1] == 1 && b.game_board[final_canon[i].first+2][final_canon[i].second-2] == 1){
                        vector<pair<int,int > > as;
                        as.push_back(make_pair(final_canon[i].first,final_canon[i].second));
                        as.push_back(make_pair(final_canon[i].first+1,final_canon[i].second-1));
                        as.push_back(make_pair(final_canon[i].first+2,final_canon[i].second-2));
                        bool sdf = false;
                        for(int i=0;i<b.white_canons.size();i++){
                            if(compare(b.white_canons[i],as)){
                                sdf = true;
                            }
                        }
                        if(!sdf){
                            b.white_canons.push_back(as);
                        }
                    }
                    
                }
                
                
            }
            
        }
        else{
            for(int it=0;it<b.black_canons.size();it++){
                if((b.black_canons[it][0].first == killer.first && b.black_canons[it][0].second == killer.second) || (b.black_canons[it][1].first == killer.first && b.black_canons[it][1].second == killer.second) || (b.black_canons[it][2].first == killer.first && b.black_canons[it][2].second == killer.second)){
                    b.black_canons.erase(b.black_canons.begin()+it);
                    it--;
                }
            }
            
            
            if(b.game_board[killer.first][killer.second] == -1){
                for(int i=0;i<b.blacks.size();i++){
                    if(killer == b.blacks[i]){
                        b.blacks.erase(b.blacks.begin() + i);
                        break;
                    }
                }
            }
            
            
            b.game_board[killer.first][killer.second] = 0;
        }
    }
    return b;
}

Board miniMax(Board root, int d, int depth){
    
    if(root.alpha >= root.beta){
        return root;
    }
    
    if(depth == d){
        root.cost = gameBoardCost(root,0);
        return root;
    }
    if(depth % 2 != 0 && depth < d-1){
        Board re = root;
        Board ret = root;
        
        
        for(int i=0;i<root.black_canons.size();i++){
            int a1 = root.black_canons[i][0].first;
            int a2 = root.black_canons[i][0].second;
            int a3 = root.black_canons[i][1].first;
            int a4 = root.black_canons[i][1].second;
            int a5 = root.black_canons[i][2].first;
            int a6 = root.black_canons[i][2].second;
            int first_max = max(max(a1,a3),a5);
            int first_min = min(min(a1,a3),a5);
            int second_max = max(max(a2,a4),a6);
            int second_min = min(min(a2,a4),a6);
            
            
            
            
            
            if(second_min == second_max && first_max+1<=7){
                if(root.game_board[first_max + 1][second_max] == 0){
                    
                    if(first_max+2<=7){
                        if(root.game_board[first_max+1][second_max] ==0 && (root.game_board[first_max+2][second_max ] == -1 || root.game_board[first_max+2][second_max] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max+2,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(first_max+3<=7){
                        if(root.game_board[first_max+1][second_max] ==0 && root.game_board[first_max+2][second_max] == 0 && (root.game_board[first_max+3][second_max] == -1 || root.game_board[first_max+3][second_max] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max+3,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    
                    vector<pair<int,int> > se;
                    se.push_back(make_pair(first_max+1,second_min));
                    se.push_back(make_pair(first_max,second_min));
                    se.push_back(make_pair(first_max-1,second_min));
                    pair<int,int> xe;
                    xe = (make_pair(-1,-1));
                    pair<int,int> pqr = make_pair(-1,-1);
                    re = newBoardBlack(false,make_pair(first_min,second_min),make_pair(first_max + 1,second_min),root,root.black_canons[i],se,xe);
                    re = miniMax(re,d,depth+1);
                    if(root.beta > re.cost){
                        root.beta = re.cost;
                        ret = re;
                    }
                    root.cost = root.beta;
                    
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                    
                }
            }
            
            
            
            
            if(second_min == second_max && first_min-1>=0){
                if(root.game_board[first_min-1][second_max] == 0){
                    
                    if(first_min-2>=0){
                        if(root.game_board[first_min-1][second_max] ==0 && (root.game_board[first_min-2][second_max ] == -1 || root.game_board[first_min-2][second_max] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_min-2,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(first_min-3>=0){
                        if(root.game_board[first_min-1][second_max] ==0 && root.game_board[first_min-2][second_max] == 0 && (root.game_board[first_min-3][second_max] == -1 || root.game_board[first_min-3][second_max] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_min-3,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    vector<pair<int,int> > se;
                    se.push_back(make_pair(first_min+1,second_min));
                    se.push_back(make_pair(first_min,second_min));
                    se.push_back(make_pair(first_min-1,second_min));
                    pair<int,int> xe;
                    xe = (make_pair(-1,-1));
                    pair<int,int> pqr = make_pair(-1,-1);
                    re = newBoardBlack(false,make_pair(first_max,second_min),make_pair(first_min - 1,second_min),root,root.black_canons[i],se,xe);
                    re = miniMax(re,d,depth+1);
                    if(root.beta > re.cost){
                        root.beta = re.cost;
                        ret = re;
                    }
                    root.cost = root.beta;
                    
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                }
            }
            
            
            
            if(((second_max == a2 && first_max == a1) || (second_max == a4 && first_max == a3) || (second_max == a6 && first_max == a5)) && second_max != second_min && first_max != first_min){
                if(second_min-1 >= 0 && first_min-1 >= 0){
                    if(root.game_board[first_min-1][second_min-1]==0){
                        
                        if(first_min-2>=0 && second_min -2 >=0){
                            if(root.game_board[first_min-1][second_min-1] ==0 && (root.game_board[first_min-2][second_min -2] == -1 || root.game_board[first_min-2][second_min -2] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_min-2,second_min-2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                        }
                        
                        if(first_min-3>=0 && second_min -3 >= 0){
                            if(root.game_board[first_min-1][second_min-1] ==0 && root.game_board[first_min-2][second_min-2] == 0 && (root.game_board[first_min-3][second_min -3] == -1 || root.game_board[first_min-3][second_min-3] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_min-3,second_min-3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                        }
                        
                        
                        
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_min-1,second_min-1));
                        se.push_back(make_pair(first_min,second_min));
                        se.push_back(make_pair(first_min+1,second_min+1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        re = newBoardBlack(false,make_pair(first_max,second_max),make_pair(first_min - 1,second_min - 1),root,root.black_canons[i],se,xe);
                        re = miniMax(re,d,depth+1);
                        if(root.beta > re.cost){
                            root.beta = re.cost;
                            ret = re;
                        }
                        root.cost = root.beta;
                        
                        if(root.alpha >= root.beta){
                            break;
                        }
                        
                        
                    }
                }
                
                
                if(second_max+1 <= 7 && first_max+1 <= 7){
                    if(root.game_board[first_min+1][second_min+1]==0){
                        
                        if(first_max+2<=7 && second_max +2 <=7){
                            if(root.game_board[first_max+1][second_max+1] ==0 && (root.game_board[first_max+2][second_max +2] == -1 || root.game_board[first_max+2][second_max +2] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+2,second_max+2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        if(first_max+3<=7 && second_max +3 <=7 ){
                            if(root.game_board[first_max+1][second_max+1] ==0 && root.game_board[first_max+2][second_max+2] == 0 && (root.game_board[first_max+3][second_max +3] == -1 || root.game_board[first_max+3][second_max+3] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+3,second_max+3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                        }
                        
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_max-1,second_max-1));
                        se.push_back(make_pair(first_max,second_max));
                        se.push_back(make_pair(first_max+1,second_max+1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        re = newBoardBlack(false,make_pair(first_min,second_min),make_pair(first_max + 1,second_max+1),root,root.black_canons[i],se,xe);
                        re = miniMax(re,d,depth+1);
                        if(root.beta > re.cost){
                            root.beta = re.cost;
                            ret = re;
                        }
                        root.cost = root.beta;
                        
                        if(root.alpha >= root.beta){
                            break;
                        }
                        
                        
                    }
                }
            }
            
            if(((second_max == a2 && first_min == a1) || (second_max == a4 && first_min == a3) || (second_max == a6 && first_min == a5)) && first_min != first_max && second_max != second_min){
                if(second_min-1 >= 0 && first_max+1 <= 7){
                    if(root.game_board[first_max+1][second_min-1]==0){
                        
                        if(first_max+2<=7 && second_min -2 >=0){
                            if(root.game_board[first_max+1][second_min-1] ==0 && (root.game_board[first_max+2][second_min -2] == -1 || root.game_board[first_max+2][second_min -2] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+2,second_min-2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                        }
                        
                        if(first_max+3<=7 && second_min -3 >= 0){
                            if(root.game_board[first_max+1][second_min-1] ==0 && root.game_board[first_max+2][second_min-2] == 0 && (root.game_board[first_max+3][second_min-3] == -1 || root.game_board[first_max+3][second_min-3] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+3,second_min-3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                        }
                        
                        
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_max+1,second_min-1));
                        se.push_back(make_pair(first_max,second_min));
                        se.push_back(make_pair(first_max-1,second_min+1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        re = newBoardBlack(false,make_pair(first_min,second_max),make_pair(first_max + 1,second_min-1),root,root.black_canons[i],se,xe);
                        re = miniMax(re,d,depth+1);
                        if(root.beta > re.cost){
                            root.beta = re.cost;
                            ret = re;
                        }
                        root.cost = root.beta;
                        
                        if(root.alpha >= root.beta){
                            break;
                        }
                        
                        
                        
                    }
                }
                
                
                if(second_max+1 <= 7 && first_min-1 >= 0){
                    if(root.game_board[first_min-1][second_min+1]==0){
                        
                        if(first_min-2>=0 && second_max +2 <=7){
                            if(root.game_board[first_min-1][second_max+1] ==0 && (root.game_board[first_min-2][second_max+2] == -1 || root.game_board[first_min-2][second_max+2] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_min-2,second_max+2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                        }
                        
                        if(first_max+3<=7 && second_min -3 >= 0){
                            if(root.game_board[first_max+1][second_min-1] ==0 && root.game_board[first_max+2][second_min-2] == 0 && (root.game_board[first_max+3][second_min-3] == -1 || root.game_board[first_max+3][second_min-3] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+3,second_min-3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                        }
                        
                        
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_min-1,second_max+1));
                        se.push_back(make_pair(first_min,second_max));
                        se.push_back(make_pair(first_min+1,second_max-1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        re = newBoardBlack(false,make_pair(first_max,second_min),make_pair(first_min - 1,second_max+ 1),root,root.black_canons[i],se,xe);
                        re = miniMax(re,d,depth+1);
                        if(root.beta > re.cost){
                            root.beta = re.cost;
                            ret = re;
                        }
                        root.cost = root.beta;
                        
                        if(root.alpha >= root.beta){
                            break;
                        }
                        
                        
                        
                    }
                }
            }
            
            
            if(first_min == first_max && second_max + 1<=7){
                if(root.game_board[first_max][second_max+1] == 0){
                    
                    
                    if(second_max+2<=7){
                        if(root.game_board[first_max][second_max+1] ==0 && (root.game_board[first_max][second_max +2] == -1 || root.game_board[first_max][second_max+2] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_max+2));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(second_max+3<=7){
                        if(root.game_board[first_max][second_max+1] ==0 && root.game_board[first_max][second_max+2] == 0 && (root.game_board[first_max][second_max + 3] == -1 || root.game_board[first_max][second_max+3] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_max+3));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    
                    vector<pair<int,int> > se;
                    se.push_back(make_pair(first_max,second_max));
                    se.push_back(make_pair(first_max,second_max-1));
                    se.push_back(make_pair(first_max,second_max+1));
                    pair<int,int> xe;
                    xe = (make_pair(-1,-1));
                    pair<int,int> pqr = make_pair(-1,-1);
                    re = newBoardBlack(false,make_pair(first_max,second_min),make_pair(first_max ,second_max+1),root,root.black_canons[i],se,xe);
                    re = miniMax(re,d,depth+1);
                    if(root.beta > re.cost){
                        root.beta = re.cost;
                        ret = re;
                    }
                    root.cost = root.beta;
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                }
            }
            
            
            if(first_min == first_max && second_min - 1>=0){
                if(root.game_board[first_max][second_min-1] == 0){
                    
                    if(second_min-2>=0){
                        if(root.game_board[first_max][second_min-1] ==0 && (root.game_board[first_max][second_min -2] == -1 || root.game_board[first_max][second_min-2] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_min-2));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(second_min-3>=0){
                        if(root.game_board[first_max][second_min-1] ==0 && root.game_board[first_max][second_min-2] == 0 && (root.game_board[first_max][second_min - 3] == -1 || root.game_board[first_max][second_min-3] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_min-3));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    vector<pair<int,int> > se;
                    se.push_back(make_pair(first_max,second_min));
                    se.push_back(make_pair(first_max,second_min-1));
                    se.push_back(make_pair(first_max,second_min+1));
                    pair<int,int> xe;
                    xe = (make_pair(-1,-1));
                    pair<int,int> pqr = make_pair(-1,-1);
                    re = newBoardBlack(false,make_pair(first_max,second_max),make_pair(first_max ,second_min - 1),root,root.black_canons[i],se,xe);
                    re = miniMax(re,d,depth+1);
                    if(root.beta > re.cost){
                        root.beta = re.cost;
                        ret = re;
                    }
                    root.cost = root.beta;
                    
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                    
                    
                }
            }
            
            
        }
        
        
        for(int i=0;i<root.blacks.size();i++){
            
            if(root.blacks[i].first-1>=0){
                if(root.game_board[root.blacks[i].first - 1][root.blacks[i].second] == 1 || root.game_board[ root.blacks[i].first -1][root.blacks[i].second] == 0 || root.game_board[ root.blacks[i].first -1][root.blacks[i].second] == 2){
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    re = newBoardBlack(false,make_pair(root.blacks[i].first , root.blacks[i].second),make_pair(root.blacks[i].first - 1, root.blacks[i].second),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            
            if(root.alpha>=root.beta){
                break;
            }
            
            if(root.blacks[i].first-1>=0 && root.blacks[i].second-1>=0){
                if(root.game_board[root.blacks[i].first-1][root.blacks[i].second-1] == 1 || root.game_board[root.blacks[i].first-1][root.blacks[i].second-1] == 0 || root.game_board[root.blacks[i].first-1][root.blacks[i].second-1] == 2){
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    
                    re = newBoardBlack(false,make_pair(root.blacks[i].first,root.blacks[i].second),make_pair(root.blacks[i].first-1,root.blacks[i].second-1),root,xyz,xyz,pqr);
                    
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            if(root.blacks[i].first-1>=0 && root.blacks[i].second+1<=7){
                if(root.game_board[root.blacks[i].first-1][root.blacks[i].second+1] == 1 || root.game_board[root.blacks[i].first-1][root.blacks[i].second+1] == 0 || root.game_board[root.blacks[i].first-1][root.blacks[i].second+1] == 2){
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    
                    re = newBoardBlack(false,make_pair(root.blacks[i].first,root.blacks[i].second),make_pair(root.blacks[i].first-1,root.blacks[i].second+1),root,xyz,xyz,pqr);
                    
                    re = miniMax(re,d,depth+1);
                    
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            if(root.blacks[i].second-1>=0){
                if(root.game_board[root.blacks[i].first][root.blacks[i].second-1] == 1 || root.game_board[root.blacks[i].first][root.blacks[i].second-1] == 2){
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    re = newBoardBlack(false,make_pair(root.blacks[i].first,root.blacks[i].second),make_pair(root.blacks[i].first,root.blacks[i].second-1),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            if(root.blacks[i].second+1<=7){
                if(root.game_board[root.blacks[i].first][root.blacks[i].second+1] == 1 || root.game_board[root.blacks[i].first][root.blacks[i].second+1] == 2){
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    re = newBoardBlack(false,make_pair(root.blacks[i].first,root.blacks[i].second),make_pair(root.blacks[i].first,root.blacks[i].second+1),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            /*if(root.blacks[i].first+2 <= 7){
             if(root.game_board[root.blacks[i].first+2][root.blacks[i].second] == 0 && root.game_board[root.blacks[i].first+1][root.blacks[i].second] == 0){
             pair<int,int> pqr = make_pair(-1,-1);
             vector<pair<int,int > > xyz;
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             re = newBoardBlack(false,make_pair(root.blacks[i].first,root.blacks[i].second),make_pair(root.blacks[i].first+2,root.blacks[i].second),root,xyz,xyz,pqr);
             re = miniMax(re,d,depth+1);
             if(root.alpha < re.cost){
             root.alpha = re.cost;
             ret = re;
             }
             root.cost = root.alpha;
             }
             }
             if(root.alpha >= root.beta){
             break;
             }
             
             if(root.blacks[i].first+2 <= 7 && root.blacks[i].second-2 >=0){
             if(root.game_board[root.blacks[i].first+1][root.blacks[i].second-1] == 0 && root.game_board[root.blacks[i].first+2][root.blacks[i].second-2] == 0){
             pair<int,int> pqr = make_pair(-1,-1);
             vector<pair<int,int > > xyz;
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             re = newBoardBlack(false,make_pair(root.blacks[i].first,root.blacks[i].second),make_pair(root.blacks[i].first+2,root.blacks[i].second-2),root,xyz,xyz,pqr);
             re = miniMax(re,d,depth+1);
             if(root.alpha < re.cost){
             root.alpha = re.cost;
             ret = re;
             }
             root.cost = root.alpha;
             }
             }
             if(root.alpha >= root.beta){
             break;
             }
             
             if(root.blacks[i].first+2 <= 7 && root.blacks[i].second+2 <=7){
             if(root.game_board[root.blacks[i].first+1][root.blacks[i].second+1] == 0 && root.game_board[root.blacks[i].first+2][root.blacks[i].second+2] == 0){
             pair<int,int> pqr = make_pair(-1,-1);
             vector<pair<int,int > > xyz;
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             re = newBoardBlack(false,make_pair(root.blacks[i].first,root.blacks[i].second),make_pair(root.blacks[i].first+2,root.blacks[i].second+2),root,xyz,xyz,pqr);
             re = miniMax(re,d,depth+1);
             if(root.alpha < re.cost){
             root.alpha = re.cost;
             ret = re;
             }
             root.cost = root.alpha;
             }
             }
             if(root.alpha >= root.beta){
             break;
             }*/
        }
        
        
        return root;
        
    }
    
    if(depth % 2 == 0 && depth >0 ){
        
        Board re = root;
        Board ret = root;
        
        
        for(int i=0;i<root.white_canons.size();i++){
            int a1 = root.white_canons[i][0].first;
            int a2 = root.white_canons[i][0].second;
            int a3 = root.white_canons[i][1].first;
            int a4 = root.white_canons[i][1].second;
            int a5 = root.white_canons[i][2].first;
            int a6 = root.white_canons[i][2].second;
            int first_max = max(max(a1,a3),a5);
            int first_min = min(min(a1,a3),a5);
            int second_max = max(max(a2,a4),a6);
            int second_min = min(min(a2,a4),a6);
            
            
            
            
            
            if(second_min == second_max && first_max+1<=7){
                if(root.game_board[first_max + 1][second_max] == 0){
                    if(first_max+2<=7){
                        if(root.game_board[first_max+1][second_max] ==0 && (root.game_board[first_max+2][second_max ] == -1 || root.game_board[first_max+2][second_max] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max+2,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(first_max+3<=7){
                        
                        if(root.game_board[first_max+1][second_max] ==0 && root.game_board[first_max+2][second_max] == 0 && (root.game_board[first_max+3][second_max] == -1 || root.game_board[first_max+3][second_max] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max+3,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    vector<pair<int,int> > se;
                    if(first_max+1<=7){
                        se.push_back(make_pair(first_max+1,second_min));
                        se.push_back(make_pair(first_max,second_min));
                        se.push_back(make_pair(first_max-1,second_min));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        
                        re = newBoardWhite(false,make_pair(first_min,second_min),make_pair(first_max + 1,second_min),root,root.white_canons[i],se,xe);
                        
                        re = miniMax(re,d,depth+1);
                        if(root.alpha < re.cost){
                            root.alpha = re.cost;
                            ret = re;
                        }
                        root.cost = root.alpha;
                    }
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                    
                }
            }
            
            
            
            
            if(second_min == second_max && first_min-1>=0){
                if(root.game_board[first_min-1][second_max] == 0){
                    
                    if(first_min-2>=0){
                        if(root.game_board[first_min-1][second_max] ==0 && (root.game_board[first_min-2][second_max ] == -1 || root.game_board[first_min-2][second_max] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_min-2,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(first_min-3>=0){
                        if(root.game_board[first_min-1][second_max] ==0 && root.game_board[first_min-2][second_max] == 0 && (root.game_board[first_min-3][second_max] == -1 || root.game_board[first_min-3][second_max] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_min-3,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(first_min+1<=7){
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_min+1,second_min));
                        se.push_back(make_pair(first_min,second_min));
                        se.push_back(make_pair(first_min-1,second_min));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        re = newBoardWhite(false,make_pair(first_max,second_min),make_pair(first_min - 1,second_min),root,root.white_canons[i],se,xe);
                        re = miniMax(re,d,depth+1);
                        if(root.alpha < re.cost){
                            root.alpha = re.cost;
                            ret = re;
                        }
                        root.cost = root.alpha;
                    }
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                }
            }
            
            
            
            if(((second_max == a2 && first_max == a1) || (second_max == a4 && first_max == a3) || (second_max == a6 && first_max == a5)) && first_max != first_min && second_max != second_min){
                if(second_min-1 >= 0 && first_min-1 >= 0){
                    if(root.game_board[first_min-1][second_min-1]==0){
                        
                        
                        if(first_min-2>=0 && second_min -2 >=0){
                            if(root.game_board[first_min-1][second_min-1] ==0 && (root.game_board[first_min-2][second_min -2] == -1 || root.game_board[first_min-2][second_min -2] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_min-2,second_min-2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        if(first_min-3>=0 && second_min -3 >= 0){
                            if(root.game_board[first_min-1][second_min-1] ==0 && root.game_board[first_min-2][second_min-2] == 0 && (root.game_board[first_min-3][second_min -3] == -1 || root.game_board[first_min-3][second_min-3] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_min-3,second_min-3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        if(first_min+1<=7 && second_min +1 <=7){
                            vector<pair<int,int> > se;
                            se.push_back(make_pair(first_min-1,second_min-1));
                            se.push_back(make_pair(first_min,second_min));
                            se.push_back(make_pair(first_min+1,second_min+1));
                            pair<int,int> xe;
                            xe = (make_pair(-1,-1));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(false,make_pair(first_max,second_max),make_pair(first_min - 1,second_min - 1),root,root.white_canons[i],se,xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                            }
                            root.cost = root.alpha;
                            
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                }
                
                
                if(second_max+1 <= 7 && first_max+1 <= 7){
                    if(root.game_board[first_min+1][second_min+1]==0){
                        
                        if(first_max+2<=7 && second_max +2 <=7){
                            if(root.game_board[first_max+1][second_max+1] ==0 && (root.game_board[first_max+2][second_max +2] == -1 || root.game_board[first_max+2][second_max +2] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+2,second_max+2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        if(first_max+3<=7 && second_max +3 <=7 ){
                            if(root.game_board[first_max+1][second_max+1] ==0 && root.game_board[first_max+2][second_max+2] == 0 && (root.game_board[first_max+3][second_max +3] == -1 || root.game_board[first_max+3][second_max+3] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+3,second_max+3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_max-1,second_max-1));
                        se.push_back(make_pair(first_max,second_max));
                        se.push_back(make_pair(first_max+1,second_max+1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        re = newBoardWhite(false,make_pair(first_min,second_min),make_pair(first_max + 1,second_max + 1),root,root.white_canons[i],se,xe);
                        re = miniMax(re,d,depth+1);
                        if(root.alpha < re.cost){
                            root.alpha = re.cost;
                            ret = re;
                        }
                        root.cost = root.alpha;
                        
                        if(root.alpha >= root.beta){
                            break;
                        }
                        
                        
                        
                        
                    }
                }
                
                
                
                
            }
            
            if(((second_max == a2 && first_min == a1) || (second_max == a4 && first_min == a3) || (second_max == a6 && first_min == a5)) && first_min != first_max && second_min != second_max){
                if(second_min-1 >= 0 && first_max+1 <= 7){
                    if(root.game_board[first_max+1][second_min-1]==0){
                        
                        if(first_max+2<=7 && second_min -2 >=0){
                            if(root.game_board[first_max+1][second_min-1] ==0 && (root.game_board[first_max+2][second_min -2] == -1 || root.game_board[first_max+2][second_min -2] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+2,second_min-2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        if(first_max+3<=7 && second_min -3 >= 0){
                            if(root.game_board[first_max+1][second_min-1] ==0 && root.game_board[first_max+2][second_min-2] == 0 && (root.game_board[first_max+3][second_min-3] == -1 || root.game_board[first_max+3][second_min-3] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+3,second_min-3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        
                        if(second_min + 1 <= 7){
                            vector<pair<int,int> > se;
                            se.push_back(make_pair(first_max+1,second_min-1));
                            se.push_back(make_pair(first_max,second_min));
                            se.push_back(make_pair(first_max-1,second_min+1));
                            pair<int,int> xe;
                            xe = (make_pair(-1,-1));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(false,make_pair(first_min,second_max),make_pair(first_max + 1,second_min-1),root,root.white_canons[i],se,xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                            }
                            root.cost = root.alpha;
                            
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                }
                
                
                if(second_max+1 <= 7 && first_min-1 >= 0){
                    
                    if(root.game_board[first_min-1][second_max+1]==0){
                        
                        if(first_min-2>=0 && second_max +2 <=7){
                            if(root.game_board[first_min-1][second_max+1] ==0 && (root.game_board[first_min-2][second_max+2] == -1 || root.game_board[first_min-2][second_max+2] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_min-2,second_max+2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        if(first_max+3<=7 && second_min -3 >= 0){
                            if(root.game_board[first_max+1][second_min-1] ==0 && root.game_board[first_max+2][second_min-2] == 0 && (root.game_board[first_max+3][second_min-3] == -1 || root.game_board[first_max+3][second_min-3] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+3,second_min-3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        if(first_min+1 <=7){
                            vector<pair<int,int> > se;
                            se.push_back(make_pair(first_min-1,second_max+1));
                            se.push_back(make_pair(first_min,second_max));
                            se.push_back(make_pair(first_min+1,second_max-1));
                            pair<int,int> xe;
                            xe = (make_pair(-1,-1));
                            pair<int,int> pqr = make_pair(-1,-1);
                            
                            re = newBoardWhite(false,make_pair(first_max,second_min),make_pair(first_min-1,second_max+1),root,root.white_canons[i],se,xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                            }
                            root.cost = root.alpha;
                            
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                }
                
                
                
            }
            
            
            if(first_min == first_max && second_max + 1<=7){
                
                if(root.game_board[first_max][second_max+1] == 0){
                    
                    if(second_max+2<=7){
                        if(root.game_board[first_max][second_max+1] ==0 && (root.game_board[first_max][second_max +2] == -1 || root.game_board[first_max][second_max+2] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_max+2));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                    }
                    
                    if(second_max+3<=7){
                        if(root.game_board[first_max][second_max+1] ==0 && root.game_board[first_max][second_max+2] == 0 && (root.game_board[first_max][second_max + 3] == -1 || root.game_board[first_max][second_max+3] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_max+3));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    vector<pair<int,int> > se;
                    if(second_max -1>=0&& second_max+1<=7){
                        se.push_back(make_pair(first_max,second_max));
                        se.push_back(make_pair(first_max,second_max-1));
                        se.push_back(make_pair(first_max,second_max+1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        
                        re = newBoardWhite(false,make_pair(first_max,second_min),make_pair(first_max,second_min - 1),root,root.white_canons[i],se,xe);
                        re = miniMax(re,d,depth+1);
                        if(root.alpha < re.cost){
                            root.alpha = re.cost;
                            ret = re;
                        }
                        root.cost = root.alpha;
                    }
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                }
            }
            
            
            if(first_min == first_max && second_min - 1>=0){
                
                if(root.game_board[first_max][second_min-1] == 0){
                    
                    if(second_min-2>=0){
                        if(root.game_board[first_max][second_min-1] ==0 && (root.game_board[first_max][second_min -2] == -1 || root.game_board[first_max][second_min-2] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_min-2));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(second_min-3>=0){
                        if(root.game_board[first_max][second_min-1] ==0 && root.game_board[first_max][second_min-2] == 0 && (root.game_board[first_max][second_min - 3] == -1 || root.game_board[first_max][second_min-3] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_min-3));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(second_min+1<=7){
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_max,second_min));
                        se.push_back(make_pair(first_max,second_min-1));
                        se.push_back(make_pair(first_max,second_min+1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        re = newBoardWhite(false,make_pair(first_max,second_max),make_pair(first_max,second_min - 1),root,root.white_canons[i],se,xe);
                        re = miniMax(re,d,depth+1);
                        if(root.alpha < re.cost){
                            root.alpha = re.cost;
                            ret = re;
                        }
                        root.cost = root.alpha;
                    }
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                    
                    
                }
            }
            
            
        }
        
        
        for(int i=0;i<root.whites.size();i++){
            
            if(root.whites[i].first+1<=7){
                if(root.game_board[root.whites[i].first + 1][root.whites[i].second] == -1 || root.game_board[ root.whites[i].first +1][root.whites[i].second] == 0 || root.game_board[ root.whites[i].first +1][root.whites[i].second] == -2){
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    
                    re = newBoardWhite(false,make_pair(root.whites[i].first , root.whites[i].second),make_pair(root.whites[i].first + 1, root.whites[i].second),root,xyz,xyz,pqr);
                    
                    re = miniMax(re,d,depth+1);
                    
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            
            if(root.alpha >= root.beta){
                break;
            }
            
            if(root.whites[i].first+1<=7 && root.whites[i].second+1<=7){
                if(root.game_board[root.whites[i].first+1][root.whites[i].second+1] == -1 || root.game_board[root.whites[i].first+1][root.whites[i].second+1] == 0 || root.game_board[root.whites[i].first+1][root.whites[i].second+1] == -2){
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    re = newBoardWhite(false,make_pair(root.whites[i].first,root.whites[i].second),make_pair(root.whites[i].first+1,root.whites[i].second+1),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            if(root.whites[i].first+1<=7 && root.whites[i].second-1>=0){
                if(root.game_board[root.whites[i].first+1][root.whites[i].second-1] == -1 || root.game_board[root.whites[i].first+1][root.whites[i].second-1] == 0 || root.game_board[root.whites[i].first+1][root.whites[i].second-1] == -2){
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    re = newBoardWhite(false,make_pair(root.whites[i].first,root.whites[i].second),make_pair(root.whites[i].first+1,root.whites[i].second-1),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            if(root.whites[i].second-1>=0){
                if(root.game_board[root.whites[i].first][root.whites[i].second-1] == -1 || root.game_board[root.whites[i].first][root.whites[i].second-1] == -2){
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    re = newBoardWhite(false,make_pair(root.whites[i].first,root.whites[i].second),make_pair(root.whites[i].first,root.whites[i].second-1),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            if(root.whites[i].second+1<=7){
                if(root.game_board[root.whites[i].first][root.whites[i].second+1] == -1 || root.game_board[root.whites[i].first][root.whites[i].second+1] == -2){
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    re = newBoardWhite(false,make_pair(root.whites[i].first,root.whites[i].second),make_pair(root.whites[i].first,root.whites[i].second+1),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            /*if(root.whites[i].first-2 >= 0){
             if(root.game_board[root.whites[i].first-2][root.whites[i].second] == 0 && root.game_board[root.whites[i].first-1][root.whites[i].second] == 0){
             pair<int,int> pqr = make_pair(-1,-1);
             vector<pair<int,int > > xyz;
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             re = newBoardWhite(false,make_pair(root.whites[i].first,root.whites[i].second),make_pair(root.whites[i].first-2,root.whites[i].second),root,xyz,xyz,pqr);
             re = miniMax(re,d,depth+1);
             if(root.alpha < re.cost){
             root.alpha = re.cost;
             ret = re;
             }
             root.cost = root.alpha;
             }
             }
             if(root.alpha >= root.beta){
             break;
             }
             
             if(root.whites[i].first-2 >= 0 && root.whites[i].second-2 >=0){
             if(root.game_board[root.whites[i].first-1][root.whites[i].second-1] == 0 && root.game_board[root.whites[i].first-2][root.whites[i].second-2] == 0){
             pair<int,int> pqr = make_pair(-1,-1);
             vector<pair<int,int > > xyz;
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             re = newBoardWhite(false,make_pair(root.whites[i].first,root.whites[i].second),make_pair(root.whites[i].first-2,root.whites[i].second-2),root,xyz,xyz,pqr);
             re = miniMax(re,d,depth+1);
             if(root.alpha < re.cost){
             root.alpha = re.cost;
             ret = re;
             }
             root.cost = root.alpha;
             }
             }
             if(root.alpha >= root.beta){
             break;
             }
             
             if(root.whites[i].first-2 >= 0 && root.whites[i].second+2 <=7){
             if(root.game_board[root.whites[i].first-1][root.whites[i].second+1] == 0 && root.game_board[root.whites[i].first-2][root.whites[i].second+2] == 0){
             pair<int,int> pqr = make_pair(-1,-1);
             vector<pair<int,int > > xyz;
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             re = newBoardWhite(false,make_pair(root.whites[i].first,root.whites[i].second),make_pair(root.whites[i].first-2,root.whites[i].second+2),root,xyz,xyz,pqr);
             re = miniMax(re,d,depth+1);
             if(root.alpha < re.cost){
             root.alpha = re.cost;
             ret = re;
             }
             root.cost = root.alpha;
             }
             }
             if(root.alpha >= root.beta){
             break;
             }*/
            
        }
        
        
        return root;
        
    }
    
    if(depth == 0){
        
        auto start = std::chrono::high_resolution_clock::now();
        //cout << start;
        
        
        Board re = root;
        Board ret = root;
        for(int i=0;i<root.white_canons.size();i++){
            
            auto end = chrono::high_resolution_clock::now();
            
            // Calculating total time taken by the program.
            int time_taken =
            std::chrono::duration_cast<chrono::seconds>(end - start).count();
            
            if(time_taken > 3){
                return ret;
            }
            
            int a1 = root.white_canons[i][0].first;
            int a2 = root.white_canons[i][0].second;
            int a3 = root.white_canons[i][1].first;
            int a4 = root.white_canons[i][1].second;
            int a5 = root.white_canons[i][2].first;
            int a6 = root.white_canons[i][2].second;
            int first_max = max(max(a1,a3),a5);
            int first_min = min(min(a1,a3),a5);
            int second_max = max(max(a2,a4),a6);
            int second_min = min(min(a2,a4),a6);
            
            if(second_min == second_max && first_max+1<=7){
                if(root.game_board[first_max + 1][second_max] == 0){
                    
                    if(first_max+2<=7){
                        if(root.game_board[first_max+1][second_max] ==0 && (root.game_board[first_max+2][second_max ] == -1 || root.game_board[first_max+2][second_max] == -2)){
                            
                            if(root.game_board[first_max + 2][second_max] == -2){
                                root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_max+2) + " " + to_string(second_max);
                                return root;
                            }
                            
                            pair<int,int> xe;
                            xe = (make_pair(first_max+2,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                                ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_max+2) + " " + to_string(second_max);
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                    }
                    
                    if(first_max+3<=7){
                        if(root.game_board[first_max+1][second_max] ==0 && root.game_board[first_max+2][second_max] == 0 && (root.game_board[first_max+3][second_max] == -1 || root.game_board[first_max+3][second_max] == -2)){
                            if(root.game_board[first_max + 3][second_max] == -2){
                                root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_max+3) + " " + to_string(second_max);
                                return root;
                            }
                            pair<int,int> xe;
                            xe = (make_pair(first_max+3,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                                ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_max+3) + " " + to_string(second_max);
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                    }
                    
                    vector<pair<int,int> > se;
                    se.push_back(make_pair(first_max+1,second_min));
                    se.push_back(make_pair(first_max,second_min));
                    se.push_back(make_pair(first_max-1,second_min));
                    pair<int,int> xe;
                    xe = (make_pair(-1,-1));
                    pair<int,int> pqr = make_pair(-1,-1);
                    re = newBoardWhite(false,make_pair(first_min,second_min),make_pair(first_max + 1,second_min),root,root.white_canons[i],se,xe);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                        ret.theMove = "S " + to_string(first_min) + " " + to_string(second_min) + " M " + to_string(first_max+1) + " " + to_string(second_max);
                    }
                    root.cost = root.alpha;
                    
                    if(root.alpha >= root.beta){
                        break;
                    }
                }
            }
            
            
            
            
            if(second_min == second_max && first_min-1>=0){
                if(root.game_board[first_min-1][second_max] == 0){
                    
                    if(first_min-2>=0){
                        if(root.game_board[first_min-1][second_max] ==0 && (root.game_board[first_min-2][second_max ] == -1 || root.game_board[first_min-2][second_max] == -2)){
                            if(root.game_board[first_min - 2][second_max] == -2){
                                root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_min-2) + " " + to_string(second_max);
                                return root;
                            }
                            pair<int,int> xe;
                            xe = (make_pair(first_min-2,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                                ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_min-2) + " " + to_string(second_max);
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(first_min-3>=0){
                        if(root.game_board[first_min-1][second_max] ==0 && root.game_board[first_min-2][second_max] == 0 && (root.game_board[first_min-3][second_max] == -1 || root.game_board[first_min-3][second_max] == -2)){
                            
                            if(root.game_board[first_min-3][second_max] == -2){
                                root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_min-3) + " " + to_string(second_max);
                                return root;
                            }
                            
                            pair<int,int> xe;
                            xe = (make_pair(first_min-3,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                                ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_min-3) + " " + to_string(second_max);
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                    }
                    
                    vector<pair<int,int> > se;
                    se.push_back(make_pair(first_min+1,second_min));
                    se.push_back(make_pair(first_min,second_min));
                    se.push_back(make_pair(first_min-1,second_min));
                    pair<int,int> xe;
                    xe = (make_pair(-1,-1));
                    pair<int,int> pqr = make_pair(-1,-1);
                    re = newBoardWhite(false,make_pair(first_max,second_min),make_pair(first_min - 1,second_min),root,root.white_canons[i],se,xe);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                        ret.theMove = "S " + to_string(first_max) + " " + to_string(second_min) + " M " + to_string(first_min-1) + " " + to_string(second_max);
                    }
                    root.cost = root.alpha;
                    
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                }
            }
            
            
            
            if(((second_max == a2 && first_max == a1) || (second_max == a4 && first_max == a3) || (second_max == a6 && first_max == a5)) && first_max != first_min && second_min != second_max){
                if(second_min-1 >= 0 && first_min-1 >= 0){
                    if(root.game_board[first_min-1][second_min-1]==0){
                        
                        if(first_min-2>=0 && second_min -2 >=0){
                            if(root.game_board[first_min-1][second_min-1] ==0 && (root.game_board[first_min-2][second_min -2] == -1 || root.game_board[first_min-2][second_min -2] == -2)){
                                
                                if(root.game_board[first_min - 2][second_min-2] == -2){
                                    root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_min-2) + " " + to_string(second_min-2);
                                    return root;
                                }
                                
                                pair<int,int> xe;
                                xe = (make_pair(first_min-2,second_min-2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                    ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_min-2) + " " + to_string(second_min-2);
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        if(first_min-3>=0 && second_min -3 >= 0){
                            if(root.game_board[first_min-1][second_min-1] ==0 && root.game_board[first_min-2][second_min-2] == 0 && (root.game_board[first_min-3][second_min -3] == -1 || root.game_board[first_min-3][second_min-3] == -2)){
                                
                                if(root.game_board[first_min- 3][second_min-3] == -2){
                                    root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_min-3) + " " + to_string(second_min-3);
                                    return root;
                                }
                                
                                pair<int,int> xe;
                                xe = (make_pair(first_min-3,second_min-3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                    ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_min-3) + " " + to_string(second_min-3);
                                    
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_min-1,second_min-1));
                        se.push_back(make_pair(first_min,second_min));
                        se.push_back(make_pair(first_min+1,second_min+1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        re = newBoardWhite(false,make_pair(first_max,second_max),make_pair(first_min - 1,second_min - 1),root,root.white_canons[i],se,xe);
                        re = miniMax(re,d,depth+1);
                        if(root.alpha < re.cost){
                            root.alpha = re.cost;
                            ret = re;
                            ret.theMove = "S " + to_string(first_max) + " " + to_string(second_max) + " M " + to_string(first_min-1) + " " + to_string(second_min-1);
                        }
                        root.cost = root.alpha;
                        
                        if(root.alpha >= root.beta){
                            break;
                        }
                        
                        
                        
                    }
                }
                
                
                if(second_max+1 <= 7 && first_max+1 <= 7){
                    if(root.game_board[first_min+1][second_min+1]==0){
                        
                        if(first_max+2<=7 && second_max +2 <=7){
                            if(root.game_board[first_max+1][second_max+1] ==0 && (root.game_board[first_max+2][second_max +2] == -1 || root.game_board[first_max+2][second_max +2] == -2)){
                                
                                if(root.game_board[first_max + 2][second_max + 2] == -2){
                                    root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_max+2) + " " + to_string(second_max + 2);
                                    return root;
                                }
                                
                                pair<int,int> xe;
                                xe = (make_pair(first_max+2,second_max+2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                    ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_max+2) + " " + to_string(second_max+2);
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        if(first_max+3<=7 && second_max +3 <=7 ){
                            if(root.game_board[first_max+1][second_max+1] ==0 && root.game_board[first_max+2][second_max+2] == 0 && (root.game_board[first_max+3][second_max +3] == -1 || root.game_board[first_max+3][second_max+3] == -2)){
                                
                                if(root.game_board[first_max + 3][second_max + 3] == -2){
                                    root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_max+3) + " " + to_string(second_max + 3);
                                    return root;
                                }
                                
                                pair<int,int> xe;
                                xe = (make_pair(first_max+3,second_max+3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                    ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_max+3) + " " + to_string(second_max+3);
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_max-1,second_max-1));
                        se.push_back(make_pair(first_max,second_max));
                        se.push_back(make_pair(first_max+1,second_max+1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        re = newBoardWhite(false,make_pair(first_min,second_min),make_pair(first_max + 1,second_max+1),root,root.white_canons[i],se,xe);
                        re = miniMax(re,d,depth+1);
                        if(root.alpha < re.cost){
                            root.alpha = re.cost;
                            ret = re;
                            ret.theMove = "S " + to_string(first_min) + " " + to_string(second_min) + " M " + to_string(first_max+1) + " " + to_string(second_max+1);
                        }
                        root.cost = root.alpha;
                        
                        if(root.alpha >= root.beta){
                            break;
                        }
                    }
                }
            }
            
            if(((second_max == a2 && first_min == a1) || (second_max == a4 && first_min == a3) || (second_max == a6 && first_min == a5)) && first_min != first_max && second_min != second_max){
                if(second_min-1 >= 0 && first_max+1 <= 7){
                    if(root.game_board[first_max+1][second_min-1]==0){
                        
                        if(first_max+2<=7 && second_min -2 >=0){
                            if(root.game_board[first_max+1][second_min-1] ==0 && (root.game_board[first_max+2][second_min -2] == -1 || root.game_board[first_max+2][second_min -2] == -2)){
                                
                                if(root.game_board[first_max + 2][second_min-2] == -2){
                                    root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_max+2) + " " + to_string(second_min-2);
                                    return root;
                                }
                                
                                pair<int,int> xe;
                                xe = (make_pair(first_max+2,second_min-2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                    ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_max + 2) + " " + to_string(second_min-2);
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                        }
                        
                        if(first_max+3<=7 && second_min -3 >= 0){
                            if(root.game_board[first_max+1][second_min-1] ==0 && root.game_board[first_max+2][second_min-2] == 0 && (root.game_board[first_max+3][second_min-3] == -1 || root.game_board[first_max+3][second_min-3] == -2)){
                                
                                if(root.game_board[first_max + 3][second_min-3] == -2){
                                    root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_max+3) + " " + to_string(second_min-3);
                                    return root;
                                }
                                
                                pair<int,int> xe;
                                xe = (make_pair(first_max+3,second_min-3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                    ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_max+3) + " " + to_string(second_min-3);
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                        }
                        
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_max+1,second_min-1));
                        se.push_back(make_pair(first_max,second_min));
                        se.push_back(make_pair(first_max-1,second_min+1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        re = newBoardWhite(false,make_pair(first_min,second_max),make_pair(first_max + 1,second_min - 1),root,root.white_canons[i],se,xe);
                        re = miniMax(re,d,depth+1);
                        if(root.alpha < re.cost){
                            root.alpha = re.cost;
                            ret = re;
                            ret.theMove = "S " + to_string(first_min) + " " + to_string(second_max) + " M " + to_string(first_max+1) + " " + to_string(second_min-1);
                        }
                        root.cost = root.alpha;
                        
                        if(root.alpha >= root.beta){
                            break;
                        }
                    }
                }
                
                
                if(second_max+1 <= 7 && first_min-1 >= 0){
                    if(root.game_board[first_min-1][second_max+1]==0){
                        
                        if(first_min-2>=0 && second_max +2 <=7){
                            if(root.game_board[first_min-1][second_max+1] ==0 && (root.game_board[first_min-2][second_max+2] == -1 || root.game_board[first_min-2][second_max+2] == -2)){
                                
                                if(root.game_board[first_min - 2][second_max + 2] == -2){
                                    root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_min-2) + " " + to_string(second_max + 2);
                                    return root;
                                }
                                
                                pair<int,int> xe;
                                xe = (make_pair(first_min-2,second_max+2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                    ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_min-2) + " " + to_string(second_max+2);
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        if(first_max+3<=7 && second_min -3 >= 0){
                            if(root.game_board[first_max+1][second_min-1] ==0 && root.game_board[first_max+2][second_min-2] == 0 && (root.game_board[first_max+3][second_min-3] == -1 || root.game_board[first_max+3][second_min-3] == -2)){
                                
                                if(root.game_board[first_max + 3][second_min - 3] == -2){
                                    root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_max+3) + " " + to_string(second_min-3);
                                    return root;
                                }
                                
                                pair<int,int> xe;
                                xe = (make_pair(first_max+3,second_min-3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.alpha < re.cost){
                                    root.alpha = re.cost;
                                    ret = re;
                                    ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_max+3) + " " + to_string(second_min-3);
                                }
                                root.cost = root.alpha;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                        }
                        
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_min-1,second_max+1));
                        se.push_back(make_pair(first_min,second_max));
                        se.push_back(make_pair(first_min+1,second_max-1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        re = newBoardWhite(false,make_pair(first_max,second_min),make_pair(first_min - 1,second_max + 1),root,root.white_canons[i],se,xe);
                        re = miniMax(re,d,depth+1);
                        if(root.alpha < re.cost){
                            root.alpha = re.cost;
                            ret = re;
                            ret.theMove = "S " + to_string(first_max) + " " + to_string(second_min) + " M " + to_string(first_min-1) + " " + to_string(second_max+1);
                        }
                        root.cost = root.alpha;
                        
                        if(root.alpha >= root.beta){
                            break;
                        }
                    }
                }
            }
            
            
            if(first_min == first_max && second_max + 1<=7){
                if(root.game_board[first_max][second_max+1] == 0){
                    
                    if(second_max+2<=7){
                        if(root.game_board[first_max][second_max+1] ==0 && (root.game_board[first_max][second_max +2] == -1 || root.game_board[first_max][second_max+2] == -2)){
                            if(root.game_board[first_max][second_max+2] == -2){
                                root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_max) + " " + to_string(second_max+2);
                                return root;
                            }
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_max+2));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                                ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_max) + " " + to_string(second_max+2);
                                
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                    }
                    
                    if(second_max+3<=7){
                        if(root.game_board[first_max][second_max+1] ==0 && root.game_board[first_max][second_max+2] == 0 && (root.game_board[first_max][second_max + 3] == -1 || root.game_board[first_max][second_max+3] == -2)){
                            if(root.game_board[first_max][second_max+3] == -2){
                                root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_max) + " " + to_string(second_max+3);
                                return root;
                            }
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_max+3));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                                ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_max) + " " + to_string(second_max+3);
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    
                    vector<pair<int,int> > se;
                    se.push_back(make_pair(first_max,second_max));
                    se.push_back(make_pair(first_max,second_max-1));
                    se.push_back(make_pair(first_max,second_max+1));
                    
                    pair<int,int> xe;
                    xe = (make_pair(-1,-1));
                    pair<int,int> pqr = make_pair(-1,-1);
                    re = newBoardWhite(false,make_pair(first_max,second_min),make_pair(first_max,second_max + 1),root,root.white_canons[i],se,xe);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                        ret.theMove = "S " + to_string(first_max) + " " + to_string(second_min) + " M " + to_string(first_max) + " " + to_string(second_max+1);
                    }
                    root.cost = root.alpha;
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                }
            }
            
            
            if(first_min == first_max && second_min - 1>=0){
                if(root.game_board[first_max][second_min-1] == 0){
                    
                    if(second_min-2>=0){
                        if(root.game_board[first_max][second_min-1] ==0 && (root.game_board[first_max][second_min -2] == -1 || root.game_board[first_max][second_min-2] == -2)){
                            
                            if(root.game_board[first_max][second_min-2] == -2){
                                root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_max) + " " + to_string(second_min-2);
                                return root;
                            }
                            
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_min-2));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                                ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_max) + " " + to_string(second_min-2);
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(second_min-3>=0){
                        if(root.game_board[first_max][second_min-1] ==0 && root.game_board[first_max][second_min-2] == 0 && (root.game_board[first_max][second_min - 3] == -1 || root.game_board[first_max][second_min-3] == -2)){
                            if(root.game_board[first_max][second_min-3] == -2){
                                root.theMove = "S "+ to_string(a1) +" "  + to_string(a2) + " B " + to_string(first_max) + " " + to_string(second_min-3);
                                return root;
                            }
                            
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_min-3));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardWhite(true,pqr,pqr,root,root.white_canons[i],root.white_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.alpha < re.cost){
                                root.alpha = re.cost;
                                ret = re;
                                ret.theMove = "S " + to_string(a1) + " " + to_string(a2) + " B " + to_string(first_max) + " " + to_string(second_min-3);
                            }
                            root.cost = root.alpha;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    
                    vector<pair<int,int> > se;
                    se.push_back(make_pair(first_max,second_min));
                    se.push_back(make_pair(first_max,second_min-1));
                    se.push_back(make_pair(first_max,second_min+1));
                    pair<int,int> xe;
                    xe = (make_pair(-1,-1));
                    pair<int,int> pqr = make_pair(-1,-1);
                    re = newBoardWhite(false,make_pair(first_max,second_max),make_pair(first_max ,second_min - 1),root,root.white_canons[i],se,xe);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                        ret.theMove = "S " + to_string(first_max) + " " + to_string(second_max) + " M " + to_string(first_max) + " " + to_string(second_min-1);
                        //cout << ret.theMove;
                        //cout << "b";
                    }
                    root.cost = root.alpha;
                    
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                    
                    
                }
            }
            
            
            
            
        }
        
        
        for(int i=0;i<root.whites.size();i++){
            
            auto end = chrono::high_resolution_clock::now();
            
            // Calculating total time taken by the program.
            int time_taken =
            std::chrono::duration_cast<chrono::seconds>(end - start).count();
            
            if(time_taken > 3){
                return ret;
            }
            
            if(root.whites[i].first+1<=7){
                
                if(root.game_board[root.whites[i].first + 1][root.whites[i].second] == -1 || root.game_board[ root.whites[i].first +1][root.whites[i].second] == 0 || root.game_board[ root.whites[i].first +1][root.whites[i].second] == -2){
                    
                    if(root.game_board[root.whites[i].first + 1][root.whites[i].second] == -2){
                        root.theMove = "S "+ to_string(root.whites[i].first) +" "  + to_string(root.whites[i].second) + " M " + to_string(root.whites[i].first+1) + " " + to_string(root.whites[i].second);
                        return root;
                    }
                    
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    
                    re = newBoardWhite(false,make_pair(root.whites[i].first , root.whites[i].second),make_pair(root.whites[i].first + 1, root.whites[i].second),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                        ret.theMove = "S " + to_string(root.whites[i].first) + " " + to_string(root.whites[i].second) + " M " + to_string(root.whites[i].first+1) + " " + to_string(root.whites[i].second);
                    }
                    root.cost = root.alpha;
                }
            }
            
            if(root.alpha >= root.beta){
                break;
            }
            
            
            if(root.whites[i].first+1<=7 && root.whites[i].second+1<=7){
                
                if(root.game_board[root.whites[i].first+1][root.whites[i].second+1] == -1 || root.game_board[root.whites[i].first+1][root.whites[i].second+1] == 0 || root.game_board[root.whites[i].first+1][root.whites[i].second+1] == -2){
                    
                    if(root.game_board[root.whites[i].first + 1][root.whites[i].second + 1] == -2){
                        root.theMove = "S "+ to_string(root.whites[i].first) +" "  + to_string(root.whites[i].second) + " M " + to_string(root.whites[i].first+1) + " " + to_string(root.whites[i].second + 1);
                        return root;
                    }
                    
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    
                    re = newBoardWhite(false,make_pair(root.whites[i].first,root.whites[i].second),make_pair(root.whites[i].first+1,root.whites[i].second+1),root,xyz,xyz,pqr);
                    
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                        ret.theMove = "S " + to_string(root.whites[i].first) + " " + to_string(root.whites[i].second) + " M " + to_string(root.whites[i].first+1) + " " + to_string(root.whites[i].second +1);
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            if(root.whites[i].first+1<=7 && root.whites[i].second-1>=0){
                if(root.game_board[root.whites[i].first+1][root.whites[i].second-1] == -1 || root.game_board[root.whites[i].first+1][root.whites[i].second-1] == 0 || root.game_board[root.whites[i].first+1][root.whites[i].second-1] == -2){
                    
                    if(root.game_board[root.whites[i].first + 1][root.whites[i].second - 1] == -2){
                        root.theMove = "S "+ to_string(root.whites[i].first) +" "  + to_string(root.whites[i].second) + " M " + to_string(root.whites[i].first+1) + " " + to_string(root.whites[i].second - 1);
                        return root;
                    }
                    
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    re = newBoardWhite(false,make_pair(root.whites[i].first,root.whites[i].second),make_pair(root.whites[i].first+1,root.whites[i].second-1),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                        ret.theMove = "S " + to_string(root.whites[i].first) + " " + to_string(root.whites[i].second) + " M " + to_string(root.whites[i].first+1) + " " + to_string(root.whites[i].second-1);
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            if(root.whites[i].second-1>=0){
                if(root.game_board[root.whites[i].first][root.whites[i].second-1] == -1 || root.game_board[root.whites[i].first][root.whites[i].second-1] == -2){
                    
                    if(root.game_board[root.whites[i].first ][root.whites[i].second - 1] == -2){
                        root.theMove = "S "+ to_string(root.whites[i].first) +" "  + to_string(root.whites[i].second) + " M " + to_string(root.whites[i].first) + " " + to_string(root.whites[i].second - 1);
                        return root;
                    }
                    
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    re = newBoardWhite(false,make_pair(root.whites[i].first,root.whites[i].second),make_pair(root.whites[i].first,root.whites[i].second-1),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                        ret.theMove = "S " + to_string(root.whites[i].first) + " " + to_string(root.whites[i].second) + " M " + to_string(root.whites[i].first) + " " + to_string(root.whites[i].second-1);
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            if(root.whites[i].second+1<=7){
                if(root.game_board[root.whites[i].first][root.whites[i].second+1] == -1 || root.game_board[root.whites[i].first][root.whites[i].second+1] == -2){
                    
                    if(root.game_board[root.whites[i].first][root.whites[i].second + 1] == -2){
                        root.theMove = "S "+ to_string(root.whites[i].first) +" "  + to_string(root.whites[i].second) + " M " + to_string(root.whites[i].first) + " " + to_string(root.whites[i].second + 1);
                        return root;
                    }
                    
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    re = newBoardWhite(false,make_pair(root.whites[i].first,root.whites[i].second),make_pair(root.whites[i].first,root.whites[i].second+1),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                        ret.theMove = "S " + to_string(root.whites[i].first) + " " + to_string(root.whites[i].second) + " M " + to_string(root.whites[i].first) + " " + to_string(root.whites[i].second+1);
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            /*if(root.whites[i].first-2 >= 0){
             if(root.game_board[root.whites[i].first-2][root.whites[i].second] == 0 && root.game_board[root.whites[i].first-1][root.whites[i].second] == 0){
             pair<int,int> pqr = make_pair(-1,-1);
             vector<pair<int,int > > xyz;
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             re = newBoardWhite(false,make_pair(root.whites[i].first,root.whites[i].second),make_pair(root.whites[i].first-2,root.whites[i].second),root,xyz,xyz,pqr);
             re = miniMax(re,d,depth+1);
             if(root.alpha < re.cost){
             root.alpha = re.cost;
             ret = re;
             ret.theMove = "S " + to_string(root.whites[i].first) + " " + to_string(root.whites[i].second) + " M " + to_string(root.whites[i].first-2) + " " + to_string(root.whites[i].second);
             }
             root.cost = root.alpha;
             }
             }
             if(root.alpha >= root.beta){
             break;
             }
             
             if(root.whites[i].first-2 >= 0 && root.whites[i].second-2 >=0){
             if(root.game_board[root.whites[i].first-1][root.whites[i].second-1] == 0 && root.game_board[root.whites[i].first-2][root.whites[i].second-2] == 0){
             pair<int,int> pqr = make_pair(-1,-1);
             vector<pair<int,int > > xyz;
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             re = newBoardWhite(false,make_pair(root.whites[i].first,root.whites[i].second),make_pair(root.whites[i].first-2,root.whites[i].second-2),root,xyz,xyz,pqr);
             re = miniMax(re,d,depth+1);
             if(root.alpha < re.cost){
             root.alpha = re.cost;
             ret = re;
             ret.theMove = "S " + to_string(root.whites[i].first) + " " + to_string(root.whites[i].second) + " M " + to_string(root.whites[i].first-2) + " " + to_string(root.whites[i].second-2);
             }
             root.cost = root.alpha;
             }
             }
             if(root.alpha >= root.beta){
             break;
             }
             
             if(root.whites[i].first-2 >= 0 && root.whites[i].second+2 <=7){
             if(root.game_board[root.whites[i].first-1][root.whites[i].second+1] == 0 && root.game_board[root.whites[i].first-2][root.whites[i].second+2] == 0){
             pair<int,int> pqr = make_pair(-1,-1);
             vector<pair<int,int > > xyz;
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             re = newBoardWhite(false,make_pair(root.whites[i].first,root.whites[i].second),make_pair(root.whites[i].first-2,root.whites[i].second+2),root,xyz,xyz,pqr);
             re = miniMax(re,d,depth+1);
             if(root.alpha < re.cost){
             root.alpha = re.cost;
             ret = re;
             ret.theMove = "S " + to_string(root.whites[i].first) + " " + to_string(root.whites[i].second) + " M " + to_string(root.whites[i].first-2) + " " + to_string(root.whites[i].second+2);
             }
             root.cost = root.alpha;
             }
             }
             if(root.alpha >= root.beta){
             break;
             }*/
        }
        return ret;
        
    }
    
    if(depth == d-1){
        Board re = root;
        Board ret = root;
        
        
        for(int i=0;i<root.black_canons.size();i++){
            int a1 = root.black_canons[i][0].first;
            int a2 = root.black_canons[i][0].second;
            int a3 = root.black_canons[i][1].first;
            int a4 = root.black_canons[i][1].second;
            int a5 = root.black_canons[i][2].first;
            int a6 = root.black_canons[i][2].second;
            int first_max = max(max(a1,a3),a5);
            int first_min = min(min(a1,a3),a5);
            int second_max = max(max(a2,a4),a6);
            int second_min = min(min(a2,a4),a6);
            
            
            
            
            
            if(second_min == second_max && first_min-1>=0){
                
                if(root.game_board[first_min-1][second_max] == 0){
                    
                    if(first_min-2>=0){
                        
                        if(root.game_board[first_min-1][second_max] ==0 && (root.game_board[first_min-1][second_max ] == -1 || root.game_board[first_min-1][second_max] == -2)){
                            
                            pair<int,int> xe;
                            xe = (make_pair(first_min-2,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(first_min-3>=0){
                        
                        if(root.game_board[first_min-1][second_max] ==0 && root.game_board[first_min-2][second_max] == 0 && (root.game_board[first_min-3][second_max] == -1 || root.game_board[first_min-3][second_max] == -2)){
                            
                            pair<int,int> xe;
                            xe = (make_pair(first_min-3,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    vector<pair<int,int> > se;
                    se.push_back(make_pair(first_min+1,second_min));
                    se.push_back(make_pair(first_min,second_min));
                    se.push_back(make_pair(first_min-1,second_min));
                    pair<int,int> xe;
                    xe = (make_pair(-1,-1));
                    pair<int,int> pqr = make_pair(-1,-1);
                    
                    re = newBoardBlack(false,make_pair(first_max,second_min),make_pair(first_min - 1,second_min),root,root.black_canons[i],se,xe);
                    
                    re = miniMax(re,d,depth+1);
                    
                    if(root.beta > re.cost){
                        root.beta = re.cost;
                        ret = re;
                    }
                    root.cost = root.beta;
                    
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                }
            }
            
            
            
            if(((second_max == a2 && first_max == a1) || (second_max == a4 && first_max == a3) || (second_max == a6 && first_max == a5)) && first_max != first_min && second_max != second_min){
                
                if(second_min-1 >= 0 && first_min-1 >= 0){
                    
                    if(root.game_board[first_min-1][second_min-1]==0){
                        
                        if(first_min-2>=0 && second_min -2 >=0){
                            if(root.game_board[first_min-1][second_min-1] ==0 && (root.game_board[first_min-2][second_min -2] == -1 || root.game_board[first_min-2][second_min -2] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_min-2,second_min-2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        if(first_min-3>=0 && second_min -3 >= 0){
                            if(root.game_board[first_min-1][second_min-1] ==0 && root.game_board[first_min-2][second_min-2] == 0 && (root.game_board[first_min-3][second_min -3] == -1 || root.game_board[first_min-3][second_min-3] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_min-3,second_min-3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_min-1,second_min-1));
                        se.push_back(make_pair(first_min,second_min));
                        se.push_back(make_pair(first_min+1,second_min+1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        
                        re = newBoardBlack(false,make_pair(first_max,second_max),make_pair(first_min - 1,second_min - 1),root,root.black_canons[i],se,xe);
                        
                        re = miniMax(re,d,depth+1);
                        if(root.beta > re.cost){
                            root.beta = re.cost;
                            ret = re;
                        }
                        root.cost = root.beta;
                        
                        if(root.alpha >= root.beta){
                            break;
                        }
                        
                        
                        
                    }
                }
                
                
                if(second_max+1 <= 7 && first_max+1 <= 7){
                    
                    if(root.game_board[first_min+1][second_min+1]==0){
                        
                        if(first_max+2<=7 && second_max +2 <=7){
                            if(root.game_board[first_max+1][second_max+1] ==0 && (root.game_board[first_max+2][second_max +2] == -1 || root.game_board[first_max+2][second_max +2] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+2,second_max+2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        if(first_max+3<=7 && second_max +3 <=7 ){
                            if(root.game_board[first_max+1][second_max+1] ==0 && root.game_board[first_max+2][second_max+2] == 0 && (root.game_board[first_max+3][second_max +3] == -1 || root.game_board[first_max+3][second_max+3] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+3,second_max+3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_max-1,second_max-1));
                        se.push_back(make_pair(first_max,second_max));
                        se.push_back(make_pair(first_max+1,second_max+1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        
                        re = newBoardBlack(false,make_pair(first_min,second_min),make_pair(first_max + 1,second_max + 1),root,root.black_canons[i],se,xe);
                        
                        re = miniMax(re,d,depth+1);
                        if(root.beta > re.cost){
                            root.beta = re.cost;
                            ret = re;
                        }
                        root.cost = root.beta;
                        
                        if(root.alpha >= root.beta){
                            break;
                        }
                        
                        
                        
                        
                    }
                }
                
                
                
                
            }
            
            if(((second_max == a2 && first_min == a1) || (second_max == a4 && first_min == a3) || (second_max == a6 && first_min == a5)) && first_max != first_min && second_max != second_min){
                if(second_min-1 >= 0 && first_max+1 <= 7){
                    if(root.game_board[first_max+1][second_min-1]==0){
                        
                        if(first_max+2<=7 && second_min -2 >=0){
                            if(root.game_board[first_max+1][second_min-1] ==0 && (root.game_board[first_max+2][second_min -2] == -1 || root.game_board[first_max+2][second_min -2] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+2,second_min-2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        if(first_max+3<=7 && second_min -3 >= 0){
                            if(root.game_board[first_max+1][second_min-1] ==0 && root.game_board[first_max+2][second_min-2] == 0 && (root.game_board[first_max+3][second_min-3] == -1 || root.game_board[first_max+3][second_min-3] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+3,second_min-3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_max+1,second_min-1));
                        se.push_back(make_pair(first_max,second_min));
                        se.push_back(make_pair(first_max-1,second_min+1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        re = newBoardBlack(false,make_pair(first_min,second_max),make_pair(first_max + 1,second_min - 1),root,root.black_canons[i],se,xe);
                        re = miniMax(re,d,depth+1);
                        if(root.beta > re.cost){
                            root.beta = re.cost;
                            ret = re;
                        }
                        root.cost = root.beta;
                        
                        if(root.alpha >= root.beta){
                            break;
                        }
                        
                        
                        
                    }
                }
                
                
                if(second_max+1 <= 7 && first_min-1 >= 0){
                    if(root.game_board[first_min-1][second_min+1]==0){
                        
                        if(first_min-2>=0 && second_max +2 <=7){
                            if(root.game_board[first_min-1][second_max+1] ==0 && (root.game_board[first_min-2][second_max+2] == -1 || root.game_board[first_min-2][second_max+2] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_min-2,second_max+2));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        if(first_max+3<=7 && second_min -3 >= 0){
                            if(root.game_board[first_max+1][second_min-1] ==0 && root.game_board[first_max+2][second_min-2] == 0 && (root.game_board[first_max+3][second_min-3] == -1 || root.game_board[first_max+3][second_min-3] == -2)){
                                pair<int,int> xe;
                                xe = (make_pair(first_max+3,second_min-3));
                                pair<int,int> pqr = make_pair(-1,-1);
                                re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                                re = miniMax(re,d,depth+1);
                                if(root.beta > re.cost){
                                    root.beta = re.cost;
                                    ret = re;
                                }
                                root.cost = root.beta;
                                if(root.alpha >= root.beta){
                                    break;
                                }
                            }
                            
                            
                        }
                        
                        vector<pair<int,int> > se;
                        se.push_back(make_pair(first_min-1,second_max+1));
                        se.push_back(make_pair(first_min,second_max));
                        se.push_back(make_pair(first_min+1,second_max-1));
                        pair<int,int> xe;
                        xe = (make_pair(-1,-1));
                        pair<int,int> pqr = make_pair(-1,-1);
                        re = newBoardBlack(false,make_pair(first_max,second_min),make_pair(first_min - 1,second_max + 1),root,root.black_canons[i],se,xe);
                        re = miniMax(re,d,depth+1);
                        if(root.beta > re.cost){
                            root.beta = re.cost;
                            ret = re;
                        }
                        root.cost = root.beta;
                        
                        if(root.alpha >= root.beta){
                            break;
                        }
                        
                        
                        
                    }
                }
                
                
                
            }
            
            
            if(first_min == first_max && second_max + 1<=7){
                
                if(root.game_board[first_max][second_max+1] == 0){
                    
                    if(second_max+2<=7){
                        if(root.game_board[first_max][second_max+1] ==0 && (root.game_board[first_max][second_max +2] == -1 || root.game_board[first_max][second_max+2] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_max+2));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(second_max+3<=7){
                        if(root.game_board[first_max][second_max+1] ==0 && root.game_board[first_max][second_max+2] == 0 && (root.game_board[first_max][second_max + 3] == -1 || root.game_board[first_max][second_max+3] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_max+3));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    vector<pair<int,int> > se;
                    se.push_back(make_pair(first_max,second_max));
                    se.push_back(make_pair(first_max,second_max-1));
                    se.push_back(make_pair(first_max,second_max+1));
                    pair<int,int> xe;
                    xe = (make_pair(-1,-1));
                    pair<int,int> pqr = make_pair(-1,-1);
                    re = newBoardBlack(false,make_pair(first_max,second_min),make_pair(first_max,second_max + 1),root,root.black_canons[i],se,xe);
                    re = miniMax(re,d,depth+1);
                    if(root.beta > re.cost){
                        root.beta = re.cost;
                        ret = re;
                    }
                    root.cost = root.beta;
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                }
            }
            
            
            if(first_min == first_max && second_min - 1>=0){
                
                if(root.game_board[first_max][second_min-1] == 0){
                    
                    if(second_min-2>=0){
                        if(root.game_board[first_max][second_min-1] ==0 && (root.game_board[first_max][second_min -2] == -1 || root.game_board[first_max][second_min-2] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_min-2));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(second_min-3>=0){
                        if(root.game_board[first_max][second_min-1] ==0 && root.game_board[first_max][second_min-2] == 0 && (root.game_board[first_max][second_min - 3] == -1 || root.game_board[first_max][second_min-3] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max,second_min-3));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    
                    vector<pair<int,int> > se;
                    se.push_back(make_pair(first_max,second_min));
                    se.push_back(make_pair(first_max,second_min-1));
                    se.push_back(make_pair(first_max,second_min+1));
                    pair<int,int> xe;
                    xe = (make_pair(-1,-1));
                    pair<int,int> pqr = make_pair(-1,-1);
                    re = newBoardBlack(false,make_pair(first_max,second_max),make_pair(first_max,second_min-1),root,root.black_canons[i],se,xe);
                    re = miniMax(re,d,depth+1);
                    if(root.beta > re.cost){
                        root.beta = re.cost;
                        ret = re;
                    }
                    root.cost = root.beta;
                    
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                    
                }
            }
            
            
            
            if(second_min == second_max && first_max+1<=7){
                
                if(root.game_board[first_max + 1][second_max] == 0){
                    
                    if(first_max+2<=7){
                        if(root.game_board[first_max+1][second_max] ==0 && (root.game_board[first_max+2][second_max ] == -1 || root.game_board[first_max+2][second_max] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max+2,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    if(first_max+3<=7){
                        if(root.game_board[first_max+1][second_max] ==0 && root.game_board[first_max+2][second_max] == 0 && (root.game_board[first_max+3][second_max] == -1 || root.game_board[first_max+3][second_max] == -2)){
                            pair<int,int> xe;
                            xe = (make_pair(first_max+3,second_max));
                            pair<int,int> pqr = make_pair(-1,-1);
                            re = newBoardBlack(true,pqr,pqr,root,root.black_canons[i],root.black_canons[i],xe);
                            re = miniMax(re,d,depth+1);
                            if(root.beta > re.cost){
                                root.beta = re.cost;
                                ret = re;
                            }
                            root.cost = root.beta;
                            if(root.alpha >= root.beta){
                                break;
                            }
                        }
                        
                        
                    }
                    
                    vector<pair<int,int> > se;
                    se.push_back(make_pair(first_max+1,second_min));
                    se.push_back(make_pair(first_max,second_min));
                    se.push_back(make_pair(first_max-1,second_min));
                    pair<int,int> xe;
                    xe = (make_pair(-1,-1));
                    pair<int,int> pqr = make_pair(-1,-1);
                    re = newBoardBlack(false,make_pair(first_min,second_min),make_pair(first_max + 1,second_min),root,root.black_canons[i],se,xe);
                    re = miniMax(re,d,depth+1);
                    if(root.beta > re.cost){
                        root.beta = re.cost;
                        ret = re;
                    }
                    root.cost = root.beta;
                    
                    if(root.alpha >= root.beta){
                        break;
                    }
                    
                    
                    
                    
                }
            }
            
            
            
        }
        
        
        
        for(int i=0;i<root.blacks.size();i++){
            if(root.blacks[i].first-1>=0){
                if(root.game_board[root.blacks[i].first - 1][root.blacks[i].second] == 1 || root.game_board[ root.blacks[i].first -1][root.blacks[i].second] == 0 || root.game_board[ root.blacks[i].first -1][root.blacks[i].second] == 2){
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    re = newBoardBlack(false,make_pair(root.blacks[i].first , root.blacks[i].second),make_pair(root.blacks[i].first - 1, root.blacks[i].second),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            
            if(root.alpha >= root.beta){
                break;
            }
            
            if(root.blacks[i].first-1>=0 && root.blacks[i].second-1>=0){
                if(root.game_board[root.blacks[i].first-1][root.blacks[i].second-1] == 1 || root.game_board[root.blacks[i].first-1][root.blacks[i].second-1] == 0 || root.game_board[root.blacks[i].first-1][root.blacks[i].second-1] == 2){
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    re = newBoardBlack(false,make_pair(root.blacks[i].first,root.blacks[i].second),make_pair(root.blacks[i].first-1,root.blacks[i].second-1),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            if(root.blacks[i].first-1>=0 && root.blacks[i].second+1<=7){
                
                if(root.game_board[root.blacks[i].first-1][root.blacks[i].second+1] == 1 || root.game_board[root.blacks[i].first-1][root.blacks[i].second+1] == 0 || root.game_board[root.blacks[i].first-1][root.blacks[i].second+1] == 2){
                    
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    
                    re = newBoardBlack(false,make_pair(root.blacks[i].first,root.blacks[i].second),make_pair(root.blacks[i].first-1,root.blacks[i].second+1),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            
            if(root.blacks[i].second-1>=0){
                if(root.game_board[root.blacks[i].first][root.blacks[i].second-1] == 1 || root.game_board[root.blacks[i].first][root.blacks[i].second-1] == 2){
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    re = newBoardBlack(false,make_pair(root.blacks[i].first,root.blacks[i].second),make_pair(root.blacks[i].first,root.blacks[i].second-1),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            if(root.blacks[i].second+1<=7){
                if(root.game_board[root.blacks[i].first][root.blacks[i].second+1] == 1 || root.game_board[root.blacks[i].first][root.blacks[i].second+1] == 2){
                    pair<int,int> pqr = make_pair(-1,-1);
                    vector<pair<int,int > > xyz;
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    xyz.push_back(pqr);
                    re = newBoardBlack(false,make_pair(root.blacks[i].first,root.blacks[i].second),make_pair(root.blacks[i].first,root.blacks[i].second+1),root,xyz,xyz,pqr);
                    re = miniMax(re,d,depth+1);
                    if(root.alpha < re.cost){
                        root.alpha = re.cost;
                        ret = re;
                    }
                    root.cost = root.alpha;
                }
            }
            if(root.alpha >= root.beta){
                break;
            }
            
            /*if(root.blacks[i].first+2 <= 7){
             if(root.game_board[root.blacks[i].first+2][root.blacks[i].second] == 0 && root.game_board[root.blacks[i].first+1][root.blacks[i].second] == 0){
             pair<int,int> pqr = make_pair(-1,-1);
             vector<pair<int,int > > xyz;
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             re = newBoardBlack(false,make_pair(root.blacks[i].first,root.blacks[i].second),make_pair(root.blacks[i].first+2,root.blacks[i].second),root,xyz,xyz,pqr);
             re = miniMax(re,d,depth+1);
             if(root.alpha < re.cost){
             root.alpha = re.cost;
             ret = re;
             }
             root.cost = root.alpha;
             }
             }
             if(root.alpha >= root.beta){
             break;
             }
             
             if(root.blacks[i].first+2 <= 7 && root.blacks[i].second-2 >=0){
             if(root.game_board[root.blacks[i].first+1][root.blacks[i].second-1] == 0 && root.game_board[root.blacks[i].first+2][root.blacks[i].second-2] == 0){
             pair<int,int> pqr = make_pair(-1,-1);
             vector<pair<int,int > > xyz;
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             re = newBoardBlack(false,make_pair(root.blacks[i].first,root.blacks[i].second),make_pair(root.blacks[i].first+2,root.blacks[i].second-2),root,xyz,xyz,pqr);
             re = miniMax(re,d,depth+1);
             if(root.alpha < re.cost){
             root.alpha = re.cost;
             ret = re;
             }
             root.cost = root.alpha;
             }
             }
             if(root.alpha >= root.beta){
             break;
             }
             
             if(root.blacks[i].first+2 <= 7 && root.blacks[i].second+2 <=7){
             if(root.game_board[root.blacks[i].first+1][root.blacks[i].second+1] == 0 && root.game_board[root.blacks[i].first+2][root.blacks[i].second+2] == 0){
             pair<int,int> pqr = make_pair(-1,-1);
             vector<pair<int,int > > xyz;
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             xyz.push_back(pqr);
             re = newBoardBlack(false,make_pair(root.blacks[i].first,root.blacks[i].second),make_pair(root.blacks[i].first+2,root.blacks[i].second+2),root,xyz,xyz,pqr);
             re = miniMax(re,d,depth+1);
             if(root.alpha < re.cost){
             root.alpha = re.cost;
             ret = re;
             }
             root.cost = root.alpha;
             }
             }
             if(root.alpha >= root.beta){
             break;
             }*/
        }
        
        
        
        
        return root;
        
        
        
    }
    return root;
}


void print_board(Board b)
{
    for (int i = 0;i<8;i++)
    {   for (int j = 0;j<8;j++)
        cout<<b.game_board[i][j];
        cout<<endl;
    }
    cout<<"white soldiers: "<<endl;
    for (int i = 0;i<b.whites.size();i++)
    {
        cout<<b.whites[i].first<<b.whites[i].second<< endl;
    }
    cout<<"black soldiers: "<<endl;
    for (int i = 0;i<b.blacks.size();i++)
    {
        cout<<b.blacks[i].first<<b.blacks[i].second<< endl;
    }
    cout<<"white canons:"<<endl;
    for (int i = 0;i<b.white_canons.size();i++)
    {
        for (int j = 0;j<3;j++)
        cout<<b.white_canons[i][j].first<<b.white_canons[i][j].second<< endl;
    }
    cout<<"black canons:"<<endl;
    for (int i = 0;i<b.black_canons.size();i++)
    {
        for (int j = 0;j<3;j++)
        cout<<b.black_canons[i][j].first<<b.black_canons[i][j].second<< endl;
    }
    
    cout<<(b.white_canons.size())<<" ";
    cout<<(b.black_canons.size())<<endl;
}

Board update(Board a, int xi,int yi,int xf,int yf,char mtype,char type)
{
    Board b;
    b = a;
    if (mtype == 'B')
    {
        if (type == 'B')
        {
            for(int i = 0;i<b.whites.size();i)
            {
                if (b.whites[i].first == xf && b.whites[i].second == yf)
                {
                    b.whites.erase(b.whites.begin()+i);
                    continue;
                }
                i++;
            }
            for (int i = 0;i<b.white_canons.size();i)
            {
                for (int j = 0;j<3;j++)
                if(b.white_canons[i][j].first == xf && b.white_canons[i][j].second == yf)
                {
                    b.white_canons.erase(b.white_canons.begin()+i);
                    continue;
                }
                i++;
            }
        }
        else
        {
            for(int i = 0;i<b.blacks.size();i)
            {
                if (b.blacks[i].first == xf && b.blacks[i].second == yf)
                {
                    b.blacks.erase(b.whites.begin()+i);
                    continue;
                }
                i++;
            }
            for (int i = 0;i<b.black_canons.size();i)
            {
                for (int j = 0;j<3;j++)
                if(b.black_canons[i][j].first == xf && b.black_canons[i][j].second == yf)
                {
                    b.black_canons.erase(b.black_canons.begin()+i);
                    continue;
                }
                i++;
            }
        }
        b.game_board[xf][yf] = 0;
    }
    else if (mtype == 'M')
    {
        if (type == 'B')
        {
            for(int i = 0;i<b.whites.size();i)
            {
                if (b.whites[i].first == xf && b.whites[i].second == yf)
                {
                    b.whites.erase(b.whites.begin()+i);
                    continue;
                }
                i++;
            }
            
            
            
            for(int i = 0;i<b.blacks.size();i++)
            {
                if (b.blacks[i].first == xi && b.blacks[i].second == yi)
                {
                    b.blacks[i].first = xf;
                    b.blacks[i].second = yf;
                    break;
                }
            }
            
            b.game_board[xi][yi] = 0;
            b.game_board[xf][yf] = -1;
            for (int i = 0;i<b.white_canons.size();i)
            {
                for (int j = 0;j<3;j++)
                if(b.white_canons[i][j].first == xf && b.white_canons[i][j].second == yf)
                {
                    b.white_canons.erase(b.white_canons.begin()+i);
                    continue;
                }
                i++;
            }
            
            for (int i = 0;i<b.black_canons.size();i)
            {
                for (int j = 0;j<3;j++)
                if(b.black_canons[i][j].first == xi && b.black_canons[i][j].second == yi)
                {
                    b.black_canons.erase(b.black_canons.begin()+i);
                    continue;
                }
                i++;
            }
        }
        else
        {
            for(int i = 0;i<b.whites.size();i++)
            {
                if (b.whites[i].first == xi && b.whites[i].second == yi)
                {
                    b.whites[i].first = xf;
                    b.whites[i].second = yf;
                    break;
                }
            }
            
            b.game_board[xi][yi] = 0;
            b.game_board[xf][yf] = 1;
            for(int i = 0;i<b.blacks.size();i)
            {
                if (b.blacks[i].first == xf && b.blacks[i].second == yf)
                {
                    b.blacks.erase(b.blacks.begin()+i);
                    continue;
                }
                i++;
            }
            
            for (int i = 0;i<b.black_canons.size();i)
            {
                for (int j = 0;j<3;j++)
                if(b.black_canons[i][j].first == xf && b.black_canons[i][j].second == yf)
                {
                    b.black_canons.erase(b.black_canons.begin()+i);
                    continue;
                }
                i++;
            }
            
            for (int i = 0;i<b.white_canons.size();i)
            {
                for (int j = 0;j<3;j++)
                if(b.white_canons[i][j].first == xi && b.white_canons[i][j].second == yi)
                {
                    b.white_canons.erase(b.white_canons.begin()+i);
                    continue;
                }
                i++;
            }
            
        }
        
        int k;
        if (type == 'B')
        k = -1;
        else
        k = 1;
        if (xf<7 && b.game_board[xf+1][yf] == k)
        {
            if (xf<6 && b.game_board[xf+2][yf] == k)
            {
                vector<pair<int,int> > a;
                a.push_back(make_pair(xf,yf));
                a.push_back(make_pair(xf+1,yf));
                a.push_back(make_pair(xf+2,yf));
                if (k == -1)
                b.black_canons.push_back(a);
                else
                b.white_canons.push_back(a);
            }
            if (xf>0 && b.game_board[xf-1][yf] == k)
            {
                vector<pair<int,int> > a;
                a.push_back(make_pair(xf-1,yf));
                a.push_back(make_pair(xf,yf));
                a.push_back(make_pair(xf+1,yf));
                if (k == -1)
                b.black_canons.push_back(a);
                else
                b.white_canons.push_back(a);
                
            }
        }
        if (yf<7 && b.game_board[xf][yf+1] == k)
        {
            if (yf<6 && b.game_board[xf][yf+2] == k)
            {
                vector<pair<int,int> > a;
                a.push_back(make_pair(xf,yf));
                a.push_back(make_pair(xf,yf+1));
                a.push_back(make_pair(xf,yf+2));
                if (k == -1)
                b.black_canons.push_back(a);
                else
                b.white_canons.push_back(a);
            }
            if (xf>0 && b.game_board[xf][yf-1] == k)
            {
                vector<pair<int,int> > a;
                a.push_back(make_pair(xf,yf-1));
                a.push_back(make_pair(xf,yf));
                a.push_back(make_pair(xf,yf+1));
                if (k == -1)
                b.black_canons.push_back(a);
                else
                b.white_canons.push_back(a);
            }
        }
        if (xf<7 && yf<7 && b.game_board[xf+1][yf+1] == k)
        {
            if (xf<6 && yf<6 && b.game_board[xf+2][yf+2] == k)
            {
                vector<pair<int,int> > a;
                a.push_back(make_pair(xf,yf));
                a.push_back(make_pair(xf+1,yf+1));
                a.push_back(make_pair(xf+2,yf+2));
                if (k == -1)
                b.black_canons.push_back(a);
                else
                b.white_canons.push_back(a);
            }
            if (xf>0 && yf>0 && b.game_board[xf-1][yf-1] == k)
            {
                vector<pair<int,int> > a;
                a.push_back(make_pair(xf-1,yf-1));
                a.push_back(make_pair(xf,yf));
                a.push_back(make_pair(xf+1,yf+1));
                if (k == -1)
                b.black_canons.push_back(a);
                else
                b.white_canons.push_back(a);
            }
        }
        if (yf>0 && xf<7 && b.game_board[xf+1][yf-1] == k)
        {
            if (xf<6 && yf>1 && b.game_board[xf+2][yf-2] == k)
            {
                vector<pair<int,int> > a;
                a.push_back(make_pair(xf,yf));
                a.push_back(make_pair(xf+1,yf-1));
                a.push_back(make_pair(xf+2,yf-2));
                if (k == -1)
                b.black_canons.push_back(a);
                else
                b.white_canons.push_back(a);
            }
            if (xf>0 && yf<7 && b.game_board[xf-1][yf+1] == k)
            {
                vector<pair<int,int> > a;
                a.push_back(make_pair(xf+1,yf-1));
                a.push_back(make_pair(xf,yf));
                a.push_back(make_pair(xf-1,yf+1));
                if (k == -1)
                b.black_canons.push_back(a);
                else
                b.white_canons.push_back(a);
            }
        }
        if (xf>0 && b.game_board[xf-1][yf] == k)
        {
            if (xf>1 && b.game_board[xf-2][yf] == k)
            {
                vector<pair<int,int> > a;
                a.push_back(make_pair(xf,yf));
                a.push_back(make_pair(xf-1,yf));
                a.push_back(make_pair(xf-2,yf));
                if (k == -1)
                b.black_canons.push_back(a);
                else
                b.white_canons.push_back(a);
            }
        }
        if (xf>0 && yf>0 && b.game_board[xf-1][yf-1] == k)
        {
            if (xf>1 && yf>1 && b.game_board[xf-2][yf-2] == k)
            {
                vector<pair<int,int> > a;
                a.push_back(make_pair(xf,yf));
                a.push_back(make_pair(xf-1,yf-1));
                a.push_back(make_pair(xf-2,yf-2));
                if (k == -1)
                b.black_canons.push_back(a);
                else
                b.white_canons.push_back(a);
            }
        }
        if (yf>0 && b.game_board[xf][yf-1] == k)
        {
            if (yf>1 && b.game_board[xf][yf-2] == k)
            {
                vector<pair<int,int> > a;
                a.push_back(make_pair(xf,yf));
                a.push_back(make_pair(xf,yf-1));
                a.push_back(make_pair(xf,yf-2));
                if (k == -1)
                b.black_canons.push_back(a);
                else
                b.white_canons.push_back(a);
                
            }
        }
        if (xf>0 && yf<7 && b.game_board[xf-1][yf+1] == k)
        {
            if (xf>1 && yf<6 && b.game_board[xf-2][yf+2] == k)
            {
                vector<pair<int,int> > a;
                a.push_back(make_pair(xf,yf));
                a.push_back(make_pair(xf-1,yf+1));
                a.push_back(make_pair(xf-2,yf+2));
                if (k == -1)
                b.black_canons.push_back(a);
                else
                b.white_canons.push_back(a);
            }
        }
    }
    return b;
}

string next_move(Board a,int type)
{
    Board b;
    string out;
    if (type == 0)
    {
        for (int i = 0;i<a.whites.size();i++)
        {
            int xi = a.whites[i].first;
            int yi = a.whites[i].second;
            if( a.whites[i].first<7)
            {
                out= "S "+to_string(xi)+" "+to_string(yi)+" M "+to_string(xi+1)+" "+to_string(yi+1);
                break;
            }
        }
    }
    else if (type == 1)
    {
        for (int i = 0;i<a.blacks.size();i++)
        {
            int xi = a.blacks[i].first;
            int yi = a.blacks[i].second;
            if( a.blacks[i].first<7)
            {
                out= "S "+to_string(xi)+" "+to_string(yi)+" M "+to_string(xi-1)+" "+to_string(yi+1);
                break;
            }
        }
    }
    return out;
}

Board swap(Board a)
{
    Board b = a;
    vector<pair<int,int> > pw;
    for(int i=0;i<b.whites.size();i++){
        pw.push_back(b.whites[i]);
    }
    
    b.whites = b.blacks;
    b.blacks = pw;
    vector<vector<pair<int ,int> > > qw;
    for(int i=0;i<b.white_canons.size();i++){
        qw.push_back(b.white_canons[i]);
    }
    
    b.white_canons = b.black_canons;
    b.black_canons = qw;
    
    for (int i = 0;i<b.whites.size();i++)
    b.whites[i] = make_pair((7-b.whites[i].first),(7-b.whites[i].second));
    for (int i = 0;i<b.blacks.size();i++)
    b.blacks[i] = make_pair((7-b.blacks[i].first),(7-b.blacks[i].second));
    for (int i = 0;i<b.black_canons.size();i++)
    {
        for (int j = 0;j<3;j++)
        b.black_canons[i][j] = make_pair(7-b.black_canons[i][j].first,7-b.black_canons[i][j].second);
    }
    for (int i = 0;i<b.white_canons.size();i++)
    {
        for (int j = 0;j<3;j++)
        b.white_canons[i][j] = make_pair(7-b.white_canons[i][j].first,7-b.white_canons[i][j].second);
    }
    for (int i = 0;i<8;i++)
    {
        for (int j = 0;j<8;j++)
        {
            if (i+j<7)
            {
                int temp = b.game_board[i][j];
                b.game_board[i][j] = -b.game_board[7-i][7-j];
                b.game_board[7-i][7-j] = -temp;
            }
        }
    }
    for (int i = 0;i<4;i++)
    {
        int temp = b.game_board[7-i][i];
        b.game_board[7-i][i] = -b.game_board[i][7-i];
        b.game_board[i][7-i] = -temp;
    }
    return b;
}

string swap1(string s)
{
    string out = "";
    char c = s.at(0);
    int xi = stoi(s.substr(2,1));
    int yi = stoi(s.substr(4,1));
    
    char mtype = s.at(6);
    int xf = stoi(s.substr(8,1));
    
    int yf = stoi(s.substr(10,1));
    
    out = out+ c+" "+to_string(7-xi)+" "+to_string(7-yi)+" "+mtype+" "+to_string(7-xf)+" "+to_string(7-yf);
    return out;
}

int main()
{
    Board a;
    int type;
    cin>>type;
    if(type == 2) {
        type = 0;
    }
    int length;
    cin>>length;
    int breadth;
    cin>>breadth;
    int time;
    cin>>time;
    int type1 = 1;
    int nmoves = 0;
    int rtime;
    while (true)
    {
        if (type1 == 0)
        {
            char c;
            int xi;
            int yi;
            char mtype;
            int xf;
            int yf;
            if (type == 0)
            {
                a.alpha = INT_MIN;
                a.beta = INT_MAX;
                Board out = miniMax(a,4,0);
                string s = out.theMove;
                c = s.at(0);
                xi = stoi(s.substr(2,1));
                yi = stoi(s.substr(4,1));
                mtype = s.at(6);
                xf = stoi(s.substr(8,1));
                yf = stoi(s.substr(10,1));
                cout<<"S "<<yi<<" "<<xi<<" "<< mtype << " "<<yf<<" "<<xf<<endl;
                
            }
            else
            {
                cin>>c;
                cin>>yi;
                cin>>xi;
                cin>>mtype;
                cin>>yf;
                cin>>xf;
            }
            char player = 'W';
            bool isCanon = false;
            if(mtype == 'B'){
                isCanon = true;
            }
            vector<pair<int,int > > sd;
            sd.push_back(make_pair(-1,-1));
            sd.push_back(make_pair(-1,-1));
            sd.push_back(make_pair(-1,-1));
            a = newBoardWhite(isCanon, make_pair(xi,yi),make_pair(xf,yf), a,sd , sd, make_pair(xf,yf));
        }
        else
        {
            char c;
            int xi;
            int yi;
            char mtype;
            int xf;
            int yf;
            if (type == 1)
            {
                a.alpha = INT_MIN;
                a.beta = INT_MAX;
                Board out = miniMax(swap(a),4,0);
                string s = swap1(out.theMove);
                c = s.at(0);
                xi = stoi(s.substr(2,1));
                yi = stoi(s.substr(4,1));
                mtype = s.at(6);
                xf = stoi(s.substr(8,1));
                yf = stoi(s.substr(10,1));
                cout<<"S "<<yi<<" "<<xi<<" "<<mtype<<" "<<yf<<" "<<xf<<endl;
            }
            else
            {
                cin>>c;
                cin>>yi;
                cin>>xi;
                cin>>mtype;
                cin>>yf;
                cin>>xf;
            }
            char player = 'B';
            
            bool isCanon = false;
            if(mtype == 'B'){
                isCanon = true;
            }
            vector<pair<int,int > > sd;
            sd.push_back(make_pair(-1,-1));
            sd.push_back(make_pair(-1,-1));
            sd.push_back(make_pair(-1,-1));
            a = newBoardBlack(isCanon, make_pair(xi,yi),make_pair(xf,yf), a,sd , sd, make_pair(xf,yf));
            
        }
        type1 = 1-type1;
    }
}
