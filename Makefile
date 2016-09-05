all:
	g++ -g -std=c++11 Rhymebot-FileParser.cpp RhymeBot.cpp RhymeBot-Sound.cpp  -o RhymeBot
clean:
	rm -f a.out
