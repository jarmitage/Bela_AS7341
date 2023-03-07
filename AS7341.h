#pragma once

#include <I2c.h>
#include <Utilities.h>
#include <stdint.h>

#define AS7341_WHOAMI 0x92
#define AS7341_CONFIG 0x70
#define AS7341_LED 0x74
#define AS7341_CFG0 0xA9 ///< Sets Low power mode, Register bank, and Trigger lengthening

class AS7341 : public I2c {
public:
	AS7341() {}

	bool begin(uint8_t bus = 1, uint8_t i2caddr = 0x39);

	bool initialise();
	bool readResult(float *result);
	
	// int readI2C() { return 0; }	// Unused from parent class
	
    bool enableLED(bool enable_led);
    bool setLEDCurrent(uint16_t led_current_ma);

private:
	int _i2c_address;
	
    bool setBank(bool low);

	bool readRegisters(uint8_t reg, uint8_t* data, uint8_t length);
	bool writeRegister(uint8_t reg, uint8_t value);

    bool writeRegisterBits(uint8_t reg, uint8_t bits, uint8_t shift, uint8_t data);
	
};
