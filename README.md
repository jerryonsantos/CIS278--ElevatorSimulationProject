# CIS 278 Eleveator Simulation Project
This is a simple C++  program that simulates the operation of a single elevator in a multi-floor building. Users can request elevator pickups and specify destination floors, and the elevator moves accordingly with direction logic and floor updates.

# How to run the code

## ON IDE
1. Open CLion or any IDE
2. Create a new project or open the folder where your main.cpp file is.
3. Paste my code into main.cpp (or add it to src if using CMake).
4. Click the green "Run" triangle button at the top right.
## USING TERMINAL
1. Clone this GitHub repo
2. Navigate to project folder
3. Compile c++ code
4. Run Program
   
# Team Members and Roles
Jeremiah David: Building and managing Elevator Class
Jaden Nguyen: Creating user interaction in main()

# Features Implemented
1. Single Elevator Logic: The simulation models a single elevator operating within a user-defined number of floors.
2. Pickup and Destination Requests: Users can call the elevator from any floor. Once inside, they’re prompted to select a destination floor.
Idle, Moving, and Rider-Inside States
3. The elevator status: Displays different statuses such as - Idle when not in use, Moving when traveling between floors, Rider inside when someone is onboard waiting to choose a floor
4. Direction Display (Up/Down): While moving, the elevator shows if it is going up or down, along with the current floor.
5. Request: If multiple floors request the elevator the simulation will handle the first request than the next
6. Exit and Input Validation: Users can skip a turn or exit the simulation cleanly. Input is validated to prevent invalid floor entries.
