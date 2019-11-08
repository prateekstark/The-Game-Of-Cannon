FLAG = -std=c++11

all: SmartPlayerMinMax

SmartPlayerMinMax: MainFileMinMax CannonGame utils
		g++ $(FLAG) outputs/MainFileMinMax outputs/CannonGame outputs/utils -o SmartPlayerMinMax

MainFileMinMax: src/MainFileMinMax.cpp include/CannonGame.h
		g++ -c $(FLAG) src/MainFileMinMax.cpp -o outputs/MainFileMinMax

CannonGame: src/CannonGame.cpp include/CannonGame.h
		g++ -c $(FLAG) src/CannonGame.cpp -o outputs/CannonGame

utils: src/utils.cpp include/utils.h
		g++ -c $(FLAG) src/utils.cpp -o outputs/utils

clean:
		rm -rf outputs/* SmartPlayerMinMax
