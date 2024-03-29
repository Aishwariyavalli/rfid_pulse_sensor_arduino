# rfid_pulse_sensor_arduino
RFID enabled health (pulse) monitoring and save data to cloud

# Hardware Requirements:
1. Aruduino R3 micro controller board
2. RFID Kit Mifare RC522 RFID Reader Module with S50 White Card and Key Ring
3. Pulse rate sensor Module
4. ESP8266 (ESP-01) Module
3. Jumper wires

# Software Requirements:
1. Arduino IDE - https://www.arduino.cc/en/Main/Software
2. Thingspeak.com account & channel API key to send the data

# Pulse rate sensor to Arduino
Connect Pulse Sensor to Arduino Uno Board as following :

[+] to +5V

[-] to GND

[S] tO A0

# RFID connection to Arduino
Pin	Wiring to Arduino Uno

[SDA]	   to       Digital 10

[SCK]	   to      Digital 13

[MOSI]	 to       Digital 11

[MISO]	 to       Digital 12

[IRQ]	   to       unconnected

[GND]	    to      GND

[RST]	    to      Digital 9

[3.3V]	   to     3.3V

# Caution: You must power this device to 3.3V! 5V will fry the components!!!!!

Download the code, compile & verify in Arduino IDE and upload it to the board.

# ESP8266 connection to Arduino

ESP8266:-------------- >Arduino:

GND -------------------------- GND

GPIO-2 -------------------------- Not connected (open)

GPIO-0 -------------------------- GND

RXD -------------------------- RX

TXD -------------------------- TX

CHPD ------------------------ 3.3V

RST -------------------------- Not connected (open) *(Read Below Instruction)

VCC -------------------------- 3.3V
