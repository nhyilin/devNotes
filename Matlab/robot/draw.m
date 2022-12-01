% functions draw[Gt]
%     % 4、目标运动算法描述
%     for i = 1:1000000
%     %----------------------- 1#跟踪者运动 -----------------------
%         Gt(i) = f1.vt * t0;                  %目标在G.vt方向上移动的距离
%         Gr(i) = f1.vr * t0;                  %目标在G.vr方向上移动的距离
%         
%         %求解t0后目标的位置
%         dGx = Gt(i) * cos(f1.th) + Gr(i) * sin(f1.th);
%         dGy = Gt(i) * sin(f1.th) - Gr(i) * cos(f1.th);
%         
%         X1(i) = f1.x + dGx;    
%         Y1(i) = f1.y + dGy;
%         %更新目标的位置信息
%         f1.x = X1(i);
%         f1.y = Y1(i);
%       
%     %----------------------- 2#跟踪者运动 -----------------------
%         %更新运动目标的实时位置
%         f2.Ox = f1.x;
%         f2.Oy = f1.y;
%      
%         St(i) = f2.vt * t0;                  %跟踪者在ri.vt方向上移动的距离
%         Sr(i) = f2.vr * t0;                  %跟踪者在ri.vr方向上移动的距离
%         %求解t0后跟踪者的位置
%         dx = St(i) * cos(f2.th) + Sr(i) * sin(f2.th);
%         dy = St(i) * sin(f2.th) - Sr(i) * cos(f2.th);
%              
%         X2(i) = f2.x + dGx + dx;    
%         Y2(i) = f2.y + dGy + dy;    
%         %更新跟踪者的位置信息
%         f2.x = X2(i);
%         f2.y = Y2(i);
%         
%         %动画设置
%         addpoints(h1,X1(i),Y1(i));
%         addpoints(h2,X2(i),Y2(i));
%             
%         p1.XData = X1(i);
%         p1.YData = Y1(i);
%         
%         p2.XData = X2(i);
%         p2.YData = Y2(i);
%         
%         drawnow
%         
%     end