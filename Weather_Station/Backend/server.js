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





const express = require('express');
const cors = require('cors');
const db = require('./database');

const app = express();
app.use(cors());
app.use(express.json());

// API 
app.post('/api/sensor', (req, res) => {
  const { device_id, temperature, timestamp } = req.body;

  const time = timestamp || new Date().toISOString();

  const query = `
    INSERT INTO measurements (device_id, timestamp, temperature)
    VALUES (?, ?, ?)
  `;

  db.run(query, [device_id || 'station_1', time, temperature], function (err) {
    if (err) {
      console.error(err);
      return res.status(500).json({ error: 'Failed to insert data' });
    }
    res.json({ success: true, id: this.lastID });
  });
});

// API for frontend gett the data
app.get('/api/sensor', (req, res) => {
  db.all("SELECT * FROM measurements ORDER BY timestamp DESC LIMIT 100", [], (err, rows) => {
    if (err) {
      return res.status(500).json({ error: 'Failed to read data' });
    }
    res.json(rows);
  });
});

app.listen(3000, () => console.log('Server running on port 3000'));
