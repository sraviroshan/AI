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

type(x1,term).
type(x2,term).
type(x3,term).
type(x4,term).
type(x5,term).
type(x0,term).

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




signal(X1,X2,X3,X4,X5,Y):- valid(X1,X2,X3,X4,X5,Y), signal(X1,X2,X3,X4,X5,x0,Y).


valid(X1,X2,X3,X4,X5,Y):- valid(X1),valid(X2),valid(X3),valid(X4),valid(X5),valid(Y).
valid(X):-member(X,[0,1]).

signal(X1,X2,X3,X4,X5,x1, X1):-valid(X1,X2,X3,X4,X5,1).
signal(X1,X2,X3,X4,X5,x2, X2):-valid(X1,X2,X3,X4,X5,1).
signal(X1,X2,X3,X4,X5,x3, X3):-valid(X1,X2,X3,X4,X5,1).
signal(X1,X2,X3,X4,X5,x4, X4):-valid(X1,X2,X3,X4,X5,1).
signal(X1,X2,X3,X4,X5,x5, X5):-valid(X1,X2,X3,X4,X5,1).


mult(1,1,1) .
mult(0,1,0).
mult(1,0,0).
mult(0,0,0).

sum(0,0,0) .
sum(1,1,1).
sum(0,1,1).
sum(1,0,1).

not(1,0) .
not(0,1).


signal(X1,X2,X3,X4,X5,X,Y):- connected(out(G1),X), type(G1, andt), signal(X1,X2,X3,X4,X5,in(1,G1),T1), signal(X1,X2,X3,X4,X5,in(2,G1),T2) ,mult(T1,T2,Y).
signal(X1,X2,X3,X4,X5,X,Y):- connected(out(G1),X), type(G1, ort),  signal(X1,X2,X3,X4,X5,in(1,G1),T1), signal(X1,X2,X3,X4,X5,in(2,G1),T2) ,sum(T1,T2,Y).
signal(X1,X2,X3,X4,X5,X,Y):- connected(out(G1),X), type(G1, nott), signal(X1,X2,X3,X4,X5,in(G1),T1), not(T1,Y).
signal(X1,X2,X3,X4,X5,X,Y):- connected(V1,X),type(V1,term),signal(X1,X2,X3,X4,X5,V1,Y).
