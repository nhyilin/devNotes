classdef Robot01 < handle
    properties
        x               %�����˺�����
        y               %������������
        Wd              %�������ٶ�
        R               %�����뾶
        k               %����ٶȿ�������
        Ox              %Ŀ��ĺ�����
        Oy              %Ŀ���������        
    end
    properties(Dependent)
        xo               %��Ŀ��Ϊԭ��ʱ�������˵���Ժ�����
        yo               %��Ŀ��Ϊԭ��ʱ�������˵����������
        vt               %�����˺�Ŀ�������ϣ�ָ��켣���ٶ�
        vr               %�����ٶȣ���ֱ��vt
        r                %�����˵�Ŀ��ľ���
        th               %��������Ŀ��������X��ļн�
        
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
        
        
        %Dependent ���Եļ��㹫ʽҪ����get������
        function xo = get.xo(obj)
            xo = obj.x-obj.Ox;
        end    
        function yo = get.yo(obj)
            yo = obj.y-obj.Oy;
        end  
        function r = get.r(obj)   
            r = sqrt(obj.xo^2 + obj.yo^2);
        end
        %��������ٶ�
        function vt = get.vt(obj)
            vt = -obj.k * (obj.r - obj.R);           %����ٶȺͻ���������֮��ľ�������ȡ�
        end
        %���㻷���ٶ�
        function vr = get.vr(obj)
            vr = obj.R * obj.Wd;
        end
        %��������˵�ǰλ����X��ļн�
        function th = get.th(obj)
            if (obj.xo >= 0)                    %��һ��������
                th = atan(obj.yo / obj.xo);
            else                                %�ڶ���������
                th = pi + atan(obj.yo / obj.xo);
            end
           
        end          
    end
end


