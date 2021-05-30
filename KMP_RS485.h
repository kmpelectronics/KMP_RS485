/*!
 * @file KMP_RS485.h
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

#ifndef KMP_RS485_H
#define KMP_RS485_H

#include <Arduino.h>

class KMP_RS485 : public Stream {
public:
#ifdef ESP32
	/*!
	 * @brief Crate an instance of KMP_RS485 with TX break control
	 * @param hwSerial Serial port which is connected with RS485 chip
	 * @param tePin Transmit enable pin
	 * @param txPin Serial port TX pin
	 * @param rxPin Serial port RX pin. Optional. Default is -1 not used.
	 * @param teLevel Transmission enable level. Default is HIGH. Values: HIGH, LOW
	 */
	KMP_RS485(HardwareSerial& hwSerial, int tePin, int txPin, int rxPin, int teLevel = HIGH);
#else
	/*!
	 * @brief Crate an instance of KMP_RS485 with TX break control
	 * @param hwSerial Serial port which is connected with RS485 chip
	 * @param tePin Transmit enable pin
	 * @param txPin Serial port TX pin
	 * @param teLevel Transmission enable level. Default is HIGH. Values: HIGH, LOW
	 */
	KMP_RS485(HardwareSerial& hwSerial, int tePin, int txPin, int teLevel = HIGH);
#endif
	/*!
	 * @brief Start RS485 connection
	 * @param baud Speed. Values: 75, 110, 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 and etc. bit/s
	 */
	virtual void begin(unsigned long baudrate);

	/*!
	 * @brief Start RS485 connection
	 * @param baud Speed. Values: 75, 110, 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 and etc. bit/s
	 * @param config Configuration - data bits, parity, stop bits. Values: SERIAL_5N1, SERIAL_6N1, SERIAL_7N1, SERIAL_8N1, SERIAL_5N2, SERIAL_6N2,
	 *               SERIAL_7N2, SERIAL_8N2, SERIAL_5E1, SERIAL_6E1, SERIAL_7E1, SERIAL_8E1, SERIAL_5E2, SERIAL_6E2, SERIAL_7E2, SERIAL_8E2,
	 *               SERIAL_5O1, SERIAL_6O1, SERIAL_7O1, SERIAL_8O1, SERIAL_5O2, SERIAL_6O2, SERIAL_7O2, SERIAL_8O2
	 */
	virtual void begin(unsigned long baudrate, uint16_t config);

	/*!
	 * @brief End RS485 connection
	 */
	virtual void end();

	/*!
	 * @brief Get the number of bytes (characters) available for reading from the RS485 port. This is data that's already arrived and stored in the serial receive buffer
	 * @return The number of bytes available to read
	 */
	virtual int available();

	/*!
	 * @brief Returns the next byte (character) of incoming serial data without removing it from the internal serial buffer. 
	 *        That is, successive calls to peek() will return the same character, as will the next call to read()
	 * @return The first byte of incoming serial data available (or -1 if no data is available)
	 */
	virtual int peek();

	/*!
	 * @brief Reads incoming RS485 data
	 * @return The first byte of incoming serial data available (or -1 if no data is available)
	 */
	virtual int read();

	/*!
	 * @brief Waits for the transmission of outgoing serial data to complete
	 */
	virtual void flush();

	/*!
	 * @brief Writes binary data to the serial port. This data is sent as a byte or series of bytes
	 * @return It will return the number of bytes written, though reading that number is optional
	 */
	virtual size_t write(byte b);

	using Print::write; // write(str) and write(buf, size)
	virtual operator bool();

	/*!
	 * @brief Enables transmission, it must be called before write(...), print(...) to send data
	 */
	void beginTransmission();

	/*!
	 * @brief Desables transmission
	 */
	void endTransmission();

	/*!
	 * @brief Enables reception. It is not mandatory by default receive is enabled
	 */
	void receive();

	/*!
	 * @brief Disables reception. It is not mandatory by default receive is enabled and not need to be disabled
	 */
	void noReceive();

	/*!
	 * @brief Sends a serial break signal for the specified duration in milliseconds
	 * @param duration duration of the break signal in milliseconds
	 */
	void sendBreak(unsigned int duration);

	/*!
	 * @brief Sends a serial break signal for the specified duration in microseconds
	 * @param duration duration of the break signal in milliseconds
	 */
	void sendBreakMicroseconds(unsigned int duration);

private:
	HardwareSerial* _serial;
	int _tePin;
	int _txPin;
#ifdef ESP32
	int _rxPin;
	uint32_t _txPinFlushDelayINuS;
#endif
	int _teLevelHigh;
	int _teLevelLow;

	unsigned long _baudrate;
	uint16_t _config;
	bool _startTransmission;

	void sendBreak(unsigned int duration, bool isMilliseconds);
	void beginSerial(unsigned long baudrate, uint16_t config);
};

#endif
