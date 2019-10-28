# rfid_pulse_sensor_arduino
RFID enabled health (pulse) monitoring

# Hardware Requirements:
1. Aruduino R3 micro controller board
2. RFID Kit Mifare RC522 RFID Reader Module with S50 White Card and Key Ring
3. Pulse rate sensor module
3. Jumper wires
4. Bread Board

# Software Requirements:
1. Arduino IDE - https://www.arduino.cc/en/Main/Software

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
