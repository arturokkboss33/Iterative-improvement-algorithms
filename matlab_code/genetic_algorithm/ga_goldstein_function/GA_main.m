%========================================================================%
% Name: Arturo Gomez Chavez
% Email: bosslegend33@gmail.com
% Date: 03/03/2012
%========================================================================%

generation_n = 50;% Number of generations
popuSize = 20; % Population size
xover_rate = 1.0; % Crossover rate
mutate_rate = 0.01; % Mutation rate
bit_n = 16; % Bit number for each input variable
global OPT_METHOD % optimization method.
OPT_METHOD = 'ga';% This is used for display in peaksfcn
limit = 0;
figure;
%blackbg;
obj_fcn = 'Obj_fcn';% Objective function
var_n = 2; % Number of input variables
range = [-2, 2; -2, 2]; % Range of the input variables
% Plot Goldstein and Price function (g_p function)
G_PFunction;
colormap((jet+white)/2);
% Plot contours of g_p function
figure;
%blackbg;
[x, y, z] = G_PFunction;
pcolor(x,y,z); shading interp;
hold on;
contour(x, y, z, 20, 'r');
hold off; colormap((jet)/2);
axis square; xlabel('X'); ylabel('Y');
t=cputime;
% Initial random population
popu = rand(popuSize, bit_n*var_n) > 0.5;
fprintf('Initial population.\n');
for i=1:popuSize
    for j=1:bit_n*var_n
        fprintf('%1.0f ',popu(i,j));
    end
    fprintf('\n');
end
upper = zeros(generation_n, 1);
average = zeros(generation_n, 1);
lower = zeros(generation_n, 1);
% Main loop of GA
i=0;
while(limit <=20)
    %for i = 1:generation_n;
    i=i+1;
    k=i;
    % delete unnecessary objects
    delete(findobj(0, 'tag', 'member'));
    delete(findobj(0, 'tag', 'individual'));
    delete(findobj(0, 'tag', 'count'));
    % Evaluate objective function for each individual
    fcn_value = evalpopu(popu, bit_n, range, obj_fcn);
    if (i==1),
        fprintf('Initial population\n ');
        for j=1:popuSize
            fprintf('f(%f, %f)=%f\n', ...
                bit2num(popu(j, 1:bit_n), range(1,:)), ...
                bit2num(popu(j, bit_n+1:2*bit_n), range(2,:)), ...
                fcn_value(j));
        end
    end
    % Fill objective function matrices
    
    upper(i) = max(fcn_value);
    average(i) = mean(fcn_value);
    lower(i) = min(fcn_value);
    
    if(i>=2)
        if(lower(i)==lower(i-1))
            limit = limit +1;
        else
            limit=0;
        end
    end
    % display current best
    [best, index] = min(fcn_value);
    fprintf('Best of Generation %i: ', i);
    fprintf('f(%f, %f)=%f\n', ...
        bit2num(popu(index, 1:bit_n), range(1,:)), ...
        bit2num(popu(index, bit_n+1:2*bit_n), range(2,:)), ...
        best);
    % generate next population via selection, crossover and mutation
    popu = nextpopu(popu, fcn_value, xover_rate, mutate_rate,k);
    if(mod(i,10)==0)
        fprintf('Population after the %d th generation.\n',i);
        fprintf('Press any key to continue...\n');
        pause;
    end
    %end
end

e=cputime-t;
fprintf('the CPU Time for the whole calculation=%10.5f\n',e);