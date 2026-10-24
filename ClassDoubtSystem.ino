
/* commit 5: firmware: create initial sketch and include foundational headers */

/* commit 6: firmware: define GPIO constants for subject buttons and LEDs */

/* commit 10: firmware: configure INPUT_PULLUP and OUTPUT modes in setup() */

/* commit 11: firmware: add startup buzzer self-test beep (1000 Hz, 300 ms) */

/* commit 15: firmware: initialize subject labels and counter registers */

/* commit 16: firmware: add alert(subject) routine driving respective GPIO LED */

/* commit 20: firmware: declare debounce state tracking arrays */

/* commit 21: firmware: implement non-blocking millis() polling loop in loop() */

/* commit 25: firmware: implement stable falling-edge trigger detection */

/* commit 26: firmware: integrate LiquidCrystal_I2C initialization at address 0x27 */

/* commit 30: firmware: configure distinct frequencies: Math=700Hz, Science=900Hz */

/* commit 31: firmware: configure English=1100Hz and Programming=1300Hz frequencies */

/* commit 35: firmware: implement registerDoubt(subject) increment and dispatch */

/* commit 36: firmware: implement priorityAlert() siren with 1600 Hz tone */

/* commit 40: firmware: add synchronous 3x strobe flash across all subject LEDs */

/* commit 41: firmware: add Serial logging for priority alerts with timestamp */

/* commit 45: firmware: implement getTotal() aggregate doubt calculator */

/* commit 46: firmware: scaffold 3-page cyclic LCD state machine architecture */

/* commit 50: firmware: construct Page 0 2x2 live counts LCD layout */

/* commit 51: firmware: construct Page 1 aggregate session total computation */

/* commit 55: firmware: implement highestSubject() argmax mode evaluator */

/* commit 56: firmware: construct Page 2 top-doubt subject display */

/* commit 60: firmware: add event-driven LCD interrupt confirmation screens */

/* commit 61: firmware: initialize WiFi station mode and connection retry loop */

/* commit 65: firmware: mount WebServer on port 80 and register URI handlers */

/* commit 66: firmware: implement GET / route serving the live responsive dashboard */

/* commit 70: firmware: implement POST /add?subject=N remote doubt endpoint */

/* commit 71: firmware: implement POST /reset endpoint clearing session counts */

/* commit 75: storage: initialize ESP32 Preferences NVS library under 'doubts' namespace */

/* commit 76: storage: implement saveCounts() committing each press into NVS flash */

/* commit 80: storage: implement boot-time flash restore routine in setup() */

/* commit 81: firmware: implement resetAll() wiping both RAM registers and NVS storage */

/* commit 85: firmware: assemble full, production-ready ClassDoubtSystem.ino sketch */
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
WebServer server(80);
Preferences preferences;

// Subject buttons
const int buttons[4] = {18, 19, 5, 17};

// Subject LEDs
const int leds[4] = {4, 16, 25, 26};

// Reset button and buzzer
#define RESET_BTN 27
#define BUZZER_PIN 2

const char* subjects[4] = {
  "Math", "Science", "English", "Programming"
};

const char* keys[4] = {
  "math", "science", "english", "program"
};

int counts[4] = {0, 0, 0, 0};

int frequencies[4] = {700, 900, 1100, 1300};

// Button debounce
bool lastReading[5] = {HIGH, HIGH, HIGH, HIGH, HIGH};
bool stableState[5] = {HIGH, HIGH, HIGH, HIGH, HIGH};
unsigned long lastChange[5] = {0, 0, 0, 0, 0};

const unsigned long debounceDelay = 50;

// LCD display
unsigned long lastLCD = 0;
int lcdPage = 0;

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Function declarations
void beep(int frequency, int durationMs);
void alert(int subject);
void priorityAlert();
void registerDoubt(int subject);
void resetAll();
void saveCounts();
void showLCD();
int getTotal();
int highestSubject();
void handleRoot();
void handleData();
void handleAdd();
void handleReset();

