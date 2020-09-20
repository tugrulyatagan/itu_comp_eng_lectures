function [ gaussianFilter ] = gaussian( size, sigma )
%GAUSSIAN Summary of this function goes here
%   Detailed explanation goes here

[x y]=meshgrid(round(-size/2):round(size/2), round(-size/2):round(size/2));
gaussianFilter=exp(-x.^2/(2*sigma^2)-y.^2/(2*sigma^2));
gaussianFilter=gaussianFilter./sum(gaussianFilter(:));
 
end

