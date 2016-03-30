C=g++
CFG=main
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
LIB = -lpthread -levent

$(CFG):$(OBJ)
	$(C) -g -Wall $(OBJ) -o $(CFG) $(LIB)
.cpp.o:
	echo $(@D) $(<F) $(@F)
	$(C) -g  -c $(<F) -o $(@F)
clear:
	rm -rf  $(OBJ)
.PHONY:clean
clean:
	rm -rf  $(OBJ) $(CFG)
	

