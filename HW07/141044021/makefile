all:  _mainTester

_mainTester: _mainTester.o Bigram.o BigramMap.o BigramDyn.o
	g++ _mainTester.o Bigram.o BigramMap.o BigramDyn.o -o exe

_mainTester.o: _mainTester.cpp
	g++ -std=c++11 -c _mainTester.cpp

Bigram.o: Bigram.cpp
	g++ -std=c++11 -c Bigram.cpp

BigramMap.o: BigramMap.cpp
	g++ -std=c++11 -c BigramMap.cpp

BigramDyn.o: BigramDyn.cpp
	g++ -std=c++11 -c BigramDyn.cpp

run0:
	./exe t1.txt 1 1 && ./exe t2.txt 2 1 && ./exe t3.txt 3 1

run1:
	./exe t1.txt 1 2 && ./exe t2.txt 2 2 && ./exe t3.txt 3 2

run2:
	./exe t4.txt 1 1 

run3:
	./exe t5.txt 2 1

clean:
	rm *.o exe
