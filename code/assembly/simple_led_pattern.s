; Simple rotating LED pattern code.

  .org $8000    ; Start the program at address 8000

reset:
  lda #$ff      ; Load the value FF into the A register.
  sta $6002     ; Store the value of A in the address 6002 (Set all of the port B pins to output).

  lda #$50      ; Load the value 50 into the A register.
  sta $6000     ; Store the value of A at address 6000 (light up 2 LEDs)

loop:
  ror           ; Rotate right the A register, shifting bits, for rotating LED pattern
  sta $6000     ; Light up the LEDs with the new LED pattern

  jmp loop


; the program starts at address 8000, and the CPU always checks that spot after reset. 
  .org $fffc
  .word reset
  .word $0000
