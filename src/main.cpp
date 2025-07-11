/*
*
*   i2c_scanner: scan the I2C bus for all addresses attached devices 
*
*   Copyright (C) 2025 Marc Bertens-Nguyen <m.bertens@pe2mbs.nl>
*   
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License.
*   
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*   
*   You should have received a copy of the GNU General Public License along
*   with this program; if not, see <https://www.gnu.org/licenses/>.
*
// ------------------------------------------------------------------------
*
*   This is based on the example sketch i2c_scanner.ino
*   Rebuild for use on PlatformIO
*/
#include <avr/pgmspace.h>
#include <HardwareSerial.h>
#include <Arduino.h>
#include <Wire.h>
#include "i2cdevices.hpp"


I2C_devices devices;


void setup() 
{
    Wire.begin();
    Serial.begin( 57600 );
    while ( !Serial );
    devices.banner();
    return;
}


void loop() 
{
    devices.scan();    
    return;
}
