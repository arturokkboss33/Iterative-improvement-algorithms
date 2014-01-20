%========================================================================%
% Name: Arturo Gomez Chavez
% Email: bosslegend33@gmail.com
% Date: 03/03/2012
%========================================================================%

function z = GA_function_MaxPotencia(input)
%Regresa el valor de la funcion de acuerdo al input.

global PREV_PT % Salida de la funcion anterior
global Vth;
global Rth;
global Xth;
RL= input(1); XL = input(2);
z = (0.5*(Vth^2)*RL)/((Rth+RL)^2+(Xth+XL)^2);
% Grafica de la funcion potencia
property='Marker';
line(RL, XL, property, 'o', 'markersize', 10, ...
'clipping', 'off', 'erase', 'xor', 'color', 'k', ...
'tag', 'member', 'linewidth', 2);

if ~isempty(PREV_PT),% Actualiza la grafica
line([PREV_PT(1) RL], [PREV_PT(2) XL], 'linewidth', 1, ...
'clipping', 'off', 'erase', 'none', ...
'color', 'w', 'tag', 'traj');
end

PREV_PT = [RL XL];
drawnow;