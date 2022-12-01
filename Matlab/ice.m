clear,clc;close all;
m=19.96;
g=9.8;
MU=[];
V=[];
THATA=[];
syms theta
for mu=0.05:0.01:0.1
    for v=1.8:0.1:3.2
        for Theta=-0.06*pi:0.2:0.06*pi
            yita=rand(1);
            F=-(1/pi)*mu*m*g*int((cos(theta+atan(v*sin(theta)/(yita*(v+v*cos(theta))))))-cos(theta-atan(v*sin(theta)/(yita*(v-v*cos(theta))))),'theta',0,pi/2);
            F=double(F);
            t=m*v/(cos(Theta)*F);
            vx=v*t*sin(Theta);
            vy=v*t*cos(Theta);
            if (vy-28.3)^2+vx^2<=0.915^2
                MU=[MU;mu];
                V=[V;v];
                THATA=[THATA;Theta];
            end
        end
    end
end


t=-1:0.03:1;
[x,y]=meshgrid(t,t);
z=y.*(y-1)./(x.*(x-1));
surf(x,y,z)
set(gcf,'unit','normalized','position',[0,0,1,1]);
view(25,14)