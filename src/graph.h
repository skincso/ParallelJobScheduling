#pragma once
#include <string>
#include <fstream>
#include "node.h"

class Graph
{
public:
	Graph(const std::string& path);
	void read_graph();
	std::vector<std::vector<std::reference_wrapper<Node>>> parallel_job_scheduling();

private:
	std::string mPath;
	std::vector<Node> mNodes;

	void add_edge(Node& from, Node& to);
	std::vector<std::vector<std::reference_wrapper<Node>>> kahns_algorithm();
	void close_file_and_throw(std::ifstream& file, const std::runtime_error& exception);
};
