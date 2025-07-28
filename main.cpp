// Authors: Jeremiah David & Jaden Ngyuen
// Date: 7/24/2025

#include <iostream>
#include <set>
#include <thread>
#include <chrono>

using namespace std;

// The Elevator class keeps track of where the elevator is,
// whether it's idle, where it’s headed, and if it’s waiting for a passenger to choose a destination.
class Elevator {
private:
    int currentFloor;
    int targetFloor;
    bool isIdle;
    bool waitingForDestination;

public:
    // Starts the elevator on floor 1, not moving
    Elevator() {
        currentFloor = 1;
        targetFloor = 1;
        isIdle = true;
        waitingForDestination = false;
    }

    // Called when someone on a floor requests the elevator
    void assignRequest(int floor) {
        targetFloor = floor;
        isIdle = false;
        waitingForDestination = false;
    }

    // Called once someone is inside and selects a destination floor
    void assignDestination(int floor) {
        targetFloor = floor;
        isIdle = false;
        waitingForDestination = false;
    }

    // Moves the elevator one floor closer to its target
    // Returns true if movement happened, false otherwise
    bool step() {
        if (isIdle || waitingForDestination) return false;

        // Move toward the target floor
        if (currentFloor < targetFloor) {
            currentFloor++;
            cout << "Elevator moving up to floor " << currentFloor << endl;
        } else if (currentFloor > targetFloor) {
            currentFloor--;
            cout << "Elevator moving down to floor " << currentFloor << endl;
        }

        // Arrived at the requested floor
        if (currentFloor == targetFloor) {
            cout << "Elevator arrived at floor " << currentFloor << endl;
            cout << "Doors opening..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Doors closing..." << endl;
            waitingForDestination = true; // Now wait for destination from rider
        }

        return true;
    }

    // functions to get status
    int getCurrentFloor() const { return currentFloor; }
    bool idle() const { return isIdle && !waitingForDestination; }
    bool needsDestination() const { return waitingForDestination; }
    void markIdle() { isIdle = true; waitingForDestination = false; }
};

// Chooses the closest floor to serve next, based on current position
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
    set<int> requestSet; // Holds floors where people requested the elevator

    // Welcome message + instructions
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

        // If someone is inside and hasn’t chosen a destination yet
        if (elevator.needsDestination()) {
            int dest;
            cout << "You are inside the elevator." << endl;
            cout << "Which floor do you want to go to? (Enter 0 to exit): ";
            cin >> dest;

            if (dest == 0) {
                // Rider exits
                cout << "You exited the elevator." << endl;
                elevator.markIdle();
                this_thread::sleep_for(chrono::seconds(1));
            } else if (dest < 1 || dest > floors) {
                // Invalid floor selection
                cout << "Invalid floor. Elevator will go idle." << endl;
                elevator.markIdle();
                this_thread::sleep_for(chrono::seconds(1));
            } else {
                // Valid destination
                cout << "Elevator going to floor " << dest << endl;
                elevator.assignDestination(dest);
            }
        }

        // If no one is inside, allow someone to call the elevator
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
                requestSet.insert(input); // Save the request
            }
        }

        // This is If the elevator is free and there’s a request waiting go get it
        if (elevator.idle() && !requestSet.empty()) {
            int nextFloor = findClosestRequest(elevator.getCurrentFloor(), requestSet);
            requestSet.erase(nextFloor);
            cout << "Sending elevator to pick up at floor " << nextFloor << endl;
            elevator.assignRequest(nextFloor);
        }

        // Simulate time passing  this gives the illusion of motion
        for (int i = 0; i < 3; ++i) {
            if (!elevator.step()) {
                // If elevator didn’t move, show its current floor
                cout << "Elevator is currently on floor " << elevator.getCurrentFloor() << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(500)); // Pause for realism
        }
    }

    return 0;
}
