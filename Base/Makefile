CXX=g++
OPTIMIZE=-O3 -march='native'
WARNINGS=-Wall -Werror -Wextra -pedantic -std=c++11
FLAGS=$(CXX) $(WARNINGS) $(OPTIMIZE)
DEBUG=$(CXX) $(WARNINGS) -g
PROFILE=$(FLAGS) -pg
OBJ_FILE=-c

all: Base.o InvertedIndex.o DynamicBitSet.o Makefile
	$(FLAGS) Base.o InvertedIndex.o DynamicBitSet.o -o Base

Base.o:Base-lvl.cpp InvertedIndex.h Makefile DynamicBitSet.h
	$(FLAGS) $(OBJ_FILE) Base-lvl.cpp -o Base.o
InvertedIndex.o: InvertedIndex.cpp InvertedIndex.h Makefile DynamicBitSet.h
	$(FLAGS) $(OBJ_FILE) InvertedIndex.cpp
DynamicBitSet.o: DynamicBitSet.cpp DynamicBitSet.h
	$(FLAGS) $(OBJ_FILE) DynamicBitSet.cpp



debug: BaseDebug.o InvertedIndexDebug.o Makefile
	$(DEBUG) BaseDebug.o InvertedIndexDebug.o -o BaseDebug

BaseDebug.o: Base-lvl.cpp InvertedIndex.h Makefile
	$(DEBUG) $(OBJ_FILE) Base-lvl.cpp -o BaseDebug.o

InvertedIndexDebug.o: InvertedIndex.cpp InvertedIndex.h Makefile
	$(DEBUG) $(OBJ_FILE) InvertedIndex.cpp -o InvertedIndexDebug.o


profile: BaseProfile.o InvertedIndexProfile.o Makefile
	$(PROFILE) BaseProfile.o InvertedIndexProfile.o -o BaseProfile

BaseProfile.o: Base-lvl.cpp InvertedIndex.h Makefile
	$(PROFILE) $(OBJ_FILE) Base-lvl.cpp -o BaseProfile.o

InvertedIndexProfile.o: InvertedIndex.cpp InvertedIndex.h Makefile
	$(PROFILE) $(OBJ_FILE) InvertedIndex.cpp -o InvertedIndexProfile.o

clear:
	rm Base BaseDebug BaseProfile *.o