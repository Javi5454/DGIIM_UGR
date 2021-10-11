function[s]=suma(a,b)
% suma suma dos polinomios 
a=reduce(a);
b=reduce(b);
if grado(a)>=grado(b)
	if grado(b)== -1
		s=a;
	else
	b=[zeros(1,grado(a)-grado(b)) b];
	s=a+b ;
	end
else
	s=suma(b,a)	;
end
