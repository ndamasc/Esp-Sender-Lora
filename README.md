## Water quality system project using Lora

This project aims to monitor water quality using the pH4502C sensor to measure water pH levels. The data is collected by an **ESP32 TBeam** and transmitted wirelessly using the **LoRa** protocol. Communication is carried out using the LoRa library from **Sandeep**. 
This repository is a part 1. The repository for the receiver microcontroller is here: [Esp-Receiver-Lora no GitHub](https://github.com/ndamasc/Esp-Receiver-Lora)

-------
## What do you need

- **PH4502C sensor**: Used to measure the pH of water.
- **DS18B20 sensor**: measure temperature. 
- **ESP32 TBeam**: Microcontroller responsible for collecting sensor data and communicating via LoRa.
- **LoRa**: Long-range wireless communication protocol used to send sensor data.
- **Sandeep LoRa Library**: Library used to facilitate communication via LoRa.

-------
## Requirements

- **ESP32 TBeam**
- **pH4502C sensor**
- **Resistors**: 1Kohm, 2Kohm, 4.7Kohm
- **Sandeep LoRa Library**
- Development environment: ESP32 T-Beam using VS Code IDE platform.

-------

## Functionality

- The pH4502C and ds18B20 sensors sends the all data to the ESP32 TBeam.
- The ESP32 TBeam transmits the pH data via LoRa to a receiver that can be connected to a monitoring system.
- The receiver can be configured to process and store the data or to display it in real time.
- In fact, I thought it would be very useful to send the parameters of the Lora protocol such as loss package, SNR and RSSI (last two I catch using sandeep lib)

-------

## Project structure

The project contains the code for:

1. **Readings**: The code obtains the pH and temperature values from the sensors connected to the ESP32 TBeam.
2. **Data transmission via LoRa**: Using Sandeep's LoRa library, the sensor data is sent via LoRa to a data receiver.
3. **Monitoring and Storage**: The received data can be processed or stored in flash memory in case of a package that couldn't be send.
4. Circuit diagram bellow:

<img src="https://github.com/user-attachments/assets/de97c8cb-4fde-4ede-be6c-89929403cf51" alt="circuit diagram" width="180">

Ps: there are needed 1 resistor for pull down in ds18b20
Ps2: it's important to add one resistor of 1Kohm and another resistor of 2Kohm on the exactly orded as shown on figure. 

-------

## Improvements

Feel free to make contributions! If you want to help with improvements or corrections, there are really nice sensors for measuring water quality as dissolved oxygen and turbidity sensors. :)

