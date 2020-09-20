%% Color Classification
% BLG-477E HW3 Part 2
% Student Name: Tugrul Yatagan
% Student Number: 040100117

%% Initialize
% Images directory
IMAGES_PATH = 'colors';

% All files which includes p letter Ex: .jpg .jpeg .png .bmp
imageDir = dir(fullfile(IMAGES_PATH,'*p*'));
imageNames =  {imageDir.name};

colorPallet = {'WHITE'; 'RED'; 'ORANGE'; 'YELLOW'; 'GREEN'; 'BLUE'; 'VIOLET'};

for k = 1:size(imageNames,2)  
    % Read Input Image
    rgbImage = imread(fullfile(IMAGES_PATH, imageNames{k}));
    hsvImage = rgb2hsv(rgbImage);
       
    colorMap = zeros(7,1);
    for i = 1 : size(hsvImage,1)
        for j = 1 : size(hsvImage,2)
            hue = hsvImage(i,j,1) * 360;
            sat = hsvImage(i,j,2) * 100;
            val = hsvImage(i,j,3) * 100;
            % 1. 0-23 Sat & 77-100 Val   White
            if sat <= 23 && val >= 77
                colorMap(1) = colorMap(1) + 1;
            
            % 2. 0-15 & 340-359   Red
            elseif hue <= 15 || hue >= 340
                colorMap(2) = colorMap(2) + 1;
                
            % 3. 16-40   Orange
            elseif hue >= 16 && hue <= 40
                colorMap(3) = colorMap(3) + 1;
                
            % 4. 46-70   Yellow
            elseif hue >= 43 && hue <= 70
                colorMap(4) = colorMap(4) + 1; 
                
            % 5. 80-163  Green
            elseif hue >= 80 && hue <= 163
                colorMap(5) = colorMap(5) + 1; 
                
            % 6. 194-250 Blue 
            elseif hue >= 194 && hue <= 250
                colorMap(6) = colorMap(6) + 1; 
                
            % 7. 261-285 Violet
            elseif hue >= 261 && hue <= 290
                colorMap(7) = colorMap(7) + 1;
            end
        end
    end
    
    % Calculate color ratios
    N = size(hsvImage,1) * size(hsvImage,2);
    colorRatios =  vec2mat(1:14,7);
    for c = 1: 7
        colorRatios(2,c) = colorMap(c) * 100 / N;
    end
    
    % Sort results
    colorRatios = transpose(sortrows(transpose(colorRatios),-2));
    
    % Print results
    disp(['IMAGE: ', imageNames{k}]);
    for c = 1: 7
        disp(['% ',sprintf('%04.1f', colorRatios(2,c)), ' ', colorPallet{colorRatios(1,c)} ]);
    end
    disp('------------------');
    
    %% Print image
    figure('Name', imageNames{k}), imshow(rgbImage), title([ colorPallet{colorRatios(1,1)}, ' with ratio % ', num2str(colorRatios(2,1))]);
end
