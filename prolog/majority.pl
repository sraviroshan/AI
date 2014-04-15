type(g1, andt).
type(g2, andt).
type(g3, andt).
type(g4, andt).
type(g5, andt).
type(g6, andt).
type(g7, andt).
type(g8, andt).
type(g9, andt).
type(h1, ort).
type(h2, ort).
type(h3, ort).
type(h4, ort).
type(h5, ort).
type(h6, ort).
type(h7, ort).
type(h8, ort).

connected(x1, in(1,h1)).
connected(x5, in(2,h1)).
connected(x2, in(1,g1)).
connected(x3, in(2,g1)).
connected(x2, in(1,g2)).
connected(x4, in(2,g2)).
connected(out(g1), in(1,h2)).
connected(out(g2), in(2,h2)).
connected(out(h1), in(1, g3)).
connected(out(h2), in(2, g3)).

connected(x1, in(1,h3)).
connected(x3, in(2,h3)).
connected(x4, in(1,g4)).
connected(x5, in(2,g4)).
connected(out(h3), in(1, g5)).
connected(out(g4), in(2, g5)).

connected(x1, in(1,h4)).
connected(x2, in(2,h4)).
connected(x3, in(1,g6)).
connected(x4, in(2,g6)).
connected(out(h4), in(1, g7)).
connected(out(g6), in(2, g7)).

connected(x2, in(1,h5)).
connected(x3, in(2,h5)).
connected(x1, in(1,g8)).
connected(x5, in(2,g8)).
connected(out(h5), in(1, g9)).
connected(out(g8), in(2, g9)).


connected(out(g3), in(1, h6)).
connected(out(g5), in(2, h6)).
connected(out(g7), in(1, h7)).
connected(out(g9), in(2, h7)).
connected(out(h6), in(1, h8)).
connected(out(h7), in(2, h8)).

connected(out(h8),x0).

signal(x1, 1).
signal(x2, 0).
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
