CXX=g++
FLAGS=-std=c++11 -pedantic
WARNINGS=-Wall -Werror -Wextra
OPTIMIZE=-O3 -march='native'
OBJ=-c
COMPILE=$(CXX) $(FLAGS) $(WARNINGS) $(OPTIMIZE)
COMPILE_OBJ=$(COMPILE) $(OBJ)

all:Standart.o InvertedIndex.o DynamicBitSet.o SortStation.o Parcer.o
	$(COMPILE) Parcer.o Standart.o InvertedIndex.o DynamicBitSet.o SortStation.o -o Standart

Standart.o: Standart.cpp InvertedIndex.h SortStation.h DynamicBitSet.h Parcer.h
	$(COMPILE_OBJ) Standart.cpp
Parcer.o: Parcer.cpp Parcer.h InvertedIndex.h
	$(COMPILE_OBJ) Parcer.cpp
InvertedIndex.o: InvertedIndex.cpp InvertedIndex.h DynamicBitSet.h
	$(COMPILE_OBJ) InvertedIndex.cpp
DynamicBitSet.o: DynamicBitSet.cpp DynamicBitSet.h
	$(COMPILE_OBJ) DynamicBitSet.cpp
SortStation.o: SortStation.cpp SortStation.h
	$(COMPILE_OBJ) SortStation.cpp


clear:
	rm *.o Standart