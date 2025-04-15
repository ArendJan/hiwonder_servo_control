#include "HW.hpp"
#include <iostream>

#include "config.hpp"

int main( int argc, char *argv[]) {
    
    HiwonderBus bus;

    // Open serial comminication pins
    bus.begin(SERIAL_PORT);
    sleep(1);
    auto id = bus.id_read();
    std::cout << "ID of the servo is " << (int) id << std::endl;
    // return 0;
    if(argc <2) {
        return 0;
    }
    if(argc > 1) {
        auto new_id = atoi(argv[1]);
        if(new_id <= 0 || new_id > 254) {
            std::cout << "ID must be between 0 and 254" << std::endl;
            return 0;
        }
        if(new_id == id) {
            std::cout << "ID is already set to " << (int) new_id << std::endl;
            return 0;
        }
        std::cout << "setting id to " << (int)atoi(argv[1]) << std::endl;
        bus.id_write(atoi(argv[1]));
        sleep(1);
        id = bus.id_read();
        std::cout << "ID of the servo is " << (int) id << std::endl;
        if (id != atoi(argv[1])) {
            std::cout << "Error setting id to " << (int)atoi(argv[1]) << std::endl;
        }
    }
    return 0;
}
