const boardElement = document.getElementById('board');
const statusElement = document.getElementById('status');
const restartButton = document.getElementById('restartButton');
const moveInput = document.getElementById('moveInput');
const submitMove = document.getElementById('submitMove');

const human = 'X';
const ai = 'O';
let board = Array(9).fill(' ');
let gameOver = false;

function buildBoard() {
    boardElement.innerHTML = '';
    board.forEach((value) => {
        const cell = document.createElement('button');
        cell.className = 'cell';
        cell.textContent = value === ' ' ? '' : value;
        if (value !== ' ' || gameOver) {
            cell.classList.add('disabled');
            cell.disabled = true;
        }
        boardElement.appendChild(cell);
    });
}

function applyHumanMove(row, col) {
    const index = row * 3 + col;
    if (board[index] !== ' ' || gameOver) return false;
    board[index] = human;
    updateGame();
    return true;
}

function handleMoveSubmit() {
    if (gameOver) return;
    const value = moveInput.value.trim();
    const [rowText, colText] = value.split(/\s+/);
    const row = parseInt(rowText, 10);
    const col = parseInt(colText, 10);

    if (
        Number.isNaN(row) ||
        Number.isNaN(col) ||
        row < 0 || row > 2 ||
        col < 0 || col > 2
    ) {
        statusElement.textContent = 'Invalid move format. Use row col from 0 to 2.';
        return;
    }

    const moved = applyHumanMove(row, col);
    if (!moved) {
        statusElement.textContent = 'Cell is taken or invalid. Try again.';
        return;
    }

    moveInput.value = '';
    if (!gameOver) {
        const aiIndex = computeBestMove(board);
        board[aiIndex] = ai;
        updateGame();
    }
}

function updateGame() {
    buildBoard();
    const winner = findWinner(board);
    if (winner === human) {
        statusElement.textContent = 'You win!';
        gameOver = true;
    } else if (winner === ai) {
        statusElement.textContent = 'AI wins.';
        gameOver = true;
    } else if (!board.includes(' ')) {
        statusElement.textContent = 'Draw.';
        gameOver = true;
    } else {
        statusElement.textContent = 'Your turn';
        if (!board.includes(' ')) {
            gameOver = true;
        }
    }
}

function findWinner(currentBoard) {
    const lines = [
        [0, 1, 2], [3, 4, 5], [6, 7, 8],
        [0, 3, 6], [1, 4, 7], [2, 5, 8],
        [0, 4, 8], [2, 4, 6]
    ];
    for (const [a, b, c] of lines) {
        if (
            currentBoard[a] !== ' ' &&
            currentBoard[a] === currentBoard[b] &&
            currentBoard[b] === currentBoard[c]
        ) {
            return currentBoard[a];
        }
    }
    return null;
}

function computeBestMove(currentBoard) {
    let bestScore = -Infinity;
    let moveIndex = -1;

    for (let i = 0; i < 9; i++) {
        if (currentBoard[i] === ' ') {
            currentBoard[i] = ai;
            const score = minimax(currentBoard, 0, false);
            currentBoard[i] = ' ';
            if (score > bestScore) {
                bestScore = score;
                moveIndex = i;
            }
        }
    }
    return moveIndex;
}

function minimax(currentBoard, depth, isMaximizing) {
    const winner = findWinner(currentBoard);
    if (winner === ai) return 10 - depth;
    if (winner === human) return depth - 10;
    if (!currentBoard.includes(' ')) return 0;

    if (isMaximizing) {
        let best = -Infinity;
        for (let i = 0; i < 9; i++) {
            if (currentBoard[i] === ' ') {
                currentBoard[i] = ai;
                best = Math.max(best, minimax(currentBoard, depth + 1, false));
                currentBoard[i] = ' ';
            }
        }
        return best;
    } else {
        let best = Infinity;
        for (let i = 0; i < 9; i++) {
            if (currentBoard[i] === ' ') {
                currentBoard[i] = human;
                best = Math.min(best, minimax(currentBoard, depth + 1, true));
                currentBoard[i] = ' ';
            }
        }
        return best;
    }
}

function resetGame() {
    board = Array(9).fill(' ');
    gameOver = false;
    statusElement.textContent = 'Your turn';
    moveInput.value = '';
    buildBoard();
}

submitMove.addEventListener('click', handleMoveSubmit);
moveInput.addEventListener('keydown', (event) => {
    if (event.key === 'Enter') {
        handleMoveSubmit();
    }
});

restartButton.addEventListener('click', resetGame);
resetGame();
