// *********************
// Define LED pins for each board and pair
// *********************

// Board A LED definitions:
// LED_RED_A1: Red LED for RFID Reader 1 is connected to pin 23
#define LED_RED_A1   23  // Red LED for RFID Reader 1
// LED_GREEN_A1: Green LED for RFID Reader 1 is connected to pin 22
#define LED_GREEN_A1 22  // Green LED for RFID Reader 1
// LED_RED_A2: Red LED for RFID Reader 2 is connected to pin 25
#define LED_RED_A2   25  // Red LED for RFID Reader 2
// LED_GREEN_A2: Green LED for RFID Reader 2 is connected to pin 24
#define LED_GREEN_A2 24  // Green LED for RFID Reader 2

// Board C LED definitions:
// LED_RED_C1: Red LED for Board C, Pair 1, is connected to pin 27
#define LED_RED_C1    27  // Board C, Pair 1, Red LED
// LED_GREEN_C1: Green LED for Board C, Pair 1, is connected to pin 26
#define LED_GREEN_C1  26  // Board C, Pair 1, Green LED
// LED_RED_C2: Red LED for Board C, Pair 2, is connected to pin 29
#define LED_RED_C2    29  // Board C, Pair 2, Red LED
// LED_GREEN_C2: Green LED for Board C, Pair 2, is connected to pin 28
#define LED_GREEN_C2  28  // Board C, Pair 2, Green LED

// Board D LED definitions:
// LED_RED_D1: Red LED for Board D, Pair 1, is connected to pin 31 (White Orange cable, In 1)
#define LED_RED_D1    31  // Board D, Pair 1, Red LED (White Orange cable, In 1)
// LED_GREEN_D1: Green LED for Board D, Pair 1, is connected to pin 30 (Orange cable, In 2)
#define LED_GREEN_D1  30  // Board D, Pair 1, Green LED (Orange cable, In 2)
// LED_RED_D2: Red LED for Board D, Pair 2, is connected to pin 33 (White Green cable, In 3)
#define LED_RED_D2    33  // Board D, Pair 2, Red LED (White Green cable, In 3)
// LED_GREEN_D2: Green LED for Board D, Pair 2, is connected to pin 32 (Blue cable, In 4)
#define LED_GREEN_D2  32  // Board D, Pair 2, Green LED (Blue cable, In 4)
// LED_RED_D3: Red LED for Board D, Pair 3, is connected to pin 35 (White Blue cable, In 5)
#define LED_RED_D3    35  // Board D, Pair 3, Red LED (White Blue cable, In 5)
// LED_GREEN_D3: Green LED for Board D, Pair 3, is connected to pin 34 (Green cable, In 6)
#define LED_GREEN_D3  34  // Board D, Pair 3, Green LED (Green cable, In 6)

// Board E LED definitions:
// LED_RED_E1: Red LED for Board E, Pair 1, is connected to pin 37 (White Orange cable, In 1)
#define LED_RED_E1    37  // Board E, Pair 1, Red LED (White Orange cable, In 1)
// LED_GREEN_E1: Green LED for Board E, Pair 1, is connected to pin 36 (Orange cable, In 2)
#define LED_GREEN_E1  36  // Board E, Pair 1, Green LED (Orange cable, In 2)
// LED_RED_E2: Red LED for Board E, Pair 2, is connected to pin 39 (White Green cable, In 3)
#define LED_RED_E2    39  // Board E, Pair 2, Red LED (White Green cable, In 3)
// LED_GREEN_E2: Green LED for Board E, Pair 2, is connected to pin 38 (Blue cable, In 4)
#define LED_GREEN_E2  38  // Board E, Pair 2, Green LED (Blue cable, In 4)

// Board F LED definitions:
// LED_RED_F1: Red LED for Board F, Pair 1, is connected to pin 41
#define LED_RED_F1    41  // Board F, Pair 1, Red LED
// LED_GREEN_F1: Green LED for Board F, Pair 1, is connected to pin 40
#define LED_GREEN_F1  40  // Board F, Pair 1, Green LED

