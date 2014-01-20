%========================================================================%
% Name: Arturo Gomez Chavez
% Email: bosslegend33@gmail.com
% Date: 03/03/2012
%========================================================================%

function new_popu = nextpopu(popu, fitness, xover_rate, mut_rate,k)

new_popu = popu;
popu_s = size(popu, 1);
string_leng = size(popu, 2);
% ====== ELITISM: find the best two and keep them
tmp_fitness = fitness;
[junk, index1] = min(tmp_fitness); % find the best
tmp_fitness(index1) = max(tmp_fitness);
[junk, index2] = min(tmp_fitness); % find the second best
new_popu([1 2], :) = popu([index1 index2], :);
% rescaling the fitness
fitness = max(fitness) - fitness;% keep it positive
total = sum(fitness);
if(k==1)
    fprintf('the fitnesses after minus\n');
    for i=1:popu_s
        fprintf('%10.3f \n',fitness(i));
    end
    fprintf('the sum of fitnesses %10.5f\n',total);
end
if total == 0,
    fprintf('=== Warning: converge to a single point ===\n');
    fitness = ones(popu_s, 1)/popu_s;% sum is 1
else
    fitness = fitness/sum(fitness); % sum is 1
end
cum_prob = cumsum(fitness);
if(k==1)
    fprintf('the probability of each chromosome, and the cumulative sum \n');
    for i=1:popu_s
        fprintf('%10.3f %10.3f\n',fitness(i),cum_prob(i));
    end
end
% ====== SELECTION and CROSSOVER
for i = 2:popu_s/2,
    % === Select two parents based on their scaled fitness values
    tmp = find(cum_prob - rand > 0);
    parent1 = popu(tmp(1), :);
    tmp = find(cum_prob - rand > 0);
    parent2 = popu(tmp(1), :);
    % === Do crossover
    if rand < xover_rate,
        % Perform crossover operation
        xover_point = ceil(rand*(string_leng-1));
        new_popu(i*2-1, :) = ...
            [parent1(1:xover_point) parent2(xover_point+1:string_leng)];
        new_popu(i*2, :) = ...
            [parent2(1:xover_point) parent1(xover_point+1:string_leng)];
    end
    if(k==1)
        fprintf('xover_point = %d \n', xover_point);
        fprintf('parent1\n');
        for j=1:string_leng
            fprintf('%d ',parent1(j));
        end
        fprintf('\n');
        fprintf('parent2\n');
        for j=1:string_leng
            fprintf('%d ',parent2(j));
        end
        fprintf('\n');
        fprintf('new_popu1\n');
        for j=1:string_leng
            fprintf('%d ',new_popu(i*2-1,j))
        end
        fprintf('\n');
        fprintf('new_popu2\n');
        for j=1:string_leng
            fprintf('%d ',new_popu(i*2,j))
        end
        fprintf('\n');
        % disp(new_popu(i*2-1, :));
        % disp(new_popu(i*2, :));
    end
    % keyboard;
end
if(k==1)
    fprintf('the result after crossover of the first population\n');
    for i=1:popu_s
        for j=1:string_leng
            fprintf('%d ',new_popu(i,j))
        end
        fprintf('\n');
        fprintf('\n');
    end
end
% ====== MUTATION (elites are not subject to this.)
mask = rand(popu_s, string_leng) < mut_rate;
new_popu = xor(new_popu, mask);
if(k==1)
    fprintf('the result after mutation of the first population\n');
    for i=1:popu_s
        for j=1:string_leng
            fprintf('%d ',new_popu(i,j))
        end
        fprintf('\n');
        fprintf('\n');
    end
end
% restore the elites
new_popu([1 2], :) = popu([index1 index2], :);