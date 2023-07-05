/*
 * Copyright 2023 ryrak
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
 * @file NMH1000_Arduino.cpp
 * @brief This file contains the functions for NMH1000 Hall sensor evaluation by Arduino
 */
 
#include <Arduino.h>
#include "NMH1000_Arduino.h"

NMH1000_Arduino::NMH1000_Arduino(Mode mode) : I2C_device(NMH1000_DEVICE_ADDRESS) {}
NMH1000_Arduino::NMH1000_Arduino(Mode mode, uint8_t i2c_address = NMH1000_DEVICE_ADDRESS) : I2C_device(i2c_address) {}
NMH1000_Arduino::NMH1000_Arduino(Mode mode, TwoWire& wire, uint8_t i2c_address = NMH1000_DEVICE_ADDRESS) : I2C_device(wire, i2c_address) {}
NMH1000_Arduino::~NMH1000_Arduino() {}

uint8_t NMH1000_Arduino::init() {
  return init(true);
}


uint8_t NMH1000_Arduino::init(bool pinconfig) {
  if (mode==_STDALONE) return 0;
  if (pinconfig) {
    pinMode(SDA, INPUT);
    pinMode(SCL, INPUT);
    pinMode(2, INPUT);
  }
  reset();
  return read_r8(NMH1000_WHO_AM_I);
}

void NMH1000_Arduino::reset() {
  if (mode==_STDALONE) return;
  write_r8(NMH1000_CONTROL_REG1, NMH1000_CONTROL_REG1_RST_RESET);
  delay(8);
}

void NMH1000_Arduino::threshold(uint8_t assert, uint8_t clear) {
  if (mode==_STDALONE) return;
  uint8_t buf[2] = {assert<<3, clear<<3};
  reg_w(NMH1000_USER_ASSERT_THRESH, buf, 2);
}

void NMH1000_Arduino::autorun(odr_freq odr) {
  if (mode==_STDALONE) return;
  reg_w(NMH1000_ODR, odr);
  reg_w(NMH1000_CONTROL_REG1, NMH1000_CONTROL_REG1_AUTO_MODE_START);
}

void NMH1000_Arduino::autorun(odr_freq odr, uint8_t assert, uint8_t clear) {
  if (mode==_STDALONE) return;
  reg_w(NMH1000_ODR, odr);
  threshold(assert, clear);
  reg_w(NMH1000_CONTROL_REG1, NMH1000_CONTROL_REG1_AUTO_MODE_START);
}

int8_t NMH1000_Arduino::read() {
  if (mode==_STDALONE) return digitalRead(7);
  int8_t reg = read_r8(NMH1000_OUT_M_REG)>>2;
  return reg;
}