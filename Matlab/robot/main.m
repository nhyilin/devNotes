clear all;
clc
clf

% 定义“机器人”类文件Robot2D_A.m
% 机器人的包围环绕函数FGtrace.m
% 机器人的避障函数ABtrace.m

% 1、初始化，生成跟踪者对象
%初始化，1#跟踪者负责环绕静止目标
Gx  = 2;              %机器人起点横坐标
Gy  = 1;              %机器人起点纵坐标
GWd = 0.04;           %期望角速度
GR  = 3;              %期望半径
Gk  = 1;          %入轨速度控制因子
GOx = 3;              %目标的横坐标
GOy = 3;              %目标的纵坐标  
f1  = Robot2D(Gx, Gy, GWd, GR, Gk, GOx, GOy);  % 1#跟踪者
 
%初始化，2#跟踪者负责环绕1#目标
x  = 5;              %跟踪者起点横坐标
y  = 3;              %跟踪者起点纵坐标
Wd = 3;              %期望角速度
R  = 1;              %期望半径
k  = 0.5;            %入轨速度控制因子
Ox = Gx;            %目标的横坐标
Oy = Gy;            %目标的纵坐标  
f2 = Robot2D(x, y, Wd, R, k, Ox, Oy);  % 2#跟踪者


% 2、初始化跟踪者对象的位置数组
t0 = 0.1;
t = t0: t0 :900;                     %机器人的移动时间
 
%初始化1#跟踪者的位置数组
X1 = zeros(1,1000);
Y1 = zeros(1,1000);
 
%初始化2#跟踪者的位置数组
X2 = zeros(1,1000);
Y2 = zeros(1,1000);


% 3、动画演示及绘图框架初始化

%设置1#跟踪者的运动轨迹,1#跟踪者负责环绕运动目标，即2#跟踪者
h1 = animatedline;
h1.Color = 'green';
h1.LineStyle = ':';
h1.LineWidth = 2;
 
%设置2#跟踪者的运动轨迹，2#跟踪者负责环绕静止目标
h2 = animatedline;
h2.Color = 'red';
h2.LineStyle = ':';
h2.LineWidth = 0.5;
 
%设置各个目标的特征标记
hold on
axis([-2 7 -2 7]);
axis equal;
%静止目标
C = plot(GOx,GOy,'+');  
C.LineWidth = 2;
%1#跟踪者
p1 = plot(Gx,Gy,'o','MarkerFaceColor','green');
%2#跟踪者
p2 = plot(x,y,'o','MarkerFaceColor','red');
hold off


% 4、目标运动算法描述
for i = 1:1000000
%----------------------- 1#跟踪者运动 -----------------------
    Gt(i) = f1.vt * t0;                  %目标在G.vt方向上移动的距离
    Gr(i) = f1.vr * t0;                  %目标在G.vr方向上移动的距离
    
    %求解t0后目标的位置
    dGx = Gt(i) * cos(f1.th) + Gr(i) * sin(f1.th);
    dGy = Gt(i) * sin(f1.th) - Gr(i) * cos(f1.th);
    
    X1(i) = f1.x + dGx;    
    Y1(i) = f1.y + dGy;
    %更新目标的位置信息
    f1.x = X1(i);
    f1.y = Y1(i);
  
%----------------------- 2#跟踪者运动 -----------------------
    %更新运动目标的实时位置
    f2.Ox = f1.x;
    f2.Oy = f1.y;
 
    St(i) = f2.vt * t0;                  %跟踪者在ri.vt方向上移动的距离
    Sr(i) = f2.vr * t0;                  %跟踪者在ri.vr方向上移动的距离
    %求解t0后跟踪者的位置
    dx = St(i) * cos(f2.th) + Sr(i) * sin(f2.th);
    dy = St(i) * sin(f2.th) - Sr(i) * cos(f2.th);
         
    X2(i) = f2.x + dGx + dx;    
    Y2(i) = f2.y + dGy + dy;    
    %更新跟踪者的位置信息
    f2.x = X2(i);
    f2.y = Y2(i);
    
    %动画设置
    addpoints(h1,X1(i),Y1(i));
    addpoints(h2,X2(i),Y2(i));
        
    p1.XData = X1(i);
    p1.YData = Y1(i);
    
    p2.XData = X2(i);
    p2.YData = Y2(i);
    
    drawnow
    
end
