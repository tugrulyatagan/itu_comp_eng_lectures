%% Counting Birds
% BLG-477E HW3 Part 1
% Student Name: Tugrul Yatagan
% Student Number: 040100117

%% Initialize
% Images directory
IMAGES_PATH = 'bird images';

imageDir = dir(fullfile(IMAGES_PATH,'*p*'));
imageNames =  {imageDir.name};

for i = 1:size(imageNames,2)  
    %% Read Input Image
    inputImage = imread(fullfile(IMAGES_PATH, imageNames{i}));
    
    %% Convert to grayscale
    grayImage = rgb2gray(inputImage);

    %% Calculate Otsu threshold
    segmentationThreshold = graythresh(grayImage);

    %% Threshold segmentatiton
    segmentedImage = im2bw(grayImage,segmentationThreshold);

    %% Smooth image with Gaussian Filter
    gaussianFilter = fspecial('gaussian',[6 6], 6);
    smoothImage = imfilter(segmentedImage, gaussianFilter, 'replicate');
    
    %% Morphologically close image with disk morphological structuring element
    structuringElement = strel('disk', 1);
    structedImage = imclose(smoothImage, structuringElement);
    
    %% Inverse image
    invertedImage = imcomplement(structedImage);

    %% Calculate connected components
    connectedComponents = bwconncomp(invertedImage, 4);
    birdNumber = connectedComponents.NumObjects;

    %% Print image
    figure(i), imshow(invertedImage), title(['Bird number: ', num2str(birdNumber)]);

end