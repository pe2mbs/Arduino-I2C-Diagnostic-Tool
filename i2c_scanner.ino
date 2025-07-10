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
// --------------------------------------
*   Thi sis based on the example sketch i2c_scanner.ino
*/
#include <avr/pgmspace.h>
#include <Wire.h>
#include "i2cdevices.cpp"


void print_I2C_Device( uint8_t address )
{
    I2C_DEVICE  device;
    memcpy_P( &device, &I2CTable[ address ], sizeof ( I2C_DEVICE ) );
    int len = strlen_P( device.devices );
    for (int k = 0; k < len; k++)
    {
        Serial.print( (char)pgm_read_byte(device.devices + k) );
    }
    return;
}

void setup() 
{
    Wire.begin();
    Serial.begin( 115200 );
    while (!Serial); // Leonardo: wait for Serial Monitor
    Serial.println( "I2C Scanner version 1.0.0, Copyright (C) 2025 Marc Bertens-Nguyen" );
    Serial.println( "I2C Scanner comes with ABSOLUTELY NO WARRANTY" );
    Serial.println( "This is free software, and you are welcome to redistribute it" );
    Serial.println( "under certain conditions; see LICENCE.md for details.\n" );
}


void loop() {
    int nDevices = 0;
    Serial.println("Scanning...");
    for ( byte address = 1; address < 127; ++address ) 
    {
        // The i2c_scanner uses the return value of
        // the Wire.endTransmission to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission( address );
        byte error = Wire.endTransmission();
        if (error == 0) 
        {
            Serial.print( "I2C device found at address 0x" );
            if ( address < 16 ) 
            {
                Serial.print("0");
            }          
            Serial.print( address, HEX );
            Serial.print( " - ");
            print_I2C_Device( address );
            Serial.println( "  !");
            ++nDevices;
        } 
        else if (error == 4) 
        {
            Serial.print("Unknown error at address 0x");
            if (address < 16) 
            {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
    }
    if ( nDevices == 0 ) 
    {
        Serial.println( "No I2C devices found\n" );
    } 
    else 
    {
        Serial.print( nDevices, DEC );
        Serial.println( " devices found\n" );
    }
    delay(5000); // Wait 5 seconds for next scan
    return;
}
