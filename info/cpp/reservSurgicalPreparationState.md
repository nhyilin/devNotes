# 需求

手术准备界面正常走完进入设备摆放界面后返回手术准备界面，需要保留以完成的验证信息，不要让用户重新做所有验证操作

# 内容

在layout或pick页面,准确说是手术准备(SurgicalPrepareWidget)


(feature_2108_reservSurgicalPreparationState)
feature_2108_reservSurgicalPreparationState




套膜位：Coating
锯片验证：Saw Check
待刀位：standby

QuickToolParam param
```cpp
struct QuickToolParam{
    double tooltipCoordInFlangeRef[6]; //刀尖在法兰参考架坐标系下的依次（X/Y/Z/RX/RY/RZ)
    double tooltipCoordInMountFlange[3];//刀尖在安装法兰坐标系下的依次（X/Y/Z)
    double centerMass[3];
    double load;
    QuickToolParam() {
        memset(tooltipCoordInFlangeRef, 0, sizeof(double) * 6);
        memset(tooltipCoordInMountFlange, 0, sizeof(double) * 3);
        memset(centerMass, 0, sizeof(double) * 3);
        load = 0.0;     
    }
}
```
如何理解函数在结构体里

```cpp
DataManager::instance()->getQuickToolParam(knifeType, param);


DataManager *DataManager::instance()
{
    if(!m_instance) {
        static DataManager _internal_instance;
        m_instance = &_internal_instance; 
    }
    return m_instance;
}
```
如何理解：这个函数返回了对象的地址，调用时，将参数赋予对象




QuickToolParam param
代码理解：
1. 通过设置里的[QuickToolParam]参数范围来认证刀片
2. 在结束这个页面后，datamanger里的m_instance对象被赋值，其参数包括toolType以及param，其中param取自设置文件
3. 其中，赋值语句为：`DataManager::instance()->getQuickToolParam(toolType, param)`
4. m_instance在之后的很多地方用到，所以要保证从手术准备页面出来之后，其参数是存在的，也就是被赋值过

有两个思路，更倾向前者：
1. 在datamanager里新增一个布尔变量，名为"switch"
    - 默认值为false
    - 当完成一次验证后，switch置true
    - 当再次进入手术准备页面，判断switch的true&false，当其值为ture，调用getQuickToolParam()函数对m_instance赋值，并置亮所有按键
    - 验证的最后一步"回待刀位"不予额外处理，直接点亮即可，因为在right button点击时，会进行是否处于待刀位的判断，且并无任何数据保存下来
2. 将param的生命周期延长（语法上还不知道怎么处理比较好,因为看到实例化param的类有三个，担心相互影响）
    - 将param放到datamanger中，使其生命周期于应用程序保持一致，达到再次进入时，m_instance不会被重置的目的

DataManager::instance()->setBladeVerifyPass(DataManager::instance()->whetherBladeAuthenticationWasComplete);


```cpp
#define SIMULATOR

（1）函数内部调用（.cpp）
void FunA(){
    #ifdef SIMULATOR
        新测试代码
    #else
        原有代码
    #endif
    
    或
    
    #ifdef SIMULATOR
        打印log
    #endif
}


（2）宏的普遍应用(.h or .cpp)
.h:
    #define ZXZ_C_SDK
    
    #ifdef ZXZ_C_SDK
        #define C_SDK
    #else
        #define C_PLUS_SDK
    #endif

    export 'C' void PrintLog(char* info);
    
.cpp
    void PrintLog(char* info)
    {
        #ifdef C_SDK
            printf(info);
        #else
            std::cout<<info;
        #endif
    }

#define ADD(a,b)/
    { /
        return (a) + (b);/
    }

#define LEN 100
```


## checkSaw
DataManager::instance()->setSawTypeVerifyPass(true);

createSetup

## judgeIdenticalSystemLayoutAndSaw

## navigatorDataChangeed

## reassignValue2QuickToolParam
无

## SurgicalPrepareWidget
tagPosition target(tag);
CommModule::instance()->sentPosition(MACHINE_ARM, HRCmd::CMD_KNIFE_TIP, target);
ModuleManager::instance()->setModule(MODULE_ROBOT_POSITION);



## verifySawBlade
DataManager::instance()->setBladeParameter(offsetData);//

DataManager::instance()->setFlangeCoordinateKnifeTip(FlangeOffset);


DataManager::instance()->isBladeVerifyPass()

DataManager::instance()->setFlangeCoordinateKnifeTip(FlangeOffset);
qInfo() << "[yilin] flang info" << FlangeOffset.x << FlangeOffset.y << FlangeOffset.z;




void SurgicalPrepareWidget::reassignValue2QuickToolParam() {
    if (DataManager::instance()->whetherBladeAuthenticationWasComplete)
    {
        qInfo() << "[yilin] go to the ressign fun";
        /******************************************************** 
            *  @function :  
            *  @brief    : 当完成一次刀具认证后，再次进入手术准备页面，无需再次进行参数判断即可对刀具进行初始化赋值，故此函数无需判断，只需计算赋值
            *  @input    : 
            *  @output   : 
            *  @return   : 
            *  @author   :  Yilin  2021/08/24 16:57
        	*  @History  :
        *********************************************************/
        QuickToolParam param;
        qInfo() << "[yilin] whetherBladeAuthenticationWasComplete:" << DataManager::instance()->whetherBladeAuthenticationWasComplete;
        qInfo()<<"[yilin] param.tooltipCoordInFlangeRef[0]"<<param.tooltipCoordInFlangeRef[0];
        qInfo()<<"[yilin] param.tooltipCoordInFlangeRef[2] "<< param.tooltipCoordInFlangeRef[2];
    }
    return;
}

setBladeVerifyPass(false);