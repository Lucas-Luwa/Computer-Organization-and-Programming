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

LD R0, ANSWER
AND R0, R0, #0      ; ANSWER = 0;
LD R1, A                ; a = (argument 1);
AND R2, R2, #0       ; Holder x = 0;
ADD R2, R2, R1      ; Holder = a;

;; WHILE (a>0){ Answer += a}

WHILE ADD R1, R1, #0
    Brnz END_WHILE

ADD R0, R0, R2         ;ANSWER += a;
ST R0, ANSWER
ADD R1, R1, #-1         ;a--;

BR WHILE
END_WHILE HALT


A .fill 9

ANSWER .blkw 1

.end
