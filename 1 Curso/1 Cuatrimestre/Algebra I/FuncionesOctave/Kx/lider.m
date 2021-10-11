function[c]=lider(a)
[m n]=size(a);
if m!=1
	disp("Revise los datos")
else
	c=reduce(a)(1);
end	