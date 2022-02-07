#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "public_header.hpp"
#include <vector>
#include <list>
#include <queue>

BEGIN_NAMESPACE(yyyyshen)

//ͼ��ʵ��

class graph {
public:
	using data_type = int;
public:
	graph(int v)
		: m_v(v)
	{
		m_adj.resize(v);
	}

	void add_edge(data_type s, data_type t)
	{
		//����ֱ���Զ���ֵ��Ϊ�±꣬������⣨s��tӦ��������v��
		m_adj[s].push_back(t);
		m_adj[t].push_back(s);//����ͼ��һ���߷ֱ������������д洢
	}

	//��������㷨 BFS
	// �Ӿ�����ʼ��������Ķ��㿪ʼ����������������ƽ�
	// ʱ�临�Ӷ�O(V+E)��V�Ƕ��������E�Ǳ������ռ临�Ӷ�O(V)������������Ͷ��и���������������������V��
	void bfs(data_type s, data_type t)
	{
		if (s == t) return;
		std::vector<int> visited(m_v, 0);//���ڼ�¼�ѱ����ʹ��Ľڵ㣬��Ϊ������ͼ��Ҫ�Թ�ǰһ��
		//��ר�����õ�bool���飬����C++��vector<bool>����������bit�洢��Ч�ʵͣ��������int��0��1��ǣ�
		std::queue<int> queue;//���ڼ�¼����ƽ�ʱ��ÿһ������һ��Ķ���
		//����㿪ʼ
		visited[s] = 1;
		queue.push(s);
		//��¼����·��
		std::vector<int> prev(m_v, -1);//prew[i]ָ������i�Ǵ��ĸ�ǰ������������ģ����綥��2������3����prev[3]Ϊ2

		while (queue.size() != 0)
		{
			int w = queue.front();
			queue.pop();

			for (auto iter = m_adj[w].begin(); iter != m_adj[w].end(); ++iter)
			{
				int q = *iter;
				if (visited[q] == 1)
					continue;

				prev[q] = w;//��¼·��
				if (q == t)
				{
					print(prev, s, t);//�����յ㣬�ݹ��ӡ
					std::cout << std::endl;
					return;
				}

				visited[q] = 1;//����ѷ���
				queue.push(q);//ÿ��������ӣ��Ա���һ��ѭ��������һ��
			}
		}
	}
	void print(std::vector<int>& prev, int s, int t)
	{
		if (prev[t] != -1 && t != s)//prev�����ŵ�
			print(prev, s, prev[t]);
		std::cout << t << " ";
	}

	//����������� DFS
	// ��һ����·�ߵ�ͷ���߲�ͨʱ���˻���һ����·������ѡ��
	// �Ӷ���V����������δ�����ʵ��ڽӶ��㣬�ٶ��ڽӶ���������ȱ�����ֱ�������ڽӶ��㱻����
	// ʹ���˻���˼�룬�ʺ��õݹ�
	// ʱ�临�Ӷ�O(E)��EΪ������ÿ�������������Σ������ͻ��ˣ����ռ临�Ӷ�O(V)
	bool found = false;
	void dfs(int s, int t)
	{
		found = false;
		//���ڼ�¼�����飻����ֱ�Ӿ����õݹ�ķ�ʽ������
		std::vector<int> visited(m_v, 0);
		std::vector<int> prev(m_v, -1);

		dfs_recur(s, t, visited, prev);
		print(prev, s, t);
	}
	void dfs_recur(int w, int t, std::vector<int>& visited, std::vector<int>& prev)
	{
		if (found) return;
		visited[w] = 1;

		if (w == t)
		{
			found = true;
			return;
		}

		for (auto iter = m_adj[w].begin(); iter != m_adj[w].end(); ++iter)
		{
			int q = *iter;
			if (visited[q] == 1)
				continue;

			prev[q] = w;
			dfs_recur(q, t, visited, prev);//��һ��·����ֱ���ߵ���
		}
	}

private:
	int m_v;//�������
	std::vector<std::list<data_type>> m_adj;//�ڽӱ�
};

END_NAMESPACE(yyyyshen)

#endif // !GRAPH_HPP
