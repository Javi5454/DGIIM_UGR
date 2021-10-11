function[u1]=invmod(a,n)
% invmod Calcula el inverso de a modulo n, si existe, en Z y Z[i]
[d u v]= bezout(a,n);
if (d==1)
	u1=resto(u,n);
	elseif (d==-1)
		u1=resto(-u,n);
	elseif (d==i)
		u1=resto(-u*i,n);
	elseif (d==-i)
		u1=resto(u*i,n);
	else
	D=[num2str(a) " no tiene inverso modulo " num2str(n) ];
	disp(D);
end

	
	
	