// *********************
// Setup function: called once at startup
// *********************
void setup() {
  // Initialize serial communications for four Nano boards:
  Serial.begin(9600);   // Communication with Nano 1 via Serial
  Serial1.begin(9600);  // Communication with Nano 2 via Serial1
  Serial2.begin(9600);  // Communication with Nano 3 via Serial2
  Serial3.begin(9600);  // Communication with Nano 4 via Serial3
  
  // Set up output pins for Board A LEDs:
  pinMode(LED_RED_A1, OUTPUT);    // Set LED_RED_A1 as an output
  pinMode(LED_GREEN_A1, OUTPUT);  // Set LED_GREEN_A1 as an output
  pinMode(LED_RED_A2, OUTPUT);    // Set LED_RED_A2 as an output
  pinMode(LED_GREEN_A2, OUTPUT);  // Set LED_GREEN_A2 as an output

  // Set up output pins for Board C LEDs:
  pinMode(LED_RED_C1, OUTPUT);    // Set LED_RED_C1 as an output
  pinMode(LED_GREEN_C1, OUTPUT);  // Set LED_GREEN_C1 as an output
  pinMode(LED_RED_C2, OUTPUT);    // Set LED_RED_C2 as an output
  pinMode(LED_GREEN_C2, OUTPUT);  // Set LED_GREEN_C2 as an output

  // Set up output pins for Board D LEDs:
  pinMode(LED_RED_D1, OUTPUT);    // Set LED_RED_D1 as an output
  pinMode(LED_GREEN_D1, OUTPUT);  // Set LED_GREEN_D1 as an output
  pinMode(LED_RED_D2, OUTPUT);    // Set LED_RED_D2 as an output
  pinMode(LED_GREEN_D2, OUTPUT);  // Set LED_GREEN_D2 as an output
  pinMode(LED_RED_D3, OUTPUT);    // Set LED_RED_D3 as an output
  pinMode(LED_GREEN_D3, OUTPUT);  // Set LED_GREEN_D3 as an output

  // Set up output pins for Board E LEDs:
  pinMode(LED_RED_E1, OUTPUT);    // Set LED_RED_E1 as an output
  pinMode(LED_GREEN_E1, OUTPUT);  // Set LED_GREEN_E1 as an output
  pinMode(LED_RED_E2, OUTPUT);    // Set LED_RED_E2 as an output
  pinMode(LED_GREEN_E2, OUTPUT);  // Set LED_GREEN_E2 as an output

  // Set up output pins for Board F LEDs:
  pinMode(LED_RED_F1, OUTPUT);    // Set LED_RED_F1 as an output
  pinMode(LED_GREEN_F1, OUTPUT);  // Set LED_GREEN_F1 as an output

  // Turn all LEDs off initially (For active-low LEDs, HIGH means off)
  resetLEDs(); // Call the function to set all LED pins to HIGH (off)
}

// *********************
// Loop function: runs continuously after setup()
// *********************
void loop() {
  // Check for commands from Nano A via Serial:
  if (Serial.available() > 0) {  
    String command = Serial.readStringUntil('\n'); // Read command until newline
    command.trim(); // Remove any extra whitespace
    handleLEDCommand(command);  // Process the received command
  }
  
  // Check for commands from Nano C via Serial1:
  if (Serial1.available() > 0) {  
    String command = Serial1.readStringUntil('\n'); // Read command until newline
    command.trim(); // Remove any extra whitespace
    handleLEDCommand(command);  // Process the received command
  }
  
  // Check for commands from Nano D via Serial2:
  if (Serial2.available() > 0) {  
    String command = Serial2.readStringUntil('\n'); // Read command until newline
    command.trim(); // Remove any extra whitespace
    handleLEDCommand(command);  // Process the received command
  }
  
  // Check for commands from Nano E via Serial3:
  if (Serial3.available() > 0) {  
    String command = Serial3.readStringUntil('\n'); // Read command until newline
    command.trim(); // Remove any extra whitespace
    handleLEDCommand(command);  // Process the received command
  }

  // Check the status of each LED group for blinking logic:
  checkGroupStatus();  
}

