 output: main.o garage.o
	g++ -std=c++17 -Wall main.o frequencyParser.o -o output

 main.o: main.cpp
	g++ -c main.cpp

 garage.o: frequencyParser.cpp frequencyParser.h
	g++ -c frequencyParser.cpp

 clean:
	rm *.o output