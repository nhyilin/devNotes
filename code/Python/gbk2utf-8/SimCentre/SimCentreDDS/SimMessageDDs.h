#ifndef SimDDSStruct_h__
#define SimDDSStruct_h__
#include <string>
#include <vector>
struct SimMessageDDs
{
	std::string tastID;	//任务代号
	std::string dest;	//信宿
	std::string src;	//信源
	std::string time;	//时间戳
	std::string step;	//步长
	std::string type;	//指令类
	std::string subtype;	//子类型
	unsigned long count;	//计数
	std::vector<uint8_t> data;
	SimMessageDDs()
	{
		tastID = "";
		dest = "";
		src = "";
		time = "";
		step = "";
		type = "";
		subtype = "";
		count = 0;
	}

	SimMessageDDs& operator=( const SimMessageDDs& o)
	{
		//防止自我赋值
		if (this == &o)
		{
			return *this;
		}
		tastID = o.tastID;
		dest = o.dest;
		src = o.src;
		time = o.time;
		step = o.step;
		type = o.type;
		subtype = o.subtype;
		count = o.count;
		data = o.data;
		return *this;
	}
	bool operator ==(SimMessageDDs& o) const
	{
		return (tastID == o.tastID
			&& dest == o.dest
			&& src == o.src
			/*&& time == o.time*/
			&& step == o.step
			&& type == o.type
			&& subtype == o.subtype
			&& count == o.count
			/*&& data == o.data*/);

	}
};
#endif // SimDDSStruct_h__