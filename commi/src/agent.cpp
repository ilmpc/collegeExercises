#include <stdexcept>
#include <set>
#include <cassert>
#include "agent.h"

agent::agent(const std::list<int> &visitedNodes, const int &destinationNode, const int &numNodes,
             const std::vector<double> &table,
             const double &cost) : numNodes(numNodes), table(table),
                                   cost(cost) {
    for (const auto &temp:visitedNodes) {
        this->visitedNodes.push_back(temp);
    }
    this->visitedNodes.push_back(destinationNode);
}

agent::agent(const int &startNode, const int &numNodes, const std::vector<double> &table) : numNodes(numNodes),
                                                                                            table(table), cost(0) {
    this->visitedNodes.push_back(startNode);
}


inline int arSum(int x) {
    return ((x - 1) * x) / 2;
}

double agent::edgeWeight(int left, int right) {
    if (left == right) {
        return 0; //Цикл
    }
    if (left < 0 || right < 0) {
        throw std::invalid_argument("Отрицательные индексы");
    }
    if (left > numNodes || right > numNodes) {
        throw std::invalid_argument("Индексы больше, чем количество узлов");
    }
    if (left < right) {
        std::swap(left, right);
    }
    assert((arSum(left) + right) < table.size());
    return table[arSum(left) + right];
}

std::vector<agent> agent::makeAStep() {
    std::vector<agent> agents;
    int last = visitedNodes.back();
    std::set<int> setOfVisitedNodes(visitedNodes.begin(), visitedNodes.end());
    for (int i = 0; i < numNodes; ++i) {
        if (setOfVisitedNodes.count(i) == 0) {
            double weightTargetEdge = edgeWeight(last, i);
            if (weightTargetEdge == 0 || weightTargetEdge == noRoadConst) {
                continue;
            }
            agents.emplace_back(visitedNodes, i, numNodes, table, cost + weightTargetEdge);
        }
    }
    return agents;
}

bool agent::isInThe(const int &node) {
    return visitedNodes.back() == node;
}

double agent::getCost() {
    return cost;
}

std::list<int> agent::getVisitedNodes() {
    return visitedNodes;
}

