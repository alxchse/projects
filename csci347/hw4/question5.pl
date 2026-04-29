% Alexandra Chase
% amchas26@g.holycross.edu
% CSCI 347 Artificial Intelligence
% Homework 4: Logic Programming in Prolog
% 01 April 2026

% maximum(X, Y): X is the biggest item in the list of integers Y
 
% base case is a single-element list, that element is the maximum
maximum(X, [X]).
 
% recursive case split list into head H and tail T,
% find the max M of the tail, then pick the larger of H and M
maximum(X, [H|T]) :-
    maximum(M, T),           % recursively find max of the tail
    (H >= M -> X = H         % if head >= tails max, head wins
             ; X = M).       % otherwise, tails max wins
 
 
% sorted(X) X is a list of integers in sorted (non-decreasing) order
 
% base case empty list is always sorted
sorted([]).
 
% second base case a single-element list is always sorted
sorted([_]).
 
% recursive case check that the first two elements are in order,
% then check that the rest of the list (from B onward) is also sorted
sorted([A, B | T]) :-
    A =< B,              % first element must be <= second element
    sorted([B | T]).     % recursively check the remainder of the list