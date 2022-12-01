clc,clear

data1=xlsread('/Users/peiyilin/code/Matlab/0624/a.xlsx',1,'D1:D10');
data2=xlsread('/Users/peiyilin/code/Matlab/0624/a.xlsx',1,'G1:G10');
data3=xlsread('/Users/peiyilin/code/Matlab/0624/a.xlsx',1,'D11:D18');
data4=xlsread('/Users/peiyilin/code/Matlab/0624/a.xlsx',1,'G11:G18');

jfg1=rms(data1);
jfg2=rms(data2);
jfg3=rms(data3);
jfg4=rms(data4);
