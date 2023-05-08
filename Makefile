CC = g++
SRC = $(wildcard *.cpp)
BIN = $(SRC:%.cpp=%)
 
all : ${BIN}

${BIN}:%:%.cpp
	${CC} $^ -O2 -o $@ -lboost_thread -pthread -lbfd
 
clean:
	rm -rf ${BIN}
 
.PHONY: all clean
