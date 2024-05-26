#include "pmsx003.hpp"

pmsx003::pmsx003(/* args */) {}

pmsx003::~pmsx003() {}

void pmsx003::begin(Stream *dev) { serial_dev = dev; }

#define START_BYTE 0x42

pmsx003data pmsx003::read() {
    pmsx003data data;
    data.success = false;
    if (!serial_dev->available()) {
        return data;
    }

    // Read a byte at a time until we get to the special '0x42' start-byte
    if (serial_dev->peek() != START_BYTE) {
        serial_dev->read();
        return data;
    }

    // Now read all 32 bytes
    if (serial_dev->available() < 32) {
        return data;
    }

    uint8_t buffer[32];
    uint16_t sum = 0;
    serial_dev->readBytes(buffer, 32);

    // Calculate checksum
    for (uint8_t i = 0; i < 30; i++) {
        sum += buffer[i];
    }

    // The data comes in endian'd, this solves it so it works on all
    // platforms
    uint16_t buffer_u16[15];
    for (uint8_t i = 0; i < 15; i++) {
        buffer_u16[i] = buffer[2 + i * 2 + 1];
        buffer_u16[i] += (buffer[2 + i * 2] << 8);
    }

    // Convert in struct
    memcpy((void *)&data, (void *)buffer_u16, 30);

    if (sum != data.checksum) {
        Serial.println("Checksum failure");
        return data;
    }
    data.success = true;

    return data;
}