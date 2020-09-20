; export symbols
			XDEF Entry				; export 'Entry' symbol
			ABSENTRY Entry			; for absolute assembly mark this as application entry point

; include derivative specific macros
			INCLUDE 'mc9s12c32.inc'

ROMStart	EQU	$4000				; absolute address to place my code/constant data

; variable/data section
			ORG RAMStart
Counter1	DC.W $FFFF
Counter2	DC.W $0010
temp		DC.B $01

; code section
			ORG ROMStart
Entry:
			LDS #RAMEnd+1			; initialize the stack pointer
			ANDCC #$BF				; Enable XIRQ interrupt on SW1	

			LDAA #$01
			STAA DDRA 				; PORTA.0 connected to LED1 is output

			LDAA #$10
			STAA DDRB				; PORTB.4 connected to LED2 is output

			LDAA #$01
			STAA PORTA				; PORTA.0 is 1, LED1 is on

			LDAA #$10	
			STAA PORTB				; PORTB.4 is 1, LED2 is off

loop1:
			BRA loop

ISR:	
			LDAA PORTA
			CMPA #$00
			BEQ BT1
			BRA	BT2

BT1:
			LDAA #$01
			STAA PORTA
			LDAA #$00
			STAA PORTB
			BRA	loop2

BT2:
			LDAA #$00
			STAA PORTA
			LDAA #$10
			STAA PORTB

loop2:
			JSR delayS
			RTI

delayS:			LDY Counter2
delaySloop:		JSR delayMs
				DEY
				BNE delaySloop
				RTS

delayMs:		LDX Counter1
delayMsloop:	DEX
				BNE delayMsloop
				RTS

			ORG $FFF4				; XIRQ interrupt vector	
			DC.W ISR				; Beginning address of ISR


