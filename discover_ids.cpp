#include "HW.hpp"
#include <iostream>
#include "config.hpp"
auto const max_id = 20;
int main( int argc, char *argv[]) {
    
    HiwonderBus bus;

    // Open serial comminication pins
    if(!bus.begin(SERIAL_PORT)){
        return 0;
    }
    sleep(1);
    for(uint8_t test_id = 0; test_id < max_id; test_id++) {
        std::cout << "Testing ID " << (int)test_id << std::endl;
        HiwonderServo servo(&bus, test_id);
        servo.initialize();
        if(servo.id_verify()){
            std::cout << "Found servo with ID " << (int)test_id << " with angle " << servo.pos_read() << std::endl;
        }
        usleep(1'000);
    }


}