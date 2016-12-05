### SparkFun RHT03 Particle Library

A firmware library for the SparkFun's [RHT03](https://www.sparkfun.com/products/10167) humidity and temperaure sensor.

[![RHT03](https://cdn.sparkfun.com//assets/parts/4/4/7/2/10167-01.jpg)](https://www.sparkfun.com/products/10167)
About
-------------------

The RHT03 is a one-wire digital sensor that measures relative humidity from 0-100% and temperature from -40-80 deg C.

Repository Contents
-------------------

* **/firmware** - Source files for the library (.cpp, .h).
* **/firmware/examples** - Example sketches for the library (.cpp). Run these from the Particle IDE. 
* **spark.json** - General library properties for the Particle library manager. 

Example Usage
-------------------

#### Create an RHT03 Object & Initialize

To begin, create an RHT03 class object. This'll often go in the global section of the code:

	///////////////////////////
	// RHT03 Object Creation //
	///////////////////////////
	RHT03 rht; // This creates a RTH03 object, which we'll use to interact with the sensor

To initialize the sensor, call the `begin([pin])` function, where `[pin]` is the Photon pin connected to the RHT03 data pin.

	void setup()
	{
		...
		rht.begin(D3); // Initialize an RHT03 sensor, with the data pin connected to D3.
		...
	}

#### Update and Read Humidity and Temp Values

Temperature and humidity values are updated in one fell single-wire swoop. To get new values from the sensor, call `update()`. `update()` returns either 1 on success, or a negative value if it fails.

	int updateRet = rht.update();

If the update succeeds, use the `humidity()`, `tempC()`, and `tempF()` functions to get relative humidity, celsius, and farenheit temperatures. All variables are returned as `float`'s.

	if (updateRet == 1)
	{
		float rh = rht.humidity();
		float tf = rht.tempF();
		float tc = rht.tempC();
	}

Recommended Components
-------------------

* [RHT03 Humidity & Temperature Sensor](https://www.sparkfun.com/products/10167)
* [Particle Photon](https://www.sparkfun.com/products/13345) or [SparkFun Photon RedBoard](https://www.sparkfun.com/products/13321)

License Information
-------------------

This product is _**open source**_! 

Please review the LICENSE.md file for license information. 

If you have any questions or concerns on licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.