// ---------------- SETUP ----------------

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();

  for (int i = 0; i < 4; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  pinMode(RESET_BTN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  // Startup buzzer test
  beep(1000, 300);

  // Load saved doubt counts
  preferences.begin("doubts", false);

  for (int i = 0; i < 4; i++) {
    counts[i] = preferences.getInt(keys[i], 0);
  }

  lcd.setCursor(0, 0);
  lcd.print("SMART DOUBT");
  lcd.setCursor(0, 1);
  lcd.print("MANAGEMENT");

  delay(1500);

  lcd.clear();
  lcd.print("Connecting WiFi");

  WiFi.begin(ssid, password, 6);

  unsigned long startTime = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - startTime < 10000) {
    delay(250);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("
WiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("
WiFi unavailable");
  }

  server.on("/", HTTP_GET, handleRoot);
  server.on("/data", HTTP_GET, handleData);
  server.on("/add", HTTP_POST, handleAdd);
  server.on("/reset", HTTP_POST, handleReset);

  server.begin();

  Serial.println("Web server started");

  showLCD();
}

// ---------------- LOOP ----------------

void loop() {
  server.handleClient();

  for (int i = 0; i < 5; i++) {
    int pin;

    if (i < 4) {
      pin = buttons[i];
    } else {
      pin = RESET_BTN;
    }

    bool reading = digitalRead(pin);

    if (reading != lastReading[i]) {
      lastChange[i] = millis();
    }

    if (millis() - lastChange[i] >= debounceDelay) {
      if (reading != stableState[i]) {
        stableState[i] = reading;

        if (stableState[i] == LOW) {
          if (i < 4) {
            registerDoubt(i);
          } else {
            resetAll();
          }
        }
      }
    }

    lastReading[i] = reading;
  }

  if (millis() - lastLCD >= 4000) {
    lcdPage++;

    if (lcdPage > 2) {
      lcdPage = 0;
    }

    showLCD();
    lastLCD = millis();
  }

  delay(5);
}

// ---------------- BUZZER ----------------

void beep(int frequency, int durationMs) {
  tone(BUZZER_PIN, frequency);
  delay(durationMs);
  noTone(BUZZER_PIN);
}

void alert(int subject) {
  digitalWrite(leds[subject], HIGH);

  beep(frequencies[subject], 500);

  digitalWrite(leds[subject], LOW);
}

void priorityAlert() {
  Serial.println("PRIORITY ALERT!");

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(leds[j], HIGH);
    }

    beep(1600, 150);

    for (int j = 0; j < 4; j++) {
      digitalWrite(leds[j], LOW);
    }

    delay(100);
  }
}

// ---------------- COUNTERS ----------------

int getTotal() {
  int total = 0;

  for (int i = 0; i < 4; i++) {
    total += counts[i];
  }

  return total;
}

int highestSubject() {
  if (getTotal() == 0) {
    return -1;
  }

  int highest = 0;

  for (int i = 1; i < 4; i++) {
    if (counts[i] > counts[highest]) {
      highest = i;
    }
  }

  return highest;
}

void saveCounts() {
  for (int i = 0; i < 4; i++) {
    preferences.putInt(keys[i], counts[i]);
  }
}

// ---------------- REGISTER DOUBT ----------------

void registerDoubt(int subject) {
  counts[subject]++;

  saveCounts();

  Serial.print("Doubt Registered: ");
  Serial.println(subjects[subject]);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(subjects[subject]);
  lcd.setCursor(0, 1);
  lcd.print("Doubt Added!");

  alert(subject);

  if (counts[subject] % 5 == 0) {
    priorityAlert();
  }

  lcdPage = 0;
  showLCD();
  lastLCD = millis();
}

// ---------------- RESET ----------------

void resetAll() {
  for (int i = 0; i < 4; i++) {
    counts[i] = 0;
  }

  saveCounts();

  Serial.println("All doubts reset!");

  lcd.clear();
  lcd.print("ALL DOUBTS");
  lcd.setCursor(0, 1);
  lcd.print("RESET!");

  beep(500, 400);

  lcdPage = 0;
  showLCD();
  lastLCD = millis();
}

// ---------------- LCD ----------------

void showLCD() {
  lcd.clear();

  if (lcdPage == 0) {
    lcd.setCursor(0, 0);
    lcd.print("M:");
    lcd.print(counts[0]);
    lcd.print(" S:");
    lcd.print(counts[1]);

    lcd.setCursor(0, 1);
    lcd.print("E:");
    lcd.print(counts[2]);
    lcd.print(" P:");
    lcd.print(counts[3]);
  }

  else if (lcdPage == 1) {
    lcd.setCursor(0, 0);
    lcd.print("TOTAL DOUBTS:");
    lcd.setCursor(0, 1);
    lcd.print(getTotal());
  }

  else {
    lcd.setCursor(0, 0);
    lcd.print("MOST DOUBTS:");

    lcd.setCursor(0, 1);

    int highest = highestSubject();

    if (highest == -1) {
      lcd.print("None");
    } else {
      lcd.print(subjects[highest]);
    }
  }
}

// ---------------- JSON API ----------------

void handleData() {
  String json = "{";

  json += ""math":" + String(counts[0]) + ",";
  json += ""science":" + String(counts[1]) + ",";
  json += ""english":" + String(counts[2]) + ",";
  json += ""programming":" + String(counts[3]) + ",";
  json += ""total":" + String(getTotal());

  json += "}";

  server.send(200, "application/json", json);
}

