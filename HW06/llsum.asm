;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 6 - Linked List Sum
;;=============================================================
;; Name: Lucas Luwa
;;============================================================

;; In this file, you must implement the 'llsum' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff: don't run
;; this directly by pressing 'RUN' in complx, since there is nothing put at
;; address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'reverseCopy' label.

.orig x3000
HALT

;; Pseudocode (see PDF for explanation):
;;
;; Arguments of llsum: Node head
;;
;; llsum(Node head) {
;;     // note that a NULL address is the same thing as the value 0
;;     if (head == NULL) {
;;         return 0;
;;     }
;;     Node next = head.next;
;;     sum = head.data + llsum(next);
;;     return sum;
;; }

llsum
;;setup
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

    LDR R0, R5, 4       ; Grab head
    ADD R0, R0, 0       ; if(head == NULL)
    BRz TEARDOWN

    LDR R1, R0, 0       ; Grab Next
    
    ADD R0, R0, #1      ; Grab Data 
    LDR R0, R0, 0       ; Data Loading

    ADD R6, R6, -1  ; allocate space for one argument
    STR R1, R6, 0   ; pass the parameter for the callee
    JSR llsum
    LDR R1, R6, 0   ; return value in R1
    ADD R6, R6, 2   ; R6 back to the top of the stack

    ADD R0, R0, R1  ; head.data+llsum(next)

;;Teardown
    TEARDOWN
    ; save the value in R0 on the stack as our return value
    STR R0, R5, 3

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

RET

;; used by the autograder
STACK .fill xF000
.end

;; The following is an example of a small linked list that starts at x4000.
;;
;; The first number (offset 0) contains the address of the next node in the
;; linked list, or zero if this is the final node.
;;
;; The second number (offset 1) contains the data of this node.
.orig x4000
.fill x4008
.fill 5
.end

.orig x4008
.fill x4010
.fill 12
.end

.orig x4010
.fill 0
.fill -7
.end
