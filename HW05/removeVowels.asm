;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 5 - Remove Vowels
;;=============================================================
;; Name: Lucas Luwa
;;=============================================================

;; Pseudocode (see PDF for explanation)
;; STRING = (argument 1);
;; ANSWER = "";
;; for (int i = 0; i < a.length; i++) {
;;       if (string[i] == '\0'){
;;          break;
;;        }

;;       if (string[i] == ’A’) {
;;           continue;
;;        } else if (string[i] == ’E’) {
;;            continue;
;;        } else if (string[i] == ’I’) {
;;            continue;
;;        } else if (string[i] == ’O’) {
;;            continue;
;;        } else if (string[i] == ’U’) {
;;            continue;
;;        } else if (string[i] == ’a’) {
;;            continue;
;;        } else if (string[i] == ’e’) {
;;            continue;
;;        } else if (string[i] == ’i’) {
;;            continue;
;;        } else if (string[i] == ’o’) {
;;            continue;
;;        } else if (string[i] == 'u') {
;;            continue;
;;        }
;;
;;        ANSWER += STRING[i];
;;	}
;;  ANSWER += '\0';
;;
;;  return ANSWER;
;; }

.orig x3000


AND R0, R0, #0               ; i = 0
AND R7, R7, #0               ; ANSWER[j]
LD R1, STRING               ; Loading String Value
LD R4, ANSWER               ; Load Answer Value


WHILE 
      ADD R4, R4, R7        ; ANSWER[i]
      ADD R1, R1, R0        ; STRING[i]
      ;LDR R4, R4, #0
      LDR R1, R1, #0
      Brz END_WHILE        ; break if string[i] == '\0'

    NOT R3, R1
    ADD R3, R3, #1

        LD R6, LOWERA
        ADD R5, R3, R6  
      BRz JUMPER
        LD R6, A
        ADD R5, R3, R6 
      BRz JUMPER
        LD R6, LOWERE
        ADD R5, R3, R6 
      BRz JUMPER
        LD R6, E
        ADD R5, R3, R6  
      BRz JUMPER
        LD R6, LOWERI
        ADD R5, R3, R6 
      BRz JUMPER
        LD R6, I
        ADD R5, R3, R6  
      BRz JUMPER
        LD R6, LOWERO
        ADD R5, R3, R6 
      BRz JUMPER
        LD R6, O
        ADD R5, R3, R6
      BRz JUMPER
        LD R6, LOWERU
        ADD R5, R3, R6 
      BRz JUMPER
        LD R6, U
        ADD R5, R3, R6 
      BRz JUMPER

      STR R1, R4, #0              ; Answer[i] = String[i]
      LD R1, STRING               ; Loading String Value
      LD R4, ANSWER               ; Load Answer Value
      ADD R0, R0, #1 
      ADD R7, R7, #1

BR WHILE
END_WHILE 
  AND R1, R1, #0
  STR R1, R4, #0
  HALT


JUMPER
    LD R1, STRING               ; Loading String Value
    LD R4, ANSWER               ; Load Answer Value
    ADD R0, R0, #1
BR WHILE

STRING .fill x4000
ANSWER .fill x4100



;;NOTE: For your convenience, you can make new labels for
;;the ASCII values of other vowels here! 2 have been done
;;here as an example.

LOWERA .fill x61    ;; a in ASCII
A .fill x41         ;; A in ASCII
LOWERE .fill x65     ;; e in ASCII
E .fill x45         ;; E in ASCII
LOWERI .fill x69     ;; i in ASCII
I .fill x49         ;; I in ASCII
LOWERO .fill x6f    ;; o in ASCII
O .fill x4f        ;; O in ASCII
LOWERU .fill x75   ;; u in ASCII
U .fill x55        ;; U in ASCII


.end

.orig x4000

.stringz "spongebob and SQUIDWARD"

.end
