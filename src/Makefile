.PHONY: tp2

CC := g++
CPP_FILES := $(wildcard *.cpp)
H_FILES := $(wildcard *.h)
LD_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system
#Make difference between x86 and arm
ifeq ($(shell uname -m), armv7l)
CC := $(CC)-6 -d
endif
CC_FLAGS := --std=c++14 -pthread -O3
OUTNAME = sudokusolver

all: clean tp2

clean:
	rm -f *.gch $(OUTNAME)

tp2:
	$(CC) $(CPP_FILES) -o $(OUTNAME) $(LD_FLAGS) $(CC_FLAGS)
