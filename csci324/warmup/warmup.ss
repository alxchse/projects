; Alexandra Chase
; amchas26@g.holycross.edu
; CSCI 324 Programming Languages
; 29 January 2026
; Scheme: Warm Up Problem

; sumAdd is a function that takes a list and adds all of the integers within the list.
; it uses recursion to go through all the nested lists and add those first, then goes
; back to the least-nested (?) integers and sums those at the end. 

(define (sumAdd lst)
  (cond
    [(null? lst) 0]                              ; if atom is an empty list, return 0 for sum
    [(number? lst) lst]                          ; if the atom is a number, return the number to be added at the end
    [(list? lst)                                 ; if the atom is a list, first recurse through the first item 
     (+ (sumAdd (car lst)) (sumAdd (cdr lst)))]  ; then recurse through the rest of the list
    [else 0]))                                   ; theres no other cases that matter

(sumAdd '(4 5 ((44 31 5) ()) x ((((10))) (5 (5))) 0 1))
(sumAdd '87)