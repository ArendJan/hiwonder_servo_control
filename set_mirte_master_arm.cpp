#include "HW.hpp"
#include <iostream>
#include "config.hpp"

typedef struct {
    uint8_t id;
    int16_t min;
    int16_t max;
    int16_t home;

} servo_settings_t;

float voltage_limit_min = 10.5f;
float voltage_limit_max = 14.0f;

std::vector<servo_settings_t> servos_settings = {{
    .id = 2,
    .min = 3400,
    .max = 21000,
    .home = 12000
}, {
    .id = 3,
    .min = 2832,
    .max = 20000,
    .home = 11450
}, {
    .id = 4,
    .min = 120,
    .max = 21000,
    .home = 11750
}, {
    .id = 5,
    .min = 1128,
    .max = 21000,
    .home = 12200
}, {
    .id = 6,
    .min = 6168,
    .max = 14224,
    .home = 10524
}};



void set_servo(HiwonderBus&bus, servo_settings_t id, bool move_home = false) {
    HiwonderServo servo(&bus, id.id);
    servo.initialize();
    if(!servo.id_verify()) {
        std::cout << "Servo ID " << (int)id.id << " not found" << std::endl;
        return;
    }
    servo.setLimitsTicks(id.min/24, id.max/24);
    std::cout << "New angle limits: " << id.min << " - " << id.max << std::endl;

    std::cout << "Current offset: " << servo.read_angle_offset() << std::endl;
    servo.angle_offset_adjust(0);
    servo.angle_offset_save();
    std::cout << "New offset: " << servo.read_angle_offset() << std::endl;

    if(move_home) {
        auto min_volt = servo.getVoltageLimits().first;
        if(min_volt < servo.vin()) {
            servo.setVoltageLimits(4, voltage_limit_max);
        }
        servo.move_time(id.home, 100);
        std::cout << "Moving to home position" << std::endl;
    }
    servo.setVoltageLimits(voltage_limit_min, voltage_limit_max);
    auto new_min_volt = servo.getVoltageLimits().first;
    auto new_max_volt = servo.getVoltageLimits().second;
    std::cout << "New voltage limits: " << new_min_volt << " - " << new_max_volt << std::endl;

};


int main( int argc, char *argv[]) {
    
    HiwonderBus bus;

    // Open serial comminication pins
    if(!bus.begin(SERIAL_PORT)){
        return 0;
    }
    sleep(1);

    for(auto& setting : servos_settings) {
        set_servo(bus, setting);
    }
}