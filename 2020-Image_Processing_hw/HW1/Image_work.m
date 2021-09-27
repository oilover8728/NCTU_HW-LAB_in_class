clear all

%讀取影像
im_road=imread('未戴口罩禁止.png');
im_gray=rgb2gray(im_road);
figure(1)
imshow(im_gray)
title('原始影像');

%產出具有雜訊的圖像
im_noise=imnoise(im_gray,'salt & pepper',0.5);
figure(2)
imshow(im_noise)
title('加入雜訊後的影像');

%均值濾波
fil_size=5;
fil_fun=fspecial('average',fil_size);
im_fill=uint8(filter2(fil_fun,im_noise));
figure(3);
imshow(im_fill)
title('均值濾波後的影像');


