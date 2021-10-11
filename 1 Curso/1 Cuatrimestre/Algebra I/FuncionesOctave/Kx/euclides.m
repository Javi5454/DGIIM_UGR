function[d]=euclides(a,b)
% euclides calcula el mcd por el algortimo de Euclides en K[x]
while grado(b)!=-1 
	r=resto(a,b);
	a=reduce(b);
	b=reduce(r);
end
d=monico(a);
