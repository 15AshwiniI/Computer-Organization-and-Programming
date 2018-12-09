;;===============================
;; CS 2110 Fall 2016
;; Homework 7 - Functions
;; Name: Ashwini Iyer
;;===============================

.orig x3000
	LD R6, STACK

	LD R0, OP			; load OP
	ADD R6, R6, -1		; \
	STR R0, R6, 0 		; / push OP on stack

	LD R0, B 			; load B
	ADD R6, R6, -1 		; \
	STR R0, R6, 0 		; / push B on stack

	LD R0, A 			; load A
	ADD R6, R6, -1 		; \
	STR R0, R6, 0 		; / push A on stack

	LD R0, OPERATIONS_ADDR 	; load address of OPERATIONS
	JSRR R0 			; call OPERATIONS

	LDR R0, R6, 0 		; load return value from top of stack
	ADD R6, R6, 4 		; pop 3 args and return value from stack

	ST R0, ANSWER 		; store final value in answer
	HALT

A 		.fill 5
B		.fill 4
OP		.fill 4
ANSWER 	.fill 0
STACK 	.fill xF000

OPERATIONS_ADDR .fill OPERATIONS
.end

.orig x4000
OPERATIONS
			; put OPERATIONS code here
			; OPERATIONS is being called by the main function
			; so, it is the callee
			; set up the callee
	ADD R6,R6,-3	; move R6 up 3 spots to point at Old Frame Pointer 
	STR R7,R6,1	; store return address that was in R7 in (R6 + 1)
	STR R5,R6,0	; store old frame pointer at R6, it was in R5 before
	ADD R5,R6,-1	; set new frame pointer (R5) to R6 + 1
	ADD R6,R6,0	; no local variables, so R6 does not move

			; OPERATIONS begins
	LDR R3,R5,4	; R3 = A
	LDR R1,R5,5	; R1 = B
	LDR R2,R5,6	; R2 = OP
	BRnp NOTXOR	; if OP is not 0 branch to NOTXOR

			; call XOR
			; set up caller, we need to push paramters to stack (reverse)
			; push B to the stack
	ADD R6,R6,-1	; R6 goes up one its now pointing at local var 1
	STR R1,R6,0	; store B (value in R1) in this new R6 -> local var 1
			; push A on the stack
	ADD R6,R6,-1	; R6 goes up one its now pointing at local var 2
	STR R3,R6,0	; store A (value in R3) in this new R6 -> local var 2

			; now actually call xor
	LD R0, XOR_ADDR	; load XOR_ADDR
	JSRR R0		; call XOR
			; clean up caller
	LDR R0, R6, 0 	; load return value from top of stack
	ADD R6, R6, 3 	; pop 2 args and return value from stack

	BR END		; return
NOTXOR	ADD R2,R2,-1    ; subtract 1 from op, if it is 1 itll be 0 now
	BRnp NOTMULT	; if OP is not 0 branch to NOTMULT
			; call MULT
			; set up caller, we need to push parameters to stack (reverse)
			; push B to the stack
	ADD R6,R6,-1	; R6 -> local var 1
	STR R1,R6,0	; store B (R1) in local var 1
	ADD R6,R6,-1	; R6 -> local var 2
	STR R3,R6,0	; store A (R3) in local var 2
			; now call mult
	LD R0,MULT_ADDR 
	JSRR R0		; call MULT
	LDR R0,R6,0	; load return value from top of the stack
	ADD R6,R6,3	; pop 2 args and return value from stack
	BR END		; return
NOTMULT	ADD R2,R2,1 	; return op to its past value
	ADD R2,R2,-2	; subtract 2 from op, if it is 2 itll be 0 now
	BRnp NOTDIV	; if OP is not 2 branch to NOTDIV
			; call div
			; set up caller
			; push B to stack
	ADD R6,R6,-1	; R6 -> local var 1
	STR R1,R6,0	; store B (R1) in local var 1
	ADD R6,R6,-1	; R6 -> local var 2
	STR R3,R6,0	; store A (R3) in local var 2
			; now call div
	LD R0,DIV_ADDR 
	JSRR R0		; call DIV
	LDR R0,R6,0	; load return value from top of the stack
	ADD R6,R6,3	; pop 2 args and return value from stack
	BR END		; return
