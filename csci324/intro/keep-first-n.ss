;; Alexandra Chase
;; amchas26@g.holycross.edu
;; CSCI 324 Programming Languages
;; 29 January 2026
;; Intro to Scheme: Recursion

;; This keep-first-n function takes a list and a number n.
;; It takes the first n atoms from this list and puts them in a list. 

(define (keep-first-n lst n)
  (cond
    ((null? lst) '())                             ;; if the list is empty, return empty list
    ((= 0 n) '())                                 ;; if the user asks for 0 numbers, return an empty list
    ((> 0 n) (display "n must not be negative!")) ;; if n is negative it will fail
    (else (cons(car lst)                          ;; otherwise, add the current atom to the end of the list
          (keep-first-n (cdr lst) (- n 1))))))    ;; and recurse through the rest, decrement n

;; This is the sample list we will use.

(define lst
  (list 'a 'b 'c 'd 'e 'f 'g 'h 'i))

;; Now test the program. 

(display "making new list using first three atoms in list (a b c d e f g h i)...")
(keep-first-n lst 3)
(newline)
(display "making new list using first 100 atoms in list (a b c d e f g h i)...")
(keep-first-n lst 100)
(newline)
(display "making new list using first zero atoms in list (a b c d e f g h i)...")
(keep-first-n lst 0)
(newline)



