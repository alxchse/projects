% Alexandra chase
% amchas26@g.holycross.edu
% CSCI 324
% 27 April 2026
% Question Prolog Lab

what([], X, X).                              % BASE CASE if the first list is empty, then all of the redundant elements have been cut
what([X | R], Y, Z) :-
    member(X, Y),                            % checks if the head of the first list is a member of the next list
    !,                                       % if so, then cut it from the first list
    what(R, Y, Z).                           % and recurse through the rest of the first list 
what([X | R], Y, [X | Z]) :- what(R, Y, Z).  % when X is not a member of Y, it becomes the head of the result list. it then recurses through the rest of the first list. 