#include"staticbitoperate.h"


std::map<std::string, unsigned short> staticBitOperater::src2TempMask;
std::map<std::string, int> staticBitOperater::src2Index;

const unsigned short staticBitOperater::index2number[MAX_NUDE_COUNT] = {
	NODE_COM1,
	NODE_COM2,
	NODE_COM3,
	NODE_COM4,
	NODE_COM5,
	NODE_COM6,
	NODE_COM7,
	NODE_COM8,
	NODE_COM9,
	NODE_COM10,
	NODE_COM11,
	NODE_COM12,
	NODE_COM13,
	NODE_COM14,
	NODE_COM15,
	NODE_COM16 };


const std::string staticBitOperater::index2str[MAX_NUDE_COUNT] = {
	std::string("01"),std::string("02"),std::string("03"),std::string("04"),std::string("05"),std::string("06"),std::string("07"),std::string("08"),
	std::string("09"),std::string("10"),std::string("11"),std::string("12"),std::string("13"),std::string("14"),std::string("15"),std::string("16")
};


void staticBitOperater::init()
{
	for (int i = 0; i < MAX_NUDE_COUNT; i++)
	{
		src2TempMask.insert(std::pair<std::string, unsigned short>(index2str[i], index2number[i]));
		src2Index.insert(std::pair<std::string, int>(index2str[i], i));
	}
}