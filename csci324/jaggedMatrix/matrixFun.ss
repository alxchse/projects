; Alexandra Chase
; amchas26@g.holycross.edu
; CSCI 324: Programming Languages
; 07 February 2026
; Scheme Lab 5: Jagged Matrix

; question? takes a column number (n) and a jagged matrix.
; the matrix is jagged because the member rows can be (but don't have to be) of different lengths.
; in question, we complete a series of procedures via the helper functions rowSorted? sorted? and sumColumn 

(define (question? n matrix)

  ; determine if the given row in the matrix is in sorted (ascending) order.
  (define (rowSorted? lst)
    (cond
      [(null? lst) #t]                      ; if we reach the end of the row or row is empty, it is sorted
      [(null? (cdr lst)) #t]                ; if there is only one item in the list, it is sorted
      [(or (< (car lst) (cadr lst))         ; if the current item is less than the next item
           (= (car lst) (cadr lst)))        ; or equal to the next item
       (rowSorted? (cdr lst))]              ; recursively continue checking the rest of the list
      [else #f]))                           ; otherwise, it is not sorted

  ; determine if every single row in the matrix is in sorted (ascending) order. calls the above function.
  (define (sorted? matrix) 
    (cond
      [(null? matrix) #t]                   ; if we have reached the end of the matrix or matrix is empty, it is sorted
      [(rowSorted? (car matrix))            ; take the current row and check if it is sorted using rowSorted?
       (sorted? (cdr matrix))]              ; recursively continue checking the rest of the matrix
      [else #f]))                           ; otherwise, not every row is sorted
  
  ; once we determine all the rows are sorted:
  ; take the nth atom in each row (in column n) and sum them
  (define (sumColumn n matrix)
    (cond
      [(null? matrix) 0]                    ; if we reach the end of the matrix or the matrix is empty, return 0     
      [(< (length (car matrix)) n)          ; ; if the column (nth item) does not exist within a particular row, 
       (sumColumn n (cdr matrix))]          ; skip the row and move onto the next.     
      [else 
       (+ (list-ref (car matrix) (- n 1))   ; otherwise, sum the nth item in the first row (n-1 because list-ref operates on 0-based index    
          (sumColumn n (cdr matrix)))]))    ; and recursively continue summing through the rest of the matrix. 

  (begin
    (newline)
    (display "__________________________________")
    (newline)
    (display matrix)
    (newline)
    (cond
      ((sorted? matrix)
       (begin
         (display "Every Row is in sorted order.")
         (newline)
         (display "The sum of column ")
         (display n)
         (display " is ")
         (display (sumColumn n matrix))))
      (else (display "The rows are not sorted.")))
    (newline)))

(question? 3 '((1 2 3) (2 3) (1 2 4 5)))
(question? 4 '((1 2 3 4 5 6 7) (1 2 3) (5 4) ()))
(question? 2 '((2 4 6 8 10 12) () (3) () ()))
(question? 6 '((1 2 3) (2 3) (1 2 4 5)))