// *********************
// Function: handleLEDCommand()
// Description: Processes incoming command strings to control the LED states.
// Commands include a board and pair identifier (e.g., "A1_RED", "C2_GREEN").
// *********************
void handleLEDCommand(String command) {
  // --- Board A Commands ---
  if (command == "A1_RED") { 
    digitalWrite(LED_RED_A1, LOW);   // Turn on Board A pair 1 red LED (active LOW)
    digitalWrite(LED_GREEN_A1, HIGH);  // Turn off Board A pair 1 green LED
  } else if (command == "A1_GREEN") {
    digitalWrite(LED_RED_A1, HIGH);    // Turn off Board A pair 1 red LED
    digitalWrite(LED_GREEN_A1, LOW);   // Turn on Board A pair 1 green LED
  } else if (command == "A2_RED") {
    digitalWrite(LED_RED_A2, LOW);    // Turn on Board A pair 2 red LED
    digitalWrite(LED_GREEN_A2, HIGH);  // Turn off Board A pair 2 green LED
  } else if (command == "A2_GREEN") {
    digitalWrite(LED_RED_A2, HIGH);    // Turn off Board A pair 2 red LED
    digitalWrite(LED_GREEN_A2, LOW);   // Turn on Board A pair 2 green LED
  }
  // --- Board C Commands ---
  else if (command == "C1_RED") { 
    digitalWrite(LED_RED_C1, LOW);    // Turn on Board C pair 1 red LED
    digitalWrite(LED_GREEN_C1, HIGH);  // Turn off Board C pair 1 green LED
  } else if (command == "C1_GREEN") {
    digitalWrite(LED_RED_C1, HIGH);    // Turn off Board C pair 1 red LED
    digitalWrite(LED_GREEN_C1, LOW);   // Turn on Board C pair 1 green LED
  } else if (command == "C2_RED") {
    digitalWrite(LED_RED_C2, LOW);    // Turn on Board C pair 2 red LED
    digitalWrite(LED_GREEN_C2, HIGH);  // Turn off Board C pair 2 green LED
  } else if (command == "C2_GREEN") {
    digitalWrite(LED_RED_C2, HIGH);    // Turn off Board C pair 2 red LED
    digitalWrite(LED_GREEN_C2, LOW);   // Turn on Board C pair 2 green LED
  }
  // --- Board D Commands ---
  else if (command == "D1_RED") {
    digitalWrite(LED_RED_D1, LOW);    // Turn on Board D pair 1 red LED
    digitalWrite(LED_GREEN_D1, HIGH);  // Turn off Board D pair 1 green LED
  } else if (command == "D1_GREEN") {
    digitalWrite(LED_RED_D1, HIGH);    // Turn off Board D pair 1 red LED
    digitalWrite(LED_GREEN_D1, LOW);   // Turn on Board D pair 1 green LED
  } else if (command == "D2_RED") {
    digitalWrite(LED_RED_D2, LOW);    // Turn on Board D pair 2 red LED
    digitalWrite(LED_GREEN_D2, HIGH);  // Turn off Board D pair 2 green LED
  } else if (command == "D2_GREEN") {
    digitalWrite(LED_RED_D2, HIGH);    // Turn off Board D pair 2 red LED
    digitalWrite(LED_GREEN_D2, LOW);   // Turn on Board D pair 2 green LED
  } else if (command == "D3_RED") {
    digitalWrite(LED_RED_D3, LOW);    // Turn on Board D pair 3 red LED
    digitalWrite(LED_GREEN_D3, HIGH);  // Turn off Board D pair 3 green LED
  } else if (command == "D3_GREEN") {
    digitalWrite(LED_RED_D3, HIGH);    // Turn off Board D pair 3 red LED
    digitalWrite(LED_GREEN_D3, LOW);   // Turn on Board D pair 3 green LED
  }
  // --- Board E Commands ---
  else if (command == "E1_RED") {
    digitalWrite(LED_RED_E1, LOW);    // Turn on Board E pair 1 red LED
    digitalWrite(LED_GREEN_E1, HIGH);  // Turn off Board E pair 1 green LED
  } else if (command == "E1_GREEN") {
    digitalWrite(LED_RED_E1, HIGH);    // Turn off Board E pair 1 red LED
    digitalWrite(LED_GREEN_E1, LOW);   // Turn on Board E pair 1 green LED
  } else if (command == "E2_RED") {
    digitalWrite(LED_RED_E2, LOW);    // Turn on Board E pair 2 red LED
    digitalWrite(LED_GREEN_E2, HIGH);  // Turn off Board E pair 2 green LED
  } else if (command == "E2_GREEN") {
    digitalWrite(LED_RED_E2, HIGH);    // Turn off Board E pair 2 red LED
    digitalWrite(LED_GREEN_E2, LOW);   // Turn on Board E pair 2 green LED
  }
  // --- Board F Commands ---
  else if (command == "F1_RED") {
    digitalWrite(LED_RED_F1, LOW);    // Turn on Board F pair 1 red LED
    digitalWrite(LED_GREEN_F1, HIGH);  // Turn off Board F pair 1 green LED
  } else if (command == "F1_GREEN") {
    digitalWrite(LED_RED_F1, HIGH);    // Turn off Board F pair 1 red LED
    digitalWrite(LED_GREEN_F1, LOW);   // Turn on Board F pair 1 green LED
  }
}

