// Game statistics module

let stats = {
    gamesPlayed: 0,
    smWins: 0,
    csmWins: 0,
    averageTurns: 0,
    totalTurns: 0
};

// Load stats from localStorage
function loadStats() {
    const saved = localStorage.getItem('wargameStats');
    if (saved) {
        stats = JSON.parse(saved);
    }
}

// Save stats to localStorage
function saveStats() {
    localStorage.setItem('wargameStats', JSON.stringify(stats));
}

// Update stats after a game
function updateStats(winner, turns) {
    stats.gamesPlayed++;
    if (winner === 'sm') {
        stats.smWins++;
    } else if (winner === 'csm') {
        stats.csmWins++;
    }
    stats.totalTurns += turns;
    stats.averageTurns = stats.totalTurns / stats.gamesPlayed;
    saveStats();
}

// Get stats
function getStats() {
    return { ...stats };
}

// Initialize
loadStats();

module.exports = { updateStats, getStats };