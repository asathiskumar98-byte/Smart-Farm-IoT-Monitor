# 🌾 Smart Farm IoT Monitor

An **IoT-based Smart Agriculture System** built using **ESP8266** to monitor and upload real-time environmental data like temperature, humidity, soil moisture, light, rain, and gas levels to **ThingSpeak Cloud**.

---

## 🧠 Project Overview
This project helps automate and monitor farming conditions to improve crop health and productivity.  
It provides **real-time monitoring**, **cloud data logging**, and **OLED visualization** — all in a compact embedded setup.

---

## ⚙️ Features
- 🌡️ Temperature & Humidity Monitoring (DHT22)
- 💧 Soil Moisture Detection
- 🌧️ Rain Status Indicator
- ☀️ Light Intensity Measurement (LDR)
- 🔥 Gas Leak Detection (MQ2)
- 🖥️ Real-time Display on OLED (SSD1306)
- ☁️ Data Logging to ThingSpeak Cloud
- 📶 Wi-Fi Connectivity (ESP8266)

---

## 🧰 Hardware Components
| Component | Description |
|------------|--------------|
| ESP8266 NodeMCU | Main Controller |
| DHT22 | Temperature & Humidity Sensor |
| Soil Moisture Sensor | Analog Input |
| Rain Sensor | Digital Input |
| LDR Sensor | Light Detection |
| MQ2 Sensor | Gas Detection |
| OLED Display (0.96”) | I²C 128x64 Display Module |

---

## 🧾 Circuit Pin Configuration
| Sensor / Module | Pin |
|------------------|-----|
| DHT22 | D3 |
| Soil Moisture | A0 |
| Rain Sensor | D5 |
| LDR | D6 |
| MQ2 | D7 |
| OLED Display | SDA → D1, SCL → D2 |

---

## 📡 ThingSpeak Cloud Integration
Data is uploaded every second to the **ThingSpeak IoT Platform** for visualization.

**ThingSpeak Fields:**
1. Temperature  
2. Humidity  
3. Soil Moisture  
4. Rain Detection  
5. LDR (Light)  
6. MQ2 (Gas)

---
