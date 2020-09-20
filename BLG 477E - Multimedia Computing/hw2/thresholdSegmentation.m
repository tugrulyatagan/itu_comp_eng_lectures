function [ outputImage ] = thresholdSegmentation( inputImage, segmentationThreshold )
%% Segmentation with threshold

imageSize = size(inputImage);
outputImage = zeros(imageSize);
for i = 1  : imageSize(1)
    for j = 1 : imageSize(2)
        if (inputImage(i,j) > segmentationThreshold)
            outputImage(i,j) = 1; 
        end
    end
end

end

