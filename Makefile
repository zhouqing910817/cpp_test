CC = g++
SRC = $(wildcard *.cpp)
OBJ = $(addprefix out/,$(SRC:%.cpp=%.o))
EXECUTABLES = $(OBJ:%.o=%)

all: $(EXECUTABLES)

out/%.o: %.cpp
	@if [ ! -d out ]; then mkdir out; fi;
	$(CC) -c $< -o $@ --std=c++14

$(EXECUTABLES): %: %.o
	@if [ ! -d out ]; then mkdir out; fi;
	$(CC) $< -o $@ -lboost_thread -lrt -pthread -lbfd --std=c++14

run:
	@if [ -z "$(target)" ]; then echo "Please specify the target name."; exit 1; fi;
	@for file in $(EXECUTABLES); do \
		if echo $$file | grep -q "$(target)"; then \
			./$$file; \
		fi; \
	done

clean:
	rm -rf out

.PHONY: all clean
