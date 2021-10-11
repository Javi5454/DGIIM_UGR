function[a]=reduce(a)
[m n]=size(a);
if m!=1
	disp("Revise los datos")
else
	while n!=1
		if a(1)==0
		            a=a(2:n);
		end
		n=n-1;
	end
end	