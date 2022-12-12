CC=mpic++
CFLAGS=-c -g
NODEPATH=./src/Node
STANDARDSOLVERPATH=./src/Solver/StandardSolver
PROPORTIONALSPLITTERPATH=./src/Splitter/ProportionalSplitter
RANDOMSPLITTERPATH=./src/Splitter/RandomSplitter
ABSTRACTSOLVERPATH=./src/Solver/AbstractSolver
ABSTRACTSPLITTERPATH=./src/Splitter/AbstractSplitter
BUILD=./build

all: main

.PHONY: clean createdirs

main: createdirs $(BUILD)/main.o $(BUILD)/standard_solver.o $(BUILD)/proportional_splitter.o $(BUILD)/node.o
	$(CC) $(BUILD)/main.o $(BUILD)/standard_solver.o $(BUILD)/proportional_splitter.o $(BUILD)/node.o -o ./main

$(BUILD)/main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(BUILD)/main.o

$(BUILD)/standard_solver.o: $(STANDARDSOLVERPATH)/standard_solver.cpp
	$(CC) $(CFLAGS) $(STANDARDSOLVERPATH)/standard_solver.cpp -o $(BUILD)/standard_solver.o

$(BUILD)/proportional_splitter.o: $(PROPORTIONALSPLITTERPATH)/proportional_splitter.cpp
	$(CC) $(CFLAGS) $(PROPORTIONALSPLITTERPATH)/proportional_splitter.cpp -o $(BUILD)/proportional_splitter.o

$(BUILD)/random_splitter.o: $(RANDOMSPLITTERPATH)/random_splitter.cpp
	$(CC) $(CFLAGS) $(RANDOMSPLITTERPATH)/random_splitter.cpp -o $(BUILD)/random_splitter.o

$(BUILD)/node.o: $(NODEPATH)/node.cpp
	$(CC) $(CFLAGS) $(NODEPATH)/node.cpp -o $(BUILD)/node.o

createdirs:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD) main test/test_functions test/test_operations test/test_root