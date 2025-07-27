// Authors: Jeremiah David & Jaden Ngyuen
// Date: 7/24/2025



#include <iostream>
#include <set>
#include <thread>
#include <chrono>
#include <cmath>

using namespace std;

// Elevator class handles the elevator's movement and state
class Elevator {
private:
    int currentFloor;
    int targetFloor;
    bool isIdle;
    bool waitingForDestination;

public:
    // Initialize elevator at floor 1 and set it to idle
    Elevator() {
        currentFloor = 1;
        targetFloor = 1;
        isIdle = true;
        waitingForDestination = false;
    }

    // Assign a floor for pickup
    void assignRequest(int floor) {
        targetFloor = floor;
        isIdle = false;
        waitingForDestination = false;
    }

    // Assign a destination floor once someone is inside
    void assignDestination(int floor) {
        targetFloor = floor;
        isIdle = false;
        waitingForDestination = false;
    }

    // Move elevator one step closer to the target
    bool step() {
        if (isIdle || waitingForDestination) return false;

        if (currentFloor < targetFloor) {
            currentFloor++;
            cout << "Elevator moving up to floor " << currentFloor << endl;
        } else if (currentFloor > targetFloor) {
            currentFloor--;
            cout << "Elevator moving down to floor " << currentFloor << endl;
        }

        if (currentFloor == targetFloor) {
            cout << "Elevator arrived at floor " << currentFloor << endl;
            cout << "Doors opening..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Doors closing..." << endl;
            waitingForDestination = true;
        }

        return true;
    }

    int getCurrentFloor() const { return currentFloor; }
    bool idle() const { return isIdle && !waitingForDestination; }
    bool needsDestination() const { return waitingForDestination; }
    void markIdle() { isIdle = true; waitingForDestination = false; }
};

// Return the closest floor request to the elevator's current location
int findClosestRequest(int currentFloor, const set<int>& requests) {
    int closest = -1;
    int minDistance = INT_MAX;
    for (int floor : requests) {
        int dist = abs(floor - currentFloor);
        if (dist < minDistance) {
            closest = floor;
            minDistance = dist;
        }
    }
    return closest;
}

int main() {
    int floors;
    cout << "Enter number of floors (e.g., 8): ";
    cin >> floors;

    Elevator elevator;
    set<int> requestSet;

    cout << "Elevator Simulation Started" << endl;
    cout << "Type a floor number to request the elevator." << endl;
    cout << "Type 0 to skip (no request)." << endl;
    cout << "Type -1 to quit." << endl;

    while (true) {
        cout << endl;
        cout << "Elevator is on floor " << elevator.getCurrentFloor();
        if (elevator.idle()) cout << " (Idle)";
        else if (elevator.needsDestination()) cout << " (Rider inside)";
        else cout << " (Moving)";
        cout << endl;

        // Ask destination from person inside
        if (elevator.needsDestination()) {
            int dest;
            cout << "You are inside the elevator." << endl;
            cout << "Which floor do you want to go to? (Enter 0 to exit): ";
            cin >> dest;

            if (dest == 0) {
                cout << "You exited the elevator." << endl;
                elevator.markIdle();
                this_thread::sleep_for(chrono::seconds(1));
            } else if (dest < 1 || dest > floors) {
                cout << "Invalid floor. Elevator will go idle." << endl;
                elevator.markIdle();
                this_thread::sleep_for(chrono::seconds(1));
            } else {
                cout << "Elevator going to floor " << dest << endl;
                elevator.assignDestination(dest);
            }
        }

        // Get new floor request if no one is inside
        if (!elevator.needsDestination()) {
            int input;
            cout << "Enter a floor number to request the elevator (0 to skip, -1 to quit): ";
            cin >> input;

            if (input == -1) {
                cout << "Exiting simulation. Goodbye!" << endl;
                break;
            } else if (input == 0) {
                cout << "No request entered." << endl;
            } else if (input < 1 || input > floors) {
                cout << "Invalid floor. Try again." << endl;
            } else {
                requestSet.insert(input);
            }
        }

        // If elevator is idle and someone requested it
        if (elevator.idle() && !requestSet.empty()) {
            int nextFloor = findClosestRequest(elevator.getCurrentFloor(), requestSet);
            requestSet.erase(nextFloor);
            cout << "Sending elevator to pick up at floor " << nextFloor << endl;
            elevator.assignRequest(nextFloor);
        }

        // Run elevator for 3 steps to simulate time passing
        for (int i = 0; i < 3; ++i) {
            if (!elevator.step()) {
                cout << "Elevator is currently on floor " << elevator.getCurrentFloor() << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }

    return 0;
}





