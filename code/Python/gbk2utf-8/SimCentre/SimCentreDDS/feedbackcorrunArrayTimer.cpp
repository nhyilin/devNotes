#include "feedbackcorrunArrayTimer.h"
#include "qtsettingset.h"
#include "MIddleByValueSet.h"
#include "SimDataAnalysis.h"
#include "simdds.h"
#include "qttestout.hpp"
#include <QDateTime>

unsigned short FeedBackcorrunArrayTimer::allReceivedNumber = 0;
unsigned short FeedBackcorrunArrayTimer::receiveBuffer =0;
unsigned short FeedBackcorrunArrayTimer::BufferTemp = 0;
unsigned short FeedBackcorrunArrayTimer::currentreceiveBufferTemp = 0;
unsigned short FeedBackcorrunArrayTimer::currentsendBufferTemp = 0;
unsigned short FeedBackcorrunArrayTimer::sendBufferTemp = 0;
unsigned short FeedBackcorrunArrayTimer::ret = 0;
unsigned int FeedBackcorrunArrayTimer::count = 10;
unsigned int FeedBackcorrunArrayTimer::slowestForTestcount[MAX_NUDE_COUNT];
std::map<std::string, int>  FeedBackcorrunArrayTimer::src2Index;
std::map<std::string, unsigned short> FeedBackcorrunArrayTimer::src2TempMask;
std::map<std::string, std::string> FeedBackcorrunArrayTimer::src2Step;
std::map<std::string, std::vector<uint8_t>> FeedBackcorrunArrayTimer::src2buffer;



QDateTime FeedBackcorrunArrayTimer::endTime;
unsigned int FeedBackcorrunArrayTimer::MaxCountForTest=50000;

//std::vector<uint8_t> FeedBackcorrunArrayTimer::allBuffers[MAX_NUDE_COUNT];

const unsigned short FeedBackcorrunArrayTimer::index2number[MAX_NUDE_COUNT]= {
	NODE_COM1,
	NODE_COM2,
	NODE_COM3,
	NODE_COM4,
	NODE_COM5,
	NODE_COM6,
	NODE_COM7,
	NODE_COM8,
	NODE_COM9,
	NODE_COM10/*,
	NODE_COM11,
	NODE_COM12,
	NODE_COM13,
	NODE_COM14,
	NODE_COM15,
	NODE_COM16*/ };


const std::string FeedBackcorrunArrayTimer::index2str[MAX_NUDE_COUNT] = {
	std::string("01"),std::string("02"),std::string("03"),std::string("04"),std::string("05"),std::string("06"),std::string("07"),std::string("08"),
	std::string("09"),std::string("10")/*,std::string("11"),std::string("12"),std::string("13"),std::string("14"),std::string("15"),std::string("16")*/
};

void FeedBackcorrunArrayTimer::init()
{
	for (int i = 0; i < MAX_NUDE_COUNT; i++)
    {
		src2TempMask.insert(make_pair(index2str[i], index2number[i]));
		src2Index.insert(make_pair(index2str[i],i));
    }
	/*src2TempMask.insert("01", NODE_COM1);
	src2TempMask.insert("02", NODE_COM2);
	src2TempMask.insert("03", NODE_COM3);
	src2TempMask.insert("04", NODE_COM4);
	src2TempMask.insert("05", NODE_COM5);
	src2TempMask.insert("06", NODE_COM6);
	src2TempMask.insert("07", NODE_COM7);
	src2TempMask.insert("08", NODE_COM8);
	src2TempMask.insert("09", NODE_COM9);
	src2TempMask.insert("10", NODE_COM10);
	src2TempMask.insert("11", NODE_COM11);
	src2TempMask.insert("12", NODE_COM12);
	src2TempMask.insert("13", NODE_COM13);
	src2TempMask.insert("14", NODE_COM14);
	src2TempMask.insert("15", NODE_COM15);
	src2TempMask.insert("16", NODE_COM16);*/
	//for (int i = 0; i < MAX_NUDE_COUNT; i++)
	//{
	//	allBuffers[i] = new std::vector<uint8_t>();
	//	src2buffer.insert(getNOdeSrcNameByIndex(i), allBuffers[i]);
	//}
}



