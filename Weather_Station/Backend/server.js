// const express = require('express');
// const app = express();
// const port = 3000;
// const db = require('./database');

// app.use(express.json()); 

// app.get('/api/sensor', (req, res) => {
//  res.json({
//     temperature: 909,
//     humidity: 50,
//     status: "OK"
//  });
// });


// app.post('/api/sensor', (req, res) => {
//     const { temperature, humidity, status } = req.body;  

//     res.json({
//         message: "Sensor data received successfully!",
//         received: {
//             temperature,
//             humidity,
//             status
//         }
//     });
// });

// app.listen(port, () => {
//  console.log(`Server running at http://localhost:${port}/`);
// });





//  SERVER.JS - Express + SQLite + MQTT Subscriber

const express = require('express');
const cors = require('cors');
const db = require('./database');
const mqtt = require('mqtt');

// MQTT CONFIGURATION
// Use MQTT URL without port in the string, and let the client handle port
const MQTT_BROKER = 'mqtt://test.mosquitto.org';   // <-- matches Wokwi broker
const MQTT_TOPIC  = 'iot/weather/station1';        // <-- matches Wokwi topic

// Create MQTT client
// port 1883 is the default for mqtt:// so this can be omitted,
// for clarity.
const mqttClient = mqtt.connect(MQTT_BROKER, {
  port: 1883,
  protocol: 'mqtt',
});

mqttClient.on('connect', () => {
  console.log(' MQTT connected to broker:', MQTT_BROKER);
  mqttClient.subscribe(MQTT_TOPIC, (err) => {
    if (err) {
      console.error('Failed to subscribe:', err.message);
    } else {
      console.log('Subscribed to topic:', MQTT_TOPIC);
    }
  });
});

mqttClient.on('error', (err) => {
  console.error('MQTT error:', err.message);
});

// Handling incoming MQTT messages from Wokwi
mqttClient.on('message', (topic, message) => {
  console.log('MQTT message received on', topic, '=>', message.toString());

  try {
    const data = JSON.parse(message.toString());
    const deviceId   = data.device_id || 'station_unknown';
    const temperature = data.temperature ?? null;
    const humidity    = data.humidity ?? null;
    const timestamp   = data.timestamp || new Date().toISOString();

    const query = `
      INSERT INTO measurements (device_id, timestamp, temperature, humidity)
      VALUES (?, ?, ?, ?)
    `;

    db.run(query, [deviceId, timestamp, temperature, humidity], function (err) {
      if (err) {
        console.error('DB Insert Error:', err.message);
      } else {
        console.log('Data inserted with ID:', this.lastID);
      }
    });

  } catch (e) {
    console.error('Failed to parse MQTT JSON:', e.message);
  }
});

// EXPRESS API SERVER
const app = express();
app.use(cors());
app.use(express.json());
app.use(express.static(__dirname));

// HTTP POST endpoint (optional – for testing without MQTT)
app.post('/api/sensor', (req, res) => {
  const { device_id, temperature, humidity, timestamp } = req.body;
  const time = timestamp || new Date().toISOString();

  const query = `
    INSERT INTO measurements (device_id, timestamp, temperature, humidity)
    VALUES (?, ?, ?, ?)
  `;

  db.run(query, [device_id, time, temperature, humidity], function (err) {
    if (err) {
      console.error(err);
      return res.status(500).json({ error: 'Failed to insert data' });
    }
    res.json({ success: true, id: this.lastID });
  });
});

// Get latest 100 records
app.get('/api/sensor', (req, res) => {
  db.all('SELECT * FROM measurements ORDER BY timestamp DESC LIMIT 100', [], (err, rows) => {
    if (err) return res.status(500).json({ error: 'Failed to read data' });
    res.json(rows);
  });
});

app.listen(3000, () => console.log('Server running on port 3000'));


