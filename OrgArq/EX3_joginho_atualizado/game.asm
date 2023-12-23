; Display Message - Outputs a stored message to the screen

; ------- COLOR TABLE -------
; Add to the character to select the corresponding color

; Refer to the original color table for values

jmp start_execution

spacecraft_msg : string "Spacecraft Game!"

;---- Start of Main Program -----

start_execution:
	loadn r0, #0	; Screen position for message output
	loadn r1, #spacecraft_msg	; Load r1 with the address of the message array
	loadn r2, #0	; Message COLOR selection

    call PrintMsg

    loadn r0, #40   ; Spacecraft's screen position
	loadn r1, #'O'	; Spacecraft character
	loadn r2, #32	; Blank space character
    loadn r6, #1199 ; End of screen marker

GameLoop:
    call ClearObj
    call UpdatePos
    call DrawObj
    call Sleep
    jmp GameLoop

	halt

;---- End of Main Program -----

;---- Start of Subroutines -----

PrintMsg:	; Message Print Routine: r0 = Screen position for first character; r1 = start address of the message; r2 = message color. Prints until '\0'
	push r0	; save r0 to stack
	push r1	; save r1 to stack
	push r2	; save r2 to stack
	push r3	; save r3 to stack for use in subroutine
	push r4	; save r4 to stack for use in subroutine

	loadn r3, #'\0'	; Stop criterion

PrintLoop:
	loadi r4, r1
	cmp r4, r3
	jeq PrintEnd
	add r4, r2, r4
	outchar r4, r0
	inc r0
	inc r1
	jmp PrintLoop

PrintEnd:
	pop r4	; restore registers from stack
	pop r3
	pop r2
	pop r1
	pop r0
	rts

ClearObj:
    outchar r2, r0  ; Clear object at position
    rts

UpdatePos:
    inc r0  ; Increment position
    cmp r0, r6
    jeq ResetPos
    rts

DrawObj:
    outchar r1, r0  ; Draw object at new position
    rts

Sleep:
    push r0
    push r1

    loadn r1, #50

    Sleep_loop_outer:
        loadn r0, #3000

        Sleep_loop_inner:
            dec r0
            jnz Sleep_loop_inner
            dec r1
            jnz Sleep_loop_outer

    pop r1
    pop r0

    rts

ResetPos:
    loadn r0, #40  ; Reset position if at end
    rts
