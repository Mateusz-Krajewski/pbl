/**
 * Simple HMC5883L Compass Library
 *
 * Implements a simple interface to get a Heading in Degrees out of a 
 * HMC5883L based compass module.
 * 
 * Datasheet: http://goo.gl/w1criV
 * 
 * Copyright (C) 2014 James Sleeman
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * @author James Sleeman, http://sparks.gogo.co.nz/
 * @license MIT License
 */

#include <Arduino.h>

// PLEASE NOTE!
// The Arduino IDE is a bit braindead, even though we include Wire.h here, it does nothing
// you must include Wire.h in your main sketch, the Arduino IDE will not include Wire
// in the build process otherwise.
#include <Wire.h>
#include "HMC5883L_Simple.h"

/** Set declination in degrees, minutes and direction (E/W)
 *   See http://www.magnetic-declination.com/
 */

void HMC5883L_Simple::SetDeclination( int declination_degs , int declination_mins, char declination_dir )
{    
  // Convert declination to decimal degrees
  switch(declination_dir)
  {
    // North and East are positive   
    case 'E': 
      declination_offset_radians = ( declination_degs + (1/60 * declination_mins)) * (M_PI / 180);
      break;
      
    // South and West are negative    
    case 'W':
      declination_offset_radians =  0 - (( declination_degs + (1/60 * declination_mins) ) * (M_PI / 180));
      break;
  } 
}

/** Set the sampling mode to one of COMPASS_CONTINUOUS or COMPASS_SINGLE
 */

void HMC5883L_Simple::SetSamplingMode( uint16_t sampling_mode )
{  
  // Mode is the bits marked M in mode
  //    xxxxxxxxxxxSSSMM
  mode = (mode & ~0x03) | (sampling_mode & 0x03);

  Write(COMPASS_MODE_REGISTER, mode & 0x03);  
}

/** Set the scale to one of COMPASS_SCALE_088 through COMPASS_SCALE_810
 * Higher scales are less sensitive and less noisy
 * Lower scales are more sensitive and more noisy
 */

void HMC5883L_Simple::SetScale( uint16_t scale )
{
  // Scale is the bits marked S in mode
  //    xxxxxxxxxxxSSSMM  
  mode = (mode & ~0x1C) | (scale & 0x1C);

  Write(COMPASS_CONFIG_REGISTER_B, (( mode >> 2 ) & 0x07) << 5);
}

/** Set the orientation to one of COMPASS_HORIZONTAL_X_NORTH 
 * through COMPASS_VERTICAL_Y_WEST
 *  
 */

void HMC5883L_Simple::SetOrientation( uint16_t orientation )
{
  // Orientation is the bits marked XXXYYYZZZ in mode
  //    xxXXXYYYZZZxxxxx
  mode = (mode & ~0x3FE0) | (orientation & 0x3FE0);    
}

/** Get the heading of the compass in degrees. */

/** Write data to the compass by I2C */
void HMC5883L_Simple::Write(uint8_t register_address, uint8_t data)
{
  Wire.beginTransmission(i2c_address);
  Wire.write(register_address);
  Wire.write(data);
  Wire.endTransmission();
}

/** Read data from the compass by I2C