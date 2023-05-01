#pragma once
#include <vector>
#include <string>
#include <functional>

struct Node
{
	Node(const std::string& name);

	const std::string name;
	int indegreesCount = 0;
	std::vector<std::reference_wrapper<Node>> outdegrees;
	bool isRemoved = false;
};
