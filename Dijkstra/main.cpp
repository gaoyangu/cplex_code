#include "Dijkstra.h"

bool check(int n_node, int n_edge)
{
	if (n_node <= 0 || n_edge <= 0 || n_node * (n_node - 1) / 2 < n_edge)
		return false;
	return true;
}

int main()
{
	int n_node;
	int n_edge;
	cout << "������ͼ�Ķ�������ͱߵ�������" << endl;
	cin >> n_node >> n_edge;
	while (!check(n_node, n_edge)) {
		cout << "�������ֵ���Ϸ������������� " << endl;
		cin >> n_node >> n_edge;
	}
	Graph_DG graph(n_node, n_edge);
	graph.creatGraph();
	graph.printArc();
	graph.Dijkstra(1);
	graph.printPath(1);
	
	system("pause");
	return 0;
}