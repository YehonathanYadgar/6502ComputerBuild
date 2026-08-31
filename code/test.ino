const byte DATA[] = {3, 4, 5, 6, 7, 8, 9, 10};
// Arduino pins:       D0 D1 D2 D3 D4 D5 D6 D7


const byte CLOCK_OUT_PIN = 11;  // Arduino 11 -> 6502 PHI2
const byte EEPROM_CE_PIN = 12;  // Arduino 12 -> EEPROM /CE
const byte RESB_PIN = 13;       // Arduino 13 -> 6502 RESB


const byte CPU_A15_PIN = A0;    // Arduino A0 -> CPU A15
const byte RAM_CS_PIN  = A1;    // Arduino A1 -> RAM /CS
const byte RAM_WE_PIN  = A2;    // Arduino A2 -> RAM /WE
const byte RAM_OE_PIN  = A4;    // Arduino A4 -> RAM /OE
const byte CPU_RW_PIN  = A5;    // Arduino A5 -> CPU R/W


unsigned long pulseCount = 0;
bool autoClockRunning = false;
bool sawR = false;


void printHex2(byte value) {
    if (value < 0x10) {
        Serial.print("0");
    }
    Serial.print(value, HEX);
}


void printBinary8(byte value) {
    for (int n = 7; n >= 0; n--) {
        Serial.print((value >> n) & 1);
    }
}


byte readDataBus() {
    byte data = 0;


    for (byte n = 0; n < 8; n++) {
        if (digitalRead(DATA[n]) == HIGH) {
            data |= (1 << n);
        }
    }


    return data;
}


void printDebugLine(
    byte data,
    int ce,
    int resb,
    int a15,
    int ramCS,
    int ramWE,
    int ramOE,
    int cpuRW,
    bool duringClockHigh
) {
    Serial.print("#");
    Serial.print(pulseCount);
    Serial.print("  ");


    if (duringClockHigh) {
        Serial.print("SAMPLED_WHILE_CLK_HIGH");
    } else {
        Serial.print("STATUS_ONLY");
    }


    Serial.print("  D0-D7=$");
    printHex2(data);


    Serial.print("  bin=");
    printBinary8(data);


    Serial.print("  A15=");
    Serial.print(a15);


    // CPU R/W
    Serial.print("  CPU_RW=");
    Serial.print(cpuRW);


    if (cpuRW == HIGH) {
        Serial.print("(READ)");
    } else {
        Serial.print("(WRITE)");
    }


    // Reset
    Serial.print("  RESB=");
    Serial.print(resb);


    if (resb == HIGH) {
        Serial.print("(RUN)");
    } else {
        Serial.print("(RESET)");
    }


    // EEPROM /CE
    Serial.print("  /CE=");
    Serial.print(ce);


    if (ce == LOW) {
        Serial.print("(EEPROM_ON)");
    } else {
        Serial.print("(EEPROM_OFF)");
    }


    // RAM /CS
    Serial.print("  RAM_CS=");
    Serial.print(ramCS);


    if (ramCS == LOW) {
        Serial.print("(SELECTED)");
    } else {
        Serial.print("(OFF)");
    }


    // RAM /WE
    Serial.print("  RAM_WE=");
    Serial.print(ramWE);


    if (ramWE == LOW) {
        Serial.print("(WRITE_ENABLED)");
    } else {
        Serial.print("(NO_WRITE)");
    }


    // RAM /OE
    Serial.print("  RAM_OE=");
    Serial.print(ramOE);


    if (ramOE == LOW) {
        Serial.print("(OUTPUT_ENABLED)");
    } else {
        Serial.print("(OUTPUT_DISABLED)");
    }


    // Compare CPU R/W against RAM /WE
    Serial.print("  RW_WE_MATCH=");


    if (cpuRW == ramWE) {
        Serial.print("YES");
    } else {
        Serial.print("NO");
    }


    Serial.println();
}


