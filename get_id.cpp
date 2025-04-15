#include "HW.hpp"
#include <iostream>
#include "config.hpp"

int main( int argc, char *argv[]) {
    
    HiwonderBus bus;
    if(!bus.begin(SERIAL_PORT)){
        return 0;
    }
    sleep(1);
    auto id = bus.id_read();
    std::cout << "ID of the servo is " << (int) id << std::endl;
    return 0;
}
