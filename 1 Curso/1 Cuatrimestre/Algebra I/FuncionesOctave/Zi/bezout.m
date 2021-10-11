function[a,u0,v0]=bezout(a,b)
h=0;
if norma(a) < norma(b)
	t=a;
	a=b;
	b=t;
	h=1;
end	
u0=1;
v0=0;
u1=0;
v1=1;
while b!=0
	r=resto(a,b);
	tu=u1;
	u1=u0 - u1*cociente(a,b);
	u0=tu;
	tv=v1;
	v1=v0 - v1*cociente(a,b);
	v0=tv;
	a=b;
	b=r;
end
if h==1
	t=u0;
	u0=v0;
	v0=t;
end	