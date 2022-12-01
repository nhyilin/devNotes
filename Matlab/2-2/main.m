clear;clc;warning off;close all;
[name,path]=uigetfile('*.xlsx');
path=[path,name];
data=xlsread(path);
x=data(:,1);
y=data(:,2);
z=data(:,3);
% scatter3(x,y,z,'filled')
%输入四个点，从记事本复制
data0=[
    139.27325518917715, 137.23916694976367, 599.2318196357929;
210.17629914770285, 123.66976860004905, 608.4292681513318;
223.17375177976893, 123.09375382654365, 530.018318552013;
285.6071623034011, 111.07436689292967, 541.0882648257524
];
X=data0(:,1);
Y=data0(:,2);
Z=data0(:,3);
f=createFit2_2(X, Y, Z);%拟合出平面
%%
%计算投影
A=f.p10;
B=f.p01;
D=f.p00;
C=-1;
t=(A*x+B*y+C*z+D)/(A^2+B^2+C^2);
xi=x-A*t;
yi=y-B*t;
zi=z-C*t;
%%
%画图1
figure;
hold on
[px,py]=meshgrid(linspace(min(xi),max(xi),100),linspace(min(yi),max(yi),100));
pz=f(px,py);
mesh(px,py,pz);
% scatter3(px,py,pz,'filled')
scatter3(x,y,z,'filled')
scatter3(xi,yi,zi,'filled')
xlim([min(pz(:)),max(pz(:))]);
ylim([min(pz(:)),max(pz(:))]);
%%
%把直线转换到xoy面，作基变换
a=[px(1)-px(2);py(1)-py(2);pz(1)-pz(2)];
b=cross(a,[A;B;-1]);
A1=[a,b,[A;B;-1]];
data2=A1\[xi,yi,zi]';
xii=data2(1,:);
yii=data2(2,:);
zii=data2(3,:);
f1=createFitii2_2(xii, yii);%拟合直线，计算斜率
b=yii-f1.p1*xii;%计算截距范围
d=abs(max(b)-min(b))/sqrt(1+(f1.p1)^2);%误差
%%
%画图2
figure;
hold on;
scatter3(data2(1,:),data2(2,:),data2(3,:),'filled')
f1.p2=max(b);
fy=f1(xii);
plot(xii,fy);
f1.p2=min(b);
fy=f1(xii);
plot(xii,fy);