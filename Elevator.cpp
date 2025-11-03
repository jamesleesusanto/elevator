#include "Elevator.hpp"
#include <iostream>

Elevator::Elevator(int startFloor)
    : currentFloor(startFloor), direction(IDLE) {}

bool Elevator::isIdle() const {
    return upStops.empty() && downStops.empty() && direction == IDLE;
}

void Elevator::addRequest(const Request& req) {
    if (direction == IDLE) {
        direction = (req.to > req.from) ? UP : DOWN;
    }

    if (direction == UP){
        if (req.from >= currentFloor && req.to >= req.from) {
            upStops.push(req.from);
            upStops.push(req.to);
        }
        else{
            downStops.push(req.from);
            downStops.push(req.to);
        }
    }

    else if (direction == DOWN){
        if (req.from <= currentFloor && req.to <= req.from) {
            downStops.push(req.from);
            downStops.push(req.to);
        }
        else{
            upStops.push(req.from);
            upStops.push(req.to);
        }
    }
}


void Elevator::move() {
    if (direction == IDLE){
        return;
    }

    handleStopsAtCurrentFloor();

    if (direction == UP) {
        currentFloor++;
        if (upStops.empty() || currentFloor > upStops.top()) {
            std::cout << "Stop at floor " << currentFloor << " (UP)\n";
            upStops.pop();
        }
    }
    else if (direction == DOWN) {
        currentFloor--;
        if (downStops.empty() || currentFloor < downStops.top()) {
            std::cout << "Stop at floor " << currentFloor << " (DOWN)\n";
            downStops.pop();
        }
    }

    handleStopsAtCurrentFloor();

    if (direction == UP && upStops.empty() && !downStops.empty()) 
        direction = DOWN;
    else if (direction == DOWN && downStops.empty() && !upStops.empty()) 
        direction = UP;
    else if (upStops.empty() && downStops.empty()) 
        direction = IDLE;
}


void Elevator::handleStopsAtCurrentFloor() {
    if (direction == UP && !upStops.empty() && currentFloor == upStops.top()) {
        std::cout << "Stop at floor " << currentFloor << " (UP)\n";
        upStops.pop();
    }
    if (direction == DOWN && !downStops.empty() && currentFloor == downStops.top()) {
        std::cout << "Stop at floor " << currentFloor << " (DOWN)\n";
        downStops.pop();
    }
}


void Elevator::printStatus() const {
    std::string dir = (direction == UP ? "UP" : direction == DOWN ? "DOWN" : "IDLE");
    std::cout << "Elevator: Floor " << currentFloor
              << " | Direction: " << dir
              << " | UpStops: " << upStops.size()
              << " | DownStops: " << downStops.size()
              << std::endl;
}