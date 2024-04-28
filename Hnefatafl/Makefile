TARGET=hnefatafl
GCFLAGS=-g -std=c++20
#SRC=$(shell ls *.cpp *.hpp)
SRC=$(shell find . -iname "*.cpp" && find . -iname "*.hpp")
GCH=$(shell find . -iname "*.gch")

all: build

build: obj 
	g++ *.o -o $(TARGET)
	make clean
obj:
	g++ -c $(GCFLAGS) $(SRC)
clean: 
	rm *.o $(GCH)
purge:
	rm $(TARGET)
run:
	./$(TARGET)
install:
	sudo cp $(TARGET) /usr/bin/$(TARGET)
uninstall:
	sudo rm /usr/bin/$(TARGET)
