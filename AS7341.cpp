#include "AS7341.h"
#include <iostream>

// Check that the sensor is accessible on the given bus and address
bool AS7341::begin(uint8_t bus, uint8_t i2caddr) 
{
	_i2c_address = i2caddr;
	
	if(initI2C_RW(bus, i2caddr, 0) > 0)
		return false;

	return true;
}

bool AS7341::initialise()
{
    uint8_t whoAmI = 0;

    // Check if the board exists
	if(!readRegisters(AS7341_WHOAMI, &whoAmI, 1))
		return false;
    
    whoAmI >>= 2;

    if(whoAmI != 0b001001) {
		rt_printf("Got unexpected identity %x from IMU board\n", whoAmI);
		return false;
	}

    rt_printf("whoAmI result %x\n", whoAmI);

    return true;
}

bool AS7341::readRegisters(uint8_t reg, uint8_t* data, uint8_t length)
{
	// Write address of first register to be read from
	if(write(i2C_file, &reg, 1) != 1) {
		rt_printf("Failed to write register reg %d\n", reg);
		return false;
	}	
	
	// Read the response of the indicated length
	int count = read(i2C_file, data, length);
	if(count != length)
	{
		rt_printf("Failed to read result on AS7341 (got length %d)\n", count);
		return false;
	}

	return true;
}

bool AS7341::writeRegister(uint8_t reg, uint8_t value)
{
	uint8_t buf[2] = { reg, value };

	if(write(i2C_file, buf, 2) != 2)
	{
		rt_printf("Failed to write register %x\n", reg);
		return false;
	}
	
	return true;
}

/**
 * @brief Write individual bit(s) of a register
 *
 * @param reg: the register to write to
 * @param bits: the number of bits to write
 * @param shift: the amount of bits to shift
 * @param data: the data to write
 * @return true: success false: failure
 */
bool AS7341::writeRegisterBits(uint8_t reg, uint8_t bits, uint8_t shift, uint8_t data)
{
    uint8_t* val;
    uint8_t length = 1; // ?

    if(!readRegisters(reg, val, length))
        return false;

    // mask off the data before writing
    uint32_t mask = (1 << (bits)) - 1;
    data &= mask;

    mask <<= shift;
    val &= ~mask;         // remove the current data at that spot
    val |= data << shift; // and add in the new data

    return writeRegister(reg, val, length);
}

/**
 * @brief Enable control of an attached LED on the LDR pin
 *
 * @param enable_led true: LED enabled false: LED disabled
 * @return true: success false: failure
 */
bool AS7341::enableLED(bool enable_led)
{
    setBank(true); // Access 0x60-0x74

    // led_sel_bit
    if(!writeRegisterBits(AS7341_CONFIG, 1, 3, enable_led))
        return false;
 
    // led_act_bit
    if(!writeRegisterBits(AS7341_LED, 1, 7, enable_led))
        return false;

    setBank(false); // Access registers 0x80 and above (default)
    return true;
}

/**
 * @brief Set the current limit for the LED
 *
 * @param led_current_ma the value to set in milliamps. With a minimum of 4. Any
 * amount under 4 will be rounded up to 4
 *
 * Range is 4mA to 258mA
 * @return true: success false: failure
 */
bool AS7341::setLEDCurrent(uint16_t led_current_ma)
{

    // led_reg
    // led_current_bits

    return true;
}

/**
 * @brief Sets the active register bank
 *
 * The AS7341 uses banks to organize the register making it nescessary to set
 * the correct bank to access a register.
 *

 * @param low **true**:
 * **false**: Set the current bank to allow access to registers with addresses
 of `0x80` and above
 * @return true: success false: failure
 */
bool AS7341::setBank(bool low)
{
    // cfg0_reg = AS7341_CFG0

    // bank_bit = &cfg0_reg, 1, 4

    return writeRegisterBits(bank_bit, low);
}

bool AS7341::readResult(float *result)
{
    result[0] = 0.5;
    return true;
}
