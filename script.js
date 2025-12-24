// Completely rewritten script.js for SIM Mateo exhibit
// This version wires up all buttons and screen transitions
// and provides a simple, self-contained logic for both scenarios.

document.addEventListener("DOMContentLoaded", function () {
    // ------------------------------
    // DOM Element References
    // ------------------------------
    const startButton = document.getElementById("start-button");
    const startScreen = document.getElementById("start-screen");

    const instructionContainer = document.getElementById("instruction-container");
    const instructionScreens = Array.from(document.getElementsByClassName("instruction-screen"));
    const instructionBack = document.getElementById("instruction-back");
    const instructionNext = document.getElementById("instruction-next");

    const header = document.getElementById("header");
    const restartButton = document.getElementById("restart-button");

    const mainScreen = document.getElementById("main-screen");
    const scenario1Page = document.getElementById("scenario1-page");
    const scenario2Page = document.getElementById("scenario2-page");

    const cardsAllCA = document.getElementById("cards-all");
    const cardsAllSMC = document.getElementById("cards-all-sm");

    const messageCA = document.getElementById("message-ca");
    const messageSMC = document.getElementById("message-sm");

    const extraAnimation = document.getElementById("extra-animation");
    const sunburst = document.getElementById("sunburst");

    const addCardButton = document.getElementById("add-card");
    const removeCardButton = document.getElementById("remove-card");

    const modal = document.getElementById("modal");
    const modalClose = document.getElementById("modal-close");

    const finalModal = document.getElementById("finalModal");
    const finalModalContent = document.getElementById("finalModalContent");
    const theEndScreen = document.getElementById("theEndScreen");
    const theEndButton = document.getElementById("theEndButton");

    // ------------------------------
    // Sound Effects Setup
    // ------------------------------
    const clickSound = new Audio("assets/SoundWindowsNavigationStart.wav");
    const scenarioCASound_Start = new Audio("assets/05-California.mp3");
    const scenarioCASound_30 = new Audio("assets/SoundScenarioCA_30.mp3");
    const scenarioCASound_win = new Audio("assets/SoundScenarioCA_win.mp3");
    const scenarioSMCSound_Start = new Audio("assets/SoundScenarioSMC_Start.mp3");
    const scenarioSMCSound_70 = new Audio("assets/SoundScenarioSMC_70.mp3");
    const scenarioSMCSound_win = new Audio("assets/SoundScenarioSMC_win.mp3");
    const wrongSound = new Audio("assets/SoundWindowsCriticalStop.mp3");
    const welcomeSound = new Audio("assets/01-Welcome.mp3");
    const instruction1Sound = new Audio("assets/02-Green Card.mp3");
    const instruction2Sound = new Audio("assets/03-Red Card.mp3"); // kept for completeness
    const instruction3Sound = new Audio("assets/04-Tap.mp3");
    const winSound = new Audio("assets/Tada_final.mp3");
    const wrongWrongSound = new Audio("assets/SoundWindowsCriticalWarning.mp3");

    let currentSound = null;      // currently playing narration sound
    let instructionSoundTimer;    // timer for any delayed instruction audio

    // ------------------------------
    // State
    // ------------------------------
    const CARD_KEYS = ["a1","a2","c1","c2","d1","d2","d3","e1","e2","f1"];

    // "Scenario" names: 1 = California, 2 = San Mateo County
    let activeScenario = 0;
    let currentInstruction = 1;
    const totalInstructions = 2; // logical: screen 1 + screen 3

    // Card state: "red" or "green"
    const caState = {};
    const smcState = {};

    let caGreenCount = 0;
    let smcGreenCount = 0;

    let consecutiveRedCount = 0;
    let milestone30Played = false;
    let milestone56Played = false; // used as CA win milestone
    let milestone70Played = false;
    let milestone100Played = false;

    // ------------------------------
    // Audio helpers
    // ------------------------------
    function playNarration(sound) {
        if (!sound) return;
        try {
            if (currentSound && currentSound !== sound) {
                currentSound.pause();
                currentSound.currentTime = 0;
            }
            currentSound = sound;
            sound.currentTime = 0;
            sound.play().catch(() => {
                // ignore autoplay errors in kiosk browsers
            });
        } catch (e) {
            console.warn("Audio play error:", e);
        }
    }

    function playClick() {
        try {
            clickSound.currentTime = 0;
            clickSound.play().catch(() => {});
        } catch (e) {
            console.warn("Click sound error:", e);
        }
    }

    // ------------------------------
    // Visual helpers
    // ------------------------------
    function animateButton(el) {
        if (!el) return;
        el.classList.add("button-click");
        setTimeout(() => el.classList.remove("button-click"), 200);
        playClick();
    }

    function hideAllScreens() {
        startScreen.style.display = "none";
        instructionContainer.style.display = "none";
        mainScreen.style.display = "none";
        scenario1Page.style.display = "none";
        scenario2Page.style.display = "none";
        theEndScreen.style.display = "none";
    }

    function hideAllModalsAndEffects() {
        if (modal) modal.style.display = "none";
        if (finalModal) finalModal.style.display = "none";
        if (extraAnimation) extraAnimation.style.display = "none";
        if (sunburst) sunburst.style.display = "none";
    }

    function showStartScreen() {
        hideAllScreens();
        hideAllModalsAndEffects();

        header.style.display = "none";
        startScreen.style.display = "block";

        activeScenario = 0;
        currentInstruction = 1;
        resetAllCards();
        resetStateFlags();
    }

    function showInstructionScreen(index) {
        hideAllScreens();
        header.style.display = "block";
        instructionContainer.style.display = "block";

        currentInstruction = index;

        instructionScreens.forEach((screen, i) => {
            screen.style.display = (i === (index - 1)) ? "block" : "none";
        });
    }

    function startScenario1() {
        hideAllScreens();
        hideAllModalsAndEffects();

        mainScreen.style.display = "block";
        scenario1Page.style.display = "block";
        scenario2Page.style.display = "none";

        activeScenario = 1;
        resetAllCards();
        resetStateFlags();

        messageCA.textContent = "";
        messageSMC.textContent = "";

        playNarration(scenarioCASound_Start);
    }

    function startScenario2() {
        hideAllScreens();
        hideAllModalsAndEffects();

        mainScreen.style.display = "block";
        scenario1Page.style.display = "none";
        scenario2Page.style.display = "block";

        activeScenario = 2;

        // reset SMC only
        smcGreenCount = 0;
        CARD_KEYS.forEach(key => {
            smcState[key] = "red";
            const el = getCardElement("smc", key);
            if (el) el.classList.remove("green");
        });

        consecutiveRedCount = 0;
        milestone70Played = false;
        milestone100Played = false;

        messageSMC.textContent = "";

        playNarration(scenarioSMCSound_Start);
    }

    function showScenario1WinModal() {
        if (modal) {
            modal.style.display = "block";
        }
    }

    function showFinalModal() {
        if (finalModal) {
            finalModal.style.display = "block";
        }
        if (extraAnimation) extraAnimation.style.display = "block";
        if (sunburst) sunburst.style.display = "block";

        playNarration(winSound);
    }

    function showTheEndScreen() {
        hideAllScreens();
        hideAllModalsAndEffects();

        header.style.display = "none";
        theEndScreen.style.display = "block";
    }

    function resetAllCards() {
        caGreenCount = 0;
        smcGreenCount = 0;

        CARD_KEYS.forEach(key => {
            caState[key] = "red";
            smcState[key] = "red";

            const elCA = getCardElement("ca", key);
            const elSMC = getCardElement("smc", key);

            if (elCA) elCA.classList.remove("green");
            if (elSMC) elSMC.classList.remove("green");
        });
    }

    function resetStateFlags() {
        consecutiveRedCount = 0;
        milestone30Played = false;
        milestone56Played = false;
        milestone70Played = false;
        milestone100Played = false;
    }

    function getCardElement(scenario, key) {
        if (scenario === "ca") {
            return document.getElementById("card-" + key);
        } else if (scenario === "smc") {
            return document.getElementById("card-" + key + "-sm");
        }
        return null;
    }

    // ------------------------------
    // Card logic
    // ------------------------------
    function applyCardState(scenario, key, color) {
        const state = (scenario === "ca") ? caState : smcState;
        const cardEl = getCardElement(scenario, key);
        if (!cardEl) {
            console.warn("No card element for", scenario, key);
            return;
        }

        const prev = state[key] || "red";
        const next = (color === "green") ? "green" : "red";

        // Visual update
        if (next === "green") {
            cardEl.classList.add("green");
        } else {
            cardEl.classList.remove("green");
        }

        state[key] = next;

        // Progress tracking
        if (scenario === "ca") {
            if (prev !== "green" && next === "green") caGreenCount++;
            if (prev === "green" && next !== "green") caGreenCount--;
            handleScenario1Progress(prev, next);
        } else {
            if (prev !== "green" && next === "green") smcGreenCount++;
            if (prev === "green" && next !== "green") smcGreenCount--;
            handleScenario2Progress(prev, next);
        }
    }

    function toggleCardFromClick(cardEl, scenario) {
        if (!cardEl) return;
        // id is "card-a1" or "card-a1-sm"
        const id = cardEl.id;
        const match = id.match(/^card-([a-z0-9]+)(-sm)?$/i);
        if (!match) return;

        const key = match[1].toLowerCase();
        const isGreen = cardEl.classList.contains("green");
        const newColor = isGreen ? "red" : "green";

        applyCardState(scenario, key, newColor);
    }

    function handleScenario1Progress(prev, next) {
        // track wrong guesses with red streaks
        if (next === "red") {
            consecutiveRedCount++;
            if (consecutiveRedCount >= 3) {
                playNarration(wrongWrongSound);
            } else {
                playNarration(wrongSound);
            }
        } else if (next === "green") {
            consecutiveRedCount = 0;
        }

        // CA cards represent 10% each
        const percent = caGreenCount * 10;
        if (percent > 0) {
            messageCA.textContent = "Your guess: " + percent + "% clean electricity in California.";
        } else {
            messageCA.textContent = "";
        }

        // Milestones (example thresholds)
        if (!milestone30Played && percent >= 30) {
            milestone30Played = true;
            playNarration(scenarioCASound_30);
        }

        // Treat 60% as the "correct" answer for this exhibit
        if (!milestone56Played && percent >= 60) {
            milestone56Played = true;
            playNarration(scenarioCASound_win);
            showScenario1WinModal();
        }
    }

    function handleScenario2Progress(prev, next) {
        if (next === "red") {
            consecutiveRedCount++;
            if (consecutiveRedCount >= 3) {
                playNarration(wrongWrongSound);
            } else {
                playNarration(wrongSound);
            }
        } else if (next === "green") {
            consecutiveRedCount = 0;
        }

        const percent = smcGreenCount * 10;
        if (percent > 0) {
            messageSMC.textContent = "Your guess: " + percent + "% clean electricity in San Mateo County.";
        } else {
            messageSMC.textContent = "";
        }

        // 70% milestone
        if (!milestone70Played && percent >= 70) {
            milestone70Played = true;
            playNarration(scenarioSMCSound_70);
        }

        // 100% (all 10 cards) as final "win"
        if (!milestone100Played && percent >= 100) {
            milestone100Played = true;
            playNarration(scenarioSMCSound_win);
            showFinalModal();
        }
    }

    // ------------------------------
    // WebSocket Integration (optional)
    // ------------------------------
    let socket = null;

    try {
        socket = new WebSocket(`ws://${window.location.hostname}:3000`);

        socket.addEventListener("open", () => {
            console.log("WebSocket connected");
        });

        socket.addEventListener("close", () => {
            console.log("WebSocket closed");
        });

        socket.addEventListener("error", (err) => {
            console.warn("WebSocket error:", err);
        });

        socket.addEventListener("message", (event) => {
            handleSocketMessage(event.data);
        });
    } catch (e) {
        console.warn("Unable to open WebSocket:", e);
    }

    function handleSocketMessage(rawMsg) {
        if (typeof rawMsg !== "string") {
            rawMsg = String(rawMsg);
        }
        const msg = rawMsg.trim().toLowerCase();
        const match = msg.match(/^(a1|a2|c1|c2|d1|d2|d3|e1|e2|f1)_(green|red)$/i);
        if (!match) {
            console.warn("Ignoring non-command message:", msg);
            return;
        }

        const key = match[1].toLowerCase();
        const color = match[2].toLowerCase();

        // Apply to whichever scenario is active; default to California
        const scenario = (activeScenario === 2) ? "smc" : "ca";
        applyCardState(scenario, key, color);
    }

    function sendCardCommand(key, color) {
        if (!socket || socket.readyState !== WebSocket.OPEN) return;
        try {
            socket.send(key + "_" + color);
        } catch (e) {
            console.warn("Failed to send WebSocket message:", e);
        }
    }

    // ------------------------------
    // Controls (hidden on kiosk, handy for testing)
    // ------------------------------
    function changeCardCount(delta) {
        const scenario = (activeScenario === 2) ? "smc" : "ca";
        const state = (scenario === "ca") ? caState : smcState;

        if (delta > 0) {
            // Turn next red card green
            for (const key of CARD_KEYS) {
                if (state[key] !== "green") {
                    applyCardState(scenario, key, "green");
                    sendCardCommand(key, "green");
                    break;
                }
            }
        } else if (delta < 0) {
            // Turn last green card red
            for (let i = CARD_KEYS.length - 1; i >= 0; i--) {
                const key = CARD_KEYS[i];
                if (state[key] === "green") {
                    applyCardState(scenario, key, "red");
                    sendCardCommand(key, "red");
                    break;
                }
            }
        }
    }

    if (addCardButton) {
        addCardButton.addEventListener("click", () => {
            animateButton(addCardButton);
            changeCardCount(1);
        });
    }

    if (removeCardButton) {
        removeCardButton.addEventListener("click", () => {
            animateButton(removeCardButton);
            changeCardCount(-1);
        });
    }

    // ------------------------------
    // Button wiring
    // ------------------------------
    if (startButton) {
        startButton.addEventListener("click", () => {
            animateButton(startButton);

            // Start at first instruction screen
            clearTimeout(instructionSoundTimer);
            playNarration(welcomeSound);
            instructionSoundTimer = setTimeout(() => {
                playNarration(instruction1Sound);
            }, 2000);

            showInstructionScreen(1);
        });
    }

    if (instructionNext) {
        instructionNext.addEventListener("click", () => {
            animateButton(instructionNext);

            if (currentInstruction < totalInstructions) {
                // Go to next instruction screen
                showInstructionScreen(currentInstruction + 1);
                playNarration(instruction3Sound);
            } else {
                // Start Scenario 1 after the last instruction
                startScenario1();
            }
        });
    }

    if (instructionBack) {
        instructionBack.addEventListener("click", () => {
            animateButton(instructionBack);

            if (currentInstruction > 1) {
                showInstructionScreen(currentInstruction - 1);
                playNarration(instruction1Sound);
            } else {
                // Back from first instruction to start screen
                showStartScreen();
            }
        });
    }

    if (restartButton) {
        restartButton.addEventListener("click", () => {
            animateButton(restartButton);
            // easiest reliable reset: full reload
            window.location.reload();
        });
    }

    if (modalClose) {
        modalClose.addEventListener("click", () => {
            animateButton(modalClose);
            if (modal) modal.style.display = "none";

            // Move to Scenario 2 after CA win modal
            if (activeScenario === 1) {
                startScenario2();
            }
        });
    }

    if (theEndButton) {
        theEndButton.addEventListener("click", () => {
            animateButton(theEndButton);
            showTheEndScreen();
        });
    }

    // ------------------------------
    // Card click wiring (for browser interaction)
    // ------------------------------
    if (cardsAllCA) {
        const caCards = Array.from(cardsAllCA.getElementsByClassName("card"));
        caCards.forEach(card => {
            card.addEventListener("click", () => {
                if (activeScenario !== 1) return;
                animateButton(card);
                toggleCardFromClick(card, "ca");
            });
        });
    }

    if (cardsAllSMC) {
        const smcCards = Array.from(cardsAllSMC.getElementsByClassName("card"));
        smcCards.forEach(card => {
            card.addEventListener("click", () => {
                if (activeScenario !== 2) return;
                animateButton(card);
                toggleCardFromClick(card, "smc");
            });
        });
    }

    // ------------------------------
    // Initial state
    // ------------------------------
    showStartScreen();
});
