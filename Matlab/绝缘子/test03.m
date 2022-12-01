%双边滤波
clc;
clear all;
close all;
Image_pri = imread('003.jpg');
a=imread('003.jpg');
Image_normalized = im2double(Image_pri);
w = 5;      %窗口大小
sigma = [3 0.1];    %方差
Image_bf = bfilter2(Image_normalized,w,sigma);
Image_bfOut = uint8(Image_bf*255);
figure(1);


imshow(Image_bfOut); 