.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYMg

qwirkle: Util.cpp Game.cpp Node.cpp LinkedList.cpp Player.cpp qwirkle.cpp Menu.cpp Tile.cpp TileBag.cpp
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^