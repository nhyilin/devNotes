
<style type="text/css">
    h1 { counter-reset: h2counter; }
    h2 { counter-reset: h3counter; }
    h3 { counter-reset: h4counter; }
    h4 { counter-reset: h5counter; }
    h5 { counter-reset: h6counter; }
    h6 { }
    h2:before {
      counter-increment: h2counter;
      content: counter(h2counter) ".\0000a0\0000a0";
    }
    h3:before {
      counter-increment: h3counter;
      content: counter(h2counter) "."
                counter(h3counter) ".\0000a0\0000a0";
    }
    h4:before {
      counter-increment: h4counter;
      content: counter(h2counter) "."
                counter(h3counter) "."
                counter(h4counter) ".\0000a0\0000a0";
    }
    h5:before {
      counter-increment: h5counter;
      content: counter(h2counter) "."
                counter(h3counter) "."
                counter(h4counter) "."
                counter(h5counter) ".\0000a0\0000a0";
    }
    h6:before {
      counter-increment: h6counter;
      content: counter(h2counter) "."
                counter(h3counter) "."
                counter(h4counter) "."
                counter(h5counter) "."
                counter(h6counter) ".\0000a0\0000a0";
    }
</style>

<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="github-markdown.css">
<style>
	.markdown-body {
		box-sizing: border-box;
		min-width: 200px;
		max-width: 980px;
		margin: 0 auto;
		padding: 45px;
	}

	@media (max-width: 767px) {
		.markdown-body {
			padding: 15px;
		}
	}
</style>
<article class="markdown-body">
	<h1>Unicorns</h1>
	<p>All the things</p>
</article>

# Table of Contents
- [Table of Contents](#table-of-contents)
  - [matplotlib](#matplotlib)
  - [B.py调用A.py的函数或类（B.py和A.py在同一个文件夹下）](#bpy调用apy的函数或类bpy和apy在同一个文件夹下)
    - [调用函数：](#调用函数)
    - [调用类：](#调用类)
    - [B.py调用A.py类中的变量（B.py和A.py在同一个文件夹下）](#bpy调用apy类中的变量bpy和apy在同一个文件夹下)

<!--more-->
---
## matplotlib

[python散点图绘制scatter](https://blog.csdn.net/weixin_31556371/article/details/112224367)

[matplotlib设置散点图点的大小(pyplot散点图标记大小)](https://blog.csdn.net/weixin_39531229/article/details/110040394)


[python 调用其他文件函数或类及类中变量](https://blog.csdn.net/mao_hui_fei/article/details/104271763)：

## B.py调用A.py的函数或类（B.py和A.py在同一个文件夹下）
### 调用函数：
A.py文件：
```python
def add(x,y):  
    print('和为：%d'%(x+y))  
```
B.py文件：
```python
import A  
A.add(1,2)  
```
或者：
```python
from A import add
add(1,2)
```

### 调用类：

A.py文件:
```python
class A:
    def __init__(self,xx,yy):
        self.x=xx
        self.y=yy
    def add(self):
        print("x和y的和为：%d"%(self.x+self.y))
```
B.py文件：
```python
import A  
a=A.A(2,3)  
a.add()  
```
或者：
```python
from A import A  
a=A(2,3)  
a.add()  
```
### B.py调用A.py类中的变量（B.py和A.py在同一个文件夹下）
A.py文件:
```python
class A:
	aaa=10         
    def hahaha(self):
        print("哈哈哈")
```
B.py文件：
```python
import A  
b=A.A.aaa  
```

或者：
```python
from A import A  
a=A.aaa  
```
在不同文件夹下
A.py文件的文件路径：D:\PythonProject\wxpyrobot

B.py文件：
```python
import sys
sys.path.append(r'D:\PythonProject\wxpyrobot')
'''
python import模块时， 是在sys.path里按顺序查找的。 
sys.path是一个列表，里面以字符串的形式存储了许多路径。 
使用A.py文件中的函数需要先将他的文件路径放到sys.path中
'''  
 
import A
 
a=A.A(2,3)
a.add()
```

