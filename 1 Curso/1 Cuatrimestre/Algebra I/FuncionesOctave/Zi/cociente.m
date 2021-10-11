function[q]=cociente(a,b)
% cociente extiende la division con resto a Z[i]
if imag(a)== 0 && imag(b)== 0
	q= floor (a/b);
else
	x=round(real(a/b));
	y=round(imag(a/b));
	q = x + y * i	;
end