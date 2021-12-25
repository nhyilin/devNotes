#ifndef feedbackcorrunArrayTimer_h__
#define feedbackcorrunArrayTimer_h__

#include <map>
#include <vector>
#include <QTime>
#include "SimMessageDDs.h"

#define CENTRAL_COM 0b0000000000000000
#define NODE_COM1   0b0000000000000001
#define NODE_COM2   0b0000000000000010
#define NODE_COM3   0b0000000000000100
#define NODE_COM4   0b0000000000001000
#define NODE_COM5   0b0000000000010000
#define NODE_COM6   0b0000000000100000
#define NODE_COM7   0b0000000001000000
#define NODE_COM8   0b0000000010000000
#define NODE_COM9   0b0000000100000000
#define NODE_COM10  0b0000001000000000
#define NODE_COM11  0b0000010000000000
#define NODE_COM12  0b0000100000000000
#define NODE_COM13  0b0001000000000000
#define NODE_COM14  0b0010000000000000
#define NODE_COM15  0b0100000000000000
#define NODE_COM16  0b1000000000000000

//#define ALL_NODE_RECEIVED 1111111111111111b

#define MAX_DATA_BUFFER  1024
#define MAX_NUDE_COUNT  10
class FeedBackcorrunArrayTimer
{
public:

	static void init();

	//节点连接时用到  计算哪些节点连接了
	static void on_nodeconnected(SimMessageDDs sim);


	//收到消息时用到 将收到消息的节点计入缓存变量,并缓存数据  如果不是新回令就返回false
	inline static bool on_nodeReceiveMessage(std::string node, const std::vector<uint8_t> &data)
	{
		BufferTemp = src2TempMask[node];
		currentreceiveBufferTemp = receiveBuffer;
		ret = currentreceiveBufferTemp & BufferTemp;//对收到节点的掩码和当前的缓存掩码按位与，如果值不变说明已经收到了该节点的回令
		if (ret == BufferTemp)
		{
			return false;
		}

		//到这里说明是新回令，赋值
		receiveBuffer |= BufferTemp;
		//setBuffer(node, data);
		//统一发送
	/*	if (receiveBuffer == allReceivedNumber)
		{
			resendCorCommd();
			slowestForTestcount[src2Index[node]]++;
		}*/
		return true;
	}



	inline static void clear() {
		receiveBuffer = 0;
		currentsendBufferTemp = 0;
		//for (int i = 0; i < MAX_NUDE_COUNT; i++)
		//{
		//	allBuffers[i].clear();
		//}
		//for (auto& node : src2buffer.keys())
		//	src2buffer[node].clear();
	}

	//static unsigned short getTempMask(std::string src) {
	//	return src2TempMask[src];
	//}

	static unsigned short receiveBuffer;//当前已收到回令的掩码
	static unsigned short allReceivedNumber;//当前连接的所有节点组成的掩码
	static unsigned short BufferTemp;

public:
	static std::string getNOdeSrcNameByIndex(int i);
	static std::string getRes(QDateTime start, QDateTime end);

	inline static void setBuffer(std::string node, const std::vector<uint8_t>& data)
	{
		src2buffer[node] = data;
	}

	static void resendCorCommd();


	static std::map<std::string, unsigned short> src2TempMask;
	static std::map<std::string, int> src2Index;
	static std::map<std::string, std::string> src2Step;
	//static std::vector<uint8_t> allBuffers[MAX_NUDE_COUNT];
	static std::map<std::string, std::vector<uint8_t>> src2buffer;

	static const unsigned short index2number[MAX_NUDE_COUNT];
	static const std::string index2str[MAX_NUDE_COUNT];

	static unsigned int slowestForTestcount[MAX_NUDE_COUNT];
	//static void staticdelete()
	//{
	//	for (int i = 0; i < MAX_NUDE_COUNT; i++)
	//	{
	//		delete allBuffers[i];
	//	}
	//}

	static unsigned short currentreceiveBufferTemp;
	static unsigned short currentsendBufferTemp;
	static unsigned short sendBufferTemp;
	static unsigned short ret ;
	static unsigned int count;
	static unsigned int MaxCountForTest;

	static QDateTime endTime;

};


#endif // feedbackcorrunArrayTimer_h__