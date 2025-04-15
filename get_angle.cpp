#include "HW.hpp"
#include <iostream>
#include "config.hpp"

int main( int argc, char *argv[]) {
    
    HiwonderBus bus;

    // Open serial comminication pins
    bus.begin(SERIAL_PORT);
    sleep(1);
    auto id = bus.id_read();
    if(argc <2) {
        return 0;
    }
    auto curr_id = atoi(argv[1]);
    if(curr_id != id) {
        std::cout << "The connected servo has not ID " << (int) curr_id << " but ID " << id  << std::endl;
        return 0;
    }
    
    HiwonderServo servo(&bus, id);
    // servo.move_time(target_pos, 1000);
    while(1) {
        auto pos = servo.pos_read();
        std::cout << "Current position: " << pos << std::endl;
        usleep(100'000); // sleep for .1 second
    }
    return 0;
}
