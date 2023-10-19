CC = g++
SRC = $(wildcard *.cpp)
BIN = $(SRC:%.cpp=%)
 
all : ${BIN}

${BIN}:%:%.cpp
	${CC} $^ -O2 -o $@ -lboost_thread -lrt -pthread -lbfd --std=c++14
 
clean:
	rm -rf ${BIN}
 
.PHONY: all clean