// *********************
// Function: checkGroupStatus()
// Description: Checks the status of each LED pair (group) across all boards.
//              If all groups are active (i.e., at least one LED in each pair is on),
//              then determine if all are green, and blink accordingly.
// *********************
void checkGroupStatus() {
  // Board A: Check if any LED (red or green) in each pair is on (active LOW)
  bool groupA1On = (digitalRead(LED_RED_A1) == LOW || digitalRead(LED_GREEN_A1) == LOW);
  bool groupA2On = (digitalRead(LED_RED_A2) == LOW || digitalRead(LED_GREEN_A2) == LOW);

  // Board C: Check status for each LED pair
  bool groupC1On = (digitalRead(LED_RED_C1) == LOW || digitalRead(LED_GREEN_C1) == LOW);
  bool groupC2On = (digitalRead(LED_RED_C2) == LOW || digitalRead(LED_GREEN_C2) == LOW);

  // Board D: Check status for each of the three LED pairs
  bool groupD1On = (digitalRead(LED_RED_D1) == LOW || digitalRead(LED_GREEN_D1) == LOW);
  bool groupD2On = (digitalRead(LED_RED_D2) == LOW || digitalRead(LED_GREEN_D2) == LOW);
  bool groupD3On = (digitalRead(LED_RED_D3) == LOW || digitalRead(LED_GREEN_D3) == LOW);

  // Board E: Check status for each LED pair
  bool groupE1On = (digitalRead(LED_RED_E1) == LOW || digitalRead(LED_GREEN_E1) == LOW);
  bool groupE2On = (digitalRead(LED_RED_E2) == LOW || digitalRead(LED_GREEN_E2) == LOW);

  // Board F: Check status for its single LED pair
  bool groupF1On = (digitalRead(LED_RED_F1) == LOW || digitalRead(LED_GREEN_F1) == LOW);

  // If all LED groups (across all boards) are active...
  if (groupA1On && groupA2On && groupC1On && groupC2On &&
      groupD1On && groupD2On && groupD3On &&
      groupE1On && groupE2On &&
      groupF1On) {

    // Check if all green LEDs in every group are on (active LOW means LED is on)
    bool allGreen = (digitalRead(LED_GREEN_A1) == LOW && digitalRead(LED_GREEN_A2) == LOW &&
                     digitalRead(LED_GREEN_C1) == LOW && digitalRead(LED_GREEN_C2) == LOW &&
                     digitalRead(LED_GREEN_D1) == LOW && digitalRead(LED_GREEN_D2) == LOW && digitalRead(LED_GREEN_D3) == LOW &&
                     digitalRead(LED_GREEN_E1) == LOW && digitalRead(LED_GREEN_E2) == LOW &&
                     digitalRead(LED_GREEN_F1) == LOW);

    // If all LED groups are green, blink all green LEDs; otherwise, blink all red LEDs.
    if (allGreen) {
      blinkLEDs(LED_GREEN_A1, LED_GREEN_A2,
                LED_GREEN_C1, LED_GREEN_C2,
                LED_GREEN_D1, LED_GREEN_D2, LED_GREEN_D3,
                LED_GREEN_E1, LED_GREEN_E2,
                LED_GREEN_F1);
    } else {
      blinkLEDs(LED_RED_A1, LED_RED_A2,
                LED_RED_C1, LED_RED_C2,
                LED_RED_D1, LED_RED_D2, LED_RED_D3,
                LED_RED_E1, LED_RED_E2,
                LED_RED_F1);
    }
  }
}

