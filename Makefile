CC = g++
SRC = $(wildcard *.cpp)
BIN = $(SRC:%.cpp=%)
 
all : ${BIN}

${BIN}:%:%.cpp
	${CC} $^ -O3 -o $@ -lboost_thread -pthread
 
clean:
	rm -rf ${BIN}
 
.PHONY: all clean
