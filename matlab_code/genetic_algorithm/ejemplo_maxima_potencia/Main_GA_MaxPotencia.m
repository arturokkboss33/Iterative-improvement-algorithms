%========================================================================%
% Name: Arturo Gomez Chavez
% Email: bosslegend33@gmail.com
% Date: 03/03/2012
%========================================================================%


popuSize = 20; % Poblacion inicial
xover_rate = 1.0; % Tasa de Cruzamiento
mutate_rate = 0.01; % Tasa de mutacion
bit_n = 16; % Numero de bits para cada variable
limit = 0;
global Vth;
global Rth;
global Xth;
%Se pide por los valores de entrada
Vth=input('Valor del voltaje Vth: ');
if isempty(Vth)
    Vth=0;
end
Rth=input('Valor de la resistencia Rth: ');
if isempty(Rth)
    Rth=0;
end
Xth=input('Valor de la impedancia Xth: ');
if isempty(Xth)
    Xth=0;
end

obj_fcn = 'GA_function_MaxPotencia';% Funcion objetivo
var_n = 2; % Numero de variables de entrada
range = [0, Rth; -Xth, Xth]; % Rango de la entradas
% Grafica de la funci�n de potencia
syms RL;
syms XL;
z = (0.5*(Vth^2)*RL)/((Rth+RL)^2+(Xth+XL)^2);
figure;
ezsurf(z,[0,Rth,-Xth,Xth]);
xlabel('Load Resistance'); ylabel('Load Impedance'); title('Potencia');
% Mapa de contornos de la funci�n potencia
figure;
ezcontour(z,[0,2*Rth,-2*Xth,2*Xth]);
hold off;
xlabel('Load Resistance'); ylabel('Load Impedance'); title('Potencia');

% Creaci�n de la poblaci�n inicial
popu = rand(popuSize, bit_n*var_n) > 0.5;

fprintf('Poblacion inicial.\n');
for i=1:popuSize
for j=1:bit_n*var_n
fprintf('%1.0f ',popu(i,j));
end
fprintf('\n');
end

upper = zeros(50, 1); %Creacion de la matriz de mejor individuo

% Loop Principal
i=0;
%Cuando el ind. M�s apto no mejora despu�s de 20 generaciones el GA
%termina
while(limit <=20) 
i=i+1;
k=i;
% Reseteo de variables
delete(findobj(0, 'tag', 'member'));
delete(findobj(0, 'tag', 'count'));
% Evaluaci�n de la funcion para cada miembro de la poblacion
fcn_value = evalpopu(popu, bit_n, range, obj_fcn);
if (i==1),
fprintf('Poblacion inicial\n ');
for j=1:popuSize
fprintf('f(%f, %f)=%f\n', ...
bit2num(popu(j, 1:bit_n), range(1,:)), ...
bit2num(popu(j, bit_n+1:2*bit_n), range(2,:)), ...
fcn_value(j));
end
end

% Llenar la matriz con los mejores individuos 
upper(i) = max(fcn_value);
 
%Registro de si el ind. M�s apto mejora o no
if(i>=2)
    if(upper(i)==upper(i-1))
        limit = limit +1;
    else
        limit=0;
    end
end

% Grafica de los mejores individuos
[best, index] = max(fcn_value);
fprintf('Generacion %i: ', i);
fprintf('f(%f, %f)=%f\n', ...
bit2num(popu(index, 1:bit_n), range(1,:)), ...
bit2num(popu(index, bit_n+1:2*bit_n), range(2,:)), ...
best);
% Creacion de la siguiente poblacion con seleccion, cruce y mutacion
popu = nextpopu(popu, fcn_value, xover_rate, mutate_rate,k);
if(mod(i,10)==0)
fprintf('Poblacion despues de la %d generacion.\n',i);
fprintf('----------------- \n');
%fprintf('Presione cualquier tecla...\n');
%pause;
end
%end
end
[best, index] = max(fcn_value);
fprintf('\nMaxima potencia: %i Watts\n ', best);
fprintf('Cuando: Rth = %f ohms, Xth = %fj ohms\n', ...
bit2num(popu(index, 1:bit_n), range(1,:)), ...
bit2num(popu(index, bit_n+1:2*bit_n), range(2,:)));