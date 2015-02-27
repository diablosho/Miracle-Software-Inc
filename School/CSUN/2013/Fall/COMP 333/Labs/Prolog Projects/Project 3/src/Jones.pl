/*
Name:      Brian Jones
Class:     Comp 333
Asmt:      Project 3
Due Date:  12/3/2013
*/

/*Problem 1:
-Create a Prolog database of your family tree (based only on parent,
male, female facts) back to your grandparents or great grandparents. Ad
parent, male, and female facts as needed if your family is small.
Similar to our Ancestor DB but for your family. Draw a graph of the
family tree.
-Add relationship rules for ancestor, grandparent, grandfather,
grandmother, mother, father, aunt, uncle, cousin, sister, brother, and
descendant.
-Test your Prolog program.  All rules should be tested at least once.
-Use the Prolog trace to trace one ancestor query that has more than 10
lines in the trace.*/

/*
Grandfather:  Raymond Keim
Grandmother:  Colette Keim
Mother:       Jacqueline Jones
Aunt:         Marge Keim
Aunt:         Denise Keim
Uncle:        Bruce Keim
Uncle:        Pat Wheeler
Uncle:        Gary Sendek
Cousin:	      Christy Wheeler
Cousin:       Aimee Wheeler
Cousin:       Lisa Sendek
Cousin:       Casey Sendek
Cousin:       Bobby Sendek

Grandfather:  Quentin Jones III
Grandmother:  Crystal Hildebrecht
Father:       Quentin Jones IV
Aunt:         Gwen Schwenk
Aunt:         Marlene Jones
Uncle:        Bob Schwenk

Brother:      Raymond Jones
Self:         Brian Jones
*/

male(raymond1).
male(bruce).
male(gary).
male(pat).
male(quentin3).
male(bob).
male(quentin4).
male(raymond2).
male(brian).
male(bob).

female(colette).
female(marge).
female(denise).
female(jacqueline).
female(crystal).
female(gwen).
female(marlene).
female(lisa).
female(casey).
female(christy).
female(aimee).
female(autumn).
female(olivia).
female(pamela).
female(esmeralda).

parent(raymond1, marge).
parent(raymond1, denise).
parent(raymond1, jacqueline).
parent(raymond1, bruce).
parent(colette, marge).
parent(colette, denise).
parent(colette, jacqueline).
parent(colette, bruce).
parent(quentin3, gwen).
parent(quentin3, marlene).
parent(quentin3, bob).
parent(quentin3, quentin4).
parent(crystal, gwen).
parent(crystal, marlene).
parent(crystal, bob).
parent(crystal, quentin4).
parent(quentin4, raymond2).
parent(quentin4, brian).
parent(jacqueline, raymond2).
parent(jacqueline, brian).
parent(marge, lisa).
parent(marge, casey).
parent(marge, bob).
parent(gary, lisa).
parent(gary, casey).
parent(gary, bob).
parent(denise, christy).
parent(denise, aimee).
parent(pat, christy).
parent(pat, aimee).
parent(christy, autumn).
parent(raymond2, olivia).
parent(raymond2, pamela).
parent(esmeralda, olivia).
parent(esmeralda, pamela).

grandparent(X,Y) :- parent(X,Z), parent(Z,Y).
grandmother(X,Y) :- female(X), grandparent(X,Y).
grandfather(X,Y) :- male(X), grandparent(X,Y).

mother(X,Y) :- female(X), parent(X,Y).
father(X,Y) :- male(X), parent(X,Y).
brother(X,Y) :- male(X), descendant(X,Z), descendant(Y,Z).
sister(X,Y) :- female(X), descendant(X,Z), descendant(Y,Z).

descendant(X,Y) :- parent(Y,X).
cousin(X,Y) :- parent(Z,Y), brother(Z, M), descendant(X, M).
cousin(X,Y) :- parent(Z,Y), sister(Z, M), descendant(X, M).
ancestor(X,Y) :- parent(X,Y).
ancestor(X,Y) :- parent(X,Z), ancestor(Z,Y).

/*Problem 2:
-Write a Prolog program to check that a list has no duplicates. Your
queries should look like nodups ([1,5,3,7,9]). It will return true if
there are no duplcates and false otherwise.*/
nodups([]).
nodups([H|T]) :- not(member(H,T)), nodups(T).

/*-Write a Prolog program to remove duplicates from a list. Your queries
should look like removedups([1,3,5,2,5,7,1,9],X) where X will be
instantiated to [3,2,5,7,1,9] and where order of the elements of X does
not matter.*/
removedups([],[]).
removedups([H|T],Return) :- member(H,T), removedups(T,Return).
removedups([H|T], [H|Return]) :- not(member(H,T)), removedups(T,Return).


/*Problem 3:
-Write a Prolog program to solve the 4 by 4 KENKEN puzzle distributed in
class. Hint: Generate needed permutations and test for compliance with
problem constraints. Your query should be:
kenken[X1,X2,X3,X4,X5,X6,X7,X8,X9,X,X11,X12,X13,X14,X15,X16].
-Adapt your solution for the 4 by 4 puzzle to solve the 6 by 6 puzzle.*/
digit(1).
digit(2).
digit(3).
digit(4).

constraintX1([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X1 =:= (2/(X2*X5)).
constraintX2([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X2 =:= (2/(X1*X5)).
constraintX3([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X3 =:= 4.
constraintX4([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X4 =:= (18/(X7*X8)).
constraintX5([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X5 =:= (2/(X1*X2)).
constraintX6([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X6 =:= 4.
constraintX7([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X7 =:= (18/(X4*X8)).
constraintX8([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X8 =:= (18/(X4*X7)).
constraintX9([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X9 =:= (7-X10).
constraintX10([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X10 =:= (7-X9).
constraintX11([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X11 =:= (2*X15).
constraintX12([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X12 =:= (3+X16).
constraintX13([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X13 =:= (6/X14).
constraintX14([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X14 =:= (6/X13).
constraintX15([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X15 =:= (2*X11).
constraintX16([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :- X16 =:= (X12-3).

cage1([X1,X2,X5]) :- X1*X2*X5 =:= 2.
cage2([X3]) :- X3 =:= 4.
cage3([X4,X7,X8]) :- X4*X7*X8 =:= 18.
cage4([X6]) :- X6 =:= 4.
cage5([X9,X10]) :- X9+X10 =:= 7.
cage6([X11,X15]) :- X11/X15 =:= 2.
cage7([X12,X16]) :- abs(X12-X16) =:= 3.
cage8([X13,X14]) :- X13*X14 =:= 6.

solve_puzzle([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :-
	constraintX1([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX2([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX3([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX4([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX5([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX6([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX7([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX8([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX9([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX10([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX11([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX12([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX13([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX14([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX15([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),
	constraintX16([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]),

	cage1([X1,X2,X5]),
	cage2([X3]),
	cage3([X4,X7,X8]),
	cage4([X6]),
	cage5([X9,X10]),
	cage6([X11,X15]),
	cage7([X12,X16]),
	cage8([X13,X14]),

	nodups([X1,X2,X3,X4]),
	nodups([X5,X6,X7,X8]),
	nodups([X9,X10,X11,X12]),
	nodups([X13,X14,X15,X16]),
	nodups([X1,X5,X9,X13]),
	nodups([X2,X6,X10,X14]),
	nodups([X3,X7,X11,X15]),
	nodups([X4,X8,X12,X16]).

%TRY USING PERM (PERMUTATIONS)...LOOKS VERY PROMISING
kenken([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]) :-
	%permutation([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16],[1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4]),

	solve_puzzle([X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16]).