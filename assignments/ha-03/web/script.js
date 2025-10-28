let currentMode = 'fpie';
const display = document.getElementById('display');
const resultDiv = document.getElementById('result');

// mode selection
document.querySelectorAll('.mode-btn').forEach(btn => {
    btn.addEventListener('click', function() {
        document.querySelectorAll('.mode-btn').forEach(b => b.classList.remove('active'));
        this.classList.add('active');
        currentMode = this.dataset.mode;
    });
});

// button clicks
document.querySelectorAll('.btn').forEach(btn => {
    btn.addEventListener('click', function() {
        const text = this.textContent;        
        if (text === 'C') {
            display.value = '';
            resultDiv.classList.remove('show');
        } else if (text === '=') {
            calculate();
        } else {
            display.value += text;
            resultDiv.classList.remove('show');
        }
    });
});

// simple input validation - just clean the input after every change
display.addEventListener('input', function() {
    const cursorPos = this.selectionStart;
    const beforeCursor = this.value.slice(0, cursorPos);
    const afterCursor = this.value.slice(cursorPos);
    const cleanedBefore = beforeCursor.replace(/[^0-9+\-*/()]/g, '');
    const cleanedAfter = afterCursor.replace(/[^0-9+\-*/()]/g, '');
    this.value = cleanedBefore + cleanedAfter;
    this.setSelectionRange(cleanedBefore.length, cleanedBefore.length);
    resultDiv.classList.remove('show');
});

// enter key to calculate
display.addEventListener('keypress', (e) => {
    if (e.key === 'Enter') {
        e.preventDefault();
        calculate();
    }
});

async function calculate() {
    const expression = display.value.trim();
    if (!expression) {
        showError('Enter an expression');
        return;
    }
    try {
        const response = await fetch('http://localhost:8080', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({expression, mode: currentMode}),
            signal: AbortSignal.timeout(3000) // 3 second timeout
        });
        const data = await response.json();
        if (data.error) {
            showError(data.error);
        } else {
            showResult(data.result);
        }
    } catch (error) {
        console.error('Fetch error:', error);
        if (error.name === 'TimeoutError') {
            showError('Request timed out');
        } else if (error.name === 'SyntaxError') {
            showError('Invalid response from server');
        } else {
            showError('Could not connect to server');
        }
    }
}

function showResult(result) {
    resultDiv.innerHTML = `<strong>Result:</strong> ${result}`;
    resultDiv.classList.remove('error');
    resultDiv.classList.add('show');
}

function showError(message) {
    resultDiv.innerHTML = `<strong>Error:</strong> ${message}`;
    resultDiv.classList.add('error', 'show');
}