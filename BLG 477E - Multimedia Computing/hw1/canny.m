%% Canny Edge Detection
% Student Name: Tugrul Yatagan
% Student Number: 040100117

%% Initialize
% Choose image
%IMAGE_PATH = 'images/Lenna.png';
%IMAGE_PATH = 'images/house.jpg';
%IMAGE_PATH = 'images/fruit-bowl.jpg';
%IMAGE_PATH = 'images/woman.JPG';
IMAGE_PATH = 'images/cameraman.jpg';

SIGMA = 5;
LOW_THRESHOLD_FACTOR = 0.1;
HIGH_THRESHOLD_FACTOR = 0.25;

%% Read Input Image
inputImage = imread(IMAGE_PATH);
imageSize = size(inputImage);
try
    numberOfColorChannel = imageSize(3);
catch
    numberOfColorChannel = 1;
end

%% Part (1) Convert to Grayscale
% Converts image into grayscale image
if numberOfColorChannel  == 3
    R = inputImage(:, :, 1);
    G = inputImage(:, :, 2);
    B = inputImage(:, :, 3);
    
    grayscaleImage = 0.2989 * R + 0.5870 * G + 0.1140 * B;
    grayscaleImage = uint8(grayscaleImage);
else
    grayscaleImage = inputImage;
end

%% Part (2) Smoothing
% Applies Gaussian filter
gaussianFilter = gaussian(5,SIGMA);
smoothImage = convolution(grayscaleImage, gaussianFilter);

%% Part (3) Finding Gradients
% Finds gradiants and tangent values of images
doubleImage = double(smoothImage);
imageGradient = zeros(size(doubleImage,1),size(doubleImage,2));
imageAngle = zeros(size(doubleImage,1),size(doubleImage,2));

% Sobel kernel
Gy = [1 2 1; 0 0 0; -1 -2 -1];
Gx = [1 0 -1; 2 0 -2; 1 0 -1];

XXX = zeros(size(doubleImage,1),size(doubleImage,2));
YYY = zeros(size(doubleImage,1),size(doubleImage,2));

% Finds X and Y gradiants
for i = 2 : size(doubleImage,1) - 1
    for j = 2 : size(doubleImage,2) - 1
        tempImage = doubleImage(i - 1 : i + 1, j - 1 : j + 1);
        XXX(i,j) = sum(sum(Gx .* tempImage));
        YYY(i,j) = sum(sum(Gy .* tempImage));
    end
end

% Calculates Gradiant magnitude and tangent
for i = 1 : size(doubleImage,1)
    for j = 1 : size(doubleImage,2)
        imageAngle(i,j) = atan2(YYY(i,j),XXX(i,j))*180/pi;
        pixValue = sqrt(XXX(i,j).^2 + YYY(i,j).^2);
        imageGradient(i, j) = pixValue;
    end
end

imageGradient = uint8(imageGradient);

% Makes discreate angle degrees
imageAngleDiscr = zeros(size(inputImage,1),size(inputImage,2));

for i = 1  : size(inputImage,1)
    for j = 1 : size(inputImage,2)
        
        if ((imageAngle(i, j) > 0 ) && (imageAngle(i, j) < 22.5) || (imageAngle(i, j) > 157.5) && (imageAngle(i, j) < -157.5))
            imageAngleDiscr(i, j) = 0;
        end
        
        if ((imageAngle(i, j) > 22.5) && (imageAngle(i, j) < 67.5) || (imageAngle(i, j) < -112.5) && (imageAngle(i, j) > -157.5))
            imageAngleDiscr(i, j) = 45;
        end
        
        if ((imageAngle(i, j) > 67.5 && imageAngle(i, j) < 112.5) || (imageAngle(i, j) < -67.5 && imageAngle(i, j) > 112.5))
            imageAngleDiscr(i, j) = 90;
        end
        
        if ((imageAngle(i, j) > 112.5 && imageAngle(i, j) <= 157.5) || (imageAngle(i, j) < -22.5 && imageAngle(i, j) > -67.5))
            imageAngleDiscr(i, j) = 135;
        end
    end
end

%% Part (4) Non-maximum Suppression
% Non-maximal suppression
supressedImage = uint8(zeros(size(inputImage,1),size(inputImage,2)));
for i = 2  : size(inputImage,1)-1
    for j = 2 : size(inputImage,2)-1
        
        if (imageAngleDiscr(i, j) == 0)
            if (imageGradient(i, j) > imageGradient(i, j - 1) && imageGradient(i, j) > imageGradient(i, j + 1))
                supressedImage(i, j) = imageGradient(i, j);
            else
                supressedImage(i, j) = 0;
            end
        end
        if (imageAngleDiscr(i, j) == 45)
            if (imageGradient(i, j) > imageGradient(i + 1, j - 1) && imageGradient(i, j) > imageGradient(i - 1, j + 1))
                supressedImage(i, j) = imageGradient(i, j);
            else
                supressedImage(i, j) = 0;
            end
        end
        if (imageAngleDiscr(i, j) == 90)
            if (imageGradient(i, j) > imageGradient(i - 1, j) && imageGradient(i, j) > imageGradient(i + 1, j))
                supressedImage(i, j) = imageGradient(i, j);
            else
                supressedImage(i, j) = 0;
            end
        end
        if (imageAngleDiscr(i, j) == 135)
            if (imageGradient(i, j) > imageGradient(i - 1, j - 1) && imageGradient(i, j) > imageGradient(i + 1, j + 1))
                supressedImage(i, j) = imageGradient(i, j);
            else
                supressedImage(i, j) = 0;
            end
        end
        
    end
end

%% Part (5 & 6) Double Thresholding and Edge Tracking by Hysteresis

% Calculates effective trehhold values
ThreshLow = LOW_THRESHOLD_FACTOR * max(max(supressedImage));
ThreshHigh = HIGH_THRESHOLD_FACTOR * max(max(supressedImage));

% Thresholding:
thresholdedImage = zeros(size(inputImage,1), size(inputImage,2));
for i = 1  : size(inputImage,1)
    for j = 1 : size(inputImage,2)
        if (supressedImage(i, j) < ThreshLow)
            thresholdedImage(i, j) = 0;
        elseif (supressedImage(i, j) > ThreshHigh)
            thresholdedImage(i, j) = 1;
        else
            % Edge linening by Hysteresis
            if ((supressedImage(i + 1, j) > ThreshHigh) || (supressedImage(i - 1, j) > ThreshHigh) || (supressedImage(i, j + 1) > ThreshHigh) || (supressedImage(i, j - 1) > ThreshHigh))
                thresholdedImage(i, j) = 1;
            end
        end
    end
end

%% Show output images

%figure(1), imshow(grayscaleImage), title('Grayscale Image');
%figure(2), imshow(smoothImage), title(['Smooth Image with Sigma: ',num2str(SIGMA)]);
%figure(3), imshow(imageGradient), title('Gradient Magnitude') ;
%figure(4), imshow(supressedImage), title('Non-Maximum Suppressed Image');
figure(5), imshow(thresholdedImage), title(['Thresholded and Edge Tracked Image with Sigma: ',num2str(SIGMA) ' Low Threshold: ', num2str(LOW_THRESHOLD_FACTOR), ' High Threshold: ', num2str(HIGH_THRESHOLD_FACTOR)]); 

