function[k]=grado(a)
[m n]=size(reduce(a));
if m!=1
	disp("Revise los datos")
else
	k=n-1;
	if k==0 && a(1)==0
		k=-1;
	end
end	