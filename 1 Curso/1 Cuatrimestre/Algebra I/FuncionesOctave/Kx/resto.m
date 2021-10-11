function[r]=resto(a,b)
% resto calcula la division con resto en R[x]
[ma na]=size(a);
[mb nb]=size(b);
if ma!=1 || mb!=1
	disp("revise los datos")
else
	[q r]=deconv(reduce(a),reduce(b));
	r=reduce(r);
end
