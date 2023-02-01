clc;
clear;

% 第一类数据
% 均值
mu1 = [-2 -2];
% 协方差
S1 = [0.5 0; 0 0.5];
% 产生高斯分布数据
% RNG = [2 9 3931 9];
data1 = csvread('result.csv',1,9); 

% data1 = mvnrnd(mu1, S1, 100);

% % 第二类数据
% mu2 = [2 -2];
% S2 = [0.5 0; 0 0.5];
% data2 = mvnrnd(mu2, S2, 100);
% 
% % 第三类数据
% mu3 = [-2 2];
% S3 = [0.5 0; 0 0.5];
% data3 = mvnrnd(mu3, S3, 100);
% 
% % 第四类数据
% mu4 = [2 2];
% S4 = [0.5 0; 0 0.5];
% data4 = mvnrnd(mu4, S4, 100);


% 显示数据
figure();
hold on;
plot(data1(:,1), data1(:,2), '+');
% plot(data2(:,1), data2(:,2), 'r+');
% plot(data3(:,1), data3(:,2), 'g+');
% plot(data4(:,1), data4(:,2), 'b+');
grid on;


% data = [data1; data2; data3; data4];
data = data1;
% 数据聚类
[idx, ctr] = k_means(data, 1, 1000);
[m, n] = size(idx);

% 显示聚类后的结果
figure();
hold on;
for i=1:m
    if idx(i, 3) == 1
        plot(idx(i, 1), idx(i, 2), 'r.', 'MarkerSize', 12); 
    elseif idx(i, 3) == 2
        plot(idx(i, 1), idx(i, 2), 'b.', 'MarkerSize', 12);
    elseif idx(i, 3) == 3
        plot(idx(i, 1), idx(i, 2), 'g.', 'MarkerSize', 12);
    else
        plot(idx(i, 1), idx(i, 2), 'y.', 'MarkerSize', 12);
    end
end
grid on;

% 绘出聚类中心点，kx表示是交叉符
plot(ctr(:,1), ctr(:,2), 'kx', 'MarkerSize', 12, 'LineWidth', 2);

