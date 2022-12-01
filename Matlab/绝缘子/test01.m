clc;
clear all;
close all;



x=[0.25:0.125:1.25];
y = -2.056 *x - 1.4869;



plot(0.25,-1.91,'rs','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',5);
hold on;
plot(0.375,-2.26,'rs','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',5);
hold on;
plot(0.5,-2.55,'rs','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',5);
hold on;
plot(0.625,-2.81,'rs','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',5);
hold on;
plot(0.75,-3.07,'rs','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',5);
hold on;
plot(0.875,-3.33,'rs','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',5);
hold on;
plot(1.0,-3.56,'rs','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',5);
hold on;
plot(1.125,-3.78,'rs','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',5);
hold on;
plot(1.25,-3.99,'rs','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',5);
hold on;







 plot(x,y,'blue-o');
xlabel('位移/mm');
ylabel('电压/V');





