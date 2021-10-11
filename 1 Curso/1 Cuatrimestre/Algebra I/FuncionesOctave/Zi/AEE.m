function[r1,u,v]=AEE(a,b)
%bezoutT Calcula el mcd y los coeficientes de Bezout mostrando la tabla
% Primero formamos una matriz T 2x4 con los datos de partida:
if norma(a) >= norma(b)
	T=[ 0 a 1 0 ; 0 b 0 1];
else
	T=[ 0 b 0 1 ;  0 a 1 0]; % Si N(a)<N(b) cambiamos las posiciones e intercambiamos los valores de u y v
end
r0=T(1,2);			%Damos valor inicial a r0 (resto antiguo)
r1=T(2,2);			% y r1 (resto nuevo)
while resto(r0 ,r1 )!=0 		% Utilizamos un comando while para que repita la operación hasta que se obtenga resto 0
[m n ]=size(T);
	q=cociente(T(m-1,2),T(m,2));	% Calculamos el cociente usando la función definida para Z[i]
	r1=resto(T(m-1,2),T(m,2));	% Igual con el resto
  u=T(m-1,3) - T(m,3)*q;			% Calculamos el nuevo valor de u
  v=T(m-1,4) - T(m,4)*q;			% y el nuevo valor de v
  r0=T(m,2)	;			% guardamos el valor del resto antiguo para usarlo en el comando while
T=[T ; q  r1  u  v];			%Construimos la nueva tabla: añadiendo como nueva fila los nuevos valores
end
T
