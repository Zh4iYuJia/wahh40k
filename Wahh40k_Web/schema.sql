-- Schema for mini wargame database

CREATE TABLE IF NOT EXISTS weapons (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    damage INTEGER NOT NULL,
    shots INTEGER NOT NULL,
    hit_threshold INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS units (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    hp INTEGER NOT NULL,
    weapon_a_id INTEGER,
    weapon_b_id INTEGER,
    FOREIGN KEY (weapon_a_id) REFERENCES weapons(id),
    FOREIGN KEY (weapon_b_id) REFERENCES weapons(id)
);

-- Insert some sample data
INSERT INTO weapons (name, damage, shots, hit_threshold) VALUES
('Boltgun', 3, 4, 3),
('Boltpistol', 3, 3, 3),
('BoltCarbine', 2, 4, 3),
('Plasma Gun', 4, 3, 4),
('Chainsword', 2, 5, 4),
('PowerWeapon', 4, 3, 4),
('Heavy Bolter', 3, 5, 4),
('Hell Bolter', 3, 4, 3),
('Phyriclave', 5, 2, 5);

INSERT INTO units (name, hp, weapon_a_id, weapon_b_id) VALUES
('UltraMarine', 20, 1, 5),
('SpaceWolf', 18, 3, 5),
('ImperialFists', 20, 2, 6),
('Legionary', 20, 8, 5),
('Thousand Sons', 20, 9, 8);