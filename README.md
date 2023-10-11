# ESP32

# ESP32 Web Server with Remote Control App Documentation

## Overview

This project demonstrates how to create a web server using the ESP32 microcontroller that allows remote control of an LED. The server serves a webpage allowing users to input the ESP32's IP address in a text box and submit it. After submission, a button is provided to toggle the LED connected to pin 2. The project uses the **WiFi** library to connect to a Wi-Fi network and the **ESPAsyncWebServer** library to handle asynchronous HTTP requests.

Additionally, a remote control app can be built (not included in this document) that inputs the ESP32's IP address in a text box and provides a button to toggle the LED remotely.

## Prerequisites

### Hardware

- ESP32 microcontroller
- LED connected to pin 2

### Software

- Arduino IDE installed
- ESP32 board support installed in the Arduino IDE
- Mobile app development environment (for building the remote control app)

## Code Explanation

### Libraries Used

- **WiFi:** Enables the ESP32 to connect to a Wi-Fi network.
- **ESPAsyncWebServer:** Allows handling HTTP requests asynchronously.

### Constants

- `ssid`: Your Wi-Fi network name.
- `password`: Your Wi-Fi network password.

### HTML Page

A simple HTML page includes an input field for the IP address and a button to toggle the LED. When the user enters the ESP32's IP address and clicks the button, an XMLHttpRequest is sent to the `/toggle` endpoint, toggling the LED state.

### Setup

1. **Serial Communication:** Initializes serial communication with a baud rate of 115200.
2. **Wi-Fi Connection:** Configures the ESP32 to connect to the specified Wi-Fi network.
3. **Web Server Routes:**
   - `/`: Handles requests to the root URL. Responds with the HTML page.
   - `/toggle`: Toggles the state of the LED connected to pin 2. Responds with "LED Toggled".
4. **Web Server Start:** Begins the web server on port 80.

### Loop

The `loop()` function is empty as the web server operates asynchronously and does not require constant looping.

## Usage

1. **Upload the Code:** Upload the code to your ESP32 board using the Arduino IDE.
2. **Access the Web Server:**
   - After uploading, open the Serial Monitor. The ESP32 will print dots until it successfully connects to the Wi-Fi network.
   - Once connected, the ESP32's IP address will be printed in the Serial Monitor.
   - Build a remote control app (not included in this document) that includes a text input field for the IP address and a button to toggle the LED.
   - Enter the ESP32's IP address in the app and click the button to toggle the LED remotely.

## Important Notes

- Ensure you have the correct Wi-Fi credentials in the `ssid` and `password` variables.
- Implement the remote control app separately, ensuring it sends a GET request to the `/toggle` endpoint with the ESP32's IP address for remote LED control.
- Modify the HTML content and web server routes as needed to suit your project requirements.

## Contributors

- Restan V. Requina
