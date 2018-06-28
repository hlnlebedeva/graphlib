#pragma once

#include <list>
#include <vector>


class Graph
{
	public:
		template
		<
			typename Matrix = std::vector< std::vector<bool> >
		>
		Graph( const Matrix& adj_matrix )
		:	adjacency_list_( adj_matrix.size() )
		{
			size_t i = 0;
			for (const auto& row : adj_matrix)
			{
				size_t j = 0;
				for (const auto& item : row)
				{
					if (j >= adj_matrix.size())
						throw std::invalid_argument("AdjacencyMatrix must be squared");
					if (item)
						adjacency_list_[i].push_back(j);
					j++;
				}
				i++;
			}
		}
	
		size_t size() const
		{
			return adjacency_list_.size();
		}

		enum Colour { White = 0, Opened = 1, Closed = 2 };
		enum StopFlag { Stop, Continue };

		bool hasCycle()
		{
			std::vector<int> colours(size(), White);
			for (size_t i = 0; i < size(); i++)
				if (colours[i] == White)
				{
					if (Stop == DFS_visit(i, colours))
						return true;
				}
			return false;
		}

	private:

		StopFlag DFS_visit(size_t i, std::vector<int>& colours)	//returns 'true' to stop iteration
		{
			colours[i] = Opened;	//Grey

			for (const auto& v : adjacency_list_[i])
				if (colours[v] == Opened)
					return Stop;

			for (const auto& v : adjacency_list_[i])
			{
				switch (colours[v])
				{
				case White:
					if (DFS_visit(v, colours) == Stop)
						return Stop;
					break;
				case Opened:
					return Stop;
				case Closed:
					break;
				}
			}
			colours[i] = Closed;	//Black
			return Continue;
		}

	private:
		std::vector< std::list<int> > adjacency_list_;
};

inline bool DetectCycleDFS(const std::vector< std::vector<bool> >& graph)
{
	return Graph(graph).hasCycle();
}
