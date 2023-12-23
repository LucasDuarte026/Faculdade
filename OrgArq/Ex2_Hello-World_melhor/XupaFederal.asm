; Greetings Display - Shows stored message on screen

; ------- COLOR TABLE -------
; Add to character to select the corresponding color

; 0 white                      0000 0000
; 256 brown                    0001 0000
; 512 green                    0010 0000
; 768 olive                    0011 0000
; 1024 navy blue               0100 0000
; 1280 purple                  0101 0000
; 1536 cyan                    0110 0000
; 1792 silver                  0111 0000
; 2048 grey                    1000 0000
; 2304 red                     1001 0000
; 2560 lime                    1010 0000
; 2816 yellow                  1011 0000
; 3072 blue                    1100 0000
; 3328 fuchsia                 1101 0000
; 3584 aqua                    1110 0000
; 3840 bright white            1111 0000

jmp start

textdata : var #21
static textdata + #0, #'E'
static textdata + #1, #'N'
static textdata + #2, #'T'
static textdata + #3, #'E'
static textdata + #4, #'R'
static textdata + #5, #' '
static textdata + #6, #'T'
static textdata + #7, #'O'
static textdata + #8, #' '
static textdata + #9, #'B'
static textdata + #10, #'E'
static textdata + #11, #'G'
static textdata + #12, #'I'
static textdata + #13, #'N'
static textdata + #14, #'\0'
static textdata + #15, #'S'
static textdata + #16, #'T'
static textdata + #17, #'A'
static textdata + #18, #'R'
static textdata + #19, #'T'
static textdata + #20, #'!'

extraText : string "Federal Institute FTW!!!"

;---- Start of Main Program -----

start:
	loadn r0, #650          ; Screen position where message will be written
	loadn r1, #extraText    ; Load r1 with the address of the message array
	loadn r2, #3072         ; Select Message COLOR
	
	call PrintString        ; r0 = Screen position for the first character of the message; r1 = address of the start of the message; r2 = color of the message. Note: the message will be printed until '\0' is encountered

	halt
	
;---- End of Main Program -----
	
;---- Start of Subroutines -----
	
PrintString:	; Print Message Routine: r0 = Screen position for the first character; r1 = start address of the message; r2 = message color. Note: printing continues until '\0'
	push r0    ; save r0 on stack to preserve its value
	push r1    ; save r1 on stack to preserve its value
	push r2    ; save r2 on stack to preserve its value
	push r3    ; save r3 on stack for use in subroutine
	push r4    ; save r4 on stack for use in subroutine
	
	loadn r3, #'\0'  ; End condition

PrintLoop:	
	loadi r4, r1
	cmp r4, r3
	jeq PrintExit
	add r4, r2, r4
	outchar r4, r0
	inc r0
	inc r1
	jmp PrintLoop
	
PrintExit:	
	pop r4    ; Retrieve register values from stack
	pop r3
	pop r2
	pop r1
	pop r0
	rts
	
