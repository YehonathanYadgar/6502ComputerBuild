/*
 * 6502 bus-monitor scaffold.
 *
 * Set the pin arrays to match the Arduino and wiring used by the build before
 * uploading. A board with enough GPIO, such as an Arduino Mega, is expected.
 */

const byte CLOCK_PIN = 2;
const byte RW_PIN = 3;
const byte ADDRESS_PINS[16] = {
  22, 23, 24, 25, 26, 27, 28, 29,
  30, 31, 32, 33, 34, 35, 36, 37
};
const byte DATA_PINS[8] = {38, 39, 40, 41, 42, 43, 44, 45};

unsigned int readAddress() {
  unsigned int value = 0;
  for (byte bit = 0; bit < 16; ++bit) {
    value |= static_cast<unsigned int>(digitalRead(ADDRESS_PINS[bit])) << bit;
  }
  return value;
}

byte readData() {
  byte value = 0;
  for (byte bit = 0; bit < 8; ++bit) {
    value |= digitalRead(DATA_PINS[bit]) << bit;
  }
  return value;
}

void setup() {
  Serial.begin(115200);
  pinMode(CLOCK_PIN, INPUT);
  pinMode(RW_PIN, INPUT);

  for (byte pin : ADDRESS_PINS) {
    pinMode(pin, INPUT);
  }
  for (byte pin : DATA_PINS) {
    pinMode(pin, INPUT);
  }
}

void loop() {
  static int previousClock = LOW;
  const int clock = digitalRead(CLOCK_PIN);

  if (clock == HIGH && previousClock == LOW) {
    const unsigned int address = readAddress();
    const byte data = readData();

    char line[24];
    snprintf(
      line,
      sizeof(line),
      "%04X  %c  %02X",
      address,
      digitalRead(RW_PIN) ? 'R' : 'W',
      data
    );
    Serial.println(line);
  }

  previousClock = clock;
}
