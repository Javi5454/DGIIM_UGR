function[u1]=invmod(a,n)
% invmod Calcula el inverso de a modulo n, si existe, en Z 
[d u v]= bezout(resto(a,n),n);
if (d==1)
	u1=resto(u,n);
elseif (d==-1)
	u1=resto(-u,n);
else
	D=[num2str(a) " no tiene inverso modulo " num2str(n) ];
	disp(D);
end

	
	
	