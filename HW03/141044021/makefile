all: hello

hello: main.o CPUProgram.o CPU.o instruction.o
	g++ main.o CPUProgram.o CPU.o instruction.o -o hello

main.o: main.cpp
	g++ -c main.cpp

CPUProgram.o: CPUProgram.cpp
	g++ -c CPUProgram.cpp

CPU.o: CPU.cpp
	g++ -c CPU.cpp

instruction.o: instruction.cpp
	g++ -c instruction.cpp

run0:
	./hello insturction.txt 0

run1:
	./hello insturction.txt 1

run2:
	./hello deneme.txt 0

run3:
	./hello deneme.txt 1


clean:
	rm *.o hello
