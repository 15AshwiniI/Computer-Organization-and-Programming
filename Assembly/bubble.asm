;;===============================
;; Name: Ashwini Iyer
;;===============================

;; Write a program that sorts an array location at address ARRAY of length
;; LENGTH in ascending order.

.orig x3000

	AND R0, R0, 0  ; clear R0, ARRAY
	AND R1, R1, 0  ; clear R1, outerloop index (k)
	AND R2, R2, 0  ; clear R2, inner loop index (i) starts at k
	AND R3, R3, 0  ; clear R3, item in Array (Array[i])
	AND R4, R4, 0  ; clear R4, next item in Array (Array[i-1])
	AND R5, R5, 0  ; clear R5, temp variable -> stores difference between values
	LD R1, LENGTH  ; load LENGTH into R1  
		       ; loops go backwards, outer index starts at LENGTH
BEGINOL ADD R1, R1, -1 ; decrement outer loop counter (BEGINOL: Begin Outer Loop)
	BRnz ISSORTED  ; if counter is <= 0 array is sorted (nz means negative or zero)
		       ; Branch to ISSORTED and program will HALT
	LD R0, ARRAY   ; load address of array into R0
	ADD R2,R1,0    ; inner loop begins at outerloop
BEGINIL	LDR R3, R0, 0  ; put first item in array in R3 (BEGINIL: Begin Inner Loop)
	LDR R4, R0, 1  ; put next item in array in R4 (R4 <- mem[R0 + 1])
		       ; calculate twos complement of R4
	NOT R5, R4     ; negate second item and store it in temp
	ADD R5, R5, 1  ; add 1 -> twos comp is now in temp
	ADD R5, R3, R5 ; difference between items, to check order stored in temp
	BRnz SKIP      ; if negative or zero do not switch, already in order
		       ; switch the items
		       ; Before: R3 was in mem [R0 + 0] and R4 was in mem[R0 + 1] 
	STR R4, R0, 0  ; R4 -> mem [R0 + 0], cant just change register value
	STR R3, R0, 1  ; R3 -> mem[R0 + 1], STR changes the value in the array
SKIP 	ADD R0, R0, 1  ; increment array
	ADD R2, R2, -1 ; decrement inner index
	BRP BEGINIL    ; continue inner loop if pos
	BRnzp BEGINOL  ; continue inner loop
	
ISSORTED HALT          ; stop program
	


ARRAY   .fill x6000
LENGTH  .fill 12
.end

;; This array should be sorted when finished
.orig x6000
.fill 28
.fill -50
.fill 7
.fill 2
.fill 42
.fill 4
.fill 15
.fill -8
.fill 34
.fill 101
.fill -5
.fill 250
.end
