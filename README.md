# PC-Based Data Acquisition System with Fault Alerts Using LPC2148
## Project Overview
This project implements a **real-time temperature data acquisition system** using the **ARM7 LPC2148 microcontroller**. It reads temperature data from an **LM35 sensor**,
timestamps it using the **on-chip RTC**, and sends it to a PC via **UART communication**. 
If the temperature exceeds a defined threshold, the system triggers a **fault alert** using an LED or buzzer.
Additionally, it features a **Time Edit Mode** that allows the user to set or update the system time using a **4x4 keypad**, 
triggered by an **external interrupt pin**.

## Hardware Requirements
- LPC2148 Development Board  
- LM35 Temperature Sensor  
- 16x2 LCD Display  
- 4x4 Keypad  
- Push Button (for Edit Mode via Interrupt)  
- LED or Buzzer (for fault indication)  
- MAX232 (for UART PC communication)  
- Power Supply  
## Software Requirements
- **Embedded C (Keil µVision IDE)**  
- **Flash Magic** (for programming LPC2148)  
- **Proteus** (for circuit simulation and testing)
## System Workflow
1. **Initialization**:
   - UART setup for serial communication.
   - RTC start-up (default or last saved time).
   - ADC setup for temperature reading.
   - LCD and Keypad initialized.
   - External interrupt enabled for Time Edit Mode.

2. **Normal Operation**:
   - Continuously reads temperature from LM35 via ADC.
   - Reads current timestamp from RTC.
   - Displays time, date, and temperature on LCD.
   - Sends formatted data to PC over UART:
     - `[INFO] Temp: 32.5°C @ 13:45:20 16/06/2025`
   - If temperature > 45°C:
     - Sends alert over UART:
       - `[ALERT] Temp: 47.3°C @ 14:10:55 16/06/2026 - OVER TEMP!`
     - Activates buzzer or LED.

3. **Time Edit Mode** (Triggered by External Interrupt):
   - When the button is pressed, system sets `edit_flag = 1
   - LCD displays :Enter PIN
   - LCD displays editable options
     1.H 2.M 3.S 4.D
     5.M 6.Y 7.Day 8.E
   - User enters values using keypad.
   - Updated values are written to RTC registers
## LCD Display Format
**Normal Mode:**
HH:MM:SS DAY
DD/MM/YY T: XX°c
**Time Edit Mode Menu:**
1.H 2.M 3.S 4.D
5.M 6.Y 7.Day 8.M

## UART Serial Output

- **Normal Data:**  
  `[INFO] Temp: 32.5°C @ 13:45:20 16/06/2025`

- **Over Temperature Alert:**  
  `[ALERT] Temp: 47.3°C @ 14:10:55 16/06/2025 - OVER TEMP!`

 **While Editing Time:**  
  `*** Time Editing Mode Activated ***`
## Simulation
Simulation is built and tested in **Proteus**, which includes:
- LPC2148 with connected peripherals.
- UART interface to Virtual Terminal.
- Real-time temperature variation and alert triggering.
- Keypad input to change system time dynamically.
