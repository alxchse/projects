; Alexandra Chase
; amchas26@g.holycross.edu
; CSCI 324 Programming Languages
; 05 February 2026
; Scheme Lab 4: Magic Rows

; magic? determines whether each of the rows of the matrix sum to the same number.
; within magic?, we use helper functions sumAdd, identical? and magicRows. 
; input: square matrix (# of rows and columns are equal).
; output: given matrix, size of the matrix, a list that contains the sum of each row, and a statement about the row sums.
; assumptions: matrix is square, integers in matrix are positive, there are no nested lists.

(define (magic? matrix)  

  ; we will be using sumAdd from the warmup lab as a helper function!
  ; sumAdd takes an atom, either a list or an integer, and returns the sum of all the integers within given list.
  (define (sumAdd lst)
    (cond
      [(null? lst) 0]                              ; if atom is an empty list, return 0 for sum
      [(number? lst) lst]                          ; if the atom is a number, return the number to be added at the end
      [(list? lst)                                 ; if the atom is a list, first recurse through the first item 
       (+ (sumAdd (car lst)) (sumAdd (cdr lst)))]  ; then recurse through the rest of the list
      [else 0]))       

  ; takes the listOfSums and recusively checks if every row's sum is the same
  (define (identical? lst)
   (cond
    [(null? lst) #t]                               ; if the list is empty, we have reached the end
    [(null? (cdr lst)) #t]                         ; if there is only one item in the list, then it must be identical
    [(= (car lst) (cadr lst))                      ; compare the first and second items of the list
     (identical? (cdr lst))]                       ; then recurse into the rest of the list and compare those. 
    [else #f]))                                    ; otherwise, the values are not identical. 

  ; takes the matrix and calls sumAdd for each row. takes the returned values and puts them into listOfSums
  (define (magicRows matrix)
    (cond
      [(null? matrix) '()]                         ; if the matrix is empty, return an empty list
      [else (cons (sumAdd (car matrix))            ; otherwise, prepend the sum of the first row to listOfSums
             (magicRows (cdr matrix)))]))          ; then recurse through the rest of the rows and do the same

  (define listOfSums (magicRows matrix))           ; list of sums for each row of the matrix, which we will run identical? on later  
  (define numRows (length matrix))                 ; number of items per row and number of rows in matrix. 
   
  (begin
         (newline)
         (display "____________Info_____________")
         (newline)
         (display matrix)
         (newline)
         (display "Number of elements in each row: ")
         (display numRows)                                 ; displays numRows
         (newline)
         (display (magicRows matrix))                      ; print the list with row sums
         (newline)
         (if (and (identical? listOfSums) (= 0 numRows))   ; if identical? returns true and numRows = 0, we know the list is empty
               (display "The list is empty.")              
             (if (identical? listOfSums)                   ; otherwise, if identical? returns #t, we know the sums are identical
               (display "Row sums are identical!")
               (display "Row sums are not the same.")))    ; alternative, if identical returns #f, we know the sums are not identical. 
         (newline)))

(magic? '((1 2 3 4 5) (2 3 4 5 1) (3 4 5 1 2) (4 5 1 2 3) (5 1 2 3 4)))
(magic? '((1 2 3) (2 3 3) (4 2 1)))
(magic? '())
