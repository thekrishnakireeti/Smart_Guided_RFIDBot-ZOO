#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

// Pin definitions
#define SS_PIN 10
#define RST_PIN 9
#define BUTTON_PIN A1
#define BUZZER_PIN A0

// Motor control pins
const int a = 1;
const int b = 2;
const int c = 3;
const int d = 4;
const int en1 = 7;
const int en2 = 8;

// RFID card UIDs (replace with your actual card UIDs)
const String START_CARD = "63 DB C9 2E";
const String TIGER_CARD = "73 4C 98 2E";
const String DEER_CARD = "0C A0 AA 81";
const String LION_CARD = "EC F8 6E 81";

// Objects
LiquidCrystal_I2C lcd(0x27, 20, 4); 
SoftwareSerial bt(5, 6);
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Variables
int buttonState = 0;
bool emergencyTriggered = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Show your Card");

  // Initialize SPI and RFID
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  
  // Initialize LCD
  lcd.init();                     
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("HELLO WORLD");
  
  // Initialize pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  
  // Initialize Bluetooth
  bt.begin(9600);

  // Stop motors initially
  stopMotors();
  
  delay(1000);
}

void loop() {
  checkEmergencyButton();
  checkRFID();
}

void checkEmergencyButton() {
  buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState == LOW && !emergencyTriggered) { // Button pressed (LOW due to INPUT_PULLUP)
    emergencyTriggered = true;
    triggerEmergency();
  } else if (buttonState == HIGH) {
    emergencyTriggered = false;
  }
}

void triggerEmergency() {
  bt.println("\ncall\n"); // Send emergency call command via Bluetooth
  lcd.clear();
  lcd.print("EMERGENCY CALL");
  digitalWrite(BUZZER_PIN, HIGH);
  delay(5000);
  lcd.clear();
  digitalWrite(BUZZER_PIN, LOW);
  delay(1000);
}

void checkRFID() {
  // Check for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Read the card
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Get card UID
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  
  Serial.print("UID tag: ");
  Serial.println(content.substring(1));
  
  // Check against known cards
  String cardUID = content.substring(1);
  
  if (cardUID == START_CARD) {
    handleStartCard();
  } else if (cardUID == TIGER_CARD) {
    handleTigerCard();
  } else if (cardUID == DEER_CARD) {
    handleDeerCard();
  } else if (cardUID == LION_CARD) {
    handleLionCard();
  } else {
    handleUnknownCard();
  }
  
  // Halt PICC and stop encryption
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void handleStartCard() {
  Serial.println("Start bot:");
  lcd.clear();
  lcd.print("START");
  moveForward();
  delay(1000);
  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.print("WELCOME");
}

void handleTigerCard() {
  Serial.println("Tiger Zone:");
  lcd.clear();
  lcd.print("TIGER ZONE");
  stopMotors();
  delay(15000);
  lcd.clear();
  lcd.print("HURRY!!!");
  digitalWrite(BUZZER_PIN, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("READY TO START");
  delay(5000);
  lcd.clear();
  digitalWrite(BUZZER_PIN, LOW);
  moveForward();
  delay(1000);
  lcd.setCursor(4, 1);
  lcd.print("WELCOME");
}

void handleDeerCard() {
  Serial.println("Deer Zone:");
  lcd.clear();
  lcd.print("DEER ZONE");
  stopMotors();
  delay(15000);
  lcd.clear();
  lcd.print("HURRY!!!");
  digitalWrite(BUZZER_PIN, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("READY TO START");
  delay(5000);
  lcd.clear();
  digitalWrite(BUZZER_PIN, LOW);
  moveForward();
  delay(1000);
  lcd.setCursor(4, 1);
  lcd.print("WELCOME");
}

void handleLionCard() {
  Serial.println("Lion Zone:");
  lcd.clear();
  lcd.print("LION ZONE");
  stopMotors();
  delay(15000);
  digitalWrite(BUZZER_PIN, HIGH);
  lcd.clear();
  lcd.print("BOT READY TO START");
  delay(5000);
  digitalWrite(BUZZER_PIN, LOW);
  moveForward();
  delay(1000);
}

void handleUnknownCard() {
  Serial.println("Access denied");
  Serial.println("Wrong Card!");
  Serial.println("Will not open the Gate");
  lcd.clear();
  lcd.print("ACCESS DENIED");
  stopMotors();
  delay(2000);
  lcd.clear();
}

void moveForward() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
}

void stopMotors() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
}
