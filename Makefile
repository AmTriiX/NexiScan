CC = g++
CFLAGS = -std=c++11 -Wall

TARGET = nexis
SRC = nexis.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
