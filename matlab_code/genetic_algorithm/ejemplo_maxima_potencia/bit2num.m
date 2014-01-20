%========================================================================%
% Name: Arturo Gomez Chavez
% Email: bosslegend33@gmail.com
% Date: 03/03/2012
%========================================================================%

function num = bit2num(bit, range)
% BIT2NUM Conversión de cadena de bits a número decimal.
integer = polyval(bit, 2);
num = integer*((range(2)-range(1))/(2^length(bit)-1)) + range(1);
