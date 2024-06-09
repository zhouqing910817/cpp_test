# usage make run target=log
CC = g++
SRC = $(wildcard *.cpp)
OBJ = $(addprefix out/,$(SRC:%.cpp=%.o))
EXECUTABLES = $(OBJ:%.o=%)

all: $(EXECUTABLES)

out/%.o: %.cpp log.h
	@if [ ! -d out ]; then mkdir out; fi;
	$(CC) -c $< -o $@ --std=c++14 -I./

$(EXECUTABLES): %: %.o
	@if [ ! -d out ]; then mkdir out; fi;
	$(CC) $< -o $@ -lboost_thread  -pthread  --std=c++14

#out/$(target): out/$(target).o
#	$(CC) -c $(target).cpp -o out/$(target).o --std=c++14 -I./
#	$(CC) out/$(target).o -o out/$(target) -lboost_thread -lrt -pthread -lbfd --std=c++14

run: out/$(target)
	@if [ ! -d out ]; then mkdir out; fi;
	@for file in $(SRC); do \
        if echo $$file | grep -q "$(target)"; then \
            bin_name=`basename -s .cpp $$file`; \
            break;\
        fi \
    done;
	@if [ -z "$(target)" ]; then echo "Please specify the target name."; exit 1; fi;
	@for file in $(EXECUTABLES); do \
		if echo $$file | grep -q "$(target)"; then \
            echo "\033[32mrunning '$$file':\033[0m"; \
		    ./$$file; \
            found=1;  \
            break;   \
		fi; \
	done;\
    if [[ found -ne 1 ]];then\
        echo -e "\033[31mrun: can't find bin contains '$(target)'\033[0m";\
    fi;

clean:
	rm -rf out

.PHONY: all clean
