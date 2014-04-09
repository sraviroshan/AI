likes(mary,food).
likes(mary,wine).
likes(john,X):- likes(mary,X).


size([],0).
size([H|T],N) :- size(T,N1), N is N1+1.

sumlist([],0).
sumlist([H|T],N) :- sumlist(T,N1), N is N1+H.


member([H|T],H) :- !.
member([H|T],X):- member(T,X), !.


helpmember([H], H).
mymember([H|T],X):- helpmember([H], X); mymember(T,X), !.


fact(0,1).
fact(N,X):- N>0, N1 is N-1,fact(N1,X1), X is X1*N.  

