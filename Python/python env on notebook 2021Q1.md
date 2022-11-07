
### History

## 准备安装包

python-3.7.9-amd64.exe

安装Python 3.7.9到 C:\Python\Python37

### 通用环境 NormalEnv

用来做一些临时测试
```
> CD D:\PyEnvs\Normal

> C:\Python\Python37\python.exe -m venv .nmvenv
完成后一定要检查路径名是否正确，一旦错误，就只能重装。
# venv目录最常用的名称是.venv

激活环境
>  .nmvenv\Scripts\activate

修改pip源，换成tsinghua pypi  
pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple  
  
```
### cmake converter

```
安装cmakt-converter
pip install cmake-converter
```


```
pip install vtk-8.1.2-cp37-cp37m-win_amd64.whl
```


===

##### 安装软件

```
安装numpy

pip install numpy
pip install matplotlib
pip install opencv-contrib-python
pip install SimpleITK
pip install pydicom
pip install pynetdicom

pip install vtk-8.1.2-cp37-cp37m-win_amd64.whl


pip install jupyter # 1.0.0

pip install plotly # 4.13

 pip install numpy-quaternion 这个不好用，接口不友好，欧卡角处理不完善。卸载掉。
 
  pip install scipy 这里面的 scioy.spartial. transform .rotation 感觉比较完善。除非需要大量的quaternion 运算，否则，这个够用。
  
  scipy-1.6.2
```

3/31 pip list
```
Package             Version
------------------- -------
argon2-cffi==20.1.0
async-generator==1.10
attrs==20.3.0
backcall==0.2.0
bleach==3.3.0
cffi==1.14.5
cmake-converter==2.1.0
colorama==0.4.4
decorator==4.4.2
defusedxml==0.7.1
entrypoints==0.3
flake8==3.8.4
importlib-metadata==3.7.0
ipykernel==5.5.3
ipython==7.22.0
ipython-genutils==0.2.0
ipywidgets==7.6.3
jedi==0.18.0
Jinja2==2.11.3
jsonschema==3.2.0
jupyter==1.0.0
jupyter-client==6.1.12
jupyter-console==6.4.0
jupyter-core==4.7.1
jupyterlab-pygments==0.1.2
jupyterlab-widgets==1.0.0
lxml==4.6.2
MarkupSafe==1.1.1
mccabe==0.6.1
mistune==0.8.4
nbclient==0.5.3
nbconvert==6.0.7
nbformat==5.1.2
nest-asyncio==1.5.1
notebook==6.3.0
numpy==1.20.1
packaging==20.9
pandocfilters==1.4.3
parso==0.8.2
pickleshare==0.7.5
plotly==4.14.3
prometheus-client==0.9.0
prompt-toolkit==3.0.18
pycodestyle==2.6.0
pycparser==2.20
pyflakes==2.2.0
Pygments==2.8.1
pyparsing==2.4.7
pyrsistent==0.17.3
python-dateutil==2.8.1
pywin32==300
pywinpty==0.5.7
pyzmq==22.0.3
qtconsole==5.0.3
QtPy==1.9.0
retrying==1.3.3
scipy==1.6.2
Send2Trash==1.5.0
six==1.15.0
terminado==0.9.4
testpath==0.4.4
tornado==6.1
traitlets==5.0.5
typing-extensions==3.7.4.3
vtk @ file:///D:/MySetup/OpenSource/Vtk.8/vtk-8.1.2-cp37-cp37m-win_amd64.whl
wcwidth==0.2.5
webencodings==0.5.1
widgetsnbextension==3.5.1
yapf==0.30.0
zipp==3.4.0

```

---


====


===



vtk-8.1.2-cp37-cp37m-win_amd64.whl

#### 国内下载方式
vtk 8 只有 whl可以从pypi中下载，vtk 9才可以pip安装
vtk 8 最高只用 Py 37版本

所以，要换装python 3.7

华为的python镜像  用来下载pyhton安装包
https://repo.huaweicloud.com/python/

