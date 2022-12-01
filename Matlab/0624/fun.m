clc,clear

data=xlsread('C:\Users\Dell\Desktop\001.xlsx');
data1=data(2:XXX,XXXX);
data=data(2:XXX,2:XXXX);
%%
>> fz=max(abs(data),[],2);
>> jz=mean(data,2);
>> pf=mean(abs(data),2);
>> fc=var(data,0,2);
>> jfg=rms(data,2);
>> fgfz=mean(sqrt(abs(data)),2).^2; 
>> zin=min(data,[],2);
>> zax=max(data,[],2);
>> qd=mean(data.^4,2);
>> xd=mean(data.^3,2);
>> ydz=fz./fgfz;
>> bxz=jfg./pf;
>> mcz=fz./jz;
>> fzz=fz./jfg;
>> qdz=qd./(jfg.^4);
>> A=[ydz,bxz,mcz,fzz,qdz,data1];
>> xlswrite('C:\Users\Dell\Desktop\math\003.xlsx',A);

%%