/*	RHT03-Example-Serial.cpp
	Jim Lindblom <jim@sparkfun.com>
	August 31, 2015
    
    Ported to Arduino by Shawn Hymel
    October 28, 2016
	https://github.com/sparkfun/SparkFun_RHT03_Arduino_Library
	
	This a simple example sketch for the SparkFunRHT03 Ardiuno
	library.
	
	Looking at the front (grated side) of the RHT03, the pinout is as follows:
	 1     2        3       4
	VCC  DATA  No-Connect  GND
	
	Connect the data pin to Arduino pin D4. Power the RHT03 off the 3.3V bus.
	
	A 10k pullup resistor can be added to the data pin, though it seems to
	work without it.
	
    Development environment specifics:
	Arduino IDE v1.6.5
	Distributed as-is; no warranty is given.  
*/

// Include the library:
#include <SparkFun_RHT03.h>

/////////////////////
// Pin Definitions //
/////////////////////
const int RHT03_DATA_PIN = 4; // RHT03 data pin

///////////////////////////
// RHT03 Object Creation //
///////////////////////////
RHT03 rht; // This creates a RTH03 object, which we'll use to interact with the sensor

void setup()
{
	Serial.begin(9600); // Serial is used to print sensor readings.
	
	// Call rht.begin() to initialize the sensor and our data pin
	rht.begin(RHT03_DATA_PIN);
	
}

void loop()
{
	// Call rht.update() to get new humidity and temperature values from the sensor.
	int updateRet = rht.update();
	
	// If successful, the update() function will return 1.
	// If update fails, it will return a value <0
	if (updateRet == 1)
	{
		// The humidity(), tempC(), and tempF() functions can be called -- after 
		// a successful update() -- to get the last humidity and temperature
		// value 
		float latestHumidity = rht.humidity();
		float latestTempC = rht.tempC();
		float latestTempF = rht.tempF();
		
		// Now print the values:
		Serial.println("Humidity: " + String(latestHumidity, 1) + " %");
		Serial.println("Temp (F): " + String(latestTempF, 1) + " deg F");
		Serial.println("Temp (C): " + String(latestTempC, 1) + " deg C");
	}
	else
	{
		// If the update failed, try delaying for RHT_READ_INTERVAL_MS ms before
		// trying again.
		delay(RHT_READ_INTERVAL_MS);
	}
	
	delay(1000);
}