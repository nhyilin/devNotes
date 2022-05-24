Linux离线安装git(eg:ubuntu)
<!--more-->
准备
1. Ubuntu16.04安装机(较低版本ubuntu内核系统，麒麟适用)
2. 任意公网机下载安装包
按照以下顺序执行安装可完美避坑

1. [gettext](https://mirror.bjtu.edu.cn/gnu/gettext/)

原因：
依赖包，防止编译时出现`msgfmt not found`报错
安装：
```bash
tar -xzf gettext-*.tar.gz
cd gettext-*/
./configure
make && make install 
```

2. 链接动态库
原因：
防止编译时出现`error while loading shared libraries: libgettextsrc-*.so`报错
命令行：

`ldconfig /usr/local/bin`

其中`/usr/local`为`./configure`的默认安装地址

3. [git](https://mirrors.edge.kernel.org/pub/software/scm/git/)

安装：
```bash
which git
git --version
tar -xJf git-*.tar.xz
cd git-*
./configure --prefix=/usr
make && make install
which git
git --version
```

prefix=/usr将会替换系统自带的/usr/bin/git

4. 本地配置

配置Git：
```bash
git config --global user.name master
git config --global user.email master@gmail.com
```
配置SSH：
`ssh-keygen -t rsa -C "master@gmail.com" `

5. 查看密钥

`cat  ~/.ssh/id_rsa.pub`

在gitlab中保存

6. 获取代码：

`git clone + URL`