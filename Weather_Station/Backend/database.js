//module.exports = db;

const sqlite3 = require('sqlite3').verbose();

//open file in db
const db = new sqlite3.Database('./sensors.db');

//create table
db.serialize(() => {
    db.run(`
    CREATE TABLE IF NOT EXISTS measurements (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        device_id TEXT,
        timestamp DATETIME,
        temperature REAL,
        humidity REAL

    )
    `);
});

module.exports = db;