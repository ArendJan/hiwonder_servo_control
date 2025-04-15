// Modified code from https://github.com/madhephaestus/lx16a-servo

#include "HW.hpp"
// #include "i2c_helpers.hpp"
// #include "pico/stdlib.h"
#include <stdio.h>
#include <vector>

// Define the millis function using the clock_gettime function: niewu
uint32_t millis() {
      struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
auto curr_ms = (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);

    static uint32_t start = 0;
    if(start == 0) {
        start = curr_ms;
    }
    return curr_ms - start;
}

// Define the time_us_32 function using the clock_gettime function: nieuw
uint32_t time_us_32() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    auto curr = (ts.tv_sec * 1000000) + (ts.tv_nsec / 1000);
  static uint32_t start = 0;
    if(start == 0) {
        start = curr;
    }
    return curr - start;
}
// write a command with the provided parameters
// returns true if the command was written without conflict onto the bus
bool HiwonderBus::write_no_retry(uint8_t cmd, const uint8_t *params,
                                 int param_cnt, uint8_t MYID) {
  
  if (param_cnt < 0 || param_cnt > 4) {
    std::cout << "Err param count " << param_cnt << std::endl;
    return false;
  }


  // prepare packet in a buffer
  int buflen = 6 + param_cnt;  
  std::vector<uint8_t> buf(buflen, 0);
  std::vector<uint8_t> ret(buflen, 0);
  

  buf[0] = 0x55;
  buf[1] = 0x55;
  buf[2] = MYID;
  buf[3] = buflen - 3;
  buf[4] = cmd;
  for (int i = 0; i < param_cnt; i++){
    buf[5 + i] = params[i];
  }
  uint8_t cksum = 0;
  for (int i = 2; i < buflen - 1; i++){
    cksum += buf[i];
  buf[buflen - 1] = ~cksum;
}

  // clear input buffer
  int junkCount = 0;
  usleep(timeus(2));
  while (available()) {
    read();

    usleep(timeus(3));

    junkCount++;
  }
  // std::cout << "junk count " << junkCount << std::endl;
  lastCommand = cmd;
  // send command packet
  uint32_t t0 = millis();

  write(buf.data(), buflen);
  // expect to read back command by virtue of single-pin loop-back
  uint32_t tout = time(buflen + 4) + 4; // 2ms margin
  int got = 0;
  bool ok = true;

 
  while ((got < buflen) && ((millis() - t0) < tout)) {
    // std::cout << "got: " << got << std::endl;
    if (available()) {
      ret[got] = read();
      if (ret[got] != buf[got]) {
        std::cout << "Err expected " << (int)buf[got] << " got "
                  << (int)ret[got] << std::endl;
        ok = false;
      }
      got++;
    }
  }



  return ok;
}
bool HiwonderBus::rcv(uint8_t cmd, uint8_t *params, int param_len,
                      uint8_t MYID) {
                        // std::cout << "rcv" << std::endl;
  // read back the expected response
  uint32_t t0 = time_us_32() / 1000;
  uint32_t tout = time(param_len + 6) + 30; // time in ms for the servo to think
  int got = 0;
  uint8_t sum = 0;
  int len = 7; // minimum length
  while (got < len && ((millis() - t0) < tout)) {
    // std::cout << "time diff " << (millis() - t0) << std::endl;
    if (available()) {
      int ch = read();
      // std::cout << "ch: " << ch << std::endl;
      switch (got) {
      case 0:
      case 1:
        if (ch != 0x55) {
          // if (_debug)
            printf("Err expected header 0x55 = %X\n", ch);
          return false;
        }
        break;
      case 2:
        if (ch != MYID && MYID != 0xfe) {
          // if (_debug)
          printf("Err id %X %X\n", MYID, ch);
          // Serial.println(" ERR (id)\n");
          return false;
        }
        break;
      case 3:
        if (ch < 3 || ch > 7) {
          // if (_debug)
            printf("Err len %X\n", ch);

          return false;
        }
        len = ch + 3;
        if (len > param_len + 6) {
          // if (_debug)

            printf("Err len got %X vs %X\n", len, param_len + 6);
          return false;
        }
        break;
      case 4:
        if (ch != cmd) {
          // if (_debug)
            printf(" ERR (cmd) %X  vs %X\n", ch, cmd);
          return false;
        }
        break;
      default:
        if (got == len - 1) {
          if ((uint8_t)ch == (uint8_t)~sum) {
            // if (_deepDebug)
            //   printf("OK msg\n");
            return true;
          } else {
            // if (_debug)
            //   printf("checksum err\n");
            return false;
          }
        }
        if (got - 5 > param_len) {
          // if (_debug)
          //   printf("checksum err2\n");

          return false;
        }
        params[got - 5] = ch;
      }
      if (got > 1) {
        sum += ch;
      }
      got++;
    }
  }
  return false;
}
// read sends a command to the servo and reads back the response into the params
// buffer. returns true if everything checks out correctly.
bool HiwonderBus::read_no_retry(uint8_t cmd, uint8_t *params, int param_len,
                                uint8_t MYID) {
  bool ok = write(cmd, NULL, 0, MYID);
      // std::cout << "ok write " << (int)ok << std::endl;
  if (!ok) {
    return false;
  }

  return rcv(cmd, params, param_len, MYID);
}
