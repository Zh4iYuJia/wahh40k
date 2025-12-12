// Game logic for Mini Wargame

let units = [];
let weapons = [];
let smUnit = null;
let csmUnit = null;
let currentTurn = 'sm'; // 'sm' or 'csm'
let gameLog = [];
let turnCount = 0;

// Dice roll function
function rollDie() {
    return Math.floor(Math.random() * 6) + 1;
}

// Resolve shooting
function resolveShooting(attacker, defender, weapon) {
    if (!attacker || !defender) return; // Safety check
    turnCount++;
    const rolls = [];
    for (let i = 0; i < weapon.shots; i++) {
        rolls.push(rollDie());
    }
    const hits = rolls.filter(r => r >= weapon.hit_threshold).length;
    const damage = hits * weapon.damage;
    defender.hp -= damage;
    if (defender.hp < 0) defender.hp = 0;

    const logEntry = `${attacker.name} fires ${weapon.name} (${weapon.shots} shots, damage ${weapon.damage}, hit ${weapon.hit_threshold}+)<br>Rolls: ${rolls.join(' ')}<br>Hits: ${hits} -> Damage: ${damage}<br>${defender.name} HP: ${defender.hp}`;
    gameLog.push(logEntry);
    updateLog();
    updateHP();
    checkWin();
}

// Update stats (placeholder, can integrate with stats.js if needed)
function updateStats(winner, turns) {
    console.log(`Game ended: ${winner} won in ${turns} turns`);
    // Here you can call stats.updateStats(winner, turns);
}

// Update log
function updateLog() {
    document.getElementById('log').innerHTML = gameLog.join('<br><br>');
}

// Update HP display
function updateHP() {
    if (smUnit) {
        document.getElementById('sm-hp').textContent = `HP: ${smUnit.hp}`;
    }
    if (csmUnit) {
        document.getElementById('csm-hp').textContent = `HP: ${csmUnit.hp}`;
    }
    updateTurnIndicator();
}

// Update turn indicator
function updateTurnIndicator() {
    const turnText = currentTurn === 'sm' ? 'SM' : 'CSM';
    document.getElementById('turn-indicator').textContent = `Current Turn: ${turnText}`;
}

// Check for win
function checkWin() {
    if (smUnit.hp <= 0) {
        alert('CSM wins!');
        updateStats('csm', turnCount);
        resetGame();
    } else if (csmUnit.hp <= 0) {
        alert('SM wins!');
        updateStats('sm', turnCount);
        resetGame();
    }
}

// Reset game
function resetGame() {
    smUnit = null;
    csmUnit = null;
    gameLog = [];
    currentTurn = 'sm';
    turnCount = 0;
    document.getElementById('battle').style.display = 'none';
    document.getElementById('unit-selection').style.display = 'block';
    loadUnits();
}

// Load units from API
function loadUnits() {
    fetch('/api/units')
        .then(response => response.json())
        .then(data => {
            console.log('Loaded units:', data);
            units = data;
            displayUnits();
        })
        .catch(error => console.error('Error loading units:', error));
}

// Display units for selection
function displayUnits() {
    const unitsList = document.getElementById('units-list');
    unitsList.innerHTML = '';
    units.forEach(unit => {
        const card = document.createElement('div');
        card.className = 'unit-card';
        card.innerHTML = `
            <h4>${unit.name}</h4>
            <p>HP: ${unit.hp}</p>
            <p>Weapon A: ${unit.weapon_a_name} (dmg: ${unit.weapon_a_damage}, shots: ${unit.weapon_a_shots}, hit: ${unit.weapon_a_hit}+)</p>
            <p>Weapon B: ${unit.weapon_b_name} (dmg: ${unit.weapon_b_damage}, shots: ${unit.weapon_b_shots}, hit: ${unit.weapon_b_hit}+)</p>
        `;
        card.onclick = () => selectUnit(unit);
        unitsList.appendChild(card);
    });
}

// Select unit (simple: first for SM, second for CSM)
function selectUnit(unit) {
    if (!smUnit) {
        smUnit = { ...unit, hp: unit.hp };
        document.getElementById('sm-unit').querySelector('h3').textContent = unit.name;
        updateHP();
    } else if (!csmUnit) {
        csmUnit = { ...unit, hp: unit.hp };
        document.getElementById('csm-unit').querySelector('h3').textContent = unit.name;
        updateHP();
        document.getElementById('unit-selection').style.display = 'none';
        document.getElementById('battle').style.display = 'flex';
    }
}

// Attack buttons
document.getElementById('sm-attack-a').onclick = () => {
    if (currentTurn === 'sm' && smUnit) {
        const weapon = { name: smUnit.weapon_a_name, damage: smUnit.weapon_a_damage, shots: smUnit.weapon_a_shots, hit_threshold: smUnit.weapon_a_hit };
        resolveShooting(smUnit, csmUnit, weapon);
        currentTurn = 'csm';
    }
};

document.getElementById('sm-attack-b').onclick = () => {
    if (currentTurn === 'sm' && smUnit) {
        const weapon = { name: smUnit.weapon_b_name, damage: smUnit.weapon_b_damage, shots: smUnit.weapon_b_shots, hit_threshold: smUnit.weapon_b_hit };
        resolveShooting(smUnit, csmUnit, weapon);
        currentTurn = 'csm';
    }
};

document.getElementById('csm-attack-a').onclick = () => {
    if (currentTurn === 'csm' && csmUnit) {
        const weapon = { name: csmUnit.weapon_a_name, damage: csmUnit.weapon_a_damage, shots: csmUnit.weapon_a_shots, hit_threshold: csmUnit.weapon_a_hit };
        resolveShooting(csmUnit, smUnit, weapon);
        currentTurn = 'sm';
    }
};

document.getElementById('csm-attack-b').onclick = () => {
    if (currentTurn === 'csm' && csmUnit) {
        const weapon = { name: csmUnit.weapon_b_name, damage: csmUnit.weapon_b_damage, shots: csmUnit.weapon_b_shots, hit_threshold: csmUnit.weapon_b_hit };
        resolveShooting(csmUnit, smUnit, weapon);
        currentTurn = 'sm';
    }
};

// Initialize
loadUnits();