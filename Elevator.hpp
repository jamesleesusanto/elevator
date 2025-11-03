#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP

#include <queue>
#include <vector>
#include <functional>
#include <string>

enum Direction { UP, DOWN, IDLE };

struct Request {
    int from;
    int to;
    Request(int f, int t) : from(f), to(t) {}
};

class Elevator {
private:
    int currentFloor;
    Direction direction;

    std::priority_queue<int, std::vector<int>, std::greater<int>> upStops;     
    std::priority_queue<int, std::vector<int>, std::less<int>> downStops;
    
    void handleStopsAtCurrentFloor();

public:
    Elevator(int startFloor = 0);

    void addRequest(const Request& req);
    void move();
    void printStatus() const;
    bool isIdle() const;
};

#endif
