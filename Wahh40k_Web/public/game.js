// Game logic for Mini Wargame

let units = [];
let weapons = [];
let smUnit = null;
let csmUnit = null;
let currentTurn = 'sm'; // 'sm' or 'csm'
let gameLog = [];
let turnCount = 0;
let bgmElement = null;
let isMuted = false;

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
    const w = String(winner || '').toLowerCase();
    const displayWinner = (w === 'sm' || w === 'player1') ? 'Player1' : (w === 'csm' || w === 'player2') ? 'Player2' : winner;
    console.log(`Game ended: ${displayWinner} won in ${turns} turns`);
    // Here you can call stats.updateStats(displayWinner.toLowerCase(), turns);
}

// Update log
function updateLog() {
    document.getElementById('log').innerHTML = gameLog.join('<br><br>');
}

// Audio controls
function initAudio() {
    bgmElement = document.getElementById('bgm');
    const muteBtn = document.getElementById('mute-btn');
    try {
        const saved = localStorage.getItem('bgmMuted');
        isMuted = saved === 'true';
    } catch (e) {
        isMuted = false;
    }
    updateMuteButton();
    if (muteBtn) {
        muteBtn.addEventListener('click', () => {
            isMuted = !isMuted;
            try { localStorage.setItem('bgmMuted', String(isMuted)); } catch(e){}
            updateMuteButton();
            if (isMuted) pauseBGM(); else playBGM();
        });
    }
    // Do not autoplay on page load. Music will play only when entering battle.
}

function updateMuteButton() {
    const muteBtn = document.getElementById('mute-btn');
    if (!muteBtn) return;
    muteBtn.textContent = isMuted ? '🔇' : '🔊';
}

function playBGM() {
    if (!bgmElement || isMuted) return Promise.resolve();
    // play may return a promise
    try {
        const p = bgmElement.play();
        if (p && p.catch) p.catch(()=>{});
        return p;
    } catch (e) {
        return Promise.reject(e);
    }
}

function pauseBGM() {
    if (!bgmElement) return;
    try { bgmElement.pause(); } catch(e){}
}

function playForMenu(menu) {
    // menu: 'selection' or 'battle'
    if (menu === 'battle') {
        if (!isMuted) playBGM();
    } else {
        // pause for selection or other menus
        pauseBGM();
    }
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
    const turnText = currentTurn === 'sm' ? 'Player1' : 'Player2';
    document.getElementById('turn-indicator').textContent = `Current Turn: ${turnText}`;
}

// Check for win
function checkWin() {
    if (smUnit && smUnit.hp <= 0) {
        alert('Player2 wins!');
        updateStats('player2', turnCount);
        // reset but keep music playing
        resetGame(true);
    } else if (csmUnit && csmUnit.hp <= 0) {
        alert('Player1 wins!');
        updateStats('player1', turnCount);
        // reset but keep music playing
        resetGame(true);
    }
}

// Reset game
function resetGame(keepPlaying = false) {
    smUnit = null;
    csmUnit = null;
    gameLog = [];
    currentTurn = 'sm';
    turnCount = 0;
    document.getElementById('battle').style.display = 'none';
    document.getElementById('unit-selection').style.display = 'block';
    loadUnits();

    // restore default button labels
    const smA = document.getElementById('sm-attack-a');
    const smB = document.getElementById('sm-attack-b');
    const csmA = document.getElementById('csm-attack-a');
    const csmB = document.getElementById('csm-attack-b');
    if (smA) smA.textContent = 'Attack with Weapon A';
    if (smB) smB.textContent = 'Attack with Weapon B';
    if (csmA) csmA.textContent = 'Attack with Weapon A';
    if (csmB) csmB.textContent = 'Attack with Weapon B';
    // switch audio to selection context unless caller wants to keep playing
    if (!keepPlaying) playForMenu('selection');
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
        // update SM attack button labels with actual weapon names
        const smA = document.getElementById('sm-attack-a');
        const smB = document.getElementById('sm-attack-b');
        if (smA) smA.textContent = `Fire: ${smUnit.weapon_a_name || 'Weapon A'}`;
        if (smB) smB.textContent = `Fire: ${smUnit.weapon_b_name || 'Weapon B'}`;
    } else if (!csmUnit) {
        csmUnit = { ...unit, hp: unit.hp };
        document.getElementById('csm-unit').querySelector('h3').textContent = unit.name;
        updateHP();
        // update CSM attack button labels with actual weapon names
        const csmA = document.getElementById('csm-attack-a');
        const csmB = document.getElementById('csm-attack-b');
        if (csmA) csmA.textContent = `Fire: ${csmUnit.weapon_a_name || 'Weapon A'}`;
        if (csmB) csmB.textContent = `Fire: ${csmUnit.weapon_b_name || 'Weapon B'}`;
        document.getElementById('unit-selection').style.display = 'none';
        document.getElementById('battle').style.display = 'flex';
        // switch audio to battle context
        playForMenu('battle');
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
initAudio();
loadUnits();