NOTDIV	ADD R2,R2,2 	; return op to its original value
	ADD R2,R2,-3	; subtract 3 from op, if it is 3 itll be 0 now
	BRnp NOTDIV	; if OP is not 3 branch to NOTMOD
			; call mod
			; set up caller
			; push B to stack
	ADD R6,R6,-1	; R6 -> local var 1
	STR R1,R6,0	; store B (R1) in local var 1
	ADD R6,R6,-1	; R6 -> local var 2
	STR R3,R6,0	; store A (R3) in local var 2
	ADD R6,R6,-1
	AND R4,R4,0
	STR R4,R6,0
			; now call mod
	LD R0,MOD_ADDR 
	JSRR R0		; call MOD
	LDR R0,R6,0	; load return value from top of the stack
	ADD R6,R6,3	; pop 2 args and return value from stack
	BR END		; return	
NOTMOD	ADD R2,R2,3
	ADD R2,R2,-4
	BRnp NOTMYST	
	ADD R6,R6,-1	; R6 -> local var 2
	STR R3,R6,0	; store A (R3) in local var 2
	LD R0,MYSTERY_ADDR 
	JSRR R0		; call MYSTERY
	LDR R0,R6,0	; load return value from top of the stack
	ADD R6,R6,2	; pop 1 args and return value from stack
	BR END		; return
	
NOTMYST	ADD R2,R2,3	; return op to its original value
	AND R0,R0,0	; clear R0
	ADD R0,R0,-1	; return -1
	BR END	
END	STR R0, R5, 3	; put answer on stack
	ADD R6, R5, 3 	; R6 POINTING TO OFP
	LDR R7, R5, 2 	; RESTORE TO STATE BEFORE CALLEE WAS CALLED, RESTORE RA
	LDR R5, R5, 1 	; RESTORE 0FP
	
	RET
	
XOR_ADDR 		.fill XOR
MULT_ADDR 		.fill MULT
DIV_ADDR 		.fill DIV
MOD_ADDR 		.fill MOD
MYSTERY_ADDR 		.fill MYSTERY
.end

.orig x4800
XOR
	; put XOR code here
			; set up callee
	ADD R6,R6,-3
	STR R7,R6,1
	STR R5,R6,0
	ADD R5,R6,-1
	ADD R6,R6,2
			; XOR begins

	LDR R1,R5,4	; R1 = A
	LDR R2,R5,5	; R2 = B
	AND R3,R1,R2	; R3 = a&b
	NOT R1,R1
	NOT R2,R2
	AND R4,R1,R2	; R4 = !a & !b
	NOT R3,R3
	NOT R4,R4
	AND R0,R3,R4	; XOR = !(a&b) & !(!a & !b)

			; clean up callee
	STR R0,R5,3
	ADD R6,R5,3
	LDR R7,R5,2
	LDR R5,R5,1
	
	
	RET
.end

.orig x5000
MULT
	; put MULT code here
			; set up callee
	ADD R6,R6,-3
	STR R7,R6,1
	STR R5,R6,0
	ADD R5,R6,-1
	ADD R6,R6,1
			; MULT Begins

	LDR R1,R5,4	; R1 = A
	LDR R2,R5,5	; R2 = B
	AND R3,R3,0	; R3 = SUM	
BEGIN	ADD R2,R2,0
	BRnz SKIP
	ADD R3,R3,R1
	ADD R2,R2,-1
	BR BEGIN
SKIP	AND R0,R0,0
	ADD R0,R3,0
	
			; clean up callee
	STR R0,R5,3
	ADD R6,R5,3
	LDR R7,R5,2
	LDR R5,R5,1
	RET
.end

.orig x5800
DIV
	; put DIV code here
			
			; set up callee
	ADD R6,R6,-3
	STR R7,R6,1
	STR R5,R6,0
	ADD R5,R6,-1
	ADD R6,R6,1	; local variable: a-b
			; DIV Begins

	LDR R1,R5,4	; R1 = A
	LDR R2,R5,5	; R2 = B
	AND R3,R3,0	; R3 = ABdiff	
	NOT R3,R2
	ADD R3,R3,1	; 2S COMPS
	ADD R3,R3,R1
	STR R3,R5,0	; store ABdiff on stack
	ADD R3,R3,0
	BRzp RECURSE	; if (a<b) ret 0, else branch to RECURSE
	AND R0,R0,0
	STR R0,R5,3
	BR E

			; set up caller
			; push B to stack
