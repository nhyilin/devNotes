#ifndef MyMap_h__
#define MyMap_h__
#include<string>
#include <stdio.h>
#include <unordered_map>
#include <mutex>

using namespace std;
class MapSet
{
public:
	MapSet();
	virtual ~MapSet();
	//设置数据
	bool SetMapData(std::string key, string value);
	string GetMapData(std::string key);

	std::mutex & getMutex() { return mutex_; }
	unordered_map<std::string, std::string> &GetMapSet();
	void LockMapData();
	void unLockMapData();
	//删除数据
	bool RemoveMapData(std::string key);
	//打印Map信息
	void PrintMap();
	//清空数据
	void Clean();
private:
	//[int]=string
	unordered_map<std::string, std::string>MapInt;
	//限制MapInt容量大小
	int MapIntMaxSize;
	//互斥锁
	std::mutex mutex_;
};

#endif // MyMap_h__