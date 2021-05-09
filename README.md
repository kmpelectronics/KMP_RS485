# KMP_RS485
## Description
This is an Arduino library which allows you send and receive data using [RS-485](https://en.wikipedia.org/wiki/RS-485) protocol. With RS232 to RS485 chip you can communicate with every RS485 device.
The library supports all [KMP Electronics](https://kmpelectronics.eu/) boards which includes RS485 and every Arduino RS485 device with a similar pin mapping.

For simplicity we used only one pin for manipulation **RE** and **DE** pins we name it **T**ransmission **E**nable pin. Pin mapping:

| RS485 | Board |
|-------|-------|
| RO | RX |
| RE | Transmit enabled connected with DE |
| DE | Transmit enabled connected with RE |
| DI | TX |

We have been using this library together with our devices:

- [PRODINo WIFI-ESP WROOM-02](https://kmpelectronics.eu/products/prodino-wifi-esp-wroom-02-v1/)
- [PRODINo MKR Zero](https://kmpelectronics.eu/products/prodino-mkr-zero-v1/)
- [PRODINo ESP32](https://kmpelectronics.eu/products/prodino-esp32-v1/)

## Installation
Open **Arduino IDE**. From menu selects Sketch -> Include Library -> Manage libraries. In **Library Manager** searches for "KMP_RS485" and install the library.

## Examples
With this library we provide following examples:
- [Echo](https://github.com/kmpelectronics/KMP_RS485/blob/main/examples/Echo/Echo.ino). The example presets using this device as a RS-485 repeater. When the device received the data then collected it and transmit it back.
- [Transmitter](https://github.com/kmpelectronics/KMP_RS485/blob/main/examples/Transmitter/Transmitter.ino). The example presets using this device as a RS-485 transmitter. When we sent some information with Serial port the program read it and send data to RS-485.
- [Receiver](https://github.com/kmpelectronics/KMP_RS485/blob/main/examples/Receiver/Receiver.ino). The example presets using this device as a RS-485 receiver. When the device receive data from RS-485 it gets it and print on Serial port.

`KMP Electronics` invests time and resources providing this open source code, please support KMP Electronics and open-source hardware by purchasing products from [KMP Electronics](https://kmpelectronics.eu/)!

## License
This project is licensed under the MIT License, see [LICENSE](https://github.com/kmpelectronics/KMP_RS485/blob/main/LICENSE) for further information.