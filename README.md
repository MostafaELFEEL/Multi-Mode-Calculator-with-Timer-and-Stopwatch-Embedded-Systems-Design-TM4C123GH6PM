# Multi-Mode Calculator with Timer and Stopwatch | Embedded Systems Design (TM4C123GH6PM)

This project demonstrates the design and implementation of a multi-mode calculator with additional timer and stopwatch features, using the **TM4C123GH6PM microcontroller**. The project integrates basic calculator operations along with real-time timing functionalities, all controlled via hardware.

## Project Objectives
- Design a multi-mode calculator using the **TM4C123GH6PM** microcontroller.
- Implement basic calculator functions (addition, subtraction, multiplication, division).
- Incorporate separate timer and stopwatch functionalities using hardware.
- Use **UART communication** to display modes and results on the **PUTTY** serial monitor.

## Features
1. **Calculator Mode**
   - Input two multi-digit numbers via a keypad and perform operations (addition, subtraction, multiplication, division).
   - Results and inputs are displayed on the PUTTY serial monitor using UART communication.

2. **Timer Mode**
   - Users can set a countdown timer via the keypad, displayed on the PUTTY serial monitor.
   - The timer can be started, paused, and reset using the keypad, with a buzzer sounding when the countdown reaches zero.

3. **Stopwatch Mode**
   - Start, pause, and reset the stopwatch with specific keys on the keypad.
   - The elapsed time is displayed in real-time on the PUTTY serial monitor.

## Keypad Connections
- The 4x4 keypad is connected as follows:
  - **PB2 to PB5**: Output pins for rows.
  - **PE0 to PE3**: Input pins for columns.
- Keypad wires are connected from **left to right**.

## Technologies Used
- **TM4C123GH6PM microcontroller**
- **GPIO** for keypad control.
- **Timers** for managing stopwatch and countdown timer.
- **Interrupts** for handling timers and UART.
- **UART communication** to display outputs and switch between modes via the **PUTTY** serial monitor.

## Video Demonstration
[Watch the project demo video here](https://youtu.be/gBvxX-iDDLU?si=FzSMhQaSHLkOLjER)

## How to Use
1. Upload the code to your **TM4C123GH6PM** microcontroller.
2. Use the keypad to input numbers and navigate between modes (Calculator, Timer, Stopwatch).
3. View the results and mode changes in real-time on the PUTTY serial monitor.
