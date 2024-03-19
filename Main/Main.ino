#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#define RST_PIN         5          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
String tagID = "nothing";
String lockID1 = "C9F24FB3";
String lockID2 = "8A72D86";

Servo myservo;  // create servo object to control a servo
int motorA = 2;
int motorB = 3;

int pos = 0;    // variable to store the servo position
bool opened = false;
int timeToOpen= 30000; //millisecods

void setup() {
  Serial.begin(115200);                       // Initialize serial communications with the PC
  myservo.attach(9);                          // attaches the servo on pin 9 to the servo object
  myservo.write(pos);
  while (!Serial);                       // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();                             // Init SPI bus
  mfrc522.PCD_Init();              // Init MFRC522
  delay(4);                                             // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();      // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}


void OpenLid() {
  //Unlock
  pos = 90;
  myservo.write(pos);

  digitalWrite(motorA, HIGH);
  digitalWrite(motorB, LOW);
  delay(timeToOpen);
  digitalWrite(motorA, LOW);
  digitalWrite(motorB, LOW);
}

void CLoseLid() {
  digitalWrite(motorA, LOW);
  digitalWrite(motorB, HIGH);
  delay(timeToOpen);
  digitalWrite(motorA, LOW);
  digitalWrite(motorB, LOW);

  //Lock
  pos = 0;
  myservo.write(pos);
}


void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
              return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
              return;
  }
  // Dump debug info about the card; PICC_HaltA() is automatically called
  tagID = "";
  // Read the 4 byte UID
  for ( uint8_t i = 0; i < 4; i++)
  {
    //readCard[i] = mfrc522.uid.uidByte[i];
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Convert the UID to a single String
  }



  //Actually check tag
  tagID.toUpperCase();
  if (tagID == lockID1 || tagID == lockID2){

    //Close chest
    if (opened){
      Serial.println("Locking!");
      CloseLid();
    }
    
    //Open chest
    else {
      Serial.println("Unlocking!");
      OpenLid();
    }
    
    opened = !opened;
    
    delay(2000);
  } else {
    Serial.println("Access denied!");
    delay(1000);
  }


  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  Serial.println(tagID);
}