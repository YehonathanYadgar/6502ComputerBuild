; Later LCD version: use subroutines and poll the HD44780 busy flag.
; JSR/RTS need RAM because return addresses are stored on the 6502 stack.

PORTB = $6000
PORTA = $6001
DDRB = $6002
DDRA = $6003

E  = %10000000
RW = %01000000
RS = %00100000

  .org $8000

reset:
  ldx #$ff
  txs             ; Initialize the stack pointer before calling subroutines.

  lda #%11111111
  sta DDRB
  lda #%11100000
  sta DDRA

  lda #%00111000  ; 8-bit mode, 2-line display, 5x8 font.
  jsr lcd_instruction
  lda #%00001110  ; Display on, cursor on, blink off.
  jsr lcd_instruction
  lda #%00000110  ; Increment cursor after each character.
  jsr lcd_instruction
  lda #%00000001  ; Clear display.
  jsr lcd_instruction

  ldx #0
print:
  lda message,x
  beq loop
  jsr print_char
  inx
  jmp print

loop:
  jmp loop

message: .asciiz "Hello, world!"

lcd_wait:
  pha             ; Preserve A while the LCD status register is checked.
  lda #%00000000
  sta DDRB

lcdbusy:
  lda #RW
  sta PORTA
  lda #(RW | E)
  sta PORTA
  lda PORTB
  and #%10000000  ; Busy flag is DB7.
  bne lcdbusy

  lda #RW
  sta PORTA
  lda #%11111111
  sta DDRB
  pla
  rts

lcd_instruction:
  jsr lcd_wait
  sta PORTB
  lda #0
  sta PORTA
  lda #E
  sta PORTA
  lda #0
  sta PORTA
  rts

print_char:
  jsr lcd_wait
  sta PORTB
  lda #RS
  sta PORTA
  lda #(RS | E)
  sta PORTA
  lda #RS
  sta PORTA
  rts

  .org $fffc
  .word reset
  .word $0000
