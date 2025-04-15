#include "HW.hpp"
#include <iostream>
#include "config.hpp"

int main( int argc, char *argv[]) {
    
    HiwonderBus bus;

    // Open serial comminication pins
    bus.begin(SERIAL_PORT);
    sleep(1);
    auto id = bus.id_read();
    if(argc <3) {
        return 0;
    }
    auto curr_id = atoi(argv[1]);
    if(curr_id != id) {
        std::cout << "The connected servo has not ID " << (int) curr_id << " but ID " << (int)id  << std::endl;
        return 0;
    }
    auto target_pos = atoi(argv[2]);
    if(target_pos < 0 || target_pos > 24000) {
        std::cout << "Target position must be between 0 and 24000" << std::endl;
        return 0;
    }    
    std::cout << "Moving servo to position " << target_pos << std::endl;
    HiwonderServo servo(&bus, id);
    servo.move_time(target_pos, 1000);
    return 0;
}
