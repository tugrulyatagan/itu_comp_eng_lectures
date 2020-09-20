function [ segmentationThreshold ] = findMaxBCVthreshold( inputImage )
%% This funciton returns segmentation threshold value
% Calculates threshold value with maximum between class variance

%% Calculate N
imageSize = size(inputImage);
N = imageSize(1) * imageSize(2);

%% Calculate Histogram
h = zeros(255,1);
for i = 1  : imageSize(1)
    for j = 1 : imageSize(2)
        h(inputImage(i,j)+1) = h(inputImage(i,j)+1) + 1;
    end
end

%% Calculate Probability Distribution
P = zeros(255,1);
for i = 1 : 255
    P(i) = h(i) / N;
end

%% Calculate w1(t) and w2(t)
w1 = zeros(255,1);
w2 = zeros(255,1);
for t = 1 : 255
    for i = 1 : t
        w1(t) = w1(t) + P(i);
    end
    
    w2(t) = 1 - w1(t);  
end

%% Calculate u1(t) and u2(t)
u1 = zeros(255,1);
u2 = zeros(255,1);
for t = 1 : 255
    for i = 1 : t
        u1(t) = u1(t) + (i * P(i)) / w1(t);
    end
    
    for i = t + 1 : 255
        u2(t) = u2(t) + (i * P(i)) / w2(t);
    end   
end

%% find t which gives maximum Between Class Variance
maxBetweenClassVariance = 0;
segmentationThreshold = 0;
for t = 1 : 255
    betweenClassVariance = w1(t) * w2(t) * ((u1(t) - u2(t)) ^ 2);
    if (betweenClassVariance > maxBetweenClassVariance)
        maxBetweenClassVariance = betweenClassVariance;
        segmentationThreshold = t;
    end
end

end

