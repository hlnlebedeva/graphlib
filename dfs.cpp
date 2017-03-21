#include <vector>
#include <stack>
#include <list>
#include "dfs.h"

using namespace std;

enum States {White = 0, Gray = 1, Black = 2};

bool DetectCycleDFS(const vector<list<int>>&  graph)
{
	stack<int> st;
	vector<States> colours(graph.size());
	
	for (int i = 0; i < graph.size(); i++)
	{
		if (colours[i] == White)
		{
			st.push(i);

			while (!st.empty())
			{
				int cur = st.top();

				switch (colours[cur])
				{
				case White:
					colours[cur] = Gray;
				
					for (int j : graph[cur])
					{
						if (colours[j] == White)
							st.push(j);

						if (colours[j] == Gray)
							return true;
					}
					break;
				case Gray :
					colours[cur] = Black;
					st.pop();
					break;
				case Black :
					st.pop();
					break;
				}
	    	}
		}
	}

	return false;
}

bool DetectCycleMatrix(const vector<vector<bool>>& matrix)
{
	int N = matrix.size();

	for (int i = 0; i < N; i++)
	{
		if (matrix[i].size() != N)
			throw invalid_argument("Matrix must be square");
	}

	vector<list<int>> graph(N);

	for (int i = 0; i < N; i++)
	{
		list<int> edges;

		for (int j = 0; j < N; j++)
		{
			if (matrix[i][j] == 1)
				edges.push_back(j);
		}

		graph[i] = edges;
	}

	return DetectCycleDFS(graph);
}
