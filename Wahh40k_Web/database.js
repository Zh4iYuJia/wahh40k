const sqlite3 = require('sqlite3').verbose();
const fs = require('fs');
const path = require('path');

const dbPath = path.join(__dirname, 'game.db');

// Initialize database
const db = new sqlite3.Database(dbPath, (err) => {
    if (err) {
        console.error('Error opening database:', err.message);
    } else {
        console.log('Connected to SQLite database.');
        initDatabase();
    }
});

function initDatabase() {
    const schemaPath = path.join(__dirname, 'schema.sql');
    const schema = fs.readFileSync(schemaPath, 'utf8');
    // Split schema into CREATE and INSERT parts
    const parts = schema.split('-- Insert some sample data');
    const createStatements = parts[0];
    const insertPart = parts[1];

    console.log('Create statements:', createStatements);
    console.log('Insert part:', insertPart);

    db.exec(createStatements, (err) => {
        if (err) {
            console.error('Error creating tables:', err.message);
        } else {
            // Check if weapons table is empty
            db.get('SELECT COUNT(*) as count FROM weapons', [], (err, row) => {
                if (err) {
                    console.error('Error checking weapons:', err.message);
                } else {
                    console.log('Weapons count:', row.count);
                    if (row.count === 0) {
                        // Insert initial data
                        db.exec(insertPart, (err) => {
                            if (err) {
                                console.error('Error inserting initial data:', err.message);
                            } else {
                                console.log('Initial data inserted.');
                            }
                        });
                    } else {
                        console.log('Database already has data.');
                    }
                }
            });
        }
    });
}

// Get all weapons
function getWeapons(callback) {
    db.all('SELECT * FROM weapons', [], (err, rows) => {
        if (err) {
            callback(err, null);
        } else {
            callback(null, rows);
        }
    });
}

// Get all units with weapon details
function getUnits(callback) {
    const query = `
        SELECT u.id, u.name, u.hp,
               w1.name as weapon_a_name, w1.damage as weapon_a_damage, w1.shots as weapon_a_shots, w1.hit_threshold as weapon_a_hit,
               w2.name as weapon_b_name, w2.damage as weapon_b_damage, w2.shots as weapon_b_shots, w2.hit_threshold as weapon_b_hit
        FROM units u
        LEFT JOIN weapons w1 ON u.weapon_a_id = w1.id
        LEFT JOIN weapons w2 ON u.weapon_b_id = w2.id
    `;
    db.all(query, [], (err, rows) => {
        if (err) {
            callback(err, null);
        } else {
            callback(null, rows);
        }
    });
}

// Add a new unit
function addUnit(name, hp, weaponAId, weaponBId, callback) {
    db.run('INSERT INTO units (name, hp, weapon_a_id, weapon_b_id) VALUES (?, ?, ?, ?)', [name, hp, weaponAId, weaponBId], function(err) {
        if (err) {
            callback(err, null);
        } else {
            callback(null, { id: this.lastID });
        }
    });
}

module.exports = { getWeapons, getUnits, addUnit };