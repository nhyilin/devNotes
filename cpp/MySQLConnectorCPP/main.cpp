#include <mysql.h>
#include <iostream>
using namespace std;

//把下面配置信息修改为自己数据库的
const char host[] = "localhost";
const char user[] = "root";
const char pwd[] = "12345678";
const char database[] = "test";
unsigned int port = 3306;

int main()
{
  MYSQL myCont;
  mysql_init(&myCont);
  if (mysql_real_connect(&myCont, host, user, pwd, database, port, NULL, 0)){
    cout << "Hello MySQL！" << endl;
  }
  else
  {
    cout << "connect failed!" << endl;
  }
  mysql_close(&myCont);
  return 0;
}

