TARGET=hnefatafl
GCFLAGS=-g -std=c++20
#SRC=$(shell ls *.cpp *.hpp)
SRC=$(shell find . -iname "*.cpp" && find . -iname "*.hpp")
GCH=$(shell ls -R *.gch)

build:
	g++ $(GCFLAGS) $(SRC)

clean:
	rm a.out $(GCH)
