
#include <sstream>
#include <unordered_map>
#include "graph.h"


Graph::Graph(const std::string &path) : mPath(path)
{}

std::vector<std::vector<std::reference_wrapper<Node>>> Graph::parallel_job_scheduling()
{
	try
	{
		return kahns_algorithm();
	}
	catch (const std::exception &e)
	{
		throw;
	}
}

std::vector<std::vector<std::reference_wrapper<Node>>> Graph::kahns_algorithm()
{
	std::vector<std::vector<std::reference_wrapper<Node>>> result = std::vector<std::vector<std::reference_wrapper<Node>>>();

	bool isZeroIndegree = true;
	int depth = 0;
	int nodesExecuted = 0;
	int nodesCount = mNodes.size();

	while (isZeroIndegree)
	{
		isZeroIndegree = false;

		std::vector<std::reference_wrapper<Node>> resultByDepth = std::vector<std::reference_wrapper<Node>>();

		// search and put nodes with 0 indegrees to resultByDepth vector
		for (auto& nodeInGraph : mNodes)
		{
			if (!nodeInGraph.isRemoved && nodeInGraph.indegreesCount == 0)
			{
				isZeroIndegree = true;
				resultByDepth.push_back(nodeInGraph);
			}
		}

		// decrement indegrees and remove executed nodes
		for (size_t j = 0; j < resultByDepth.size(); j++)
		{
			Node& node = resultByDepth[j].get();

			// iterate through outdegrees
			for (size_t k = 0; k < node.outdegrees.size(); k++)
			{
				Node& outdegree = node.outdegrees[k].get();
				outdegree.indegreesCount--;
			}
			node.isRemoved = true;
			nodesExecuted++;
		}
		if (!resultByDepth.empty())
		{
			result.push_back(resultByDepth);
		}
		depth++;
	}

	// check if the graph is acyclic
	if (nodesExecuted == nodesCount)
	{
		return result;
	}
	else
	{
		throw std::runtime_error("Graph is not acyclic!");
	}
}

void Graph::close_file_and_throw(std::ifstream& file, const std::runtime_error& exception)
{
	if (file.is_open())
	{
		file.close();
	}

	throw exception;
}

void Graph::read_graph()
{
	std::unordered_map<std::string, size_t> nodeNamesMap;
	std::ifstream inputFile(mPath);

	if (inputFile.is_open())
	{
		// read the first line and add nodes to the graph
		std::string firstLine;
		std::getline(inputFile, firstLine);
		std::stringstream ssFirstLine(firstLine);
		std::string nodeName;

		while (std::getline(ssFirstLine, nodeName, ';'))
		{
			if (nodeNamesMap.find(nodeName) != nodeNamesMap.end())
			{
				close_file_and_throw(inputFile, std::runtime_error("Node's name must be unique!"));
			}

			mNodes.push_back(Node(nodeName));
			nodeNamesMap[nodeName] = mNodes.size() - 1;
		}

		// read the lines where edges are defined
		while (!inputFile.eof())
		{
			// get the node and its outdegrees
			std::string line;
			std::getline(inputFile, line);
			std::stringstream ssLine(line);
			std::vector<std::string> nodeAndOutdegrees;
			std::string strNode;

			if (line == "")
			{
				close_file_and_throw(inputFile, std::runtime_error("Invalid input file!"));
			}

			while (std::getline(ssLine, strNode, ':'))
			{
				nodeAndOutdegrees.push_back(strNode);
			}

			// get the outdegrees
			std::stringstream ssOutdegrees(nodeAndOutdegrees[1]);
			std::vector<std::string> outdegrees;

			while (std::getline(ssOutdegrees, strNode, ','))
			{
				outdegrees.push_back(strNode);
			}

			for (size_t i = 0; i < outdegrees.size(); i++)
			{
				std::unordered_map<std::string, size_t>::iterator fromNode = nodeNamesMap.find(nodeAndOutdegrees[0]);
				std::unordered_map<std::string, size_t>::iterator toNode = nodeNamesMap.find(outdegrees[i]);

				if (fromNode == nodeNamesMap.end() || toNode == nodeNamesMap.end())
				{
					close_file_and_throw(inputFile, std::runtime_error("Invalid input file!"));
				}

				add_edge(mNodes[fromNode->second], mNodes[toNode->second]);
			}
		}
		inputFile.close();
	}
}

void Graph::add_edge(Node& from, Node& to)
{
	from.outdegrees.push_back(to);
	to.indegreesCount++;
}
