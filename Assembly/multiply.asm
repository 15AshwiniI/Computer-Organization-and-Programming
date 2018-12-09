;;===============================
;; Name: Ashwini Iyer
;;===============================

;; Write a program that stores the value of U * V in ANSWER.

.orig x3000

	AND R1, R1, 0   ; clear R1, will have U
	AND R2, R2, 0   ; clear R2, will have V
	AND R3, R3, 0   ; clear R3, will have SUM/ANSWER
	AND R4, R4, 0   ; clear R4, will have negative status
	LD R2, V	; loads the value of V in R1
	LD R1, U        ; loads the value of U in R1
			; condition code (U) has now been set
	BRzp ISPOS	; if U is pos skip neg code
			; if u is negative code
	LD R4, 1	; set negative to 1
	NOT R1, R1	; flipped U, set U to negative
	ADD R1, R1, 1	; R1 is now set to 2s complement of U

ISPOS   ADD R3, R3, R2  ; while U > 0 sum += V
	ADD R1, R1, -1  ; U--
	BRp ISPOS	; if is still positive continue while

	ADD R4, R4, 0 	; condition code (negative status) is set
	BRzp SKIP	; if is positive skip this code
	NOT R3, R3	; flip sum
	ADD R3, R3, 1	; add 1, we now have 2s complement	
	
SKIP	ST R3, ANSWER	; store the sum in answer
			; stop running
HALT


U       .fill -3
V       .fill 4
ANSWER  .fill 0
.end
