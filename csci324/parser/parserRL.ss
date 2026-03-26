; Alexandra Chase
; amchas26@g.holycross.edu
; CSCI 324 Programming Languages
; 03 February 2026
; Scheme Lab 3: Arithmetic Parser

(define (parse input)
  (cond
    [(null? input) 0] ; check if the atom passed as input is an empty list, if so return zero
    [(number? input) input] ; if the item is a number, return the number
    [(symbol? input) 1] ; otherwise, it must be a letter, return a value of one
    [(null? (cdr input)) (parse(car input))]
    [(list? input) ; if the item is a list... 
     (cond
      [(equal? '- (cadr input)) (- (parse(car input)) (parse(cdr(cdr input))))]
      [(equal? '+ (cadr input)) (+ (parse(car input)) (parse(cdr(cdr input))))]
      [(equal? '/ (cadr input)) (/ (parse(car input)) (parse(cdr(cdr input))))]
      [(equal? '* (cadr input)) (* (parse(car input)) (parse(cdr(cdr input))))])]))

(parse '5)
(parse '(6))
(parse '(5 + 6 + 7))
(parse '(5 - 6 - 7))
(parse '((5 - (6 - 7))))
(parse '((5 - 6) - 7))
(parse '(36 / 6 / 2 - 5 - a + 7))
