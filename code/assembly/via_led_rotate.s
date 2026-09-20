; Part 3: write a rotating LED pattern through the W65C22 VIA.
; PORTB is memory-mapped at $6000 in this build.

PORTB = $6000
DDRB = $6002

  .org $8000

reset:
  lda #$ff        ; Make all PORTB pins outputs.
  sta DDRB

  lda #$50        ; Starting LED pattern.
  sta PORTB

loop:
  ror             ; Rotate the pattern through carry.
  sta PORTB
  jmp loop

  .org $fffc
  .word reset     ; Reset vector: start executing at $8000.
  .word $0000
