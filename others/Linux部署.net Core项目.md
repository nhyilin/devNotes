场景：项目基于c#做后端程序，html做前端，通过js、css来控制反馈信号及样式。发布在win系统相对麻烦，需要找到对应版本的sdk，网上笔记很多，且当电脑联网后，过程很简单，不做赘述。

发布Linux网上教程看了很多，几乎都有或多或少的毛病，对阅读者造成不少困扰，故在此记录，以便查阅。

<!--more-->

# 环境准备


- Ubuntu（原目标为银河麒麟，借助Ubuntu进行测试）
- 能使用sudo的账户或root账户
- 端口可控
- 编译通过的ASP.NET Core项目
- 在vs中发布对应版本的ASP.NET Core项目（建议发布Self-contained模式，后面只需配置第三方库支持即可，无需.net core环境）

# 部署过程
## 安装组件

在线安装：
1. `sudo mkdir /usr/local/dotnet` //创建目录
2. `cd /usr/local/dotnet`
3. `sudo wget https://download.visualstudio.microsoft.com/download/......（选取需要的版本路径即可）`
4. `sudo tar -xvf aspnetcore-runtime-5.0.0-linux-x64.tar.gz` //解压
5. `./dotnet --info` //查看(显示版本等即为安装成功)

离线安装：
1. `sudo mkdir /usr/local/dotnet` //创建目录
2. `cd /usr/local`
3. `sudo chmod 777 dotnet` //赋予文件写入权限
4. 将aspnetcore-runtime-5.0.0-linux-x64.tar.gz放置在`/usr/local/dotnet`中
5. `sudo tar -xvf aspnetcore-runtime-5.0.0-linux-x64.tar.gz` //解压
6. `./dotnet --info` //查看（如果报错没关系，等后面添加好环境变量再检查也不迟）


此时，dotnet路径为：`/usr/local/dotnet`

## 环境配置

1. `export DOTNET_ROOT=/usr/local/dotnet`
2. `export PATH=$PATH:/usr/local/dotnet`
3. `source /etc/profile` //启用新环境

此时执行`./dotnet --info`可检查环境，可以看到runtime已安装成功。但是这种设置环境变量方式只能对当前会话窗口起作用，在其它窗口就不再适用。

为解决此问题，可创建软连接的方式来设置环境变量：`ln -s /var/local/dotnet/dotnet /usr/local/bin`，创建完成后，即可在所有会话窗口访问dotnet

# 网页部署

1. `sudo mkdir /var/www` //创建项目目录
2. `cd /var`
3. `sudo chmod 777 www` //赋予权限否则无法放置项目文件，具体权限后期可补充修改
4. 将publish文件夹内文件复制到www文件夹内
5. `dotnet xxx.dll` //xxx是项目名


# 补充说明

1. 可以选择nginx来配置项目，效果预估会更好一些，但是如果不是必须，没必要配置。
2. 防火墙信息
    - `service firewalld status`//查看防火墙状态
    - `firewall-cmd --zone=public --add-port=5000/tcp --permanent`//将5000端口添加到防火墙中
    - `firewall-cmd --reload`//重启防火墙

