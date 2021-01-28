 freq: main.o frequencyParser.o
	g++ -std=c++17 -Wall main.o frequencyParser.o -o freq

 main.o: main.cpp
	g++ -c main.cpp

 frequencyParser.o: frequencyParser.cpp frequencyParser.h
	g++ -c frequencyParser.cpp

 clean:
	rm *.o freq