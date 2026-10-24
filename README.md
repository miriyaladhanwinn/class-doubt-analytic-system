# Class Doubt Analytic System (v2.0)
> **Advanced IoT-Based Real-Time Student Engagement Platform Powered by ESP32 with Wi-Fi Web Dashboard, Non-Volatile Flash Analytics, and Multi-Level Smart Alerts**

[![Wokwi Simulation](https://img.shields.io/badge/Wokwi-Verified%20Simulation%20v2.0-brightgreen.svg)](https://wokwi.com/projects/477976559592126465)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32%20Xtensa%20Dual--Core-blue.svg)](https://espressif.com)
[![Commits](https://img.shields.io/badge/Commits-100%20Verified-blueviolet.svg)](#git-contribution-metrics)

---

## 👥 Team Members & Project Contributors

| Contributor Name | Roll / Reg Number | GitHub Profile | Email | Project Role |
| :--- | :---: | :---: | :--- | :--- |
| **Miriyala Dhanwin** *(Lead)* | `CB.SC.U4CSE25639` | [@miriyaladhanwinn](https://github.com/miriyaladhanwinn) | `dhanwinn15@gmail.com` | IoT Architecture, Firmware Engine, State Machine (40 Commits) |
| **Koushik Reddy Poluri** | `CB.SC.U4CSE25645` | [@koushikreddy](https://github.com/koushikpoluri7) | `koushikpoluri7@gmail.com` | Circuit Design, Wokwi Pinout & Simulation Schematics (20 Commits) |
| **Shahil Saginala** | `CB.SB.SC.U4CSE25651` | [@Shahil](https://github.com/Shahilsaginala27) | `Shahilsaginala27@gmail.com` | Web Dashboard, REST API Telemetry & UI Styling (20 Commits) |
| **Himanshu Gautam** | `CB.SC.U4CSE25625` | [@nerdgautam](https://github.com/nerdgautam) | `nerdgautam@gmail.com` | Analytics Modeling, Testbench & Benchmark Evaluation (20 Commits) |

---

## ⚡ Live Simulation & Repository Links
* **Wokwi Virtual Testbench**: [https://wokwi.com/projects/477976559592126465](https://wokwi.com/projects/477976559592126465)
* **GitHub Official Repository**: [https://github.com/miriyaladhanwinn/class-doubt-analytic-system](https://github.com/miriyaladhanwinn/class-doubt-analytic-system)

---

## 🛠️ Hardware Interfacing & GPIO Map

| Component | ESP32 GPIO | Electrical Mode | Functional Operational Role |
| :--- | :---: | :---: | :--- |
| **Math Button** | `GPIO 18` | `INPUT_PULLUP` | Active LOW tactile switch registering Math confusion |
| **Science Button** | `GPIO 19` | `INPUT_PULLUP` | Active LOW tactile switch registering Science confusion |
| **English Button** | `GPIO 5` | `INPUT_PULLUP` | Active LOW tactile switch registering English confusion |
| **Programming Button** | `GPIO 17` | `INPUT_PULLUP` | Active LOW tactile switch registering Programming confusion |
| **Reset Button** | `GPIO 27` | `INPUT_PULLUP` | Active LOW dedicated hardware session reset |
| **Math LED (Red)** | `GPIO 4` | `OUTPUT` | Active HIGH visual confirmation for Math |
| **Science LED (Blue)** | `GPIO 16` | `OUTPUT` | Active HIGH visual confirmation for Science |
| **English LED (Yellow)** | `GPIO 25` | `OUTPUT` | Active HIGH visual confirmation for English |
| **Programming LED (Green)** | `GPIO 26` | `OUTPUT` | Active HIGH visual confirmation for Programming |
| **Piezo Audio Buzzer** | `GPIO 2` | `OUTPUT (PWM)` | Distinct acoustic frequencies (700-1600 Hz) |
| **16x2 Character LCD** | `GPIO 21 (SDA), 22 (SCL)` | `I2C (0x27)` | 3-Page auto-rotating local analytics display |

---

## 📊 Git Contribution Metrics (100 Commits)

| Contributor | Email | Commits | Contribution Share | Primary Focus |
| :--- | :--- | :---: | :---: | :--- |
| **Miriyala Dhanwin** | `dhanwinn15@gmail.com` | **40** | **40% (Lead)** | Core Firmware, Debounce Engine, LCD Cyclic State Machine, NVS Flash Storage |
| **Koushik Reddy Poluri** | `koushikpoluri7@gmail.com` | **20** | **20%** | Hardware Interfacing, Wokwi Netlist, Power Distribution, Circuit Layout |
| **Shahil Saginala** | `Shahilsaginala27@gmail.com` | **20** | **20%** | Embedded WebServer, HTML5 Dashboard, JSON REST API, Responsive Design |
| **Himanshu Gautam** | `nerdgautam@gmail.com` | **20** | **20%** | Statistical Hotspot Modeling, Latency Benchmarks, Debounce Verification |
| **TOTAL** | — | **100** | **100%** | Production-Ready IoT Smart Classroom System |

---
*Verified in Wokwi Simulation Environment v2.0*
