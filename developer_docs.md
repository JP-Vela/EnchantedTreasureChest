# Developer Docs 🏴‍☠️

Enchanted Treasure Chest is a kid's pirate themed treasure chest. It uses an electronic lock trigger by an RFID keycard. This project is built around an **Arduino** using the mfrc522 to read the card and control a servo locking, as well as a motorized opening mechanism.

# Arrrrrduino Packages

 - SPI.h (Serial Communication Library used to communicate with RFID module)
 - MFRC522.h (RFID Reader Library)
 - Servo.h (Servo Library)
 

# Logic
![enter image description here](https://raw.githubusercontent.com/JP-Vela/EnchantedTreasureChest/master/logic_flowchart.png)


# Files

**4 Arduino sketches**

 1. lockTest (servo test)
 3. rfidLockTest (rfid reader test)
 4. linearActuatorTest (linear actuator test)
 5. **Main (everything put together)**
