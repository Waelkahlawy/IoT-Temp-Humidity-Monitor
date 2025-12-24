# IoT Temperature & Humidity Monitoring System  
ESP32 (ESP-IDF) + Mosquitto MQTT + Telegraf + InfluxDB + Grafana  

This project implements a full end-to-end IoT monitoring and control system.  
The ESP32 programmed with **ESP-IDF** collects temperature & humidity data and publishes it to **Mosquitto MQTT Broker**.  
**Telegraf** receives the data and stores it inside **InfluxDB**, and **Grafana** visualizes everything on a real-time dashboard.  

The dashboard also includes interactive control elements that allow authorized users on the same network to control the system remotely.

---

## 🔥 Features
- ESP32 programmed using **ESP-IDF**
- Reads temperature & humidity sensors (DHT/SHT/etc.)
- Publishes data through **MQTT (Mosquitto Broker)**
- **Telegraf** for automatic data ingestion → InfluxDB
- **Grafana Dashboard** for real-time visualization & historical graphing
- Control switches/buttons accessible from the local network
- Access control so only allowed users can operate the system

---

## 🧱 System Architecture 
┌───────────┐ MQTT ┌──────────────┐ Inputs ┌───────────┐
│ ESP32 │ ─────────────→ │ Mosquitto │ ───────────────→ │ Telegraf │
│ (ESP-IDF) │ Publish │ Broker │ Subscriber └─────┬─────┘
└─────┬──────┘ └──────┬───────┘ │
│ Sensor Data │ MQTT Topics │ Writes
│          ▼
│ ┌────────────────┐ ┌───────────────┐
└──────────────────────────→ │ InfluxDB │ ←──── │ Grafana │
│ Time-Series DB │ Query │ Visualization │
└────────────────┘ └───────────────┘

---

## 🔄 System Flow Diagram


[Sensors]
│
▼
[ESP32 (ESP-IDF)]
│ Reads data + formats JSON
▼
[MQTT Publish → Mosquitto Broker]
│
▼
[Telegraf MQTT Consumer]
│ Extracts fields
▼
[InfluxDB Bucket]
│ Query
▼
[Grafana Dashboard]
│
├── Displays gauges, charts, logs
└── Provides control buttons/switches
│
▼
[MQTT Control Topics]
│
▼
[ESP32 Takes Action]


---

## 📊 Dashboard Mockups (ASCII Visualization)

### 1) **Overview Dashboard**


┌─────────────────────────────────────────────┐
│ SYSTEM DASHBOARD │
├─────────────────────┬───────────────────────┤
│ Temperature Gauge │ Humidity Gauge │
│ ( °C ) │ ( % ) │
│ ███████ 29°C │ ██████ 45% │
├─────────────────────┴───────────────────────┤
│ Real-Time Graph (Temp/Hum vs Time) │
│ ● ● ● ● ● ● ● ● ● ● ● ● ● ● │
│ ░ ░ ░ ░ ░ ░ ░ ░ ░ ░ ░ ░ ░ ░ │
├─────────────────────────────────────────────┤
│ System Control Panel │
│ [●] System Power ON/OFF │
│ [●] Fan Control │
│ [●] Threshold Alarm Enable │
└─────────────────────────────────────────────┘

---

---

### 3) **Control Dashboard Layout**
┌───────────────────────────────┐
│ CONTROL DASHBOARD │
├───────────────────────────────┤
│ SYSTEM STATUS: RUNNING │
├───────────────────────────────┤
│ [Toggle] System ON/OFF │
│ [Toggle] Relay Control │
│ [Toggle] Alarm Mode │
└───────────────────────────────┘
### 2) **InfluxDB Data Preview Screen**

---

## 🛠 Technologies Used
- **ESP32 (ESP-IDF)**
- **Mosquitto MQTT Broker**
- **Telegraf**
- **InfluxDB**
- **Grafana**

---

## 📦 Folder Structure
/esp32-firmware → ESP-IDF source code
/telegraf → Telegraf config files
/grafana → Dashboard JSON exports
/influxdb → DB setup scripts
/docs → diagrams & documentation

---

## 🚀 How to Run
1. Flash ESP32 firmware (ESP-IDF)  
2. Run Mosquitto broker  
3. Start Telegraf service  
4. Start InfluxDB  
5. Open Grafana and import dashboard  

---

## 📸 Dashboard Screenshots (Ready to Generate)
<img width="1861" height="914" alt="Screenshot 2025-12-16 182636" src="https://github.com/user-attachments/assets/22e4c5ef-8678-4c16-a3ba-f32e068e3699" />

<img width="1456" height="867" alt="Screenshot 2025-12-16 144104" src="https://github.com/user-attachments/assets/95f5d5e7-03c2-4ee0-92c5-89a166806fbe" />

<img width="750" height="1334" alt="image" src="https://github.com/user-attachments/assets/b149a4c7-f76d-44e7-bf6f-39b8e14f1579" />




