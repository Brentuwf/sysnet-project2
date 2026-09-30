CXXFLAGS = -std=c++11 -g -Wall -Wextra -Wpedantic
LDFLAGS = -pthread
CC = g++

OBJS = mt-collatz.o CommandLineParser.o FrequencyHistogram.o CollatzCalculator.o ThreadManager.o 
SRC = mt-collatz.cpp CommandLineParser.cpp FrequencyHistogram.cpp CollatzCalculator.cpp ThreadManager.cpp
HDR = CommandLineParser.hpp FrequencyHistogram.hpp CollatzCalculator.hpp ThreadManager.hpp
BINARY = mt-collatz

${BINARY}: ${OBJS} 
	${CC} ${LDFLAGS} -o ${BINARY} ${OBJS}

${OBJS}: ${SRC} ${HDR} 
	${CC} -c ${CXXFLAGS} ${SRC}

memory-test: ${BINARY}
	valgrind -s --leak-check=full --show-leak-kinds=all ./${BINARY} -Debug

clean:
	rm -f ${BINARY} *.o
