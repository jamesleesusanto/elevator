CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -g
TARGET := elevator
SRC := main.cpp Elevator.cpp

build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)
