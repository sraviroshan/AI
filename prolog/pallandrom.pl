type(g1, andt).
type(g2, andt).
type(g3, andt).
type(g4, andt).
type(g5, andt).
type(g6, ort).
type(g7, ort).
type(g8, nott).
type(g9, nott).
type(g10, nott).
type(g11, nott).

connected(x1, in(1,g1)).
connected(x5, in(2,g1)).
connected(x1, in(g8)).
connected(x5, in(g9)).
connected(out(g8), in(1,g2)).
connected(out(g9), in(2,g2)).
connected(out(g1), in(1,g6)).
connected(out(g2), in(2,g6)).

connected(x2, in(1,g3)).
connected(x4, in(2,g3)).
connected(x2, in(g10)).
connected(x4, in(g11)).
connected(out(g10), in(1, g4)).
connected(out(g11), in(2, g4)).
connected(out(g3), in(1, g7)).
connected(out(g4), in(2, g7)).

connected(out(g6), in(1, g5)).
connected(out(g7), in(2, g5)).

connected(out(g5),x0).

signal(x1, 0).
signal(x2, 1).
signal(x3, 1).
signal(x4, 1).
signal(x5, 0).








mult(1,1,1) :- !.
mult(_,_,0).

sum(0,0,0) :- !.
sum(_,_,1).

not(1,0) :- !.
not(0,1).




signal(X, Y):- connected(out(G1),X), type(G1, andt),  signal(in(1, G1),X1), signal(in(2, G1),X2) ,mult(X1,X2,Y),!.
signal(X, Y):- connected(out(G1),X), type(G1, ort),  signal(in(1, G1),X1), signal(in(2, G1),X2) ,sum(X1,X2,Y),!.
signal(X, Y):- connected(out(G1),X), type(G1, nott),  signal(in(G1),X1), not(X1,Y),!.
signal(X, Y):- connected(V1,X),signal(V1,Y),!.
