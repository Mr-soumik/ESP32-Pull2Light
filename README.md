# 💡 ESP32 Pull2Light — Interactive IoT Smart Lamp Switch

An all-in-one IoT smart switch project that transforms your mobile browser into an interactive, animated bedside lamp with a virtual pull-chain cord. Tapping or dragging the pull chain on your smartphone screen animates the lamp UI and triggers an ESP32 micro-webserver to toggle an AC relay, switching your real room light on or off with zero external cloud dependencies.

![Platform](https://img.shields.io/badge/Platform-ESP32-blue?style=flat-square)
![Framework](https://img.shields.io/badge/Framework-Arduino%20C%2B%2B-orange?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)

## Connect with TechTadka360💝👇

- YouTube: [@techtadka360official](https://youtube.com/@techtadka360official?si=GdlIntZKv30kPgBk)
- Instagram: [@techtadka360official](https://www.instagram.com/techtadka360official?igsh=cWR4bnhjdWw1MHdh)
- Facebook: [TechTadka360](https://www.facebook.com/share/1EkKAJNLdB/)
---

## 📑 Table of Contents

1. [Project Overview & Features](#1-project-overview--features)
2. [Components Required](#2-components-required)
3. [Full Circuit Diagram & Wiring](#3-full-circuit-diagram--wiring)
4. [Software Setup (Arduino IDE)](#4-software-setup-arduino-ide)
5. [Required Code Adjustments](#5-required-code-adjustments)
6. [Complete Project Code](#6-complete-project-code)
7. [Step-by-Step Flashing Guide](#7-step-by-step-flashing-guide)
8. [Finding the IP Address & Accessing the Dashboard](#8-finding-the-ip-address--accessing-the-dashboard)
9. [Troubleshooting Guide](#9-troubleshooting-guide)
10. [License](#10-license)

---

## 1. Project Overview & Features

* **Interactive Pull-Chain Cord:** CSS keyframe animations replicate a mechanical chain being pulled downward and springing back.
* **Realistic Light Cone:** Toggling the light casts a semi-transparent yellow light beam from the lamp shade.
* **Standalone Webserver:** Runs directly on ESP32 flash memory (`PROGMEM`). No third-party IoT clouds, Blynk, or external servers needed.
* **Instant State Synchronization:** Asynchronous JavaScript `fetch()` calls toggle and read state without refreshing the webpage.
* **Local Network Control:** Runs completely inside your private home Wi-Fi network with minimal latency.

---

## 2. Components Required

| Component | Quantity | Purpose |
| :--- | :--- | :--- |
| **ESP32 Dev Board** (30/38 pin) | 1 | Microcontroller running the local web server |
| **5V Relay Module (1-Channel)** | 1 | Electromechanical switch to handle AC voltage |
| **Light Bulb + Lamp Holder** | 1 | Room appliance to be controlled |
| **2-Pin AC Mains Cable** | 1 | AC power source connection |
| **Jumper Wires (Female-to-Female)**| 3 | Signal and DC power lines between ESP32 & Relay |
| **Micro-USB Cable** | 1 | Uploading firmware and 5V power supply |

## ⭐ Support

If you found this project helpful, consider giving this repository a **⭐ Star**.

Your support helps **TECHTADKA360** create more open-source Arduino, ESP32, IoT, and Robotics projects.

---

## 3. Full Circuit Diagram & Wiring

### A. ESP32 to 5V Relay Module (DC Signals)

Connect your ESP32 board to the relay board using 3 jumper wires:

```text
ESP32 Dev Board                5V Relay Module
+------------------+          +---------------+
|             VIN  | -------- | VCC           |
|             GND  | -------- | GND           |
|         GPIO 23  | -------- | IN            |
+------------------+          +---------------+
