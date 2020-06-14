CC = g++ -g -std=c++11
exe_file = qbert
TIMESTAMP := $(shell date '+%y%m%d_%H%M%S')

$(exe_file): application.o board.o
	$(CC) application.o board.o -o $(exe_file)
application.o: application.cpp
	$(CC) -c application.cpp
board.o: board.cpp board.h 
	$(CC) -c board.cpp
run: $(exe_file)
	./$(exe_file)
valgrind: $(exe_file)
	valgrind ./$(exe_file)
clean:
	rm -f out *.o $(exe_file)