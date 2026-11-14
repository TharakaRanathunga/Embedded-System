# ESP32 IoT Weather Station

## Table of Contents

* [Overview](#overview)
* [Wokwi Simulation](#wokwi-simulation)
* [Features](#features)
* [System Architecture](#system-architecture)
* [Technologies Used](#technologies-used)
* [Hardware and Components](#hardware-and-components)
* [Software Dependencies](#software-dependencies)
* [Project Structure](#project-structure)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
* [Configuration](#configuration)
* [Running the Project](#running-the-project)
* [Web Dashboard](#web-dashboard)
* [MQTT Communication](#mqtt-communication)
* [REST API](#rest-api)
* [Database](#database)
* [Temperature Indicators](#temperature-indicators)
* [Example Sensor Data](#example-sensor-data)
* [Troubleshooting](#troubleshooting)
* [Semantic Versioning](#semantic-versioning)
* [Versioning Use Cases](#versioning-use-cases)
* [Future Improvements](#future-improvements)
* [Software License](#software-license)
* [Maintainer](#maintainer)

---

## Overview and Purpose

The **ESP32 IoT Weather Station** is an IoT-based weather monitoring project developed and simulated using **Wokwi**.

The project uses an ESP32 with a DHT22 sensor to measure temperature and humidity. The ESP32 sends the sensor measurements through Wi-Fi using the MQTT communication protocol.

A Node.js backend receives the MQTT messages and stores the measurements in an SQLite database. The backend also provides a REST API that is used by a web dashboard to display the collected weather data.

The project demonstrates how an IoT device can collect sensor data, communicate through MQTT, store data in a database, and display the information through a web interface.

---
## Wokwi Simulation

The ESP32 weather station is simulated using Wokwi.

**Wokwi Project:** [Open the ESP32 Weather Station simulation](https://wokwi.com/projects/449580644297769985)

---

## Features

* Temperature and humidity measurement using a DHT22 sensor.
* ESP32-based IoT device.
* Wokwi simulation support.
* Wi-Fi connectivity.
* MQTT communication.
* SQLite database for storing sensor measurements.
* Node.js and Express backend.
* REST API for sensor data.
* Web dashboard for visualizing sensor measurements.
* Dashboard displays the latest temperature and humidity.
* Dashboard displays the latest 10 sensor readings.
* Dashboard automatically refreshes every 2 seconds.
* 16x2 I2C LCD display for temperature and status.
* Three LEDs indicate the temperature range.
* Error handling for MQTT, database, and API operations.

---

## System Architecture

The overall data flow of the project is:

```text
+----------------------+
| ESP32 + DHT22 Sensor |
+----------+-----------+
           |
           | Wi-Fi
           v
+----------------------+
|    MQTT Broker       |
| test.mosquitto.org   |
+----------+-----------+
           |
           | MQTT Topic
           | iot/weather/station1
           v
+----------------------+
| Node.js Backend      |
| Express + MQTT       |
+----------+-----------+
           |
           v
+----------------------+
| SQLite Database      |
| sensors.db           |
+----------+-----------+
           |
           | REST API
           v
+----------------------+
| Web Dashboard        |
| HTML + CSS + JS      |
+----------------------+
```

### Data Flow

1. The DHT22 sensor measures temperature and humidity.
2. The ESP32 reads the sensor values.
3. The ESP32 displays the temperature on the LCD.
4. LEDs indicate the current temperature range.
5. The ESP32 creates an MQTT message containing the sensor data.
6. The message is published to the MQTT broker.
7. The Node.js backend subscribes to the MQTT topic.
8. The backend receives and parses the MQTT message.
9. The sensor measurement is stored in SQLite.
10. The web dashboard requests data from the REST API.
11. The dashboard displays the latest measurements and recent history.

---

## Technologies Used

| Technology            | Purpose                                     |
| --------------------- | ------------------------------------------- |
| ESP32                 | IoT microcontroller                         |
| DHT22                 | Temperature and humidity sensor             |
| Wokwi                 | ESP32 and sensor simulation                 |
| C++ / Arduino         | ESP32 programming                           |
| MQTT                  | IoT messaging protocol                      |
| Mosquitto MQTT Broker | MQTT message broker                         |
| Node.js               | Backend runtime                             |
| Express.js            | REST API and web server                     |
| SQLite                | Database                                    |
| HTML                  | Dashboard structure                         |
| CSS                   | Dashboard styling                           |
| JavaScript            | Dashboard data handling                     |
| Fetch API             | Communication between dashboard and backend |

---

## Hardware and Components

The project uses the following components in the Wokwi simulation:

### ESP32

The ESP32 is the main microcontroller. It connects to Wi-Fi, reads the DHT22 sensor, controls the LCD and LEDs, and publishes sensor data through MQTT.

### DHT22 Sensor

The DHT22 measures:

* Temperature
* Relative humidity

The sensor is connected to GPIO pin `15`.

### 16x2 I2C LCD

The LCD displays the current temperature and a temperature status message.

The ESP32 uses:

* SDA: GPIO `21`
* SCL: GPIO `22`
* I2C address: `0x27`

### LEDs

Three LEDs are used to indicate temperature conditions:

* Red LED: temperature above 30°C
* Yellow LED: temperature from 20°C to 30°C
* Cyan LED: temperature below 20°C

### Wokwi Wi-Fi

The simulation uses the Wokwi network:

```text
SSID: Wokwi-GUEST
Password: empty
```

---

## Software Dependencies

### Backend Dependencies

The Node.js backend uses the following packages:

```json
{
  "cors": "^2.8.5",
  "express": "^5.1.0",
  "mqtt": "^5.14.1",
  "sqlite3": "^5.1.7"
}
```

These dependencies provide:

* **Express** — web server and REST API.
* **CORS** — Cross-Origin Resource Sharing support.
* **MQTT** — communication with the MQTT broker.
* **SQLite3** — connection to the SQLite database.

### ESP32 Libraries

The ESP32 code uses:

* `WiFi.h`
* `WiFiClient.h`
* `PubSubClient.h`
* `DHTesp.h`
* `LiquidCrystal_I2C.h`
* `Wire.h`

Some of these libraries are provided by the ESP32/Arduino environment, while others are external libraries used for MQTT, DHT22, and LCD functionality.

---

## Project Structure

A simplified project structure is:

```text
weather-station/
│
├── server.js
├── database.js
├── package.json
├── sensors.db
├── index.html
└── ESP32 Wokwi code
```

### Main Files

#### `server.js`

The main Node.js backend.

It:

* Connects to the MQTT broker.
* Subscribes to the weather station MQTT topic.
* Receives sensor messages.
* Stores MQTT data in SQLite.
* Provides REST API endpoints.
* Serves the web dashboard files.

#### `database.js`

Creates and connects to the SQLite database.

It creates the `measurements` table if it does not already exist.

#### `package.json`

Contains the Node.js project information and backend dependencies.

#### `sensors.db`

SQLite database file used to store sensor measurements.

#### `index.html`

Contains the web dashboard interface.

The dashboard uses HTML, CSS, and JavaScript to display the sensor data received from the backend API.

---

## Prerequisites

Before running the project, install or have access to:

1. **Node.js and npm**
2. **Wokwi** for running the ESP32 simulation
3. A web browser such as Chrome, Firefox, Edge, or Safari
4. Internet access for the MQTT connection

The project does not require a physical ESP32 board when using the Wokwi simulation.

---

## Installation Instructions

### Step 1: Download or Clone the Project

Open the project folder in a terminal.

### Step 2: Install Node.js Dependencies

Run:

```bash
npm install
```

This installs the dependencies defined in `package.json`.

### Step 3: Check the Configuration

The ESP32 and Node.js backend must use the same MQTT broker and topic.

The project uses:

```text
MQTT Broker: test.mosquitto.org
MQTT Port: 1883
MQTT Topic: iot/weather/station1
```

### Step 4: Start the Backend

Run:

```bash
node server.js
```

If the server starts successfully, the terminal displays:

```text
Server running on port 3000
```

The MQTT connection should also display messages indicating that the backend connected to the broker and subscribed to the topic.

---

## Configuration

### MQTT Configuration

The backend uses:

```text
mqtt://test.mosquitto.org
```

with port:

```text
1883
```

The MQTT topic is:

```text
iot/weather/station1
```

The ESP32 uses the same broker, port, and topic.

### ESP32 Configuration

The Wokwi ESP32 connects using:

```text
SSID: Wokwi-GUEST
Password: empty (No password required)
```

The MQTT configuration in the ESP32 code is:

```cpp
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* mqtt_topic = "iot/weather/station1";
```

---

## Running the Project

### 1. Start the Node.js Backend

From the project directory:

```bash
node server.js
```

### 2. Start the Wokwi Simulation

Open the ESP32 project in Wokwi and start the simulation.

The ESP32 will:

1. Connect to Wokwi Wi-Fi.
2. Connect to the MQTT broker.
3. Read temperature and humidity from the DHT22.
4. Update the LCD.
5. Control the LEDs.
6. Publish sensor data through MQTT.

The ESP32 publishes a new measurement approximately every **5 seconds**.

### 3. Open the Dashboard

Once the Node.js server is running, open the dashboard through the local server.

For example:

```text
http://localhost:3000/
```

The dashboard will request sensor data from:

```text
/api/sensor
```

and display the results in the browser.

---

## Web Dashboard

The project includes a web dashboard for visualizing the weather station data.

The dashboard is built using:

* HTML
* CSS
* JavaScript
* Fetch API

### Dashboard Layout

The dashboard contains:

#### Temperature Card

Displays the latest temperature reading in degrees Celsius.

Example:

```text
Temperature
24.50 °C
```

#### Humidity Card

Displays the latest humidity reading.

Example:

```text
Humidity
55.20 %
```

#### Latest Readings Table

The dashboard displays the **latest 10 sensor readings**.

The table contains:

| Column      | Description                      |
| ----------- | -------------------------------- |
| Time        | Date and time of the measurement |
| Temperature | Temperature measurement in °C    |
| Humidity    | Humidity measurement in %        |

The device ID of the latest reading is also displayed.

### Automatic Refresh

The dashboard automatically calls the API every **2 seconds**:

```javascript
setInterval(fetchData, 2000);
```

This allows newly stored measurements to appear on the dashboard without manually refreshing the browser.

### Error Handling

If the dashboard cannot retrieve data from the backend, an error message is displayed.

It also reports when no sensor data is available yet.

### Responsive Design

The dashboard uses CSS media queries so that the layout adapts to smaller screens.

On smaller screens, the temperature and humidity cards are displayed in a single column.

---

## MQTT Communication

MQTT is used to transfer sensor data from the ESP32 to the Node.js backend.

### MQTT Broker

```text
test.mosquitto.org
```

### Port

```text
1883
```

### Topic

```text
iot/weather/station1
```

### Device ID

The ESP32 identifies itself as:

```text
station_esp32_1
```

### Example MQTT Payload

The ESP32 sends data in JSON format:

```json
{
  "device_id": "station_esp32_1",
  "temperature": 24.50,
  "humidity": 55.20,
  "timestamp": "2025-12-04T00:00:00Z"
}
```

The Node.js backend receives the message and parses the JSON data.

The backend then inserts the device ID, temperature, humidity, and a server-generated timestamp into the SQLite database.

> **Note:** The MQTT handler in `server.js` currently uses the Node.js server's current time for the database timestamp instead of using the timestamp supplied by the ESP32.

---

## REST API

The Node.js backend provides REST API endpoints for accessing and inserting sensor data.

### Get Sensor Measurements

**Endpoint:**

```http
GET /api/sensor
```

This endpoint returns the latest 100 measurements from the database.

Example:

```bash
curl http://localhost:3000/api/sensor
```

The dashboard uses this endpoint to retrieve the sensor data.

### Insert Sensor Measurement

**Endpoint:**

```http
POST /api/sensor
```

Example JSON request:

```json
{
  "device_id": "station_esp32_1",
  "temperature": 24.50,
  "humidity": 55.20
}
```

Example using JavaScript:

```javascript
fetch('/api/sensor', {
    method: 'POST',
    headers: {
        'Content-Type': 'application/json'
    },
    body: JSON.stringify({
        device_id: 'station_esp32_1',
        temperature: 24.50,
        humidity: 55.20
    })
});
```

The API stores the submitted measurement in the SQLite database.

---

## Database

The project uses **SQLite** to store sensor measurements.

The database file is:

```text
sensors.db
```

The database contains a table named:

```text
measurements
```

### Database Schema

| Column        | Type     | Description                          |
| ------------- | -------- | ------------------------------------ |
| `id`          | INTEGER  | Unique automatically generated ID    |
| `device_id`   | TEXT     | Identifier of the ESP32 device       |
| `timestamp`   | DATETIME | Time associated with the measurement |
| `temperature` | REAL     | Temperature measurement              |
| `humidity`    | REAL     | Humidity measurement                 |

The table is automatically created by `database.js` if it does not already exist.

---

## Temperature Indicators

The ESP32 uses the temperature measurement to control the LEDs and LCD status.

| Temperature | LED    | LCD Status   |
| ----------- | ------ | ------------ |
| Below 20°C  | Cyan   | `COLD! <20C` |
| 20°C – 30°C | Yellow | `NORMAL`     |
| Above 30°C  | Red    | `HOT! >30C`  |

For example, if the measured temperature is:

```text
32°C
```

the red LED is turned on and the LCD displays:

```text
Temp: 32°C
HOT! >30C
```

---

## Example Sensor Data

A typical measurement stored by the backend could look like:

```json
{
  "id": 1,
  "device_id": "station_esp32_1",
  "timestamp": "2025-12-04T12:30:00.000Z",
  "temperature": 24.50,
  "humidity": 55.20
}
```

The dashboard uses these values to display the latest measurement and the recent reading history.

---

## Troubleshooting

### Backend Does Not Start

Make sure Node.js is installed and run:

```bash
npm install
```

Then start the backend:

```bash
node server.js
```

### MQTT Does Not Connect

Check that:

* The ESP32 and Node.js backend use the same MQTT broker.
* The MQTT topic is exactly:

```text
iot/weather/station1
```

* The Wokwi simulation has an internet connection.

### If No Data Appears on the Dashboard

Check the following:

1. The Node.js server is running.
2. The Wokwi simulation is running.
3. The ESP32 is connected to Wi-Fi.
4. The ESP32 is connected to MQTT.
5. The backend is subscribed to the correct topic.
6. Sensor data is being inserted into SQLite.
7. The browser can access:

```text
http://localhost:3000/api/sensor
```

### Dashboard Shows "No Data Available Yet"

This normally means that the database does not contain any measurements yet.

Start the Wokwi simulation and wait for the ESP32 to publish sensor data.

### DHT22 Reading Fails

If the serial monitor displays:

```text
DHT read failed!
```

check that the DHT22 is correctly configured and connected to the expected GPIO pin.

---

## Semantic Versioning

This project follows the semantic versioning format **MAJOR.MINOR.PATCH**.

According to [Semantic Versioning 2.0.0](https://semver.org/), the version
number communicates the type of change introduced by a release:

* **MAJOR** is incremented when incompatible or breaking changes are made.
* **MINOR** is incremented when new functionality is added in a
  backward-compatible manner.
* **PATCH** is incremented for backward-compatible bug fixes.

## Versioning Use Cases

### Major version update

A major release would be required if the REST API or MQTT data format were
changed incompatibly. For example, replacing the existing sensor-data
response fields with a new structure that requires dashboard clients to be
rewritten would be a breaking change.

**Example:** `1.0.0` -> `2.0.0`

### Minor version update

A minor release would be appropriate when a new feature is added without
breaking existing clients. For example, adding rainfall or wind-speed
measurements, a new API endpoint, and an additional dashboard chart would
extend the application while preserving the existing temperature and
humidity endpoints.

**Example:** `1.0.0` -> `1.1.0`

### Patch version update

A patch release would contain a backward-compatible correction. Examples
include fixing an incorrect temperature conversion, correcting a dashboard
refresh error, or improving MQTT reconnection handling without changing the
public API.

**Example:** `1.0.0` -> `1.0.1`

---

## Future Improvements

Possible future improvements include:

* Add filtering by date and time.
* Support multiple ESP32 weather stations.
* Add user authentication.
* Add API input validation.
* Add data export functionality.
* Add automated backend tests.
* Add more detailed charts to the dashboard.
* Add cloud deployment.
* Improve MQTT security by using authenticated and encrypted communication.

---

## Software License

This project is released under the **MIT License**. See the [LICENSE](LICENSE)
file for the full license text.

---

## Maintainer

I. Tharaka Ranathunga maintain this project and it was done as a component of course work under Embedded Systems Course.

---