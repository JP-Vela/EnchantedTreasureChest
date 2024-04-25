# Enchanted Treasure Chest! 🏴‍☠️

Enchanted Treasure Chest is a kid's pirate themed treasure chest. It uses an electronic lock trigger by an RFID keycard. This project is built around an **Arduino** using the mfrc522 to read the card and control a servo locking, as well as a motorized opening mechanism.

# Arduino Packages

 - SPI.h (Serial Communication Library used to communicate with RFID module)
 - MFRC522.h (RFID Reader Library)
 - Servo.h (Servo Library)
 
# Electronics

 - Arduino Mega
 - MFRC522 RFID Reader
 - L9110S DC Motor Driver
 - SG90 Micro Servo
 - NORJIN 12v Linear Actuator
 - 12v 1.5a Power Supply

# Circuit Diagram
![enter image description here](https://raw.githubusercontent.com/JP-Vela/EnchantedTreasureChest/master/circuit_diagram.png)

# Note About Circuit Diagram

 - The above circuit diagram does not match the match the pins used in the code.
 - If using Arduino UNO the SPI pins will be in a different place comared to the Arduino Mega. See [this diagram](https://www.circuitbasics.com/wp-content/uploads/2020/04/arduino-spi-tutorial-uno-pins.png) for SPI pin location.
 - Servo motor should be powered by the Arduinno 5v pin instead of the breadboard power rail.
 - The breadboard power rail should be powered using the 12v power supply
 - The Arduino should be powered by the breadboard power rail



# Logic
![enter image description here](https://raw.githubusercontent.com/JP-Vela/EnchantedTreasureChest/master/logic_flowchart.png)


# Files

**4 Arduino sketches**

 1. lockTest (servo test)
 3. rfidLockTest (rfid reader test)
 4. linearActuatorTest (linear actuator test)
 5. **Main (everything put together)**
