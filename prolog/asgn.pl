type(g1, andt).
type(g2, ort).
connected(x1, in(1,g1)).
connected(x2, in(2,g1)).
connected(x2, in(2,g2)).
connected(out(g1), in(1,g2)).
connected(out(g2),x3).

signal(x1, 1).
signal(x2, 1).

mult(1,1,1) :- !.
mult(_,_,0).

sum(0,0,0) :- !.
sum(_,_,1).





signal(X, Y):- connected(out(G1),X), type(G1, andt),  signal(in(1, G1),X1), signal(in(2, G1),X2) ,mult(X1,X2,Y),!.
signal(X, Y):- connected(out(G1),X), type(G1, ort),  signal(in(1, G1),X1), signal(in(2, G1),X2) ,sum(X1,X2,Y),!.
signal(X, Y):- connected(V1,X),signal(V1,Y),!.
