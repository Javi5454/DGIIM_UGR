function[h]=primosrelativos(M)
% primosrelativos aplicada a un vector de números da valor 1 sin son primos relativos dos a dos y 0 en caso contrario
[m n]=size(M);
if (m!=1)
	disp("La entrada debe ser un vector de números")	
else
	h=1;
	for i=2:n
		for j=1:(i-1)
			d=euclides(M(i),M(j));
			if abs(d)!=1
			h=0
			end
		end
	end
end