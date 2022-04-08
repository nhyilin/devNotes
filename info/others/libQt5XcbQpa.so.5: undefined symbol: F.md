解决libQt5XcbQpa.so.5: undefined symbol: FT_Property_Set

遇到的问题
`symbol lookup error: /home/frank/Qt5.12.2/5.12.2/gcc_64/lib/libQt5XcbQpa.so.5: undefined symbol: FT_Property_Set`
解决方法
分析
我遇到的这种情况是因为有两个版本的`freeetype`导致的。
输入：

`find /usr -name libfreetype*`
如果出现：
```bash
/usr/lib/x86_64-linux-gnu/libfreetype.a
/usr/lib/x86_64-linux-gnu/libfreetype.so.6
/usr/lib/x86_64-linux-gnu/libfreetype.la
/usr/lib/x86_64-linux-gnu/libfreetype.so
/usr/lib/x86_64-linux-gnu/libfreetype.so.6.12.1
/usr/local/lib/libfreetype.a
/usr/local/lib/libfreetype.so.6
/usr/local/lib/libfreetype.so.6.9.0
/usr/local/lib/libfreetype.la
/usr/local/lib/libfreetype.so
```
以上类似的两个版本的`freetype`，可以参考我的解决方案。

解决方案
`sudo rm /usr/local/lib/libfreetype.so.6`
或者
```bash
cd  /usr/local/lib
sudo rm libfreetype.so.6 libfreetype.so libfreetype.so.6.9.0
```
切记
不要把两个地方的`libfreetype.so.6`都删出了，我都删了之后，出现无法使用快捷键(如：`ctrl+alt+t`无法弹出终端)，以及重启无法进入系统的情况，最后通过重新创建`/usr/lib/x86_64-linux-gnu/`里面的`/usr/lib/x86_64-linux-gnu/libfreetype.so.6`，才重新进入系统。（`libfreetype.so.6`是一个软链接文件）
```bash
ln -s /usr/lib/x86_64-linux-gnu/libfreetype.so.6.12.1 /usr/lib/x86_64-linux-gnu/libfreetype.so.6
ll | grep /usr/lib/x86_64-linux-gnu/libfreetype
```