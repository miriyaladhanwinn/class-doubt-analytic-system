
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
