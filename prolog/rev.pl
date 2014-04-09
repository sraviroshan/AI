myappend([], L, L).
myappend([H|L1], L2, [H|R]) :- myappend(L1, L2, R).

myreverse([],[]).
myreverse([H|L], R) :- myreverse(L,R1), myappend(R1,[H],R).

