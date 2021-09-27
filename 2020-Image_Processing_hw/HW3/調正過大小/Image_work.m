clear all

%讀取影像
im_road=imread('05.jpg');
im_gray=rgb2gray(im_road);
figure(1)
imshow(im_gray)
title('原始影像');


