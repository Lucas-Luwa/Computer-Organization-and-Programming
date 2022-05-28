;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 5 - Toggle Case
;;=============================================================
;; Name: Lucas Luwa
;;=============================================================

;; Pseudocode (see PDF for explanation):
;;
;;	string = "Assembly is interesting"; // given string
;;	Array[string.len()] answer; // array to store the result string
;;	i = 0;
;;
;;	while (string[i] != '\0') {
;;	    if (string[i] == " ") {
;;	        answer[i] = " ";
;;	    } else if (string[i] >= "A" && string[i] <= "Z") {
;;	        answer[i] = string[i].lowerCase();
;;	    } else {
;;	        answer[i] = string[i].upperCase();
;;	    }
;;	    i++;
;;	}


.orig x3000


;; READ LINE 40
;; put your code here

AND R0, R0, #0          ; i = 0
LD R6, STRING           ; Load Starting Address 
LD R7, ANSWER           ; Load Starting Address

WHILE AND R2, R2, #0    ; Clear R2
      AND R1, R1, #0    ; Clear R1
      ADD R1, R6, R0    ; string[i]
      ADD R2, R7, R0    ; answer[i]
      LDR R1, R1, #0    ; string[i] value
      BRz END_WHILE

      AND R3, R3, #0    ; Clear R3
      NOT R3, R1        ; Flip R1 Bits
      ADD R3, R3, #1    ; R3 = -R1

      LD R4, SPACE
      ADD R4, R4, R3
      Brz COND1

      LD R4, A
      ADD R4, R4, R3
      Brnz COND2A

      LD R4, Z
      ADD R4, R4, R3
      Brzp COND2Z
      ADD R0, R0, #1    ; i++  
BR WHILE

COND1
      STR R1, R2, #0
      ADD R0, R0, #1    ; i++    
BR WHILE

COND2A
    LD R4, Z
    ADD R4, R4, R3
    Brn CONDELSE
    ADD R1, R1, #15
    ADD R1, R1, #15
    ADD R1, R1, #2
    STR R1, R2, #0
    ADD R0, R0, #1    ; i++
BR WHILE

COND2Z
      LD R4, A
      ADD R4, R4, R3
      Brp CONDELSE
      ADD R1, R1, #15
      ADD R1, R1, #15 
      ADD R1, R1, #2  
      STR R1, R2, #0
      ADD R0, R0, #1    ; i++
BR WHILE

CONDELSE
      ADD R1, R1, #-15
      ADD R1, R1, #-15
      ADD R1, R1, #-2
      STR R1, R2, #0
      ADD R0, R0, #1    ; i++
BR WHILE

END_WHILE 
    AND R5, R5, #0
    STR R5, R2, #0
HALT


;; ASCII table: https://www.asciitable.com/


;; FILL OUT THESE ASCII CHARACTER VALUE FIRST TO USE IT IN YOUR CODE
SPACE	.fill x20
A		.fill x41
Z		.fill x5a
a       .fill x61
z       .fill x7a
BREAK	.fill x5D	;; this is the middle of uppercase and lowercase characters

STRING .fill x4000
ANSWER .fill x4100
.end

.orig x4000
.stringz "Assembly is INTERESTING"
.end

.orig x4100
.blkw 23
.end