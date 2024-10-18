CC = g++
CFLAGS = -std=c++17 -Wall
SRC = huffmanCompressor.cpp main.cpp
OUT = huffman

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