std::string FeedBackcorrunArrayTimer::getNOdeSrcNameByIndex(int i) {
	std::string retstr;
	if (i >= 0 && i <= 9)
	{
		char temp;
		itoa(i, &temp, 10);
		retstr += '0';
		retstr += temp;
	}
	else if (i >= 10 && i <= MAX_NUDE_COUNT)
	{
		char temp;
		itoa(i, &temp, 10);
		retstr += temp;
	}
	return retstr;
}

void FeedBackcorrunArrayTimer::on_nodeconnected(SimMessageDDs sim)
{
	BufferTemp = src2TempMask[sim.src];
	allReceivedNumber |= BufferTemp;
	src2Step.insert(make_pair(sim.src,sim.step));
}


void FeedBackcorrunArrayTimer::resendCorCommd()
{
	SimMessageDDs simdds;
	QtSettingSet::instance()->readConfig("COR_RUN_BEGIN", simdds);

	std::string destination;
	for (int i = 0; i < MAX_NUDE_COUNT; i++)
	{
		if ((index2number[i] & allReceivedNumber) == index2number[i])//为true 则该节点已连接 需要给该节点发消息
		{
			destination += index2str[i];
		}
	}
	simdds.dest = destination;
	static QDateTime startTime = QDateTime::currentDateTime();
	if (count == 0)
		startTime = QDateTime::currentDateTime();

	endTime = QDateTime::currentDateTime();
	simdds.time = endTime.toString("yyyy-MM-dd hh:mm:ss.zzz").toStdString();
	simdds.count = ++count;

	simdds.data.push_back((unsigned char)allReceivedNumber);//低8位
	simdds.data.push_back((unsigned char)(allReceivedNumber >> 8));//高8位

	//拼接数据 step + stepnum + count;
	//std::string step = QString::number(
	//	MIddleByValueSet::instance()->getpublishertime()).toStdString();
	//for (int j = 0; j < step.length(); j++)
	//{
	//	simdds.data.push_back(step[j]);
	//}
	//simdds.data.push_back('-');
	////count;
	//std::string num = QString::number(simdds.count).toStdString();
	//for (int k = 0; k < num.length(); k++)
	//{
	//	simdds.data.push_back(num[k]);
	//}
	clear();
	//std::cout << "count:"<< count << "type:" << simdds.type << "\n";
	//if (MaxCountForTest == count)
	//{
	//	int a;
	//	cout << getRes(startTime, endTime);
	//	cout << "\n按任意键继续\n";
	//	cin >> a;
	//}
	SimDDS::instance()->SimDDSPubPublisher(simdds);
	//TerminalPubPublisherOutput(simdds);

}


std::string FeedBackcorrunArrayTimer::getRes(QDateTime start, QDateTime end)
{
	int allMS = end.msecsTo(start);

	int msPerCount = allMS / count;

	QString resStrTemp = "共发送"+ QString::number(count)+"次，平均每个命令回复时间为"+ QString::number(count)+"毫秒";



	int slowstCom = 0;
	int secondslowCom = 0;

	for (int i = 0; i < MAX_NUDE_COUNT; i++)
	{
		if (slowestForTestcount[i] > slowstCom)
			slowstCom = i;
	}

	for (int i = 0; i < MAX_NUDE_COUNT; i++)
	{
		if (i == slowstCom)
			continue;
		if (slowestForTestcount[i] > slowstCom)
			secondslowCom = i;
	}

	for (int i = 0; i < MAX_NUDE_COUNT; i++)
	{
		resStrTemp +=  QString::number(i) + "号节点最后发送的次数为：" + slowestForTestcount[i] + "次";
	}

	std::string resStr = resStrTemp.toStdString();

	return resStr;
}