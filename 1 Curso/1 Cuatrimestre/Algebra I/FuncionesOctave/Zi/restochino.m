function[]=restochino(A,M)
% restochino usa el algoritmo chino del resto, si es posible, para resolver el sistema
% de ecuaciones en congruencias x cong a_i (mod m_i) en Z y Z[i]
[m n]=size(A);
[m2 n2]=size(M);
if (m!=1 || m2!=1 || n!=n2)
	disp("Revise los datos, no son correctos")	
elseif primosrelativos(M)==0
		disp("Los módulos no son primos relativos")
else
	MOD=prod(M);
	S=0;
		for i=1:n
		C=invmod(MOD/M(i),M(i))*MOD/M(i);
		S=S+A(i)*C;
		end
	x0=resto(S,MOD) ;
	X=["x=(" num2str(x0)  ")+("  num2str(MOD) ")t"];
	S=[];
	for k=1:n
	S=[S ; "x ≡ "  num2str(A(k))  " (mod " num2str(M(k))  ")"];
	end
	disp("La solucion general del sistema : ")
	disp(S)
	disp("es:")
	disp(X)		
end

