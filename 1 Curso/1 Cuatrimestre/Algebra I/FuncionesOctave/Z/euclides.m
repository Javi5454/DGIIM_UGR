function[a]=euclides(a,b)
% euclides calcula el mcd por el algortimo de Euclides en Z 
while b!=0
	r=resto(a,b);
	a=b;
	b=r;
end
