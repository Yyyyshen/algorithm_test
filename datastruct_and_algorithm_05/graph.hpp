#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "public_header.hpp"
#include <vector>
#include <list>
#include <queue>

BEGIN_NAMESPACE(yyyyshen)

//图简单实现

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
		//这里直接以顶点值作为下标，方便理解（s和t应都不超过v）
		m_adj[s].push_back(t);
		m_adj[t].push_back(s);//无向图，一条边分别在两个顶点中存储
	}

	//广度优先算法 BFS
	// 从距离起始顶点最近的顶点开始，往外搜索，层层推进
	// 时间复杂度O(V+E)，V是顶点个数，E是边数，空间复杂度O(V)（借助了数组和队列辅助，但都不超过顶点数V）
	void bfs(data_type s, data_type t)
	{
		if (s == t) return;
		std::vector<int> visited(m_v, 0);//用于记录已被访问过的节点，因为是无向图，要略过前一层
		//（专栏里用的bool数组，但是C++中vector<bool>有特殊性是bit存储，效率低，这里改用int的0和1标记）
		std::queue<int> queue;//用于记录层层推进时，每一层中下一层的顶点
		//从起点开始
		visited[s] = 1;
		queue.push(s);
		//记录搜索路径
		std::vector<int> prev(m_v, -1);//prew[i]指，顶点i是从哪个前驱顶点遍历来的，例如顶点2到顶点3，则prev[3]为2

		while (queue.size() != 0)
		{
			int w = queue.front();
			queue.pop();

			for (auto iter = m_adj[w].begin(); iter != m_adj[w].end(); ++iter)
			{
				int q = *iter;
				if (visited[q] == 1)
					continue;

				prev[q] = w;//记录路径
				if (q == t)
				{
					print(prev, s, t);//到达终点，递归打印
					std::cout << std::endl;
					return;
				}

				visited[q] = 1;//标记已访问
				queue.push(q);//每个顶点入队，以便下一轮循环访问下一层
			}
		}
	}
	void print(std::vector<int>& prev, int s, int t)
	{
		if (prev[t] != -1 && t != s)//prev是逆着的
			print(prev, s, prev[t]);
		std::cout << t << " ";
	}

	//深度优先搜索 DFS
	// 从一个岔路走到头，走不通时，退回上一个岔路，重新选择
	// 从顶点V触发，访问未被访问的邻接顶点，再对邻接顶点深度优先遍历，直到所有邻接顶点被访问
	// 使用了回溯思想，适合用递归
	// 时间复杂度O(E)，E为边数，每个边最多访问两次（遍历和回退），空间复杂度O(V)
	bool found = false;
	void dfs(int s, int t)
	{
		found = false;
		//用于记录的数组；队列直接就是用递归的方式代替了
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
			dfs_recur(q, t, visited, prev);//从一条路径先直接走到底
		}
	}

private:
	int m_v;//顶点个数
	std::vector<std::list<data_type>> m_adj;//邻接表
};

END_NAMESPACE(yyyyshen)

#endif // !GRAPH_HPP
