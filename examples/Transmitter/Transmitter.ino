/*!
 * @file Transmitter.ino
 *
 * In this example you can see how to use KMP_RS485 library.
 * The example presets using this device as a RS-485 transmitter.
 * When we sent some information with Serial port the program read it and send data to RS-485.
 *
 * Connection diagram will be different in most of cases. Mandatory is to be connected RE and DE together and link them to tePin.
 *
 * KMP Electronics invests time and resources providing this open source code,
 * please support KMP Electronics and open-source hardware by purchasing
 * products from KMP Electronics!
 *
 * Created: 09 May 2021
 * Written by Plamen Kovandzhiev for KMP Electronics Ltd. contact@kmpelectronics.eu
 * It is licensed under the MIT License, see LICENSE
 */

#include <KMP_RS485.h>

KMP_RS485 _rs485(Serial1, 3 /*tePin*/, 14 /*TX pin*/); // This configuration is liked with PRODINo MKR Zero you can change it to fit with your needs

void setup()
{
	Serial.begin(19200);

	_rs485.begin(19200); // Start RS-485 communication
}

void loop() {
	// Exit if data is not available
	if (!Serial.available()) {
		return;
	}
	
	String data = Serial.readString(); // Read data as string

	// Transmit data back
	_rs485.beginTransmission();
	_rs485.print(data);
	_rs485.endTransmission();
}