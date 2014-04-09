%t1----\
%		and ---- t3
%t2----/

type(g, andt).
in(1, g, t1).
in(2, g, t2).
out(g,t3).
in(g,v1).
%=======

signal(t1, 1).
signal(t2, 0).
signal(v1,0).

mult(1,1,1) :- !.
mult(V1,V2,0).

sum(0,0,0) :- !.
sum(V1,V2,1).

not(1,0) :- !.
not(0,1).

eval(G,X) :- type(G, andt),in(1,G,T1),in(2,G,T2),signal(T1,T1v),signal(T2, T2v),mult(T1v,T2v,X), !.
eval(G,X) :- type(G, ort),in(1,G,T1),in(2,G,T2),signal(T1,T1v),signal(T2, T2v),sum(T1v,T2v,X), !.
eval(G,X) :- type(G, nott),in(G,V1),signal(V1, V1v),not(V1v,X).

