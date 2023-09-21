




jmp main


main:
    loadn r0, #0 ; onde vai escrever o inicio do texto
    loadn r1, #mensagem_inicio    
    loadn r2,# 256

    call imprimestr

    loadn r0, #40
    loadn r1, #'+'
    loadn r2, #3000




loop:
    call apagaObj
    call recalculaPos
    call imprimeObj
    call delay
    call loop

    halt

mensagem_inicio: string "JOGO DA NOVINHA"

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


    imprimestr_Sai:
        pop r4 
        pop r3 
        pop r2 
        pop r1 
        pop r0
        rts

apagaObj:
    outchar r2,r0  ; o r0 é para guardar a posição do objeto e r2 para guardar 32 = ' ' ascii do espaço
    rts

recalculaPos:
    inc r0;
    rts

imprimeObj:
    outchar r1, r0 ; Posição recebe r0 e r1 carrega o simbolo da nave
    rts

delay:
    push r0
    push r1

    loadn r1, #5
    delay_volta2:
        loadn r0, #3000
    delay_volta1:
        dec r0
        jnz delay_volta1
    dec r1
    jnz delay_volta2

    pop r0
    pop r1
    rts