RECURSE	ADD R6,R6,-1	; R6 -> local var 1
	STR R2,R6,0	; store B (R2) in local var 1
	ADD R6,R6,-1	; R6 -> local var 2
	LDR R3,R5,0
	STR R3,R6,0	; store A-B (R3) in local var 2
			; now call mod
	JSR DIV		; call DIV

	LDR R0,R6,0	; load return value from top of the stack


	;ADD R6,R6,1	; pop 2 args and return value from stack
	ADD R0, R0, 1	; R0 = 1 + div(a-b,b)


	STR R0, R5, 3	; put answer on stack
	BR E		; return
	
			; clean up callee
E	;STR R0,R5,3
	ADD R6,R5,3
	LDR R7,R5,2
	LDR R5,R5,1
	ADD R6,R6,3
	
	RET
.end

.orig x6000
MOD
	; put MOD code here
			; set up callee
	ADD R6,R6,-3
	STR R7,R6,1
	STR R5,R6,0
	ADD R5,R6,-1
	ADD R6,R6,1	; local variable: a-b
			; MOD Begins

	LDR R1,R5,4	; R1 = A
	LDR R2,R5,5	; R2 = B
	AND R3,R3,0	; R3 = ABdiff	
	NOT R3,R2
	ADD R3,R3,1	; 2S COMPS
	ADD R3,R3,R1
	STR R3,R5,0	; store ABdiff on stack
	ADD R3,R3,0
	BRzp R	; if (a<b) ret 0, else branch to RECURSE
	AND R0,R0,0
	STR R0,R5,3
	BR EN

			; set up caller
			; push B to stack
R	ADD R6,R6,-1	; R6 -> local var 1
	STR R2,R6,0	; store B (R2) in local var 1
	ADD R6,R6,-1	; R6 -> local var 2
	LDR R3,R5,0
	STR R3,R6,0	; store A-B (R3) in local var 2
			; now call mod
	JSR MOD		; call DIV

	LDR R0,R6,0	; load return value from top of the stack


	;ADD R6,R6,1	; pop 2 args and return value from stack
	ADD R0, R0, 0	; R0 = mod(a-b,b)


	STR R0, R5, 3	; put answer on stack
	BR EN		; return
	
			; clean up callee
EN	;STR R0,R5,3
	ADD R6,R5,3
	LDR R7,R5,2
	LDR R5,R5,1
	ADD R6,R6,3
	
	RET
	
	RET
.end

.orig x7000
MYSTERY
	ADD R6, R6, -3
	STR R7, R6, 1
	STR R5, R6, 0
	ADD R5, R6, -1

	LDR R0, R5, 4

	ADD R1, R0, -1
	BRnp SKIP_MYSTERY1
	AND R0, R0, 0
	BR RETURN_MYSTERY

SKIP_MYSTERY1
	AND R1, R1, 0
	ADD R1, R1, 2

	ADD R6, R6, -1
	STR R1, R6, 0
	ADD R6, R6, -1
	STR R0, R6, 0
	
	LD R0, DIV_FUNC
	JSRR R0

	LDR R1, R6, 0
	ADD R6, R6, 3

	ADD R6, R6, -1
	STR R1, R5, 0

	LDR R0, R5, 4

	AND R1, R1, 0
	ADD R1, R1, 2

	ADD R6, R6, -1
	STR R1, R6, 0
	ADD R6, R6, -1
	STR R0, R6, 0
	
	LD R0, MOD_FUNC
	JSRR R0

	LDR R1, R6, 0
	ADD R6, R6, 3

	ADD R1, R1,0
	BRnp SKIP_MYSTERY2
	
	LDR R0, R5, 0
	ADD R6, R6, -1
	STR R0, R6, 0
	JSR MYSTERY

	LDR R0, R6, 0
	ADD R6, R6, 2

	ADD R0, R0, 1

	BR RETURN_MYSTERY

SKIP_MYSTERY2
	LDR R0, R5, 4
	ADD R1, R0, R0
	ADD R1, R1, R0
	ADD R1, R1, 1

	ADD R6, R6, -1
	STR R1, R6, 0
	JSR MYSTERY

	LDR R0, R6, 0
	ADD R6, R6, 2
	ADD R0, R0, 1

RETURN_MYSTERY
	STR R0, R5, 3
	ADD R6, R5, 3
	LDR R7, R5, 2
	LDR R5, R5, 1
	RET

DIV_FUNC .fill DIV
MOD_FUNC .fill MOD
.end
