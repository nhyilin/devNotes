#pragma once
#include <map>
#include <vector>
#include<string>
#include <stdio.h>

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

#define MAX_DATA_BUFFER  1024
#define MAX_NUDE_COUNT  16

class staticBitOperater
{
public:

	static void init();

	static const unsigned short index2number[MAX_NUDE_COUNT];
	static const std::string index2str[MAX_NUDE_COUNT];
	static std::map<std::string, unsigned short> src2TempMask;
	static std::map<std::string, int> src2Index;
};
