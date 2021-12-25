#include "MapSet.h"


MapSet::MapSet()
{
	MapIntMaxSize = 500;
}


MapSet::~MapSet()
{

	if (!MapInt.empty()) {
		for (auto iter = MapInt.begin(); iter != MapInt.end(); iter++) {
			MapInt.erase(iter);
		}
		MapInt.clear();
	}
}

bool MapSet::SetMapData(std::string key, std::string value)
{
	mutex_.lock();
	auto iter = MapInt.find(key);
	if (iter != MapInt.end()) {
		MapInt.erase(iter);
	}
	else {
		int size = MapInt.size();
		if (size > MapIntMaxSize) {
			mutex_.unlock();
			return false;
		}
	}
	MapInt.insert(pair<std::string, std::string>(key, value));
	mutex_.unlock();
	return true;
}


string MapSet::GetMapData(std::string key)
{
	mutex_.lock();
	auto iter = MapInt.find(key);
	if (iter == MapInt.end()) {
		mutex_.unlock();
		return "";
	}
	mutex_.unlock();
	return iter->second;
}

void MapSet::LockMapData()
{
	mutex_.lock();
}

void MapSet::unLockMapData()
{
	mutex_.unlock();
}

bool MapSet::RemoveMapData(std::string key)
{
	mutex_.lock();
	auto iter = MapInt.find(key);
	if (iter == MapInt.end()) {
		mutex_.unlock();
		return false;
	}
	MapInt.erase(iter);
	return true;
}

void MapSet::PrintMap()
{
	if (!MapInt.empty()) {
		for (auto iter = MapInt.begin(); iter != MapInt.end(); iter++) {
			printf("MapInt  first:%s, second:%s \n", iter->first, iter->second.c_str());
		}
	}
}

unordered_map<std::string, std::string> & MapSet::GetMapSet()
{
	mutex_.lock();
	return MapInt;
}

void MapSet::Clean()
{
	mutex_.lock();
	if (!MapInt.empty()) {
		//for (map<std::string, std::string>::iterator iter = MapInt.begin();
		//	iter != MapInt.end(); iter++) {
		//	MapInt.erase(iter);
		//}
		MapInt.clear();
	}
	mutex_.unlock();
}