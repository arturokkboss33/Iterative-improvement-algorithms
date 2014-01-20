%========================================================================%
% Name: Arturo Gomez Chavez
% Email: bosslegend33@gmail.com
% Date: 03/03/2012
%========================================================================%

function fitness = evalpopu(popu, bit_n, range, obj_fcn)
%EVALPOPU Evaluaci�n de ajuste de la poblaci�n.

global count %Contador global de individuos
pop_n = size(popu, 1);
fitness = zeros(pop_n, 1);
%Evaluaci�n miembro por miembro
for count = 1:pop_n,
fitness(count) = evaleach(popu(count, :), bit_n, range, obj_fcn);
end