// *********************
// Function: blinkLEDs()
// Description: Blinks a group of 10 LED pins five times.
// Parameters: 10 LED pin numbers (one for each group)
// *********************
void blinkLEDs(int led1, int led2, int led3, int led4, int led5, int led6,
               int led7, int led8, int led9, int led10) {
  // Blink the LEDs five times:
  for (int i = 0; i < 5; i++) {
    // Turn on (set LOW for active-low LEDs) all 10 LEDs:
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    digitalWrite(led9, LOW);
    digitalWrite(led10, LOW);
    delay(500);  // Wait 500 milliseconds

    // Turn off (set HIGH for active-low LEDs) all 10 LEDs:
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    digitalWrite(led7, HIGH);
    digitalWrite(led8, HIGH);
    digitalWrite(led9, HIGH);
    digitalWrite(led10, HIGH);
    delay(500);  // Wait 500 milliseconds
  }
  // After blinking, reset all LEDs to the off state.
  resetLEDs();
}

// *********************
// Function: resetLEDs()
// Description: Turns off all LEDs by setting each pin HIGH (for active-low configuration)
// *********************
void resetLEDs() {
  // Reset Board A LEDs to off:
  digitalWrite(LED_RED_A1, HIGH);
  digitalWrite(LED_GREEN_A1, HIGH);
  digitalWrite(LED_RED_A2, HIGH);
  digitalWrite(LED_GREEN_A2, HIGH);
  
  // Reset Board C LEDs to off:
  digitalWrite(LED_RED_C1, HIGH);
  digitalWrite(LED_GREEN_C1, HIGH);
  digitalWrite(LED_RED_C2, HIGH);
  digitalWrite(LED_GREEN_C2, HIGH);
  
  // Reset Board D LEDs to off:
  digitalWrite(LED_RED_D1, HIGH);
  digitalWrite(LED_GREEN_D1, HIGH);
  digitalWrite(LED_RED_D2, HIGH);
  digitalWrite(LED_GREEN_D2, HIGH);
  digitalWrite(LED_RED_D3, HIGH);
  digitalWrite(LED_GREEN_D3, HIGH);
  
  // Reset Board E LEDs to off:
  digitalWrite(LED_RED_E1, HIGH);
  digitalWrite(LED_GREEN_E1, HIGH);
  digitalWrite(LED_RED_E2, HIGH);
  digitalWrite(LED_GREEN_E2, HIGH);
  
  // Reset Board F LEDs to off:
  digitalWrite(LED_RED_F1, HIGH);
  digitalWrite(LED_GREEN_F1, HIGH);
}
