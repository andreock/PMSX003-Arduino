#include <Arduino.h>

typedef struct pmsx003data {
    uint16_t framelen;
    uint16_t pm10_standard;
    uint16_t pm25_standard;
    uint16_t pm100_standard;
    uint16_t pm10_env;
    uint16_t pm25_env;
    uint16_t pm100_env;
    uint16_t particles_03um;
    uint16_t particles_05um;
    uint16_t particles_10um;
    uint16_t particles_25um;
    uint16_t particles_50um;
    uint16_t particles_100um;
    uint16_t unused;
    uint16_t checksum;
    bool success;
} pmsx003data;

class pmsx003 {
   private:
    Stream *serial_dev;
   public:
    pmsx003(/* args */);
    ~pmsx003();
    void begin(Stream *dev);
    pmsx003data read();
};
