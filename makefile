 freq: main.o frequencyParser.o
	gcc -std=c++17 -Wall main.o frequencyParser.o -o freq

 main.o: main.cpp
	gcc -c main.cpp

 frequencyParser.o: frequencyParser.cpp frequencyParser.h
	gcc -c frequencyParser.cpp

 clean:
	rm *.o freq