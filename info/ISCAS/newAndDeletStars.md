# Table of Contents
<pre>
<a href="#introduction">introduction</a>
<a href="#accumulate">accumulate</a>
<a href="#furtherjob">furtherJob</a>
</pre>


# introduction

借助stk删除或者新建星系，借助QSTKEarth类来访问stk的相关功能和接口

1. 找到新建星座的函数，将新建的星座返回值找到（btw，是否储存）



[![top] Goto Top](#table-of-contents)



# coding 

目前CECA项目中，暂未引入cstkKernel的相关功能，固本项目以命令行的方式控制为主例如：
```cpp
void QSTKEarth::DeletSatelliteTest(QString objName)
{
	Q_ASSERT(m_app != NULL);
	STKXLib::IAgSTKXApplicationPtr pSTKXapp(m_app);
	QString conmmond = "UnloadMulti / */Satellite/" + objName;
	_bstr_t conmmond_bstr = _com_util::ConvertStringToBSTR(QStr2Stdstr(conmmond).c_str());
	pSTKXapp->ExecuteCommand(conmmond_bstr);
}
```
方式来删除或者其他操作












# accumulate
## 参数初始化
新建卫星：
```
卫星名称：xxx

半长轴:7163
偏心率:0
倾角:98.5
近地点幅角:0
升交点赤经:99.3
真近点角:0
```

新建星座：
```
轨道面数:2
每个轨道面卫星数:3
相位因子:1
RAAN扩散:360
```

## stk新建、删除卫星
通过命令行方式来控制stk的新建与删除，具体见`QSTKEarth`类

```cpp

void QSTKEarth::DeleteConstellationTest(QString objName)
{
	Q_ASSERT(m_app != NULL);
	/*Constellation *constellation = (Constellation *)object;
	QString constellationname = object->preName;
	object->preName = object->GetName();
	*/
	STKXLib::IAgSTKXApplicationPtr pSTKXapp(m_app);
	QString conmmond = "UnloadMulti / */Constellation/" + objName;

	_bstr_t conmmond_bstr = _com_util::ConvertStringToBSTR(QStr2Stdstr(conmmond).c_str());
	pSTKXapp->ExecuteCommand(conmmond_bstr);
}

void QSTKEarth::DeletSatelliteTest(QString objName)
{
	Q_ASSERT(m_app != NULL);
	STKXLib::IAgSTKXApplicationPtr pSTKXapp(m_app);
	QString conmmond = "UnloadMulti / */Satellite/" + objName;
	_bstr_t conmmond_bstr = _com_util::ConvertStringToBSTR(QStr2Stdstr(conmmond).c_str());
	pSTKXapp->ExecuteCommand(conmmond_bstr);
}

```

新建卫星时，在LatitudeBounds.cpp中定义卫星名:`QString satName = "seed" + QString::number(satOrder);`

[![top] Goto Top](#table-of-contents)

# furtherJob

1. extern用法：

2. `QString satName = "seed" + QString::number(satOrder);`中，seed的含义

3. qInstallMessageHandler，安装log信息(结合中哥代码，将其完善在info笔记中)
























[![top] Goto Top](#table-of-contents)


[top]: up.png
