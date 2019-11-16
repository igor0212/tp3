CC=g++
C=gcc
#CFLAGS=-std=c++11 -Wall
CFLAGS=

BUILD_DIR = ./build
SRC_DIR = ./src
INCLUDE_DIR = ./include
 
all: main 

####################################################
#                                                  #
#                       APP                        #
#                                                  #
####################################################

# Graph
Graph.o: ${INCLUDE_DIR}/Graph.hpp ${SRC_DIR}/models/Graph.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/models/Graph.cpp -o ${BUILD_DIR}/Graph.o

# GraphUtilities
GraphUtilities.o: ${INCLUDE_DIR}/GraphUtilities.hpp ${SRC_DIR}/utility/GraphUtilities.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/utility/GraphUtilities.cpp -o ${BUILD_DIR}/GraphUtilities.o

# tp3  
tp3.o: ${INCLUDE_DIR}/tp3.hpp ${SRC_DIR}/tp3.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/tp3.cpp -o ${BUILD_DIR}/tp3.o

# main
main.o: ${INCLUDE_DIR}/tp3.hpp main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c main.cpp -o ${BUILD_DIR}/main.o

# app
main: Graph.o GraphUtilities.o tp3.o main.o 
	${CC} ${CFLAGS} -o tp3 ${BUILD_DIR}/*.o

# Rule for cleaning files generated during compilation. 
# Call 'make clean' to use it 
clean: 
	rm -rf ${BUILD_DIR}/*.o    

clean_windows:
	del /S "%dir%\build\*.o"    

run:
	./tp3 221.txt

run_windows:
	./tp3.exe 221.txt