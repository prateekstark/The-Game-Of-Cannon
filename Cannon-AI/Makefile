FLAG = -std=c++11

all: SmartPlayerMinMax SmartPlayerMCTS

SmartPlayerMinMax: MainFileMinMax CannonGame utils
		g++ $(FLAG) outputs/MainFileMinMax outputs/CannonGame outputs/utils -o SmartPlayerMinMax


SmartPlayerMCTS: MainFileMCTS MCTS CannonGame utils
		g++ $(FLAG) outputs/MainFileMCTS outputs/MCTS outputs/CannonGame outputs/utils -o SmartPlayerMCTS

CannonGame: src/CannonGame.cpp include/CannonGame.h
		g++ -c $(FLAG) src/CannonGame.cpp -o outputs/CannonGame

MCTS: src/MCTS.cpp include/MCTS.h
		g++ -c $(FLAG) src/MCTS.cpp -o outputs/MCTS

MainFileMCTS: src/MainFileMCTS.cpp include/CannonGame.h
		g++ -c $(FLAG) src/MainFileMCTS.cpp -o outputs/MainFileMCTS

MainFileMinMax: src/MainFileMinMax.cpp include/CannonGame.h
		g++ -c $(FLAG) src/MainFileMinMax.cpp -o outputs/MainFileMinMax

utils: src/utils.cpp include/utils.h
		g++ -c $(FLAG) src/utils.cpp -o outputs/utils

clean:
		rm -rf outputs/* SmartPlayerMinMax SmartPlayerMCTS