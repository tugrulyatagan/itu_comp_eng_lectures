%% BLG 477E HW2 Otsu's Algorithm Segmentation
% Student Name: Tugrul Yatagan
% Student Number: 040100117

%% Initialize
% Choose image
IMAGE_PATH = 'images/lena.jpg';
%IMAGE_PATH = 'images/houses.jpg';
%IMAGE_PATH = 'images/nature.jpg';
%IMAGE_PATH = 'images/otsu1.png';
%IMAGE_PATH = 'images/robot.jpg';


%% Read Input Image
inputImage = imread(IMAGE_PATH);
imageSize = size(inputImage);
try
    numberOfColorChannel = imageSize(3);
catch
    numberOfColorChannel = 1;
end

if numberOfColorChannel  == 3
    redInput = inputImage(:, :, 1);
    greenInput = inputImage(:, :, 2);
    blueInput = inputImage(:, :, 3);
else
    greyInput = inputImage;
end


%% Calculate threshold value with maximum between class variance
% Segmentation with threshold
if numberOfColorChannel  == 3
    redThreshold = findMaxBCVthreshold(redInput);
    redOutput = thresholdSegmentation(redInput, redThreshold);
    
    greenThreshold = findMaxBCVthreshold(greenInput);
    greenOutput = thresholdSegmentation(greenInput, greenThreshold);
    
    blueThreshold = findMaxBCVthreshold(blueInput);
    blueOutput = thresholdSegmentation(blueInput, blueThreshold);
    
    combinedOutput = redOutput & greenOutput & blueOutput;
    
    figure(1), imshow(redOutput), title(['Red channel segmentation with threshold: ',num2str(redThreshold)]);
    figure(2), imshow(greenOutput), title(['Green channel segmentation with threshold: ',num2str(greenThreshold)]);
    figure(3), imshow(blueOutput), title(['Blue channel segmentation with threshold: ',num2str(blueThreshold)]);
    figure(4), imshow(combinedOutput), title('Combined channel segmentation');
else
    greyThreshold = findMaxBCVthreshold(greyInput);
    greyOutput = thresholdSegmentation(greyInput, greyThreshold);
    figure(1), imshow(greyOutput), title(['Grey channel segmentation with threshold: ',num2str(greyThreshold)]);
end
