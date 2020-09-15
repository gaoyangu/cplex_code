#include "Dijkstra.h"


bool Graph_DG::checkEdge(int start, int end, int weight)
{
	if (start < 1 || end < 1 || start > nodeNum || end > nodeNum || weight < 0) {
		return false;
	}
	return true;
}

void Graph_DG::creatGraph()
{
	cout << "请输入每条边的起点和终点（顶点编号从1开始）以及其权重" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	while (count != edgeNum) {
		cin >> start >> end >> weight;
		while (!checkEdge(start, end, weight)) {
			cout << "输入的信息不合法，请重新输入" << endl;
			cin >> start >> end >> weight;
		}
		//对邻接矩阵对应上的点赋值
		arc[start - 1][end - 1] = weight;
		//无向图
		//arc[end - 1][start - 1] = weight;
		++count;
	}
}

void Graph_DG::printArc() {
	cout << "图的邻接矩阵为：" << endl;
	for (int i = 0; i < nodeNum; i++) {
		for (int j = 0; j < nodeNum; j++) {
			if (arc[i][j] == INT_MAX)
				cout << "∞" << " ";
			else
				cout << arc[i][j] << " ";
		}
		cout << endl;
	}
}

void Graph_DG::Dijkstra(int begin)
{
	Dis tmp_dis;
	for (int i = 0; i < nodeNum; i++) {
		//设置当前的路径
		//tmp_dis.path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
		tmp_dis.IsVisited = false;
		tmp_dis.parent = to_string(begin) + " -> " + to_string(i + 1);
		tmp_dis.distance = arc[begin - 1][i];
		dis.push_back(tmp_dis);
	}
	//设置起点起点的路径为0
	dis[begin - 1].distance = 0;
	dis[begin - 1].IsVisited = true;

	int count = 1;
	//计算剩余的顶点的最短路径
	while (count != nodeNum) {
		//min_Index 用于保存当前 dis 数组中最小的那个下标
		//min 记录当前的最小值
		int min_Index = 0;
		int min = INT_MAX;
		for (int i = 0; i < nodeNum; i++) {
			if ((!dis[i].IsVisited) && (dis[i].distance < min)) {
				min = dis[i].distance;
				min_Index = i;
			}
		}
		//把 temp 对应的顶点加入到已经找到的最短路径的集合中
		dis[min_Index].IsVisited = true;		
		for (int i = 0; i < nodeNum; i++) {
			if ((!dis[i].IsVisited) && (arc[min_Index][i] != INT_MAX) && (dis[min_Index].distance + arc[min_Index][i] < dis[i].distance)) {
				dis[i].distance = dis[min_Index].distance + arc[min_Index][i];
				dis[i].parent = dis[min_Index].parent + " -> " + to_string(i + 1);
			}
		}
		++count;
	}
}

void Graph_DG::printPath(int begin)
{
	cout << "以< " << begin<< " >为起点的图的最短路径为：" << endl;
	for (int i = 0; i != nodeNum; i++) {
		if (dis[i].distance != INT_MAX) {
			cout << dis[i].parent << " = " << dis[i].distance << endl;
		}		
		else
			cout << dis[i].parent << "是无最短路径的" << endl;
	}

}