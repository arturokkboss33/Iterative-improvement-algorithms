%========================================================================%
% Name: Arturo Gomez Chavez
% Email: bosslegend33@gmail.com
% Date: 03/03/2012
%========================================================================%

function [xz,y,z] = G_PFunction(arg1,arg2);
if nargin == 0
    dx = 1/8;
    [x,y] = meshgrid(-2:dx:2);
elseif nargin == 1
    if length(arg1) == 1
        [x,y] = meshgrid(-2:4/(arg1-1):2);
    else
        [x,y] = meshgrid(arg1,arg1);
    end
else
    x = arg1; y = arg2;
end
z=(1+(x+y+1).^2.*(19-14*x+3*x.^2-14*y+6*x.*y+3*y.^2)).*...
    (30+(2*x-3*y).^2.*(18-32*x+12*x.^2+48*y-36*x.*y+27*y.^2));
if nargout > 1
    xz = x;
elseif nargout == 1
    xz = z;
else
    % Self demonstration
    disp(' ')
    disp(' z=(1+(x+y+1).^2.*(19-14*x+3*x.^2-14*y+6*x.*y+3*y.^2)).*... ')
    disp(' (30+(2*x-3*y).^2.*(18-32*x+12*x.^2+48*y-36*x.*y+27*y.^2)) ')
    surf(x,y,z)
    axis([min(min(x)) max(max(x)) min(min(y)) max(max(y)) ...
        min(min(z)) max(max(z))])
    xlabel('x'), ylabel('y'), title('G-P Function')
end