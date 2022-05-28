;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 5 - Square
;;=============================================================
;; Name: Lucas Luwa
;;=============================================================

;; Pseudocode (see PDF for explanation)
;; a = (argument 1);
;; ANSWER = 0;
;; for (int i = 0; i < a; i++) {
;;		ANSWER += a;
;; }
;; return ANSWER;

.orig x3000

;;put your code here

LD R1, ANSWER
AND R1, R1, #0      ; ANSWER = 0;
LD R2, A                ; a = (argument 1);
AND R3, R3, #0       ; Holder x = 0;
ADD R3, R3, R2      ; Holder = a;

;; WHILE (a>0){ Answer += a}

WHILE ADD R2, R2, #0
    Brnz END_WHILE

ADD R1, R1, R3         ;ANSWER += a;
ADD R2, R2, #-1         ;a--;

BR WHILE
END_WHILE HALT


A .fill 9

ANSWER .blkw 1

.end
