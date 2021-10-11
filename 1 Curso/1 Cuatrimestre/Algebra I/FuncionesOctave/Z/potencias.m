function[P]=potencias(x,n)
P=[0 ; 1]
b=2
while b!=1
  [a k]=size(P)
  b=resto(P(2,k)*x,n)
  K=[P(1,k)+1 ; b]
  P=[P K];
 end