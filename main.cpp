#include "HW.hpp"
#include <iostream>

#define SERVO_ID 4
#define SERIAL_PORT "/dev/ttyUSB0" // this should be either serial0 

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
            return 0;
        }
        return 0;
    }
//     uint16_t steps = 0;
//     uint8_t params[2];

//     while (true) {
//         std::cout << "Give a value between (0-1000): ";
//         // std::cin >> steps;
// steps =200;
//         if (steps > 1000) {
//             std::cout << "invalid entry! Choose a value between 0 and 1000." << std::endl;
//             continue;
//         }

//         // Convert 0-1000 to 0-240 deg
//         uint16_t angle = (steps * 24);

//         // // Convert to two bytes (low and high)
//         // params[0] = angle & 0xFF;        // Lowest byte
//         // params[1] = (angle >> 8) & 0xFF; // Highest byte
        


//     HiwonderServo servo(&bus, SERVO_ID);
//     servo.initialize();
//     // servo.setVoltageLimits(0, 10000);
//     // servo.move_time(angle, 200);
//             usleep(500000); //0.5 s

//     auto pos = servo.pos_read();
//     std::cout << "currently at  " << (int) pos << " centidegrees" << std::endl;
//         std::cout << "currently at  " <<  pos << " centidegrees" << std::endl;
// std::cout << "command ok " << (int) servo.isCommandOk() << std::endl;
//     // servo.pos_read();
//     //~ servo.pos_read();
//     //~ std::cout << "command ok " << (int) servo.pos_read() << std::endl;
//         std::cout << "command ok " << std::endl;
//         std::cout << "currently at  " << (int) servo.pos_read()<< " centidegrees" << std::endl;
//                 std::cout << "currently at  " << servo.pos_read()<< " centidegrees" << std::endl;
// // std::cout << "faults " << (int) servo.getFaults() << std::endl;
//             return 0;


//     }
    return 0;
}
