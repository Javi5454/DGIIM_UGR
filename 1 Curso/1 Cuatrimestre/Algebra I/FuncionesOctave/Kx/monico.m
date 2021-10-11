function[b]=monico(a)
[m n]=size(a);
if m!=1
	disp("Revise los datos")
else
	b=(1/lider(a))*reduce(a);
end	