void printStatusOnly() {
    byte data = readDataBus();


    int ce = digitalRead(EEPROM_CE_PIN);
    int resb = digitalRead(RESB_PIN);
    int a15 = digitalRead(CPU_A15_PIN);
    int ramCS = digitalRead(RAM_CS_PIN);
    int ramWE = digitalRead(RAM_WE_PIN);
    int ramOE = digitalRead(RAM_OE_PIN);
    int cpuRW = digitalRead(CPU_RW_PIN);


    printDebugLine(
        data,
        ce,
        resb,
        a15,
        ramCS,
        ramWE,
        ramOE,
        cpuRW,
        false
    );
}


void makeClockPulse() {
    pulseCount++;


    // Rising edge
    digitalWrite(CLOCK_OUT_PIN, HIGH);


    // Allow signals to settle
    delayMicroseconds(10);


    // Sample while PHI2 is HIGH
    byte data = readDataBus();


    int ce = digitalRead(EEPROM_CE_PIN);
    int resb = digitalRead(RESB_PIN);
    int a15 = digitalRead(CPU_A15_PIN);
    int ramCS = digitalRead(RAM_CS_PIN);
    int ramWE = digitalRead(RAM_WE_PIN);
    int ramOE = digitalRead(RAM_OE_PIN);
    int cpuRW = digitalRead(CPU_RW_PIN);


    // Falling edge
    digitalWrite(CLOCK_OUT_PIN, LOW);


    printDebugLine(
        data,
        ce,
        resb,
        a15,
        ramCS,
        ramWE,
        ramOE,
        cpuRW,
        true
    );
}


void setup() {
    for (byte n = 0; n < 8; n++) {
        pinMode(DATA[n], INPUT);
    }


    pinMode(EEPROM_CE_PIN, INPUT);
    pinMode(RESB_PIN, INPUT);


    pinMode(CPU_A15_PIN, INPUT);
    pinMode(RAM_CS_PIN, INPUT);
    pinMode(RAM_WE_PIN, INPUT);
    pinMode(RAM_OE_PIN, INPUT);
    pinMode(CPU_RW_PIN, INPUT);


    pinMode(CLOCK_OUT_PIN, OUTPUT);
    digitalWrite(CLOCK_OUT_PIN, LOW);


    Serial.begin(57600);


    Serial.println("6502 + EEPROM + RAM debug monitor");
    Serial.println();


    Serial.println("Pins:");
    Serial.println("  Arduino 3-10 = CPU D0-D7");
    Serial.println("  Arduino 11   = clock out to 6502 PHI2");
    Serial.println("  Arduino 12   = EEPROM /CE");
    Serial.println("  Arduino 13   = 6502 RESB");
    Serial.println("  Arduino A0   = CPU A15");
    Serial.println("  Arduino A1   = RAM /CS");
    Serial.println("  Arduino A2   = RAM /WE");
    Serial.println("  Arduino A4   = RAM /OE");
    Serial.println("  Arduino A5   = CPU R/W");


    Serial.println();


    Serial.println("Commands:");
    Serial.println("  p = one clock pulse");
    Serial.println("  t = ten clock pulses");
    Serial.println("  s = status only");
    Serial.println("  rc = run automatically");
    Serial.println("  x = stop");


    Serial.println();


    Serial.println("Expected:");
    Serial.println("  CPU_RW=1 and RAM_WE=1 during READ");
    Serial.println("  CPU_RW=0 and RAM_WE=0 during WRITE");
    Serial.println("  RW_WE_MATCH should always be YES");
    Serial.println();
}


void loop() {
    if (autoClockRunning) {
        makeClockPulse();
        delay(10);
    }


    if (Serial.available() > 0) {
        char command = Serial.read();


        if (command == 'r' || command == 'R') {
            sawR = true;
        }
        else if ((command == 'c' || command == 'C') && sawR) {
            autoClockRunning = true;
            sawR = false;
            Serial.println("Automatic clock running");
        }
        else {
            sawR = false;
        }


        if (command == 'x' || command == 'X') {
            autoClockRunning = false;
            Serial.println("Automatic clock stopped");
        }


        if (command == 'p' || command == 'P') {
            makeClockPulse();
        }


        if (command == 't' || command == 'T') {
            for (byte i = 0; i < 10; i++) {
                makeClockPulse();
                delay(100);
            }
        }


        if (command == 's' || command == 'S') {
            printStatusOnly();
        }
    }
}

