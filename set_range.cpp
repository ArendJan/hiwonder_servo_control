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
        std::cout << "missing args"<< std::endl;
        return 0;
    }
    auto curr_id = atoi(argv[1]);
    if(curr_id != id) {
        std::cout << "The connected servo has not ID " << (int) curr_id << " but ID " << (int)id  << std::endl;
        return 0;
    }
    // auto target_pos = atoi(argv[2]);
    HiwonderServo servo(&bus, id);
    servo.initialize();
    auto min_range = servo.getMinCentDegrees();
    auto max_range = servo.getMaxCentDegrees();
    std::cout << "Current range: " << min_range << " - " << max_range << std::endl;
return 0;
    auto target_min = 10.5f;
    auto target_max = 14.0f;
    servo.setVoltageLimits(target_min * 1000, target_max * 1000);
    auto new_min_volt = servo.getVoltageLimits().first;
    auto new_max_volt = servo.getVoltageLimits().second;
    std::cout << "New voltage limits: " << new_min_volt << " - " << new_max_volt << std::endl;
    auto current_vin = servo.vin();
    std::cout << "Current voltage: " << current_vin/1000.0f << std::endl;
    return 0;
}
