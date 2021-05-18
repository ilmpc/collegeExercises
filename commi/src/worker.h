#ifndef COMMI_WORKER_H
#define COMMI_WORKER_H

#include <queue>
#include <mutex>
#include "agent.h"

class worker {
    const int destinationNode;
    std::queue<agent> &queueOfAgents;
    std::mutex &queueLocker;
    std::list<agent> &suitableAgents;
    std::mutex &suitableLocker;
    bool emptyQueue = false;
public:
    worker(int destinationNode, std::queue<agent> &queueOfAgents, std::mutex &queueLocker,
           std::list<agent> &suitableAgents, std::mutex &suitableLocker);

    void operator()(int &completedTasks);

    static std::tuple<double, std::list<int>>
    solveMultithreading(std::initializer_list<double> &valuesWeightTable, int startNode, int finishNode, int numNodes, int numThreads = 2);
};


#endif //COMMI_WORKER_H
