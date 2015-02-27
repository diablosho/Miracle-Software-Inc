#lang racket
( define g
   (lambda (x y)
     ( if (< x y) (+ x y) (* x y))))
(define quadsolver
  (lambda (a b c)
    (let*
        ([disc(-(* b b) (* 4 a c ))]
      (root1(/(+(- b)(sqrt disc))(* 2 a)))
      (root2(/ (-(- b)(sqrt disc))(* 2 a))))
    (list root1 root2))))

  