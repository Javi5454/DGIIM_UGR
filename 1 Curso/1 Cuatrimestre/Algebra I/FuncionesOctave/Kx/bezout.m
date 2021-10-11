function[d,u,v]=bezout(a,b)
%bezout Calcula el mcd y los coeficientes de Bezout en K[x]
if grado(a) >= grado(b)
u0=1;
v0=0;
u1=0;
v1=1;
	while grado(b)!=-1 
	r=resto(a,b);
	tu=u1;
	u1=suma(u0,  -conv(u1,cociente(a,b)) );
	u0=tu;
	tv=v1;
	v1=suma(v0,  -conv(v1,cociente(a,b)));
	v0=tv;
	a=reduce(b);
	b=reduce(r);
	end
	d=monico(a);
	u=(1/lider(a))*u0;
	v=(1/lider(a))*v0;
else	
[d v u]=bezout(b,a);
end		