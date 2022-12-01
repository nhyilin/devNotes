%只有障碍物作用下的跟随者避障轨迹
%该函数只有距离限制，没有角度限制
function ABtrace(Obj)
    xo = Obj.x - Obj.Bx;           %以障碍物为原点时，机器人的相对横坐标
    yo = Obj.y - Obj.By;           %以障碍物为原点时，机器人的相对纵坐标
    th = atan(yo / xo);            %计算机器人当前位置与X轴的夹角
    r = sqrt(xo^2 + yo^2);         %得到机器人与障碍物之间的距离
            
    %跟随者的方向修正,当跟随者的相对位置处于不同象限时，to内的位移方向会发生改变
    if (xo < 0)            %第二、三象限
        th = pi + th;
    end
            
    if r <= Obj.Rb
        vb = Obj.kb / r^2;            %障碍物产生的斥力
        Obj.Bdx = vb * Obj.to * cos(th);
        Obj.Bdy = vb * Obj.to * sin(th);
    else
        Obj.Bdx = 0;
        Obj.Bdy = 0;
    end            
end  
