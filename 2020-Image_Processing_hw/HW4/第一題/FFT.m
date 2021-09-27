clc;
clear all;
close all;
img=imread('HW4-woman.tif');
fimg=fft2(img);%作fft變換-abs(Y)可得到幅度譜，angle(Y)可得到相位譜
ffimg=fftshift(fimg);%將零點移動到中心
simg=log(1+abs(ffimg));%對幅值作對數變換，壓縮動態範圍
magg=abs(ffimg);
pahh=angle(ffimg);


figure;
subplot(1,4,1);imshow(img);
title('原圖');
subplot(1,4,2);imshow(simg,[]);
title('幅值');
subplot(1,4,3);imshow(magg,[]);
title('magnitude');
subplot(1,4,4);imshow(pahh,[]);
title('phase');
