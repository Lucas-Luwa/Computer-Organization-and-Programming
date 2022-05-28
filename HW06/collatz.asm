;;=======================================
;; CS 2110 - Fall 2021
;; HW6 - Collatz Conjecture
;;=======================================
;; Name: Lucas Luwa
;;=======================================

;; In this file, you must implement the 'collatz' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in Complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'collatz' label.


.orig x3000
HALT

collatz
;; See the PDF for more information on what this subroutine should do.
;;
;; Arguments of collatz: postive integer n
;;
;; Pseudocode:
;; collatz(int n) {
;;     if (n == 1) {
;;         return 0;
;;     }
;;     if (n % 2 == 0) {
;;         return collatz(n/2) + 1;
;;     } else {
;;         return collatz(3 * n + 1) + 1;
;;     }
;; }


;; YOUR CODE HERE
;; Setup
    ADD R6, R6, -4  ; make space for RA, RV, old FP and one local
    STR R7, R6, 2   ; save return address
    STR R5, R6, 1   ; saves old frame pointer
    ADD R5, R6, 0   ; point frame pointer at the first local variable
    ADD R6, R6, -5  ; allocate space to save all five registers R0-R4
    
    ; save registers
    STR R0, R6, 0
    STR R1, R6, 1
    STR R2, R6, 2
    STR R3, R6, 3
    STR R4, R6, 4

    LDR R0, R5, 4   ;R0 = N ;R0 = N
    ADD R0, R0, #-1  ;R0 = R0-1
    BRz RETURN1


    LDR R0, R5, 4   ;R0 = N ;R0 = N
    AND R0, R0, 1   ;R0 = R0
    Brz RETURN2

    LDR R0, R5, 4   ;R0 = N ;R0 = N
    AND R1, R1, 0   ;R1 = 0
    ADD R1, R0, 0   ;R1 = R0
    ADD R0, R0, R1  ;R0 = R0+R0
    ADD R0, R0, R1  ;R0 = R0+R0
    ADD R0, R0, 1   ;R0 = R0+1

    ADD R6, R6, -1  ; allocate space for orne argument
    STR R0, R6, 0   ; pass the parameter for the callee
    JSR collatz
    LDR R1, R6, 0   ; return value in R1
    ADD R6, R6, 2   ; R6 back to the top of the stack

    ADD R3, R1, 1   ;return collatz(n*3+1) + 1;
    BR TEARDOWN

    RETURN1
    AND R3, R0, 0 ; R0 = 0
    BR TEARDOWN
 
    RETURN2
    LDR R0, R5, 4   ;R0 = N ;R0 = N
    ADD R6, R6, -1  ; allocate space for one argument
    STR R0, R6, 0   ; pass the parameter for the callee
    JSR divideBy2
    LDR R1, R6, 0   ; return value in R1
    ADD R6, R6, 2   ; R6 back to the top of the stack

    ADD R6, R6, -1  ; allocate space for one argument
    STR R1, R6, 0   ; pass the parameter for the callee
    JSR collatz
    LDR R2, R6, 0   ; return value in R2
    ADD R6, R6, 2   ; R6 back to the top of the stack

    ADD R3, R2, 1   ;return collatz(n/2) + 1;
    BR TEARDOWN

    TEARDOWN
    ; save the value in R0 on the stack as our return value
    STR R3, R5, 3

    ; restore registers
    LDR R0, R6, 0
    LDR R1, R6, 1
    LDR R2, R6, 2
    LDR R3, R6, 3
    LDR R4, R6, 4

    ; restore return address, frame pointer, and move R6 to Return Value
    ADD R6, R6, 6
    LDR R5, R6, 0
    LDR R7, R6, 1
    ADD R6, R6, 2

    RET ;Return to caller

;; The following is a subroutine that takes a single number n and returns n/2.
;; You may call this subroutine to help you with 'collatz'.

;; DO NOT CHANGE THIS SUBROUTINE IN ANY WAY
divideBy2
.fill x1DBC
.fill x7F82
.fill x7B81
.fill x1BA0
.fill x1DBB
.fill x7184
.fill x7383
.fill x7582
.fill x7781
.fill x7980
.fill x6144
.fill x5260
.fill x1020
.fill x0C03
.fill x103E
.fill x1261
.fill x0FFB
.fill x7343
.fill x6980
.fill x6781
.fill x6582
.fill x6383
.fill x6184
.fill x1D60
.fill x6B81
.fill x6F82
.fill x1DA3
.fill xC1C0


; Needed by Simulate Subroutine Call in Complx
STACK .fill xF000
.end