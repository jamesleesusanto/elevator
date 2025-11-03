#include "Elevator.hpp"
#include <iostream>
#include <vector>
#include <tuple>

struct TimedRequest {
    int time;
    int from;
    int to;
};

int main() {
    int startFloor, numRequests;
    std::cin >> startFloor >> numRequests;

    Elevator e(startFloor);
    std::vector<TimedRequest> requests;

    //read reqs
    for (int i = 0; i < numRequests; ++i) {
        int t, f, to;
        std::cin >> t >> f >> to;
        requests.push_back({t, f, to});
    }

    int time = 0;
    int reqIndex = 0;
    int maxTime = 1000; //req limit

    std::cout << "Starting elevator simulation from floor " << startFloor << "\n";

    //main loop
    while (!e.isIdle() || reqIndex < numRequests) {
        
        while (reqIndex < numRequests && requests[reqIndex].time == time) {
            const auto &r = requests[reqIndex];
            std::cout << "[t=" << time << "] New request: from " 
                      << r.from << " to " << r.to << "\n";
            e.addRequest({r.from, r.to});
            reqIndex++;
        }

        std::cout << "\n--- Step " << time << " ---\n";
        e.move();
        e.printStatus();

        time++;
        if (time > maxTime) break; // prevent infinite loop
    }

    std::cout << "\nSimulation complete at time " << time << ".\n";
    return 0;
}
