#ifndef COMMI_AGENT_H
#define COMMI_AGENT_H


#include <list>
#include <vector>
#include <limits>

class agent {
private:
    int numNodes;
    const std::vector<double> &table;
    std::list<int> visitedNodes;
    double cost;

    double edgeWeight(int left, int right);

public:
    constexpr static const double noRoadConst = std::numeric_limits<double>::infinity();

    agent(const std::list<int> &visitedNodes, const int &destinationNode, const int &numNodes,
          const std::vector<double> &table,
          const double &cost);

    agent(const int &startNode, const int &numNodes, const std::vector<double> &table);

    std::vector<agent> makeAStep();

    bool isInThe(const int &node);

    double getCost();

    std::list<int> getVisitedNodes();
};


#endif //COMMI_AGENT_H
