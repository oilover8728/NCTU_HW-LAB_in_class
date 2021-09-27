 
close all;  
clc;
% 字符识别的应用
A=imread('HW4-woman.tif');  
out1=GLPF(A,50);
figure;
subplot(1,2,1);  imshow(A);  title('低分辨率文本');
subplot(1,2,2);  imshow(out1);  title('Gauss濾波withpadding');

function [image_out] = GLPF(image_in,D0)
%GLPF为高斯低通滤波器，D0为截止频率
%输入为需要进行高斯低通滤波的灰度图像，输出为经过滤波之后的灰度图像
f=image_in;
f=im2double(f);
% 1、给定一副大小为M×N的输入图像f(x,y)，得到填充参数P=2M，Q=2N
M=size(f,1);   N=size(f,2);
P=2*M;          Q=2*N; 
% 2、对输入图像f(x,y)添加必要数量的0,形成大小为P×Q的填充图像fp(x,y)
fp=zeros(P,Q);
fp(1:M,1:N)=f(1:M,1:N);
% 3、用（-1）^(x+y)乘以fp(x,y)移到其变换的中心
for i=1:P
    for j=1:Q
        fp(i,j)=(-1)^(i+j)*double(fp(i,j));
    end
end
% 4、计算来自步骤3的图像的DFT，得到F（u,v）
F=fft2(fp,P,Q);
% 5、生成一个实的、对称的滤波函数H(u,v)，其大小为P×Q，中心在（P/2，Q/2）处。用阵列相乘形成乘积G（u,v）=H(u,v)F(u,v)
H=zeros(P,Q);
a=2*(D0^2);
for u=1:P
    for v=1:Q
        D=(u-P/2)^2+(v-Q/2)^2;
        H(u,v)=exp(-D./a);
    end
end
G=F.*H; %频率域滤波
imshow(log((abs(G))),[]);%显示滤波后图像的频谱图
% 6、得到处理后的图像
gp=ifft2(G); %频域转换到时域图像
gp=real(gp);
for i=1:P
    for j=1:Q
        gp(i,j)=(-1)^(i+j)*double(gp(i,j));
    end
end
% 7、通过从gp(x,y)的左上象限提取M×N区域，得到最终处理结果g(x,y)
image_out=gp(1:M,1:N);  
end