#ifndef qttestout_h__
#define qttestout_h__

#include <iostream>
#include "SimMessageDDs.h"
 static void TerminalPubPublisherOutput(SimMessageDDs simdds)
{
	std::cout << "TastID" << simdds.tastID << " "
		<< "src" << simdds.src << " "
		<< "dest" << simdds.dest << " "
		<< "time" << simdds.time << " "
		<< "step" << simdds.step << " " 
		<< "type" << simdds.type << " "
		<< "subtype" << simdds.subtype << " "
		<< "count" << simdds.count << " "
		<< "data" << simdds.data.at(0) << " "
		<< "data " << simdds.data.at(1) << " "
		<< "协同发送指令" << " "
		<< "\n";
}

 static void TerminalSubPublisherOutput(SimMessageDDs simdds)
 {
	 std::cout << "TastID" << simdds.tastID << " "
		 << "src" << simdds.src << " "
		 << "dest" << simdds.dest << " "
		 << "time" << simdds.time << " "
		 << "step" << simdds.step << " "
		 << "type" << simdds.type << " "
		 << "subtype" << simdds.subtype << " "
		 << "count" << simdds.count << " ";
		 for (int i = 0;i< simdds.data.size();i++)
		 {
			 std::cout << simdds.data.at(i);
		 }
		 std::cout <<" "<< "反馈发送指令" << " "<< std::endl;
 }

 static void TerminalSubSubsciberOutput(SimMessageDDs simdds)
 {
	 static uint32_t sample = 0;
	 std::cout << "TastID" << simdds.tastID << " "
		 << "src" << simdds.src << " "
		 << "dest" << simdds.dest << " "
		 << "time" << simdds.time << " "
		 << "step" << simdds.step << " "
		 << "type" << simdds.type << " "
		 << "subtype" << simdds.subtype << " "
		 << "count" << simdds.count << " "
		 << "接收的总数据量" << sample++ << " ";
		for (int i = 0 ;i< simdds.data.size();i++)
		{
			std::cout <<simdds.data.at(i);
		}
		std::cout <<" "<<"接收数据" << " " << std::endl;
 }

 
#endif // qttestout_h__
