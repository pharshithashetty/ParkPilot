# 🚗 ParkPilot - Automated Parking System 🚦

Welcome to **ParkPilot**, an Arduino-based automated parking system that manages entry and exit gates while keeping track of available parking slots. This project uses IR sensors, servos, and an LCD display to provide a seamless parking experience.

## 📂 Project Structure

- **`2gate2sensor.ino`**: Main program for managing parking slots and gate operations.
- **`finalpark.ino`**: Alternate implementation with additional LCD messages for full and empty parking states.

## 🛠️ Features

- 🚪 **Automated Entry and Exit Gates**: Controlled by servos and IR sensors.
- 📊 **Real-Time Slot Tracking**: Displays available parking slots on an LCD.
- 🔄 **Dynamic Updates**: Automatically updates the LCD display when cars enter or exit.
- ⚠️ **Full Parking Alerts**: Notifies when parking is full.
- 🅿️ **Empty Parking Alerts**: Notifies when parking is empty.

## 🧰 Hardware Requirements

- Arduino board
- 2 IR sensors
- 2 Servo motors
- LiquidCrystal_I2C LCD (16x2)
- Jumper wires
- Breadboard

## 🚀 Getting Started

1. Connect the hardware components as per the pin configuration in the code.
2. Upload either `2gate2sensor.ino` or `finalpark.ino` to your Arduino board.
3. Monitor the serial output for debugging and observe the LCD for parking updates.

## 📜 Code Highlights

### Pin Configuration
- **IR Sensors**: Entry sensor on pin `2`, Exit sensor on pin `4`.
- **Servos**: Entry gate servo on pin `3`, Exit gate servo on pin `5`.

### LCD Display
- Address: `0x27`
- Displays parking slot availability dynamically.

## 🖼️ Demo

### LCD Display States
- **Parking Full**: `"Parking Full! Wait for exit."`
- **Parking Empty**: `"Parking Empty! Please Enter."`

### Serial Output
- `"Car Entered. Slots available: X"`
- `"Car Exited. Slots available: X"`

## 📧 Contact

Feel free to reach out for questions or suggestions! 🚀

Happy Parking! 🅿️