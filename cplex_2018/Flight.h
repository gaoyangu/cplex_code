#pragma once
#include <string>
using namespace std;

//����
class Flight{
public:
	int name;
	int startTime;		//����ʱ��
	int endTime;		//����ʱ��
	int arriveType;		//��������
	int leaveType;		//��������
	string planeType;	//�ɻ��ͺ�

	string arriveNum;	//���ﺽ��
	string leaveNum;	//��������
};