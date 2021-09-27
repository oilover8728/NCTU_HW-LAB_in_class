% program L5_1.m: histogram equalization% 
	%image_1: original image, image_2: histoeq image%
	image_1=imread('L5_1.bmp');  % read image
	image_2=histeq(image_1);     % do histogram qualization
	imshow(image_1)              % show original image
	figure,imshow(image_2)       % show processed image
	figure,imhist(image_1)       % show the histogram of original image
	figure,imhist(image_2)      % show the histogram of processed image
