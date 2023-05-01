#include <iostream>
#include <sstream>
#include "graph.h"

void write_result_to_console(const std::vector<std::vector<std::reference_wrapper<Node>>>& result)
{
    std::cout << "Depth\tIndependent nodes" << std::endl;

    for (size_t i = 0; i < result.size(); i++)
    {
        std::stringstream ss;
        ss << i + 1 << "\t";
        std::string s = ss.str();

        for (auto& node : result[i])
        {
            s += node.get().name;
            s += " ";
        }

        std::cout << s << std::endl;
    }
}

int main()
{
    std::string path = "graph.txt";
    Graph graph = Graph(path);
    std::vector<std::vector<std::reference_wrapper<Node>>> result;

    try
    {
        graph.read_graph();
        result = graph.parallel_job_scheduling();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    write_result_to_console(result);
}

