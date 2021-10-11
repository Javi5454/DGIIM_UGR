function[a]=euclides(a,b)
% euclides calcula el mcd por el algortimo de Euclides, sin los coeficientes de Bezout en Z y Z[i]
while b!=0
	r=resto(a,b);
	a=b;
	b=r;
end
