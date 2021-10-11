function[q]=cociente(a,b)
% cociente calcula la division con resto en K[x]
[ma na]=size(a);
[mb nb]=size(b);
if ma!=1 || mb!=1
	disp("revise los datos")
else
	[q r]=deconv(reduce(a),reduce(b));
	q=reduce(q);
end