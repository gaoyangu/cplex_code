#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//��¼��㵽ÿ����������·����Ϣ
class Dis {
public:
	Dis()
	{
		IsVisited = false;
		distance = 0;
		parent = "";
	}
	string parent;
	int distance;
	bool IsVisited;
};

class Graph_DG {
public:
	//���캯��
	Graph_DG(int n_node, int n_edge) :
		nodeNum(n_node), edgeNum(n_edge) 
	{
		//��ʼ���ڽӾ���
		for (int i = 0; i < nodeNum; i++) {
			vector<int> vec;
			for (int j = 0; j < nodeNum; j++) {
				vec.push_back(INT_MAX);
			}
			arc.push_back(vec);
		}
	};

	//�ж�ÿ������ıߵ���Ϣ�Ƿ�Ϸ�
	//�����1��ʼ���
	bool checkEdge(int start, int end, int weight);
	//����ͼ
	void creatGraph();
	//��ӡ�ڽӾ���
	void printArc();
	//�����·��
	void Dijkstra(int begin);
	//��ӡ���·��
	void printPath(int begin);

	
private:
	int nodeNum;				//ͼ�Ķ������
	int edgeNum;				//ͼ�ı���
	vector<vector<int>> arc;	//�ڽӾ���
	vector<Dis> dis;			//��¼ÿ���������·������Ϣ
};