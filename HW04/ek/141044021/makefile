all: testMain Main

testMain: _mainTester.o CPUProgram.o CPU.o instruction.o Computer.o Memory.o
	g++ _mainTester.o CPUProgram.o CPU.o instruction.o Computer.o Memory.o -o testMain

Main: main.o
	g++ main.o CPUProgram.o CPU.o instruction.o Computer.o Memory.o -o Main

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

_mainTester.o: _mainTester.cpp
	g++ -std=c++11 -c _mainTester.cpp

CPUProgram.o: CPUProgram.cpp
	g++ -std=c++11 -c CPUProgram.cpp

CPU.o: CPU.cpp
	g++ -c CPU.cpp

instruction.o: instruction.cpp
	g++ -std=c++11 -c instruction.cpp

Computer.o: Computer.cpp
	g++ -std=c++11 -c Computer.cpp

Memory.o: Memory.cpp
	g++ -std=c++11 -c Memory.cpp

run0:
	./testMain sort.txt 0

run1:
	./testMain sort.txt 1

run2:
	./testMain sort.txt 2

run3:
	./Main sort.txt 1

run4:
	./Main sort.txt 2


clean:
	rm *.o Main testMain
