/*
 * Copyright 2023 ryrak
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
/**
 * @file NMH1000_Arduino.h
 * @brief This file is the header for NMH1000_Arduino
 */

#ifndef _NMH1000_ARDUINO_H
#define _NMH1000_ARDUINO_H

#include <Arduino.h>
#include <Wire.h>
#include <I2C_device.h>
#include "nmh1000_regdef.h"

#define NMH1000_DEVICE_ADDRESS 0x60   //!< @brief NMH1000 default I2C address

enum odr_freq {
  NMH1000_ODR_0_1HZ = NMH1000_USER_ODR_ODR_LSP,
  NMH1000_ODR_0_5HZ = NMH1000_USER_ODR_ODR_5X_LSP,
  NMH1000_ODR_1HZ = NMH1000_USER_ODR_ODR_MSP,
  NMH1000_ODR_10HZ = NMH1000_USER_ODR_ODR_HSP,
  NMH1000_ODR_50HZ = NMH1000_USER_ODR_ODR_5X_HSP,
  NMH1000_ODR_100HZ = NMH1000_USER_ODR_ODR_10X_HSP
};

class NMH1000_Arduino : public I2C_device {
  public:
    enum Mode {_I2C, _STDALONE};
    Mode mode;   //!< @brief If STANDALONE mode is used, the device cannot be setup and read function returns only HIGH or LOW.

    /**
    * @brief Initialize the device with reset with several GPIO pin configuration
    * @return WHO_AM_I register value
    */
    uint8_t init();

    /**
    * @brief Initialize the device with reset
    * @param pinconfig If you wouldn't like to config the pins by this function, put false in this parameter. This parameter can be skipped.
    * @return WHO_AM_I register value
    */
    uint8_t init(bool pinconfig);


    /**
    * @brief Reset the device by writing CONTROL_REG1=0x01
    */
    void reset();

    /**
    * @brief Set the threshold to output HIGH or LOW. Be sure assert is always smaller than clear.
    * @param assert The threshold to assert. Shall be smaller than clear.
    * @param clear The threshold to clear. Shall be bigger than assert.
    */    
    void threshold(uint8_t assert, uint8_t clear);

    /**
    * @brief Start autonomous mode by setting AUTO=0b01.
    * @param odr The ODR frequency selected from odr_freq.
    */        
    void autorun(odr_freq odr);

    /**
    * @brief Start autonomous mode by setting AUTO=0b01 with threshold values.
    * @param odr The ODR frequency selected from odr_freq.
    * @param assert The threshold to assert. Shall be smaller than clear.
    * @param clear The threshold to clear. Shall be bigger than assert.
    */    
    void autorun(odr_freq odr, uint8_t assert, uint8_t clear);

    /**
    * @brief Read magnetic field value. Only outputs HIGH or LOW when STANDALONE mode is selected.
    * @return MAG_DATA value when I2C mode or output state when STANDALONE mode
    */    
    int8_t read();
    
    /** Create a NMH1000_Arduino instance
    * @param mode Be selected from _I2C when I2C mode or _STDALONE when STANDALONE mode
    */
    NMH1000_Arduino(Mode mode);

    /** Create a NMH1000_Arduino instance
    * @param mode Be selected from _I2C when I2C mode or _STDALONE when STANDALONE mode
    * @param i2c_address I2C address for NMH1000. This does NOT change NMH1000 I2C address by writing register.
    */
    NMH1000_Arduino(Mode mode, uint8_t i2c_address);

    /** Create a NMH1000_Arduino instance
    * @param mode Be selected from _I2C when I2C mode or _STDALONE when STANDALONE mode
    * @param wire TwoWire instance
    * @param i2c_address I2C address for NMH1000. This does NOT change NMH1000 I2C address by writing register.
    */    
    NMH1000_Arduino(Mode mode, TwoWire& wire, uint8_t i2c_address);

    /** Destructor of FXLS89xx_Arduino
    */
    ~NMH1000_Arduino();

    #if DOXYGEN_ONLY
      /** Get temperature value in degree Celsius [°C] 
      *
      *	This method simply calls "temp()" method	
      *
      * @return temperature value in degree Celsius [°C] 
      */
      virtual float read( void );

      /** Ping the device
      *
      * @return true when ACK 
      */
      bool ping( void );
        
      /** Multiple register write
      * 
      * @param reg register index/address/pointer
      * @param data pointer to data buffer
      * @param size data size
      * @return transferred data size
      */
      int reg_w( uint8_t reg_adr, uint8_t *data, uint16_t size );

      /** Single register write
      * 
      * @param reg register index/address/pointer
      * @param data pointer to data buffer
      * @param size data size
      * @return transferred data size
      */
      int reg_w( uint8_t reg_adr, uint8_t data );

      /** Multiple register read
      * 
      * @param reg register index/address/pointer
      * @param data pointer to data buffer
      * @param size data size
      * @return transferred data size
      */
      int reg_r( uint8_t reg_adr, uint8_t *data, uint16_t size );

      /** Single register read
      * 
      * @param reg register index/address/pointer
      * @return read data
      */
      uint8_t	reg_r( uint8_t reg_adr );

      /** Register write, 8 bit
      *
      * @param reg register index/address/pointer
      * @param val data value
      */
      void write_r8( uint8_t reg, uint8_t val );

      /** Register write, 16 bit
      * 
      *	This 16 bit access may ot be common but it's useful for sensor devices
      *
      * @param reg register index/address/pointer
      * @param val data value
      */
      void write_r16( uint8_t reg, uint16_t val );

      /** Register read, 8 bit
      *
      * @param reg register index/address/pointer
      * @return data value
      */
      uint8_t read_r8( uint8_t reg );

      /** Register read, 16 bit
      *	
      *	This 16 bit access may ot be common but it's useful for sensor devices
      *
      * @param reg register index/address/pointer
      * @return data value
      */
      uint16_t read_r16( uint8_t reg );

      /** Register overwriting with bit-mask
      *	
      *	Register can be updated by bit level
      *
      * @param reg register index/address/pointer
      * @param mask bit-mask to protect overwriting
      * @param value value to overwrite
      */
      void bit_op8(  uint8_t reg,  uint8_t mask,  uint8_t value );
      void bit_op16( uint8_t reg, uint16_t mask, uint16_t value );
   #endif	// DOXYGEN_ONLY
};

#endif