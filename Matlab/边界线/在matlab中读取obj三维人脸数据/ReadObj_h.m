function data = ReadObj_h(fileName)
% ʱ�䣺2009.04.23
% ���ߣ������
% �޸ģ�2010.03.27
%      ԭ�����ڽ��������Ƥ���Ľ���Ƥ��ʱ���õİ취�Ƚϱ�����ʵMATLAB���ṩ�˸��õİ취
%      �Ǿ��������������Ƭ�Ļ���Ȼ��������������Ȼ���ĸ��������һ��Ϊ�����
%      ����������ֱ���͵�patch�����оͿ����Զ��������Ǻ��Ľ���Ƭ

% ���룺ģ�͵�OBJ�ļ��ľ����ļ���
% �����һ���ṹ�壬���а�������ÿ�������ĵ����
% ����ǰ�������𣺸���OBJ�ļ��еķ�����Ϣ����ȡ

% fileName = 'I:\HeadModel\ѵ��ѡȡ\����ѡȡ\ѵ������\1.obj';
fid = fopen(fileName);
%fid=fopen('E:\work\1.obj');
%%% �޸���2009.09.02��Ϊ��ʹ�ú���֧��û�з�������ݣ���������gǰ׺�����ݡ�
vertexCount = 0;
faceCount = 0;
partCount = 1;
data(partCount).name = 'Global';
% ���²��������������Ϊ��ʹ���ļ����ܶ�ȡȫ��ģ�ͣ�Ҳ�ɶ�ȡ����ģ��
IsHaveGroupInformation = 0;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
data(1).fname = fileName;
while 1
    [prefix,count] = fscanf(fid,'%s',1);
    switch prefix
        case '#'
            tline = fgetl(fid);
        case 'g'
            partname = fgetl(fid);
            
            if IsHaveGroupInformation == 1
                [prefix,count] = fscanf(fid,'%s',1);
                if prefix == 's'
                    tline = fgetl(fid);
                    partCount = str2num(tline);
%                 else
%                     errordlg('��ȡ�ļ�����','������ʾ');
                end;
                vertexCount = 0;
                faceCount = 0;   
            end
            data(partCount).name = partname;
       
            IsHaveGroupInformation = 1;
         case 'v'
             vertexCount = vertexCount + 1;
             [data(partCount).vertexes(:,vertexCount),count1] = fscanf(fid,'%f',3);
         case 'f'
             faceCount = faceCount + 1;
             i = 1;
             face = zeros(4,1);
             face(4,1) = NaN;
             face(i,1) = fscanf(fid,'%d',1);
             guard = fscanf(fid,'%c',1);
            while guard ~= '\n'
                if guard == ' '
                    i = i + 1;
                    face(i,1) = fscanf(fid,'%d',1);
                   guard = fscanf(fid,'%c',1);
                elseif guard == '/'
                    temp = fscanf(fid,'%d',1);
                   guard = fscanf(fid,'%c',1);
                else
                   break;
                end               
            end
            
            data(partCount).faces(:,faceCount) = face(:,1);
             
        otherwise
            tline = fgetl(fid);
    end
    
    if count == 0
        break;
    end
end
[M,N] = size(data);
count = 0;
for partnum = 1:1:N
    data(partnum).prepartsVcount = count;
    [M2,N2] = size(data(partnum).vertexes);
    
    count = count + N2;
end

fclose(fid);