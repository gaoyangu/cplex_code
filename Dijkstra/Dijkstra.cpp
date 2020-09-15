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
	cout << "������ÿ���ߵ������յ㣨�����Ŵ�1��ʼ���Լ���Ȩ��" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	while (count != edgeNum) {
		cin >> start >> end >> weight;
		while (!checkEdge(start, end, weight)) {
			cout << "�������Ϣ���Ϸ�������������" << endl;
			cin >> start >> end >> weight;
		}
		//���ڽӾ����Ӧ�ϵĵ㸳ֵ
		arc[start - 1][end - 1] = weight;
		//����ͼ
		//arc[end - 1][start - 1] = weight;
		++count;
	}
}

void Graph_DG::printArc() {
	cout << "ͼ���ڽӾ���Ϊ��" << endl;
	for (int i = 0; i < nodeNum; i++) {
		for (int j = 0; j < nodeNum; j++) {
			if (arc[i][j] == INT_MAX)
				cout << "��" << " ";
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
		//���õ�ǰ��·��
		//tmp_dis.path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
		tmp_dis.IsVisited = false;
		tmp_dis.parent = to_string(begin) + " -> " + to_string(i + 1);
		tmp_dis.distance = arc[begin - 1][i];
		dis.push_back(tmp_dis);
	}
	//�����������·��Ϊ0
	dis[begin - 1].distance = 0;
	dis[begin - 1].IsVisited = true;

	int count = 1;
	//����ʣ��Ķ�������·��
	while (count != nodeNum) {
		//min_Index ���ڱ��浱ǰ dis ��������С���Ǹ��±�
		//min ��¼��ǰ����Сֵ
		int min_Index = 0;
		int min = INT_MAX;
		for (int i = 0; i < nodeNum; i++) {
			if ((!dis[i].IsVisited) && (dis[i].distance < min)) {
				min = dis[i].distance;
				min_Index = i;
			}
		}
		//�� temp ��Ӧ�Ķ�����뵽�Ѿ��ҵ������·���ļ�����
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
	cout << "��< " << begin<< " >Ϊ����ͼ�����·��Ϊ��" << endl;
	for (int i = 0; i != nodeNum; i++) {
		if (dis[i].distance != INT_MAX) {
			cout << dis[i].parent << " = " << dis[i].distance << endl;
		}		
		else
			cout << dis[i].parent << "�������·����" << endl;
	}

}