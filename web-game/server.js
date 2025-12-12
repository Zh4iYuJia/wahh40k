const express = require('express');
const cors = require('cors');
const { getWeapons, getUnits, addUnit } = require('./database');

const app = express();
const PORT = 3000;

app.use(cors());
app.use(express.json());
app.use(express.static('public')); // Serve static files from public directory

// API endpoints
app.get('/api/weapons', (req, res) => {
    getWeapons((err, weapons) => {
        if (err) {
            res.status(500).json({ error: err.message });
        } else {
            res.json(weapons);
        }
    });
});

app.get('/api/units', (req, res) => {
    getUnits((err, units) => {
        console.log('Units from DB:', units);
        if (err) {
            res.status(500).json({ error: err.message });
        } else {
            res.json(units);
        }
    });
});

app.post('/api/units', (req, res) => {
    const { name, hp, weaponAId, weaponBId } = req.body;
    addUnit(name, hp, weaponAId, weaponBId, (err, result) => {
        if (err) {
            res.status(500).json({ error: err.message });
        } else {
            res.json(result);
        }
    });
});

app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});