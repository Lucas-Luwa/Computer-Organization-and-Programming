;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 6 - Selection Sort
;;=============================================================
;; Name: Lucas Luwa 
;;=============================================================

;; In this file, you must implement the 'SORT' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff: don't run
;; this directly by pressing 'RUN' in complx, since there is nothing put at
;; address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'sort' label.

.orig x3000
HALT

;;Pseudocode (see PDF for explanation)
;;  arr: memory address of the first element in the array
;;  n: integer value of the number of elements in the array
;;
;;  sort(array, len, function compare) {
;;      i = 0;
;;      while (i < len - 1) {  ;; This essentiall equals i-len+1<0 if soo keep rollin'
;;          j = i;
;;          k = i + 1;
;;          while (k < len) { ;; again destroy len by doing k - len < 0
;;              // update j if ARRAY[j] > ARRAY[k]
;;              if (compare(ARRAY[j], ARRAY[k]) > 0) { so we need 2 items so destroy len and arr again
;;                  j = k;
;;              }
;;              k++;
;;          }
;;          temp = ARRAY[i]; good time to destroy stuff aka rip len
;;          ARRAY[i] = ARRAY[j];
;;          ARRAY[j] = temp;
;;          i++;
;;      }
;;  }

sort
;;start at 0 for first 
;;setup
ADD R6, R6, #-4 ; make space for RA, RV, old FP and one local
STR R7, R6, #2  ; save return address
STR R5, R6, #1  ; saves old frame pointer
ADD R5, R6, 0   ; point frame pointer at the first local variable
ADD R6, R6, #-1 ; One more local
ADD R6, R6, #-5 ; allocate space to save all five registers R0-R4

; save registers
STR R0, R6, 0
STR R1, R6, 1
STR R2, R6, 2
STR R3, R6, 3
STR R4, R6, 4

;;Startup!
;;R5, 0 (j)
;;R5, -1 (k)
AND R0, R0, #0       ; i = 0
LDR R3, R5, #4       ; array initialization
LDR R4, R5, #5       ; len inititialization

WHILE   LDR R3, R5, #4       ; array initialization ; again just in case we have some funny business happening
        LDR R4, R5, #5       ; len inititialization

        NOT R4, R4          ; FLIP BITS
        ADD R4, R4, #1      ; len = -len
        ADD R4, R4, #1      ; len = -len+1
        ADD R4, R4, R0      ; len = i-len+1
        BRzp TEARDOWN

        LDR R4, R5, #5      ; len = len;

        STR R0, R5, 0       ; j=i

        AND R1, R1, 0       ; R2 = 0
        ADD R1, R0, #1      ; k = i+1
        STR R1, R5, -1      ; k

    WHILE2  LDR R4, R5, #5   ; len = len;
            NOT R4, R4      ; FLIP BITS
            ADD R4, R4, #1  ; len = -len
            LDR R1, R5, #-1 ; R1 = k
            ADD R4, R4, R1  ; k-len < 0 keep goin'
            BRzp ENDGAME


                LDR R1, R5, #-1   ; R1 = k
                LDR R3, R5, 4   ; array initialization 
                ADD R3, R3, R1  ; ARRAY[k]
                LDR R3, R3, #0  ; ARRAY[k] value set

                ADD R6, R6, -1  ; allocate space for one argument
                STR R3, R6, 0   ; pass the parameter for the callee

                LDR R3, R5, 4   ; array initialization
                LDR R1, R5, #0  ; R1 = j
                ADD R3, R3, R1  ; ARRAY[j]
                LDR R3, R3, #0  ; ARRAY[j] val set

                ADD R6, R6, -1  ; allocate space for one argument
                STR R3, R6, 0   ; pass the parameter for the callee

                LDR R4, R5, 6
                JSRR R4
                LDR R4, R6, 0   ; return value in R4
                ADD R6, R6, 3   ; R6 back to the top of the stack

                ADD R4, R4, 0   ; Set Condition Codes
                BRnz JUMPER

                ;AND R1, R1, 0   ; Clear j
                ;ADD R1, R2, 0   ; j = k
                LDR R1, R5, #-1
                STR R1, R5, #0   ; j = k
                BR JUMPER               
    BR WHILE2
;;          temp = ARRAY[i]; good time to destroy stuff aka rip len
;;          ARRAY[i] = ARRAY[j];
;;          ARRAY[j] = temp; do this stuff

ENDGAME      
    LDR R3, R5, 4   ; array initialization
    AND R4, R4, 0   ; Clear R4
    ADD R4, R3, R0  ; ARRAY[i]
    LDR R2, R4, #0  ; Value Set R4 = temp = ARRAY[i]

    LDR R3, R5, 4   ; array initialization
    LDR R1, R5, #0  ; R1 = j
    ADD R1, R3, R1  ; ARRAY[j]
    LDR R1, R1, #0  ; Value set R2 for ARRAY[j]

    LDR R3, R5, 4   ; array initialization
    ADD R3, R3, R0  ; Set Location for ARRAY[i]
    STR R1, R3, #0

    LDR R3, R5, 4   ; array initialization  
    LDR R1, R5, #0  ; R1 = j
    ADD R1, R3, R1  ; ARRAY[j] = temp
    STR R2, R1, #0  ; ARRAY[j]

    ADD R0, R0, #1      ; i++
BR WHILE

JUMPER 
    LDR R1, R5, #-1       ; R1 = k
    ADD R1, R1, #1       ; k++;
    STR R1, R5, #-1            
BR WHILE2

;;Teardown
TEARDOWN
    ; restore registers
    LDR R0, R6, 0
    LDR R1, R6, 1
    LDR R2, R6, 2
    LDR R3, R6, 3
    LDR R4, R6, 4

    ; restore return address, frame pointer, and move R6 to Return Value
    ADD R6, R6, 6
    ADD R6, R6, #1 ;changes
    LDR R5, R6, 0
    LDR R7, R6, 1
    ADD R6, R6, 2
RET

;; used by the autograder
STACK .fill xF000
.end

;; USE FOR DEBUGGING IN COMPLX
;; load array at x4000 and put the length as 7

;; ARRAY
.orig x4000
    .fill 4
    .fill -9
    .fill 0
    .fill -2
    .fill 9
    .fill 3
    .fill -10
.end

;; The following subroutine is the compare function that is passed  
;; as the function address parameter into the sorting function. It   
;; will work perfectly fine as long as you follow the   
;; convention on the caller's side. 
;; DO NOT edit the code below; it will be used by the autograder.   
.orig x5000 
    ;;greater than  
CMPGT   
    .fill x1DBD
    .fill x7180
    .fill x7381
    .fill x6183
    .fill x6384
    .fill x927F
    .fill x1261
    .fill x1201
    .fill x0C03
    .fill x5020
    .fill x1021
    .fill x0E01
    .fill x5020
    .fill x7182
    .fill x6180
    .fill x6381
    .fill x1DA2
    .fill xC1C0
    .fill x9241
.end