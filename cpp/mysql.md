
允许某用户从任何IP连接：
```cpp
GRANT ALL PRIVILEGES ON *.* TO 'your_username'@'%' IDENTIFIED BY 'your_password';
FLUSH PRIVILEGES;
```