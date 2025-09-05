# Smart_Guided_RFIDBot-ZOO
# Zoological Park Autonomous Smart Guide (ZooPAS Guide)

An autonomous self-driving vehicle system designed to enhance the visitor experience in large zoological parks by providing automated navigation, informational displays, and audio guides.

## 🚀 Features

- **Automated Navigation:** Follows a predefined path using RFID tags for localization.
- **Interactive Tour:** Stops automatically at designated animal zones.
- **Multi-modal Information:**
  - **Visual:** LCD display shows facts about the current exhibit.
  - **Auditory:** Audio narration provides a rich, guided experience.
- **Visitor Management:** Audible siren alerts visitors 5 minutes before departure from a stop.
- **Emergency System:** Integrated emergency button triggers a siren and alerts park staff.

## 🛠️ Hardware & Components

The system is built using the following components:
- **Microcontroller:** Arduino Uno
- **Navigation:** RFID Reader (e.g., RC522) + Passive RFID Tags
- **Motility:** Chassis Kit, DC Motors, Motor Driver (e.g., L298N)
- **User Interface:** 16x2 LCD with I2C Module, Buzzer, Push Button
- **Power:** 9V Battery
- **Connectivity:** Bluetooth Module (HC-05) for potential future expansion

## 🚦 Usage

1.  Place the "START" RFID tag at the beginning of the track.
2.  Power on the vehicle.
3.  The vehicle will begin moving forward.
4.  It will stop at each subsequent tag, display info, play audio, and wait for a set duration.
5.  Press the emergency button at any time to trigger an alert.



