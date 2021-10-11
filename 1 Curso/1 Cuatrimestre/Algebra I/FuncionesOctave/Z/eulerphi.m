function[r]=eulerphi(n)
F=factor(n);
[a k]=size(F);
r=n;
a=1;
for i=1:k ;
if F(i) !=a ;
  r=r*(1-1/F(i)) ;
  a=F(i) ;
end
end
