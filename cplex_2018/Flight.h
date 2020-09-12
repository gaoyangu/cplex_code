#pragma once
#include <string>
using namespace std;

//航班
class Flight{
public:
	int name;
	int startTime;		//到达时刻
	int endTime;		//出发时刻
	int arriveType;		//到达类型
	int leaveType;		//出发类型
	string planeType;	//飞机型号

	string arriveNum;	//到达航班
	string leaveNum;	//出发航班
};