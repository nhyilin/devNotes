clear all;
%clear classes;


%初始化，1#跟踪者负责环绕静止目标
Gx  = 2;              %机器人起点横坐标
Gy  = 1;              %机器人起点纵坐标
GWd = 0.04;           %期望角速度
GR  = 3;              %期望半径
Gk  = 0.001;          %入轨速度控制因子
GOx = 3;              %目标的横坐标
GOy = 3;              %目标的纵坐标  

f1  = Robot01(Gx, Gy, GWd, GR, Gk, GOx, GOy);  % 1#跟踪者

%初始化，2#跟踪者负责环绕1#目标
x  = 5;              %跟踪者起点横坐标
y  = 3;              %跟踪者起点纵坐标
Wd = 1;              %期望角速度
R  = 1;              %期望半径
k  = 0.1;            %入轨速度控制因子
Ox = Gx;            %目标的横坐标
Oy = Gy;            %目标的纵坐标  

f2 = Robot01(x, y, Wd, R, k, Ox, Oy);  % 2#跟踪者

%初始化，3#跟踪者负责环绕1#目标
x  = 5;              %跟踪者起点横坐标
y  = 5;              %跟踪者起点纵坐标
Wd = 1;              %期望角速度
R  = 1;              %期望半径
k  = 0.1;            %入轨速度控制因子
Ox = Gx;            %目标的横坐标
Oy = Gy;            %目标的纵坐标  

f3 = Robot01(x, y, Wd, R, k, Ox, Oy);  % 3#跟踪者

%初始化，4#跟踪者负责环绕1#目标
x  = 6;              %跟踪者起点横坐标
y  = 5;              %跟踪者起点纵坐标
Wd = 1;              %期望角速度
R  = 1;              %期望半径
k  = 0.1;            %入轨速度控制因子
Ox = Gx;            %目标的横坐标
Oy = Gy;            %目标的纵坐标  

f4 = Robot01(x, y, Wd, R, k, Ox, Oy);  % 4#跟踪者

%初始化，5#跟踪者负责环绕1#目标
x  = 2;              %跟踪者起点横坐标
y  = 3;              %跟踪者起点纵坐标
Wd = 1;              %期望角速度
R  = 1;              %期望半径
k  = 0.1;            %入轨速度控制因子
Ox = Gx;            %目标的横坐标
Oy = Gy;            %目标的纵坐标  

f5 = Robot01(x, y, Wd, R, k, Ox, Oy);  % 5#跟踪者

t0 = 0.1;
t = t0: t0 :100;                     %机器人的移动时间

%初始化1#跟踪者的位置数组
X1 = zeros(1,1000);
Y1 = zeros(1,1000);

%初始化2#跟踪者的位置数组
X2 = zeros(1,1000);
Y2 = zeros(1,1000);

%初始化3#跟踪者的位置数组
X3 = zeros(1,1000);
Y3 = zeros(1,1000);

%初始化4#跟踪者的位置数组
X4 = zeros(1,1000);
Y4 = zeros(1,1000);

%初始化5#跟踪者的位置数组
X5 = zeros(1,1000);
Y5 = zeros(1,1000);

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

%设置3#跟踪者的运动轨迹，3#跟踪者负责环绕静止目标
h3 = animatedline;
h3.Color = 'red';
h3.LineStyle = ':';
h3.LineWidth = 0.5;

%设置4#跟踪者的运动轨迹，4#跟踪者负责环绕静止目标
h4 = animatedline;
h4.Color = 'red';
h4.LineStyle = ':';
h4.LineWidth = 0.5;

%设置5#跟踪者的运动轨迹，5#跟踪者负责环绕静止目标
h5 = animatedline;
h5.Color = 'red';
h5.LineStyle = ':';
h5.LineWidth = 0.5;

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
%3#跟踪者
p3 = plot(x,y,'o','MarkerFaceColor','red');
%4#跟踪者
p4 = plot(x,y,'o','MarkerFaceColor','red');
%5#跟踪者
p5 = plot(x,y,'o','MarkerFaceColor','red');


hold off

for i = 1:2000
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
    
    %----------------------- 3#跟踪者运动 -----------------------
    %更新运动目标的实时位置
    f3.Ox = f1.x;
    f3.Oy = f1.y;

    St(i) = f3.vt * t0;                  %跟踪者在ri.vt方向上移动的距离
    Sr(i) = f3.vr * t0;                  %跟踪者在ri.vr方向上移动的距离
    %求解t0后跟踪者的位置
    dx = St(i) * cos(f3.th) + Sr(i) * sin(f3.th);
    dy = St(i) * sin(f3.th) - Sr(i) * cos(f3.th);
         
    X3(i) = f3.x + dGx + dx;    
    Y3(i) = f3.y + dGy + dy;    
    %更新跟踪者的位置信息
    f3.x = X3(i);
    f3.y = Y3(i);
    
     %----------------------- 4#跟踪者运动 -----------------------
    %更新运动目标的实时位置
    f4.Ox = f1.x;
    f4.Oy = f1.y;

    St(i) = f4.vt * t0;                  %跟踪者在ri.vt方向上移动的距离
    Sr(i) = f4.vr * t0;                  %跟踪者在ri.vr方向上移动的距离
    %求解t0后跟踪者的位置
    dx = St(i) * cos(f4.th) + Sr(i) * sin(f4.th);
    dy = St(i) * sin(f4.th) - Sr(i) * cos(f4.th);
         
    X4(i) = f4.x + dGx + dx;    
    Y4(i) = f4.y + dGy + dy;    
    %更新跟踪者的位置信息
    f4.x = X4(i);
    f4.y = Y4(i);
    
     %----------------------- 5#跟踪者运动 -----------------------
    %更新运动目标的实时位置
    f5.Ox = f1.x;
    f5.Oy = f1.y;

    St(i) = f5.vt * t0;                  %跟踪者在ri.vt方向上移动的距离
    Sr(i) = f5.vr * t0;                  %跟踪者在ri.vr方向上移动的距离
    %求解t0后跟踪者的位置
    dx = St(i) * cos(f5.th) + Sr(i) * sin(f5.th);
    dy = St(i) * sin(f5.th) - Sr(i) * cos(f5.th);
         
    X5(i) = f5.x + dGx + dx;    
    Y5(i) = f5.y + dGy + dy;    
    %更新跟踪者的位置信息
    f5.x = X5(i);
    f5.y = Y5(i);
    
    %动画设置
    addpoints(h1,X1(i),Y1(i));
    addpoints(h2,X2(i),Y2(i));
    addpoints(h3,X3(i),Y3(i));
    addpoints(h4,X4(i),Y4(i));
    addpoints(h5,X5(i),Y5(i));
    
    %更新机器人的实时位置，以便产生动画
    p1.XData = X1(i);
    p1.YData = Y1(i);
    
    p2.XData = X2(i);
    p2.YData = Y2(i);
        
    p3.XData = X3(i);
    p3.YData = Y3(i);
    
    p4.XData = X4(i);
    p4.YData = Y4(i);
    
    p5.XData = X5(i);
    p5.YData = Y5(i);
    
    drawnow
    
end


%plot(Xi,Yi,'-',Xg, Yg, '*',GOx,GOy,'x',x,y,'O',Gx,Gy,'+');
%axis equal;
%grid on
%xlabel('X(m)');ylabel('Y(m)');title('单个智能体对单个静止目标的包围环绕路线');



