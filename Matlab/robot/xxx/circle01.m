clear all;
%clear classes;


%��ʼ����1#�����߸����ƾ�ֹĿ��
Gx  = 2;              %��������������
Gy  = 1;              %���������������
GWd = 0.04;           %�������ٶ�
GR  = 3;              %�����뾶
Gk  = 0.001;          %����ٶȿ�������
GOx = 3;              %Ŀ��ĺ�����
GOy = 3;              %Ŀ���������  

f1  = Robot01(Gx, Gy, GWd, GR, Gk, GOx, GOy);  % 1#������

%��ʼ����2#�����߸�����1#Ŀ��
x  = 5;              %��������������
y  = 3;              %���������������
Wd = 1;              %�������ٶ�
R  = 1;              %�����뾶
k  = 0.1;            %����ٶȿ�������
Ox = Gx;            %Ŀ��ĺ�����
Oy = Gy;            %Ŀ���������  

f2 = Robot01(x, y, Wd, R, k, Ox, Oy);  % 2#������

%��ʼ����3#�����߸�����1#Ŀ��
x  = 5;              %��������������
y  = 5;              %���������������
Wd = 1;              %�������ٶ�
R  = 1;              %�����뾶
k  = 0.1;            %����ٶȿ�������
Ox = Gx;            %Ŀ��ĺ�����
Oy = Gy;            %Ŀ���������  

f3 = Robot01(x, y, Wd, R, k, Ox, Oy);  % 3#������

%��ʼ����4#�����߸�����1#Ŀ��
x  = 6;              %��������������
y  = 5;              %���������������
Wd = 1;              %�������ٶ�
R  = 1;              %�����뾶
k  = 0.1;            %����ٶȿ�������
Ox = Gx;            %Ŀ��ĺ�����
Oy = Gy;            %Ŀ���������  

f4 = Robot01(x, y, Wd, R, k, Ox, Oy);  % 4#������

%��ʼ����5#�����߸�����1#Ŀ��
x  = 2;              %��������������
y  = 3;              %���������������
Wd = 1;              %�������ٶ�
R  = 1;              %�����뾶
k  = 0.1;            %����ٶȿ�������
Ox = Gx;            %Ŀ��ĺ�����
Oy = Gy;            %Ŀ���������  

f5 = Robot01(x, y, Wd, R, k, Ox, Oy);  % 5#������

t0 = 0.1;
t = t0: t0 :100;                     %�����˵��ƶ�ʱ��

%��ʼ��1#�����ߵ�λ������
X1 = zeros(1,1000);
Y1 = zeros(1,1000);

%��ʼ��2#�����ߵ�λ������
X2 = zeros(1,1000);
Y2 = zeros(1,1000);

%��ʼ��3#�����ߵ�λ������
X3 = zeros(1,1000);
Y3 = zeros(1,1000);

%��ʼ��4#�����ߵ�λ������
X4 = zeros(1,1000);
Y4 = zeros(1,1000);

%��ʼ��5#�����ߵ�λ������
X5 = zeros(1,1000);
Y5 = zeros(1,1000);

%����1#�����ߵ��˶��켣,1#�����߸������˶�Ŀ�꣬��2#������
h1 = animatedline;
h1.Color = 'green';
h1.LineStyle = ':';
h1.LineWidth = 2;

%����2#�����ߵ��˶��켣��2#�����߸����ƾ�ֹĿ��
h2 = animatedline;
h2.Color = 'red';
h2.LineStyle = ':';
h2.LineWidth = 0.5;

%����3#�����ߵ��˶��켣��3#�����߸����ƾ�ֹĿ��
h3 = animatedline;
h3.Color = 'red';
h3.LineStyle = ':';
h3.LineWidth = 0.5;

%����4#�����ߵ��˶��켣��4#�����߸����ƾ�ֹĿ��
h4 = animatedline;
h4.Color = 'red';
h4.LineStyle = ':';
h4.LineWidth = 0.5;

%����5#�����ߵ��˶��켣��5#�����߸����ƾ�ֹĿ��
h5 = animatedline;
h5.Color = 'red';
h5.LineStyle = ':';
h5.LineWidth = 0.5;

%���ø���Ŀ����������
hold on
axis([-2 7 -2 7]);
axis equal;
%��ֹĿ��
C = plot(GOx,GOy,'+');  
C.LineWidth = 2;
%1#������
p1 = plot(Gx,Gy,'o','MarkerFaceColor','green');
%2#������
p2 = plot(x,y,'o','MarkerFaceColor','red');
%3#������
p3 = plot(x,y,'o','MarkerFaceColor','red');
%4#������
p4 = plot(x,y,'o','MarkerFaceColor','red');
%5#������
p5 = plot(x,y,'o','MarkerFaceColor','red');


