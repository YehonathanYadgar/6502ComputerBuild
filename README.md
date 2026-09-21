# 6502 Computer Build

Sorry for the quality of the images and videos! I didn’t know I was going to upload this project to GitHub—they were originally just for me to keep track of my progress.

<p align="center">
  <a href="Imgs/finished-computer.jpeg"><img src="Imgs/finished-computer.jpeg" alt="Finished 6502 breadboard computer" width="500"></a>
</p>

[Watch the final full-build Hello World demo](Imgs/final-full-build-hello-world-6x.mp4).

This repository documents my personal Ben Eater-style 6502 breadboard computer build. The build is finished through Part 7 of the 6502 video series, with code, datasheets, notes, and progress media documenting the journey.

## Current Status

- Status: **Finished**.
- Completed: Ben Eater 6502 computer through **Part 7**.

## Hardware

- W65C02S CPU
- AT28C256 EEPROM
- HM62256 SRAM
- W65C22 VIA
- HD44780-compatible LCD
- 74HC00 NAND gates for address decoding

## Repository Layout

- `code/` - build code in three groups: `machine_code/` (hand-written opcodes and ROM images), `assembly/` (6502 assembly source), and `debug/` (Arduino monitor sketches).
- `docs/` - datasheets for the CPU, VIA, EEPROM, RAM, LCD, and support chips.
- `notes/` - project goals, low level details, and full summery.
- `Imgs/` - build photos and progress videos.

## Build Photos

Earlier stages of the build, leading up to the finished computer shown above.

<p align="center">
  <a href="Imgs/img1.jpeg"><img src="Imgs/img1.jpeg" alt="Early breadboard setup" width="500"></a>
  <br>
  <em>Early breadboard setup</em>
</p>

<p align="center">
  <a href="Imgs/img2.jpeg"><img src="Imgs/img2.jpeg" alt="Initial CPU wiring" width="500"></a>
  <br>
  <em>Initial CPU wiring</em>
</p>

<p align="center">
  <a href="Imgs/img3.jpeg"><img src="Imgs/img3.jpeg" alt="Expanded breadboard wiring" width="500"></a>
  <br>
  <em>Expanded breadboard wiring</em>
</p>

<p align="center">
  <a href="Imgs/img4.jpeg"><img src="Imgs/img4.jpeg" alt="LED output stage" width="500"></a>
  <br>
  <em>LED output stage</em>
</p>

<p align="center">
  <a href="Imgs/img5.jpeg"><img src="Imgs/img5.jpeg" alt="LCD wiring stage" width="500"></a>
  <br>
  <em>LCD wiring stage</em>
</p>

## Documentation

- [Code folder](code/)
- [Datasheets](docs/)
- [Project goals](notes/project_goals.md)
- [Low-level architecture](notes/low-level-architecture.md)
- [How the 6502 works](notes/how_6502_works.md)
