;;===============================
;; CS 2110 Fall 2016
;; Homework 7 - Functions
;; Name:
;;===============================

.orig x3000
	LD R6, STACK

	LEA R0, STRING 		; load address of string
	ADD R6, R6, -1 		; \ 
	STR R0, R6, 0 		; / push address of string on stack as arg to LENGTH
	
	LD R0, LEN_FUNC 	; load address of LENGTH function
	JSRR R0 			; call LENGTH

	LDR R0, R6, 0 		; load return value
	ADD R6, R6, 2 		; pop return value and arg off stack

	ST R0, STRLEN 		; store length

	LEA R1, STRING 		; \ 
	ADD R2, R1, R0 		; | string + len - 1
	ADD R2, R2, -1 		; / 

	ADD R6, R6, -1
	STR R2, R6, 0 		; push (string + len - 1)
	ADD R6, R6, -1
	STR R1, R6, 0 		; push string address

	LD R0, PAL_FUNC 	; load address of PALINDROME function
	JSRR R0 			; call PALINDROME

	LDR R0, R6, 0 		; load return value
	ADD R6, R6, 3		; pop return value and both args off stack

	ST R0, ANSWER 		; store answer
	HALT

STRLEN   .fill 0
ANSWER 	 .fill 0
STRING   .stringz "rAceCaR"

STACK 	 .fill xF000
LEN_FUNC .fill LENGTH
PAL_FUNC .fill PALINDROME
.end

.orig x6000
LENGTH
	; put LENGTH code here
	
	RET
.end

.orig x7000
PALINDROME
	; put PALINDROME code here
	
	RET
.end
