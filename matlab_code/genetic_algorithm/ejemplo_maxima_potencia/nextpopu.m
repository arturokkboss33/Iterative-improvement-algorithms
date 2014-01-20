%========================================================================%
% Name: Arturo Gomez Chavez
% Email: bosslegend33@gmail.com
% Date: 03/03/2012
%========================================================================%

function new_popu = nextpopu(popu, fitness, xover_rate, mut_rate,k)
new_popu = popu;
popu_s = size(popu, 1);
string_leng = size(popu, 2);
% ====== ELITISMO: Se conservan los mejores 2 individuos
tmp_fitness = fitness;
[a, index1] = max(tmp_fitness); % Encuentra al mejor
tmp_fitness(index1) = min(tmp_fitness);
[a, index2] = max(tmp_fitness); % Encuentra al segundo mejor
new_popu([1 2], :) = popu([index1 index2], :);
% Se reescala la function de ajuste
fitness = fitness - min(fitness);% Positiva
total = sum(fitness);
if(k==1)
fprintf('Funcion de ajuste despues de nueva escala\n');
for i=1:popu_s
fprintf('%10.3f \n',fitness(i));
end
fprintf('La suma de cada ajuste %10.5f\n',total);
end
if total == 0,
fprintf('=== Error ===\n');
fitness = ones(popu_s, 1)/popu_s;% sum is 1
else
fitness = fitness/sum(fitness); % sum is 1
end
cum_prob = cumsum(fitness);
if(k==1)
fprintf('La probabilidad de cada cromosoma, y su prob. acumulada \n');
for i=1:popu_s
fprintf('%10.3f %10.3f\n',fitness(i),cum_prob(i));
end
end
% ====== SELECCI�N Y CRUZAMIENTO
for i = 2:popu_s/2,
% === Se seleccionan dos padres de acuerdo a su nivel de ajuste
tmp = find(cum_prob - rand > 0);
parent1 = popu(tmp(1), :);
tmp = find(cum_prob - rand > 0);
parent2 = popu(tmp(1), :);
% === Se determina si se cruza o no
if rand < xover_rate,
% Operaci�n de cruzamiento
xover_point = ceil(rand*(string_leng-1));
new_popu(i*2-1, :) = ...
[parent1(1:xover_point) parent2(xover_point+1:string_leng)];
new_popu(i*2, :) = ...
[parent2(1:xover_point) parent1(xover_point+1:string_leng)];
end
if(k==1)
fprintf('Punto de cruce = %d \n', xover_point);
fprintf('Padre1\n');
for j=1:string_leng
fprintf('%d ',parent1(j));
end
fprintf('\n');
fprintf('Padre2\n');
for j=1:string_leng
fprintf('%d ',parent2(j));
end
fprintf('\n');
fprintf('Nueva poblaci�n1\n');
for j=1:string_leng
fprintf('%d ',new_popu(i*2-1,j))
end
fprintf('\n');
fprintf(' Nueva poblaci�n2\n');
for j=1:string_leng
fprintf('%d ',new_popu(i*2,j))
end
fprintf('\n');
end
end

if(k==1)
fprintf('El resultado despu�s del cruce de la 1a poblaci�n\n');
for i=1:popu_s
for j=1:string_leng
fprintf('%d ',new_popu(i,j))
end
fprintf('\n');
fprintf('\n');
end
end
% ====== MUTACION (los elites no se mutan)
mask = rand(popu_s, string_leng) < mut_rate;
new_popu = xor(new_popu, mask);
if(k==1)
fprintf('El resultado de la mutacion de la 1a poblaci�n\n');
for i=1:popu_s
for j=1:string_leng
fprintf('%d ',new_popu(i,j))
end
fprintf('\n');
fprintf('\n');
end
end
% Se restaurant los miembros elite
new_popu([1 2], :) = popu([index1 index2], :);