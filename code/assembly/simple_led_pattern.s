; Part 3, first pass: the same rotating LED pattern as via_led_rotate.s, kept as
; the raw version written against literal addresses ($6000 = PORTB, $6002 = DDRB)
; before named constants and comments were introduced.

  .org $8000

reset:
  lda #$ff
  sta $6002

  lda #$50
  sta $6000

loop:
  ror
  sta $6000

  jmp loop

  .org $fffc
  .word reset
  .word $0000
