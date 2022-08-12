SRC=./src
TARGET=./target
INCLUDE=./include
GCC = g++

default:
	$(GCC) -I $(INCLUDE) -o $(TARGET)/bin/snarf.exe $(SRC)/*.*