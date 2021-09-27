I=imread('HW4-woman.tif');
[m,n]=size(I);
Do=0.1*m;
F=fft2(I);

u=0:(m-1);
v=0:(n-1);
idx=find(u>m/2);
u(idx)=u(idx)-m;
idy=find(v>n/2);
v(idy)=v(idy)-n;
[V,U]=meshgrid(v,u);
D=sqrt(U.^2+V.^2);%%距离矩阵，表示各个像素与图像中心距离的矩阵

H=exp(-(D.^2)./(2*(Do^2)));%%高斯低通滤波器guassian high-path filter

Fout=F.*H;

imshow(log(fftshift(abs(Fout))+1),[]);%显示滤波后图像的频谱图
f=real(ifft2(Fout));
f=uint8(f);
figure,imshow(f),title('處理後');
figure,imshow(I),title('處理前');
