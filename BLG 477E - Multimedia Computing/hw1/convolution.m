function [ result ] = convolution(input , kernel )
%CONVOLUTION Summary of this function goes here
%   Detailed explanation goes here
[row, col] = size(input);
[m, n] = size(kernel);
h = rot90(kernel, 2);
center = floor((size(h)+1)/2);
left = center(2) - 1;
right = n - center(2);
top = center(1) - 1;
bottom = m - center(1);
Rep = zeros(row + top + bottom, col + left + right);
for x = 1 + top : row + top
    for y = 1 + left : col + left
        Rep(x,y) = input(x - top, y - left);
    end
end
result = zeros(row , col);
for x = 1 : row
    for y = 1 : col
        for i = 1 : m
            for j = 1 : n
                q = x - 1;
                w = y -1;
                result(x, y) = result(x, y) + (Rep(i + q, j + w) * h(i, j));
            end
        end
    end
end

result = uint8(result);

end