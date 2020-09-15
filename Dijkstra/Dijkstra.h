#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//记录起点到每个顶点的最短路径信息
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
	//构造函数
	Graph_DG(int n_node, int n_edge) :
		nodeNum(n_node), edgeNum(n_edge) 
	{
		//初始化邻接矩阵
		for (int i = 0; i < nodeNum; i++) {
			vector<int> vec;
			for (int j = 0; j < nodeNum; j++) {
				vec.push_back(INT_MAX);
			}
			arc.push_back(vec);
		}
	};

	//判断每次输入的边的信息是否合法
	//顶点从1开始编号
	bool checkEdge(int start, int end, int weight);
	//创建图
	void creatGraph();
	//打印邻接矩阵
	void printArc();
	//求最短路径
	void Dijkstra(int begin);
	//打印最短路径
	void printPath(int begin);

	
private:
	int nodeNum;				//图的顶点个数
	int edgeNum;				//图的边数
	vector<vector<int>> arc;	//邻接矩阵
	vector<Dis> dis;			//记录每个顶点最短路径的信息
};