pypi索引，可以直接搜索，查找。只是页面和pypi官网不一样，内容一样。
https://mirrors.huaweicloud.com/search/pypi?q=&license=&date=all

可以用来下载一些whl


vtk 8.1.2 whl可以从
https://mirrors.huaweicloud.com/package/pypi?name=vtk 中8.1.2的包列表找到下载


#### 安装

安装Python 3.7.9到 C:\Python\Python37

### 通用环境 NormalEnv

用来做一些临时测试
```
> CD D:\PyEnvs\Normal

> C:\Python\Python37\python.exe -m venv .nmvenv
完成后一定要检查路径名是否正确，一旦错误，就只能重装。
# venv目录最常用的名称是.venv

激活环境
>  .nmvenv\Scripts\activate

修改pip源

> pip config set global.index-url  https://repo.huaweicloud.com/repository/pypi/simple

  结果 Writing to C:\Users\User\AppData\Roaming\pip\pip.ini
 
# 使用华为云pypi安装matplotlib的时候，不知道为什么，依赖库找不到，换成tsinghua pypi  
pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple  
  
```

##### 安装软件

```
安装numpy

pip install numpy
pip install matplotlib
pip install opencv-contrib-python
pip install SimpleITK
pip install pydicom
pip install pynetdicom

pip install vtk-8.1.2-cp37-cp37m-win_amd64.whl
```


安装结果
```
(.nmvenv) D:\PyEnvs\Normal>pip freeze

cycler==0.10.0
kiwisolver==1.3.1
matplotlib==3.3.4
numpy==1.20.1
opencv-contrib-python==4.5.1.48
Pillow==8.1.0
pydicom==2.1.2
pynetdicom==1.5.6
pyparsing==2.4.7
python-dateutil==2.8.1
SimpleITK==2.0.2
six==1.15.0
vtk @ file:///D:/PyEnvs/Normal/vtk-8.1.2-cp37-cp37m-win_amd64.whl
```

##### 安装python lint
根据以前经验，flake8 、 yapf比较好用

```
pip install flake8
pip install yapf
```
修改vs code settings, 指定
python.linting.flake8Enabled = True
python.linting.pylintEnabled = True
python.formatting.provider 使用 yapf


## Others

#### windows terminal
Windows 10G 无法直接使用 microsoft store，所以，从github下载Windows Terminal
https://github.com/microsoft/terminal/releases

安装
```
Add-AppxPackage '.\Microsoft.WindowsTerminalPreview_1.6.10412.0_8wekyb3d8bbwe.msixbundle'
``` 
安装失败，根据windows terminal readme的说明 **Windows Terminal requires Windows 10 1903 (build 18362) or later**

在windows 10G 上无法安装 windows terminal

#### reinstall pip

https://pip.pypa.io/en/stable/installing/

参考页面链接，下载get-pip.py
运行
```
d:\pyenvs\normal\.nmvenv\scripts\python.exe get-pip.py
```

#### 记录
vtk 9可以直接用pip安装

#### requirements.txt
pip freeze会把安装的依赖包都列出来，但是pipreqs搜索指定路径，只列出import的包
```
pipreqs .\ --encoding utf8 --force

pipreqs some_path --encoding utf8 --force --debug --ignore .normal-venv
```
--force 强制覆盖文件
--debug 输出调试信息
--ignore 忽略目录

##### opencv python

pip只有非官方包

https://github.com/opencv/opencv-python

有4个不同包，常规首选
pip install opencv-contrib-python


#### 华为云pypi

华为的python镜像  用来下载pyhton安装包
https://repo.huaweicloud.com/python/

pypi索引，可以直接搜索，查找。只是页面和pypi官网不一样，内容一样。
https://mirrors.huaweicloud.com/search/pypi?q=&license=&date=all

可以用来下载一些whl


vtk 8.1.2 whl可以从
https://mirrors.huaweicloud.com/package/pypi?name=vtk 中8.1.2的包列表找到下载

完整的国内源配置参数，参考tuna或者huaweicloud的官方说明


-----------------------------


=================================

