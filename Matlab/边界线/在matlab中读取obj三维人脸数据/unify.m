function varargout = unify(varargin)
%UNIFY M-file for unify.fig
%      UNIFY, by itself, creates a new UNIFY or raises the existing
%      singleton*.
%
%      H = UNIFY returns the handle to a new UNIFY or the handle to
%      the existing singleton*.
%
%      UNIFY('Property','Value',...) creates a new UNIFY using the
%      given property value pairs. Unrecognized properties are passed via
%      varargin to unify_OpeningFcn.  This calling syntax produces a
%      warning when there is an existing singleton*.
%
%      UNIFY('CALLBACK') and UNIFY('CALLBACK',hObject,...) call the
%      local function named CALLBACK in UNIFY.M with the given input
%      arguments.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help unify

% Last Modified by GUIDE v2.5 06-Jun-2011 22:32:44

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @unify_OpeningFcn, ...
                   'gui_OutputFcn',  @unify_OutputFcn, ...
                   'gui_LayoutFcn',  [], ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
   gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before unify is made visible.
function unify_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   unrecognized PropertyName/PropertyValue pairs from the
%            command line (see VARARGIN)

% Choose default command line output for unify
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes unify wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = unify_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbuttonload.
function pushbuttonload_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonload (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% global flag;
[fname,pname]=uigetfile('*.obj','Open Stand Model');%通过uigetfile函数获取文件名和路径
filename=strcat(pname,fname);%获取文件的绝对路径
data=ReadObj_h(filename);
setappdata(gcf,'fname',fname); %setappdata(h,'name',value)
setappdata(gcf,'pname',pname);%当前路径

facecolor = ...
    [0.8,0.8,0.8;
    0.8,0.8,0.8;
    0.8,0.8,0.8;
    0.8,0.8,0.8;
    0.8,0.8,0.8];

axes(handles.axes_model);%获取坐标轴的句柄handles.axes_model

FPnum = 0; %代表第几个特征点的个数。
setappdata(gcf,'FPnum',FPnum);  %给此变量赋值
FPpos=[];
setappdata(gcf,'FPpos',FPpos); 
global faces;
global vertexes;
faces = [];
vertexes = [];
faces=data.faces;
vertexes=data.vertexes;
vertexes=vertexes';%矩阵转置,每一行表示一个点的坐标
faces=faces(1:3,:);
faces=faces';
setappdata(gcf,'vertexes',vertexes);
setappdata(gcf,'faces',faces);


%%
light('Color','w','Position',[0 -1 0],'Style','infinite');hidden off;

trisurf(faces,vertexes(:,1),vertexes(:,2),vertexes(:,3), 'FaceColor', 'yellow', 'EdgeColor', 'none', 'FaceAlpha', 0.99);

hold on;
light('Color','w','Position',[1 -2 1],'Style','infinite');
light('Color','w','Position',[-1  2 -0.5],'Style','infinite');

xlabel('X轴');
ylabel('Y轴');
zlabel('Z轴');
view(0,90);
axis tight;
grid off;
hold on;
title([fname]);
rotate3d on;

% --- Executes on button press in pushbutonselect.
function pushbutonselect_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutonselect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
dcm_obj = datacursormode(handles.figure1); 

set(dcm_obj,'SnapToDataVertex','on','Enable','on','UpdateFcn', @dataCursorText);

function output_text = dataCursorText( handles, event_obj) %子函数
 
 postarget = get(event_obj,'Target')

 pos = get(event_obj, 'Position');%得到离特征点最近的点；
 output_text = pos; 
htable = findobj('Tag','uitablecurrent');%uitableCurrentFP);
set(htable,'data',pos);

% --- Executes on selection change in popupmenunum.
function popupmenunum_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenunum (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenunum contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenunum


% --- Executes during object creation, after setting all properties.
function popupmenunum_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenunum (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



% --- Executes on button press in pushbuttonsfp.
function pushbuttonsfp_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonsfp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
FP_pos =  getappdata(gcf,'FP_pos');
[m,n]=size(FP_pos);
for i=1:m
    for j=1:n
        cent(i,j)=FP_pos(i,j);
    end
end
save('marks','cent')

% --------------------------------------------------------------------
function file_Callback(hObject, eventdata, handles)
% hObject    handle to file (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on mouse press over axes background.
function axes_model_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to axes_model (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbuttoninsert.
function pushbuttoninsert_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttoninsert (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
hmenu = findobj('Tag','popupmenunum');%获取句柄的另一种方法
FPnum = get(hmenu,'value'); %表示 特征点的序号
htable = findobj('Tag','uitablecurrent');
pos = get(htable,'data'); %得到特征点的坐标

plot3(pos(1),pos(2),pos(3),'r.','MarkerFaceColor','r', 'MarkerSize',20 );

text(pos(1)+5,pos(2)+5,pos(3)+5,num2str(FPnum));
pos = [FPnum pos]; %给特征点加上顺序号
disp (pos);
htableFP = findobj('Tag','uitableFP');
FP_pos = getappdata(gcf,'FP_pos');
FP_pos = [FP_pos;pos];
set(htableFP,'data',FP_pos);
setappdata(gcf,'FP_pos',FP_pos);


% --------------------------------------------------------------------
function Untitled_2_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function rotate_on_Callback(hObject, eventdata, handles)
% hObject    handle to rotate_on (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
rotate3d on;

% --------------------------------------------------------------------
function rotate_off_Callback(hObject, eventdata, handles)
% hObject    handle to rotate_off (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
rotate3d off;

% --- Executes on selection change in popupmenu2.
function popupmenu2_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu2


% --- Executes during object creation, after setting all properties.
function popupmenu2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- If Enable == 'on', executes on mouse press in 5 pixel border.
% --- Otherwise, executes on mouse press in 5 pixel border or over pushbutonselect.
function pushbutonselect_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to pushbutonselect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


function output_text = dataCursorText(handles, event_obj) %子函数

 postarget = get(event_obj,'Target')

 pos = get(event_obj, 'Position');%得到离特征点最近的点；

output_text = pos; 
htable = findobj('Tag','uitablecurrent');%uitableCurrentFP);
set(htable,'data',pos);
