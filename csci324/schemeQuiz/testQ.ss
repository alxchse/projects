;; Alexandra Chase
;; amchas26@g.holycross.edu
;; CSCI 324 Scheme Quiz

(define (question? grid)

  ; helper function returns absolute value of a number
  (define (abs n)
    (cond
      [(< 0 n) n] ; if number is positive, return number
      [(= 0 n) 0] ; if number equals zero, return 0 
      [else (- 0 n)])) ; if number is negative, return (0 - n)
      
  ; helper function that executes the subtraction of two consecutive numbers and puts their absolute values in a list        
  (define (absDifference lst)
    (cond
      [(null? lst) '()] ; if the list is empty, return empty list...?
      [(null? (cdr lst)) '()] ; if there is values left to subtract (only one value left), we reached the end and break recursion.
      [else
       (cons (difList) (abs(- (car lst) (cadr lst))))])) ; otherwise add the absolute value of the difference to the list

  ; helper function determines if a specified number, in our case length of the original list (n) is in the given list
  (define (inList? n lst)
    (cond
      [(null? lst) #f] ; if list is empty, n is definitely not in it
      [(= (car list) n) #t] ; if we found n in the car, yay, return true
      [else (inList? n (cdr lst))])) ; if not, recursively check the rest of the list
       
  ; helper function that takes the difference list and determines if the elements take successive values from 1 through n-1
  (define (jolly? n lst)
    (cond
      [(null? lst) #t] ; if we have reached the end of the list, hooray its jolly
      [(inList? n lst) (jolly? (- 1 n) lst)] ; if the current n is in the lst, take n-1 and recursively check the list again
      [else #f])) ; otherwise its not in the list, and we fail. 

  ; main function if you will
  (cond
    [(null? grid) '()] ; if the list is empty, it is not possible to be jolly, return empty list
    [(null? (cdr grid)) '()] ; if the list only has one item, it is not possible to be jolly, return empty list
    [else
     (jolly? (- 1 (length grid)) (list difList(absDifference grid)))]) ; otherwise, pass on to the difference function
     
      
   (begin
         (display "____________Results_____________")
         (newline)
         (display grid)
         (newline)

         (newline)
         (display "The list is ")
         (if (question? grid)
             (display "jolly!")
             (display "not jolly."))
         (newline)        
         (newline)
    )
)  ;; question

;; -------------------------------- TESTS --------------------------------------

(display "Testing:  ")
 (newline)
;; Add appropriate additional test cases here, remove any below that do not work
;; This is not an exhaustive list of test cases, but it will get you started.
;; 
(display "Example 1:")
(question?  '(10 3 17 4 8) ) ;; Expect NOT 
(newline) (newline)

(display "Example 2:")
(question?  '(19 10 5 2 6 8 9 15 8 16) ) ;; Expect that it is 
(newline)(newline)

(display "Example 3:")
(question?  '(10 5 2 6 8 9) ) ;; Expect that it is 
(newline)(newline)

(display "Example 4:")
(question?  '(1 4 2 3) ) ;; Expect that it is 
(newline)(newline)

(display "Example 5:")
(question?  '(9) ) ;; Expect NOT 
(newline)(newline)

(display "Example 6:")
(question?  '() ) ;; Expect NOT 
(newline)(newline)
