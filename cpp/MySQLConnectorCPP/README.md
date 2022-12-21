macos使用C++-connector连接mysql环境配置

其实官网的教程只说明了最终步骤，但是你去执行一定会报错。

错误可以分为两种：

找不到头文件（如mysql.h）
找不到lib库（如libssl.1.1.dylib)
第一个问题需要你指定头文件所在的目录，其实就是两个目录`/usr/local/mysql/include`，`/usr/local/mysql-connector-c++/include`。只要在IDE中指定即可，或者命令行g++编译的话就直接用-I参数指定。
第二个问题需要你指定库，也是在两个目录里`/usr/local/mysql/lib`和`/usr/local/mysql-connector-c++/lib64/`，命令行的话使用-I参数指定。
所以集合起来写就是这样：`g++ -std=c++11 -I /usr/local/mysql-connector-c++-8.0.22/include -I /usr/local/mysql/include -L /usr/local/mysql-connector-c++-8.0.22/lib64 -L /usr/local/mysql/lib mysql.cpp -lmysqlcppconn8 -lmysqlclient -lssl -lcrypto -lresolv`（如果你用jdbc版c++Connector的话，就把`-lmysqlcppconn8`改成`-lmysqlcppconn`，不然会出现找不到_get_driver_instace()错误）
这样就可以通过编译，不过这个用到的是动态库，你要执行的话它会报找不到lib库（其实就在刚才-L的两个目录里）的错误。

一个解决方案是使用静态库编译，可行，但就会带来静态库的一些问题，先上解决方案：`g++ -std=c++11 -DSTATIC_CONCPP -lmysqlcppconn-static -I /usr/local/mysql-connector-c++-8.0.22/inclsude -I /usr/local/mysql/include mysql.cpp /usr/local/mysql-connector-c++-8.0.22/lib64/libmysqlcppconn8-static.a -lssl -lcrypto -lpthread`

再一个解决方案就是仍用动态库，但是把刚才-L的两个目录中的lib库拷贝到默认的动态库路径`/usr/local/lib`里，这样执行程序时就可以找到这些动态库了。

最终还是因为静态库有奇奇怪怪的问题，使用了动态库，将如下两个库放在了可执行文件所在目录

- /usr/local/mysql-connector-c++-8.0.27/libssl.1.1.dylib
- /usr/local/mysql-connector-c++-8.0.27/libcrypto.1.1.dylib