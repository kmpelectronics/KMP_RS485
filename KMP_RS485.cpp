/*!
 * @file KMP_RS485.cpp
 *
 * This library supports KMP Electronics boards includes RS485.
 * For simplicity we used only one pin for manipulation RE and DE pins
 * Pin maping:
 *  RS485 | Board
 *  -------------
 *     RO | RX
 *     RE | Transmit enabled connected with DE
 *     DE | Transmit enabled connected with RE
 *     DI | TX
 * 
 * This library can work with every Arduino device and KMP Electronics use it together its devices:
 * ----> https://kmpelectronics.eu/products/prodino-wifi-esp-wroom-02-v1/
 * ----> https://kmpelectronics.eu/products/prodino-mkr-zero-v1/
 * ----> https://kmpelectronics.eu/products/prodino-esp32-v1/
 *
 * This is an Arduino library which allows you send and receieve data using RS-485 protocol.
 * 
 * KMP Electronics invests time and resources providing this open source code,
 *     please support KMP Electronics and open-source hardware by purchasing
 *     products from KMP Electronics!
 *
 * Written by Plamen Kovandzhiev for KMP Electronics Ltd. contact@kmpelectronics.eu
 * It is licensed under the MIT License, see LICENSE.txt.
 */

#include "KMP_RS485.h"

KMP_RS485::KMP_RS485(HardwareSerial& hwSerial, int tePin, int txPin, int teLevel) :
	_serial(&hwSerial),
	_tePin(tePin),
	_txPin(txPin),
	_startTransmission(false) 
{ 
	_teLevelHigh = teLevel;
	_teLevelLow = teLevel == LOW ? HIGH : LOW ;
}

void KMP_RS485::begin(unsigned long baudrate)
{
	begin(baudrate, SERIAL_8N1);
}

void KMP_RS485::begin(unsigned long baudrate, uint16_t config)
{
	_baudrate = baudrate;
	_config = config;

	pinMode(_tePin, OUTPUT);
	digitalWrite(_tePin, _teLevelLow);

	_startTransmission = false;

	beginSerial(baudrate, config);
}

void KMP_RS485::end()
{
	_serial->end();

	digitalWrite(_tePin, LOW);
	pinMode(_tePin, INPUT);
}

int KMP_RS485::available()
{
	return _serial->available();
}

int KMP_RS485::peek()
{
	return _serial->peek();
}

int KMP_RS485::read()
{
	return _serial->read();
}

void KMP_RS485::flush()
{
	return _serial->flush();
}

size_t KMP_RS485::write(byte b)
{
	if (!_startTransmission) {
		setWriteError();
		return 0;
	}

	return _serial->write(b);
}

KMP_RS485::operator bool()
{
	return true;
}

void KMP_RS485::beginTransmission()
{
	digitalWrite(_tePin, _teLevelHigh);
	delayMicroseconds(50);

	_startTransmission = true;
}

void KMP_RS485::endTransmission()
{
	_serial->flush();

	delayMicroseconds(50);
	digitalWrite(_tePin, _teLevelLow);

	_startTransmission = false;
}

void KMP_RS485::receive()
{
	digitalWrite(_tePin, _teLevelLow);
}

void KMP_RS485::noReceive()
{
	digitalWrite(_tePin, _teLevelHigh);
}

void KMP_RS485::sendBreak(unsigned int duration, bool isMilliseconds)
{
	_serial->flush();
	_serial->end();

	pinMode(_txPin, OUTPUT);
	digitalWrite(_txPin, LOW);
	
	if (isMilliseconds)	{
		delay(duration);
	}
	else {
		delayMicroseconds(duration);
	}
	
	beginSerial(_baudrate, _config);
}

void KMP_RS485::sendBreak(unsigned int duration)
{
	sendBreak(duration, true);
}

void KMP_RS485::sendBreakMicroseconds(unsigned int duration)
{
	sendBreak(duration, false);
}

void KMP_RS485::beginSerial(unsigned long baudrate, uint16_t config)
{
#ifdef ESP8266
	SerialConfig serialConfig = static_cast<SerialConfig>(config);
	_serial->begin(baudrate, serialConfig);
#else
	_serial->begin(baudrate, config);
#endif
}