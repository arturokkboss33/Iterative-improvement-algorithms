%========================================================================%
% Name: Arturo Gomez Chavez
% Email: bosslegend33@gmail.com
% Date: 03/03/2012
%========================================================================%

function out = evaleach(string, bit_n, range, obj_fcn)
% EVALEACH Evaluaci�n de cada individuo.
% string: cadena de bits que representan un individuo.

var_n = length(string)/bit_n;
input = zeros(1, var_n);
%Ciclo para convertir cada indiviudo de bits a decimal
for i = 1:var_n,
input(i) = bit2num(string((i-1)*bit_n+1:i*bit_n), range(i, :));
end
out = feval(obj_fcn, input);%Regresa el valor de salida