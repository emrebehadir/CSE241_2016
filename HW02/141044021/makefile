all: hello

hello: main.o 
	g++ main.o -o hello

main.o: main.cpp
	g++ -c main.cpp

run0:
	./hello sort.txt 0	
run1:
	./hello sort.txt 1
run2:
	./hello sort.txt 2
run3:
	./hello deneme.txt 0
run4:
	./hello deneme.txt 1
run5:
	./hello deneme.txt 2
	
clean:
	rm *.o hello
