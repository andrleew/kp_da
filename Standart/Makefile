CXX=g++
FLAGS=-std=c++11 -pedantic
WARNINGS=-Wall -Werror -Wextra
OPTIMIZE=-O3 -march='native'
OBJ=-c
COMPILE=$(CXX) $(FLAGS) $(WARNINGS) $(OPTIMIZE)
COMPILE_OBJ=$(COMPILE) $(OBJ)

all:Standart.o InvertedIndex.o DynamicBitSet.o SortStation.o
	$(COMPILE) Standart.o InvertedIndex.o DynamicBitSet.o SortStation.o -o Standart

Standart.o: Standart.cpp InvertedIndex.h SortStation.h DynamicBitSet.h
	$(COMPILE_OBJ) Standart.cpp -o Standart.o
InvertedIndex.o: InvertedIndex.cpp InvertedIndex.h DynamicBitSet.h
	$(COMPILE_OBJ) InvertedIndex.cpp -o InvertedIndex.o
DynamicBitSet.o: DynamicBitSet.cpp DynamicBitSet.h
	$(COMPILE_OBJ) DynamicBitSet.cpp -o DynamicBitSet.o
SortStation.o: SortStation.cpp SortStation.h
	$(COMPILE_OBJ) SortStation.cpp -o SortStation.o

clear:
	rm *.o Standart