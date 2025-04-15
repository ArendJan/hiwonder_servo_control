# Hiwonder servo control
Control Hiwonder servos from any computer with an UART interface.
Currently only supports Linux due to serial.

# Connect
Connect UART RX&TX to the data pin of the servo.
Connect power to the power pins of the servo and connect ground to the ground pin of the UART cable/interface.

Doesn't (currently) work with the official Hiwonder boards as they have a buffer to prevent loopback.

Original source from [madhephaestus/lx16a-servo](https://github.com/madhephaestus/lx16a-servo)

Thanks to @[vvannoesel](https://github.com/vvannoesel) for converting the library to work on Linux.