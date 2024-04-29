/*
 * RFID Example Used: https://circuitdigest.com/microcontroller-projects/interfacing-rfid-reader-module-with-arduino
 */

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#define RST_PIN         5          // Configurable
#define SS_PIN          53         // Configurable
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance (RFID Reader)
String tagID = "nothing";
String lockID1 = "C9F24FB3";
String lockID2 = "8A72D86";

Servo myservo;  // create servo object to control a servo

// Digital pins assigned to the same motor
// Left HIGH Right LOW  moves actuator forward
// Left LOW Right HIGH  moves actuator backwards
// Left LOW Right LOW  stops actuator
int motorLeftPin = 2;
int motorRightPin = 3;

int pos = 180;  // variable to store the servo position
bool opened = true;
int timeToOpen= 29000; //milliseconds

void setup() {
  Serial.begin(115200);                   // Initialize serial communications with the PC
  myservo.attach(9);                      // attaches the servo on pin 9 to the servo object
  myservo.write(pos);
  while (!Serial);                        // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();                            // Init SPI bus
  mfrc522.PCD_Init();                     // Init MFRC522
  delay(4);                               // Wait for MFRC522 to initialize
  mfrc522.PCD_DumpVersionToSerial();

  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  pinMode(motorLeftPin, OUTPUT);
  pinMode(motorRightPin, OUTPUT);
}


void OpenLid() {
  //Unlock
  pos = 60;
  myservo.write(pos);

  // Move actuator forward
  digitalWrite(motorLeftPin, HIGH);
  digitalWrite(motorRightPin, LOW);
  delay(timeToOpen);

  // Stop actuator
  digitalWrite(motorLeftPin, LOW);
}

void CloseLid() {
  
  // Move actuator backwards
  digitalWrite(motorLeftPin, LOW);
  digitalWrite(motorRightPin, HIGH);
  delay(timeToOpen);

  // Stop actuator
  digitalWrite(motorRightPin, LOW);

  //Lock
  pos = 180;
  myservo.write(pos);
}


void loop() {
  // Reset the loop if no new card present on the sensor/reader
  if(!mfrc522.PICC_IsNewCardPresent()) {
              return;
  }
  // At this point it is safe to assume a card is present
  // Read the data on the present card
  if (!mfrc522.PICC_ReadCardSerial()) {
              return;
  }

  // Dump debug info about the card
  tagID = "";

  // Read the 4 byte UID
  for ( uint8_t i = 0; i < 4; i++)
  {
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Convert the UID to a single String from array
  }



  // Make tag upper case
  tagID.toUpperCase();

  //Check for the two existing keys
  if (tagID == lockID1 || tagID == lockID2){

    //Close chest
    if (opened){
      Serial.println("Closing!");
      CloseLid();
    }
    
    //Open chest
    else {
      Serial.println("Opening!");
      OpenLid();
    }
    
    //Toggle the current state
    opened = !opened;
    
  } else {
    Serial.println("Access denied!");
    delay(1000);
  }


  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  Serial.println(tagID);
}