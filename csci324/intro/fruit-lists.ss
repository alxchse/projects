;; Alexandra Chase
;; amchas26@g.holycross.edu
;; CSCI 324
;; Scheme Lab 1: Find Pear
;; 27 January 2026

;; Picking out "pear" from three different list structures.
;; Each expression uses car and/ or cdr to find the symbol "pear."

;; List 1: (apple orange pear grapefruit)
(car (cdr (cdr '(apple orange pear grapefruit))))

;; List 2: (((apple) (orange) (pear) (grapefruit)))
(car (car (cdr (cdr (car '(((apple) (orange) (pear) (grapefruit))))))))

;; List 3: (apple (orange) ((pear)) (((grapefruit))))
(car (car (car (cdr (cdr '(apple (orange) ((pear)) (((grapefruit)))))))))