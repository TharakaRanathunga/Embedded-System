const sqlite3 = require('sqlite3').verbose();
const db = new sqlite3.Database('./sensors.db');

db.all('SELECT * FROM measurements ORDER BY id DESC LIMIT 10', [], (err, rows) => {
  if (err) {
    console.error('Error:', err.message);
  } else {
    console.log('Latest 10 measurements:');
    console.log(rows);
  }
  db.close();
});