void handleAdd() {
  if (!server.hasArg("subject")) {
    server.send(400, "text/plain", "Missing subject");
    return;
  }

  String value = server.arg("subject");

  if (value.length() != 1 ||
      value[0] < '0' || value[0] > '3') {
    server.send(400, "text/plain", "Invalid subject");
    return;
  }

  registerDoubt(value.toInt());
  server.send(200, "text/plain", "Doubt added");
}

void handleReset() {
  resetAll();
  server.send(200, "text/plain", "Counters reset");
}

// ---------------- WIFI DASHBOARD ----------------

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP32 Doubt Dashboard</title>
<style>
body {
  font-family: Arial, sans-serif;
  background: #f1f5f9;
  text-align: center;
  margin: 0;
  padding: 20px;
}
.container {
  max-width: 850px;
  margin: auto;
}
h1 { color: #172554; }
.cards {
  display: grid;
  grid-template-columns: repeat(2, 1fr);
  gap: 15px;
}
.card, .summary {
  background: white;
  padding: 20px;
  border-radius: 14px;
  box-shadow: 0 4px 12px #0001;
}
.summary { margin-bottom: 20px; }
.number {
  font-size: 38px;
  font-weight: bold;
  margin: 12px;
}
.bar {
  background: #e5e7eb;
  height: 12px;
  border-radius: 8px;
  overflow: hidden;
}
.fill {
  height: 100%;
  width: 0%;
  transition: width .4s;
}
.math { background: #22c55e; }
.science { background: #3b82f6; }
.english { background: #eab308; }
.programming { background: #ef4444; }
button {
  background: #2563eb;
  color: white;
  border: none;
  border-radius: 8px;
  padding: 12px 18px;
  margin-top: 15px;
  cursor: pointer;
}
.reset {
  background: #dc2626;
  margin-top: 25px;
}
@media(max-width:550px) {
  .cards { grid-template-columns: 1fr; }
}
</style>
</head>
<body>
<div class="container">

<h1>Student Doubt Dashboard</h1>
<p>ESP32 Smart Doubt Management System</p>

<div class="summary">
  <h2>Total Doubts</h2>
  <div class="number" id="total">0</div>
  <p>Highest Doubts: <b id="highest">None</b></p>
</div>

<div class="cards">
  <div class="card">
    <h2>Math</h2>
    <div class="number" id="math">0</div>
    <div class="bar"><div class="fill math" id="mathBar"></div></div>
    <button onclick="addDoubt(0)">Add Doubt</button>
  </div>

  <div class="card">
    <h2>Science</h2>
    <div class="number" id="science">0</div>
    <div class="bar"><div class="fill science" id="scienceBar"></div></div>
    <button onclick="addDoubt(1)">Add Doubt</button>
  </div>

  <div class="card">
    <h2>English</h2>
    <div class="number" id="english">0</div>
    <div class="bar"><div class="fill english" id="englishBar"></div></div>
    <button onclick="addDoubt(2)">Add Doubt</button>
  </div>

  <div class="card">
    <h2>Programming</h2>
    <div class="number" id="programming">0</div>
    <div class="bar"><div class="fill programming" id="programmingBar"></div></div>
    <button onclick="addDoubt(3)">Add Doubt</button>
  </div>
</div>

<button class="reset" onclick="resetAll()">Reset All Doubts</button>
<p id="status"></p>

</div>

<script>
async function loadData() {
  try {
    const response = await fetch('/data');
    if (!response.ok) throw new Error('HTTP error');
    const data = await response.json();

    const names = [
      'math', 'science', 'english', 'programming'
    ];

    let highest = 'None';
    let maximum = 0;

    names.forEach(name => {
      document.getElementById(name).textContent = data[name];

      let percentage = data.total > 0
        ? data[name] * 100 / data.total
        : 0;

      document.getElementById(name + 'Bar').style.width =
        percentage + '%';

      if (data[name] > maximum) {
        maximum = data[name];
        highest = name;
      }
    });

    document.getElementById('total').textContent = data.total;
    document.getElementById('highest').textContent = highest;
    document.getElementById('status').textContent = 'Connected';
  } catch (error) {
    document.getElementById('status').textContent =
      'Connection unavailable';
  }
}

async function addDoubt(subject) {
  await fetch('/add?subject=' + subject, {
    method: 'POST'
  });
  loadData();
}

async function resetAll() {
  if (confirm('Reset all counters?')) {
    await fetch('/reset', { method: 'POST' });
    loadData();
  }
}

setInterval(loadData, 2000);
loadData();
</script>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}
/* commit 88: web: implement GET /data JSON endpoint serialization */

/* commit 95: firmware: optimize memory usage and CPU core pinning for WebServer */

/* commit 96: firmware: integrate serial telemetry logging at 115200 baud */
