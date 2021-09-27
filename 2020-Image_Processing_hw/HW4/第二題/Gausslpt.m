I=imread('HW4-woman.tif');
[m,n]=size(I);
Do=0.1*m;
F=fft2(I);

A=im2double(I);
M=size(A,1);   
N=size(A,2);
P=2*M;          
Q=2*N; 
fp=zeros(P,Q);
fp(1:M,1:N)=A(1:M,1:N);

figure,imshow(fp),title('處理後');
F1=fft2(fp,P,Q);

u=0:(P-1);
v=0:(Q-1);
D01=0.05*P;
idx=find(u>P/2);
u(idx)=u(idx)-P;
idy=find(v>Q/2);
v(idy)=v(idy)-Q;
[V,U]=meshgrid(v,u);
H=zeros(P,Q);
D=sqrt(U.^2+V.^2);%%距離矩陣，表示各個像速與圖像中心距離矩陣 

H=exp(-(D.^2)./(2*(Do^2)));%%高斯低通濾波器

Fout=F1.*H;

imshow(log(fftshift(abs(Fout))+1),[]);%显示滤波后图像的频谱图
f=real(ifft2(Fout));
f=uint8(Fout);
%figure,imshow(Fout),title('處理後2');
figure,imshow(ifft2(Fout)),title('處理後3');
Fout2=ifft2(Fout);
fp2=zeros(M,N);
fp2(1:M,1:N)=Fout2(1:M,1:N);
figure,imshow(fp2),title('處理後4');
figure,imshow(I),title('處理前');
