CXX=g++
#FLAGS=-pthread -pg
FLAGS=-std=c++11 -pedantic -pthread
WARNINGS=-Wall -Werror -Wextra
OPTIMIZE=-O3 -march='native'
OBJ=-c
COMPILE=$(CXX) $(FLAGS) $(WARNINGS) $(OPTIMIZE)
COMPILE_OBJ=$(COMPILE) $(OBJ)

all:Standart.o BaseInvertedIndex.o DynamicBitSet.o SortStation.o Parcer.o InvertedIndex.o Worker.o
	$(COMPILE) Parcer.o Standart.o BaseInvertedIndex.o DynamicBitSet.o SortStation.o InvertedIndex.o Worker.o -o Standart

Standart.o: Standart.cpp BaseInvertedIndex.h SortStation.h DynamicBitSet.h Parcer.h
	$(COMPILE_OBJ) Standart.cpp
Parcer.o: Parcer.cpp Parcer.h InvertedIndex.h
	$(COMPILE_OBJ) Parcer.cpp
InvertedIndex.o: InvertedIndex.h InvertedIndex.cpp BaseInvertedIndex.h SaveQueue.h DynamicBitSet.h Worker.h SaveCounter.h
	$(COMPILE_OBJ) InvertedIndex.cpp
BaseInvertedIndex.o: BaseInvertedIndex.cpp BaseInvertedIndex.h DynamicBitSet.h
	$(COMPILE_OBJ) BaseInvertedIndex.cpp
DynamicBitSet.o: DynamicBitSet.cpp DynamicBitSet.h
	$(COMPILE_OBJ) DynamicBitSet.cpp
SortStation.o: SortStation.cpp SortStation.h
	$(COMPILE_OBJ) SortStation.cpp
Worker.o: Worker.h Worker.cpp
	$(COMPILE_OBJ) Worker.cpp

clean:
	rm *.o Standart