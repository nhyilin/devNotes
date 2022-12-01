classdef Robot01 < handle
    properties
        x               %机器人横坐标
        y               %机器人纵坐标
        Wd              %期望角速度
        R               %期望半径
        k               %入轨速度控制因子
        Ox              %目标的横坐标
        Oy              %目标的纵坐标        
    end
    properties(Dependent)
        xo               %以目标为原点时，机器人的相对横坐标
        yo               %以目标为原点时，机器人的相对纵坐标
        vt               %机器人和目标连线上，指向轨迹的速度
        vr               %环绕速度，垂直于vt
        r                %机器人到目标的距离
        th               %机器人与目标连线与X轴的夹角
        
    end
    
    methods
        function obj = Robot01(x0, y0, Wd0, R0, k0, Ox0, Oy0)
            obj.x = x0;
            obj.y = y0;
            obj.Wd = Wd0;
            obj.R = R0;
            obj.k = k0;
            obj.Ox = Ox0;
            obj.Oy = Oy0;
            
        end
        
        
        %Dependent 属性的计算公式要放在get方法中
        function xo = get.xo(obj)
            xo = obj.x-obj.Ox;
        end    
        function yo = get.yo(obj)
            yo = obj.y-obj.Oy;
        end  
        function r = get.r(obj)   
            r = sqrt(obj.xo^2 + obj.yo^2);
        end
        %计算入轨速度
        function vt = get.vt(obj)
            vt = -obj.k * (obj.r - obj.R);           %入轨速度和机器人与轨道之间的距离成正比。
        end
        %计算环绕速度
        function vr = get.vr(obj)
            vr = obj.R * obj.Wd;
        end
        %计算机器人当前位置与X轴的夹角
        function th = get.th(obj)
            if (obj.xo >= 0)                    %第一、四象限
                th = atan(obj.yo / obj.xo);
            else                                %第二、三象限
                th = pi + atan(obj.yo / obj.xo);
            end
           
        end          
    end
end