hold off

for i = 1:2000
%----------------------- 1#�������˶� -----------------------
    Gt(i) = f1.vt * t0;                  %Ŀ����G.vt�������ƶ��ľ���
    Gr(i) = f1.vr * t0;                  %Ŀ����G.vr�������ƶ��ľ���
    
    %���t0��Ŀ���λ��
    dGx = Gt(i) * cos(f1.th) + Gr(i) * sin(f1.th);
    dGy = Gt(i) * sin(f1.th) - Gr(i) * cos(f1.th);
    
    X1(i) = f1.x + dGx;    
    Y1(i) = f1.y + dGy;
    %����Ŀ���λ����Ϣ
    f1.x = X1(i);
    f1.y = Y1(i);
  
%----------------------- 2#�������˶� -----------------------
    %�����˶�Ŀ���ʵʱλ��
    f2.Ox = f1.x;
    f2.Oy = f1.y;

    St(i) = f2.vt * t0;                  %��������ri.vt�������ƶ��ľ���
    Sr(i) = f2.vr * t0;                  %��������ri.vr�������ƶ��ľ���
    %���t0������ߵ�λ��
    dx = St(i) * cos(f2.th) + Sr(i) * sin(f2.th);
    dy = St(i) * sin(f2.th) - Sr(i) * cos(f2.th);
         
    X2(i) = f2.x + dGx + dx;    
    Y2(i) = f2.y + dGy + dy;    
    %���¸����ߵ�λ����Ϣ
    f2.x = X2(i);
    f2.y = Y2(i);
    
    %----------------------- 3#�������˶� -----------------------
    %�����˶�Ŀ���ʵʱλ��
    f3.Ox = f1.x;
    f3.Oy = f1.y;

    St(i) = f3.vt * t0;                  %��������ri.vt�������ƶ��ľ���
    Sr(i) = f3.vr * t0;                  %��������ri.vr�������ƶ��ľ���
    %���t0������ߵ�λ��
    dx = St(i) * cos(f3.th) + Sr(i) * sin(f3.th);
    dy = St(i) * sin(f3.th) - Sr(i) * cos(f3.th);
         
    X3(i) = f3.x + dGx + dx;    
    Y3(i) = f3.y + dGy + dy;    
    %���¸����ߵ�λ����Ϣ
    f3.x = X3(i);
    f3.y = Y3(i);
    
     %----------------------- 4#�������˶� -----------------------
    %�����˶�Ŀ���ʵʱλ��
    f4.Ox = f1.x;
    f4.Oy = f1.y;

    St(i) = f4.vt * t0;                  %��������ri.vt�������ƶ��ľ���
    Sr(i) = f4.vr * t0;                  %��������ri.vr�������ƶ��ľ���
    %���t0������ߵ�λ��
    dx = St(i) * cos(f4.th) + Sr(i) * sin(f4.th);
    dy = St(i) * sin(f4.th) - Sr(i) * cos(f4.th);
         
    X4(i) = f4.x + dGx + dx;    
    Y4(i) = f4.y + dGy + dy;    
    %���¸����ߵ�λ����Ϣ
    f4.x = X4(i);
    f4.y = Y4(i);
    
     %----------------------- 5#�������˶� -----------------------
    %�����˶�Ŀ���ʵʱλ��
    f5.Ox = f1.x;
    f5.Oy = f1.y;

    St(i) = f5.vt * t0;                  %��������ri.vt�������ƶ��ľ���
    Sr(i) = f5.vr * t0;                  %��������ri.vr�������ƶ��ľ���
    %���t0������ߵ�λ��
    dx = St(i) * cos(f5.th) + Sr(i) * sin(f5.th);
    dy = St(i) * sin(f5.th) - Sr(i) * cos(f5.th);
         
    X5(i) = f5.x + dGx + dx;    
    Y5(i) = f5.y + dGy + dy;    
    %���¸����ߵ�λ����Ϣ
    f5.x = X5(i);
    f5.y = Y5(i);
    
    %��������
    addpoints(h1,X1(i),Y1(i));
    addpoints(h2,X2(i),Y2(i));
    addpoints(h3,X3(i),Y3(i));
    addpoints(h4,X4(i),Y4(i));
    addpoints(h5,X5(i),Y5(i));
    
    %���»����˵�ʵʱλ�ã��Ա��������
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
%xlabel('X(m)');ylabel('Y(m)');title('����������Ե�����ֹĿ��İ�Χ����·��');



