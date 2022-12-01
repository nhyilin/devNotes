load C:\Users\Admin\Documents\MATLAB\ver.txt
load C:\Users\Admin\Documents\MATLAB\face.txt
face=face+1;
patch('faces',face,'vertice',ver,'facecolor',[0.4804,0.4804,0.9804]);
view(-10,80);
light('position',[0.1,0.5,5]);
lightangle(90,-90);
lighting gouraud;
