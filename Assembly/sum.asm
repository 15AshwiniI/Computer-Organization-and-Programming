;;===============================
;; Name: Ashwini Iyer
;;===============================

;; Write a program that sums up the array, you should then check if your sum is
;; negative. If your result is negative then return the absolute value of it. So if
;; your sum happens to be -42, you should return 42. If your sum is 42 then return
;; that.

.orig x3000
	AND R0, R0, 0  ; clear R0, it will be our array index
	AND R1, R1, 0  ; clear R1, it will be our length, limit of the loop
	AND R2, R2, 0  ; clear R2, it will be our value at array index
	AND R3, R3, 0  ; clear R3, it will be our sum of the array values
	AND R4, R4, 0  ; clear R4, it will be our temp value
	AND R5, R5, 0  ; clear R5, it will hold the address of array

	LD R5, ARRAY
BEGIN	LDR R2, R5,0   ; load the value at the index of the array in R2.
	LD R1, LENGTH  ; load the length of the array in R1
		       ; check if index is less than length
		       ; get 2s complement of the length
	NOT R1, R1
	ADD R1, R1, 1
	ADD R4, R0, R1 ; index - limit kept in R4
	BRzp FINISH    ; continue while (index - limit) is less than 0
	ADD R3, R3, R2 ; sum += array[k]
	
	ADD R0, R0, 1  ; increment array index
	ADD R5, R5, 1  ; increment array address
	
	BR BEGIN
FINISH  ADD R3, R3, 0  ; condition code (negative status) is set
	BRzp SKIP
	NOT R3, R3     ; flip sum
	ADD R3, R3, 1  ; add 1, we now have 2s complement
SKIP	ST R3, ANSWER  ; store the sum in answer
		       ; stop running
HALT

ARRAY   .fill x6000
LENGTH  .fill 10
ANSWER	.fill 0		; The answer should have the abs(sum) when finished
.end

.orig x6000
.fill 8
.fill 9
.fill 7
.fill 0
.fill -3
.fill 11
.fill 9
.fill -9
.fill 2
.fill 9
.end
