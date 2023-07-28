/*
 * Copyright 2023 ryrak
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
 * @file example_read.ino
 * @brief This file can measure magnetic value by read function
 */
#include "Wire.h"
#include "NMH1000_Arduino.h"

/*
 * Definition for test functions
 */
NMH1000_Arduino nmh1000(NMH1000_Arduino::Mode::_I2C);

/*
 * Functions
 */
void setup() {
  // put your setup code here, to run once:
  // Initialize the device and set autorun with ODR=10Hz
  Wire.begin();
  Serial.begin(115200);
  pinMode(7, INPUT);
  nmh1000.init();
  nmh1000.autorun(NMH1000_ODR_10HZ, 0x10, 0x15);
}

void loop() {
  // Infinite loop of reading magnetic value
  delay(300);
  int8_t output = nmh1000.read();
  Serial.print("H/L:");
  if (digitalRead(7)) Serial.print("10,");
  else Serial.print("0,");
  Serial.print("Output:");
  Serial.println(output, DEC);
}
