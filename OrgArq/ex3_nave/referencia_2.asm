; Hello World - Escreve mensagem armazenada na memoria na tela


; ------- TABELA DE CORES -------
; adicione ao caracter para Selecionar a cor correspondente

; 0 branco							0000 0000
; 256 marrom						0001 0000
; 512 verde							0010 0000
; 768 oliva							0011 0000
; 1024 azul marinho					0100 0000
; 1280 roxo							0101 0000
; 1536 teal							0110 0000
; 1792 prata						0111 0000
; 2048 cinza						1000 0000
; 2304 vermelho						1001 0000
; 2560 lima							1010 0000
; 2816 amarelo						1011 0000
; 3072 azul							1100 0000
; 3328 rosa							1101 0000
; 3584 aqua							1110 0000
; 3840 branco						1111 0000



jmp main


;mensagem : var #21



mensagem2 : string "Joguinho da Nave!"

;---- Inicio do Programa Principal -----

main:
	loadn r0, #0		; Posicao na tela onde a mensagem sera' escrita
	loadn r1, #mensagem2	; Carrega r1 com o endereco do vetor que contem a mensagem
	loadn r2, #256		; Seleciona a COR da Mensagem
	
	call Imprimestr   ;  r0 = Posicao da tela que o primeiro caractere da mensagem sera' impresso;  r1 = endereco onde comeca a mensagem; r2 = cor da mensagem.   Obs: a mensagem sera' impressa ate' encontrar "/0"

	loadn r0, #40		; Posicao da Nave na tela
	loadn r1, #'O'		; Char da Nave
	loadn r2, #' '		; Char espaco em branco
	

Loop:
	call ApagaObj
	call RecalculaPos
	call ImprimeObj
	call Delay
	jmp Loop

	halt
	
;---- Fim do Programa Principal -----
	
;---- Inicio das Subrotinas -----
	
Imprimestr:	;  Rotina de Impresao de Mensagens:    r0 = Posicao da tela que o primeiro caractere da mensagem sera' impresso;  r1 = endereco onde comeca a mensagem; r2 = cor da mensagem.   Obs: a mensagem sera' impressa ate' encontrar "/0"
	push r0	; protege o r0 na pilha para preservar seu valor
	push r1	; protege o r1 na pilha para preservar seu valor
	push r2	; protege o r1 na pilha para preservar seu valor
	push r3	; protege o r3 na pilha para ser usado na subrotina
	push r4	; protege o r4 na pilha para ser usado na subrotina
	
	loadn r3, #'\0'	; Criterio de parada

Imprimestr_Loop:	
	loadi r4, r1
	cmp r4, r3
	jeq Imprimestr_Sai
	add r4, r2, r4
	outchar r4, r0
	inc r0
	inc r1
	jmp Imprimestr_Loop
	
Imprimestr_Sai:	
	pop r4	; Resgata os valores dos registradores utilizados na Subrotina da Pilha
	pop r3
	pop r2
	pop r1
	pop r0
	rts
	
	
ApagaObj:
	outchar r2, r0	; r0->Pos   r2->" "
	rts	
	
RecalculaPos:
	inc r0			; r0++
	rts	
	
ImprimeObj:
	outchar r1, r0	; r0->Pos   r1->"O"
	rts	
	
;----------------------------------
Delay:
						;Utiliza Push e Pop para nao afetar os Ristradores do programa principal
	push R0
	push R1
	
	loadn R1, #50  ; a
   Delay_volta2:				; contador de tempo quebrado em duas partes (dois loops de decremento)
		loadn R0, #3000	; b
	   Delay_volta1: 
			dec R0					; (4*a + 6)b = 1000000  == 1 seg  em um clock de 1MHz
			jnz Delay_volta1	
		dec R1
		jnz Delay_volta2
	
	pop R1
	pop R0
	
	rts							;return
