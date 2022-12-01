%跟随者对目标进行环绕包围的函数
function FGtrace(Obj)
    xo = Obj.x - Obj.Gx;             %以目标为原点时，机器人的相对横坐标
    yo = Obj.y - Obj.Gy;             %以目标为原点时，机器人的相对纵坐标
    th = atan(yo / xo);            %计算机器人当前位置与X轴的夹角
    r = sqrt(xo^2 + yo^2);         %得到机器人与目标之间的距离
    vt = - Obj.k * (r - Obj.R);       %计算入轨速度
    vr = Obj.R * Obj.Wd;           %计算环绕速度            
            
    St = vt * Obj.to;                  %机器人在vt方向上移动的距离
    Sr = vr * Obj.to;                  %机器人在vr方向上移动的距离
              
    %跟随者的环绕修正,当跟随者的相对位置处于不同象限时，to内的位移方向会发生改变
    if (xo < 0)            %第二、三象限
        th = pi + th;
    end
    
    %计算机器人在时间间隔内，在X和Y方向上的移动距离        
    Obj.Gdx = St * cos(th) + Sr * sin(th);
    Obj.Gdy = St * sin(th) - Sr * cos(th);
end 
