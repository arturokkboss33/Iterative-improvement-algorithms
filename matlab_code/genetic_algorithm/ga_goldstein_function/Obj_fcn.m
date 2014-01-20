%========================================================================%
% Name: Arturo Gomez Chavez
% Email: bosslegend33@gmail.com
% Date: 03/03/2012
%========================================================================%

function z = Obj_fcn(input)
%G_Pfunction The Goldstein and price Function.
%G_Pfunction(INPUT) returns the value of the Goldstein and price function 
%at the INPUT.

global OPT_METHOD % optimization method
global PREV_PT % previous data point, used by simplex
x= input(1); y = input(2);
z=(1+(x+y+1)^2*(19-14*x+3*x^2-14*y+6*x*y+3*y^2))...
    *(30+(2*x-3*y)^2*(18-32*x+12*x^2+48*y-36*x*y+27*y^2));

property='Marker';

% Plotting ...
if strcmp(OPT_METHOD, 'ga'), % plot each member; for GA
    line(x, y, property, 'o', 'markersize', 10, ...
        'clipping', 'off', 'erase', 'xor', 'color', 'k', ...
        'tag', 'member', 'linewidth', 2);
else % plot input point for simplex method
    line(x, y, property, '.', 'markersize', 10, ...
        'clipping', 'off', 'erase', 'none', 'color', 'k', ...
        'tag', 'member');
    if ~isempty(PREV_PT),% plotting traj
        line([PREV_PT(1) x], [PREV_PT(2) y], 'linewidth', 1, ...
            'clipping', 'off', 'erase', 'none', ...
            'color', 'k', 'tag', 'traj');
    else % plotting starting point
        % line(x, y, property, 'o', 'markersize', 10, ...
        % 'clipping', 'off', 'erase', 'none', ...
        % 'color', 'w', 'tag', 'member', 'linewidth', 3);
    end
    PREV_PT = [x y];
end
drawnow;