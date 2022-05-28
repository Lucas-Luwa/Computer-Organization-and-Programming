;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 5 - Array Modify
;;=============================================================
;; Name: Lucas Luwa
;;=============================================================

;; Pseudocode (see PDF for explanation)
;;
;;    i = 0; // first index 
;;    len = Len(ARR_X);
;;
;;    while (i < len) {    --> len-i>0
;;        if (i % 2 == 0) {
;;            //if we are at an even index, subtract 10 and save it to the array at that index 
;;    	    ARR_Y[i] = ARR_X[i] - 10;
;;        } else {
;;            //if we are at odd index, multiply by 2 and save it to the array at that index 
;;    	    ARR_Y[i] = ARR_X[i] * 2;
;;        }
;;        	i++;
;;    }

.orig x3000

;WHILE LD L2, LENGTH         ; L2 = LENGTH
;      NOT R2, R2            ; R2 = -LENGTH
;      ADD R2, R2, #1        ; R2 = R2 + 1
;      ADD R1, R2, #0        ; R1 = 
;      Brnz END_WHILE
;;put your code here

LD R6, ARR_X
LD R7, ARR_Y
LD R3, LENGTH
AND R0, R0, #0              ; i = 0
AND R1, R1, #0              ; len = 0
ADD R1, R1, R3              ; len = Len(ARR_X);

WHILE NOT R2, R0             ; R2 = -R0 | IF len-i <=0 then problem
      ADD R2, R2, #1         ; R2 = R2 + 1
      ADD R2, R2, R1         ; R2 = R2 + R1 
      Brnz END_WHILE         ; while (i<len)
      

      IF AND R4, R4, #0      ; R4 = 0
         AND R4, R0, #1      ; R4 = R0 & 1
         Brp ELSE

      ADD R6, R6, R0         ; ARR_X[i]
      LDR R6, R6, #0            ; ARR_X[i] 
      ADD R6, R6, #-10       ; ARR_X[i]-10
      ADD R7, R7, R0         ; ARR_Y[i]
      STR R6, R7, #0      ; ARR_Y[i] = ARR_X[i]-10
      LD R6, ARR_X
      LD R7, ARR_Y
      ADD R0, R0, #1         ;i++


BR WHILE
END_WHILE HALT

ELSE 
      ADD R6, R6, R0         ; ARR_X[i] ; dumbass fix this 
      ;LDR R6, R6, #0            ; ARR_X[i] ; wut in the sus is this??
      AND R5, R5, #0
      LDR R5, R6, #0
      ADD R5, R5, R5      ; ARR_X[i] * 2
      ADD R7, R7, R0         ; ARR_Y[i]
      STR R5, R7, #0      ; ARR_Y[i] = ARR_X[i]*2
      LD R6, ARR_X
      LD R7, ARR_Y
      ADD R0, R0, #1         ;i++
BR WHILE

ARR_X       .fill x4000
ARR_Y       .fill x4100
LENGTH      .fill 4
.end







.orig x4000
.fill 1
.fill 5
.fill 10
.fill 11
.end

.orig x4100
.blkw 4
.end
