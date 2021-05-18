#include <thread>
#include <iostream>
#include "worker.h"

worker::worker(const int destinationNode, std::queue<agent> &queueOfAgents, std::mutex &queueLocker,
               std::list<agent> &suitableAgents, std::mutex &suitableLocker)
        : destinationNode(destinationNode),
          queueOfAgents(queueOfAgents), queueLocker(queueLocker), suitableAgents(suitableAgents),
          suitableLocker(suitableLocker) {}

void worker::operator()(int &completedTasks) {
    while (true) {
        queueLocker.lock();
        if (queueOfAgents.empty()) {
            queueLocker.unlock();
            //std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (emptyQueue) {
                break;
            } else {
                emptyQueue = true;
                continue;
            }
        }
        emptyQueue = false;
        agent currentAgent = queueOfAgents.front();
        queueOfAgents.pop();
        queueLocker.unlock();
        auto nextAgents = currentAgent.makeAStep();
        std::list<agent> suitable;
        std::list<agent> other;
        for (auto item:nextAgents) {
            if (item.isInThe(destinationNode)) {
                suitable.push_back(item);
            } else {
                other.push_back(item);
            }
        }
        {
            std::lock_guard<std::mutex> lock(suitableLocker);
            suitableAgents.splice(suitableAgents.end(), suitable);
        }
        {
            std::lock_guard<std::mutex> lock(queueLocker);
            for (const auto &item:other) {
                queueOfAgents.push(item);
            }
        }
        completedTasks++;
    }
}

std::tuple<double, std::list<int>>
worker::solveMultithreading(std::initializer_list<double> &valuesWeightTable, int startNode, int finishNode, int numNodes,
                            int numThreads) {
    if(startNode < 0 || startNode >= numNodes || finishNode < 0 || finishNode >= numNodes || valuesWeightTable.size() != numNodes*(numNodes-1)/2){
        throw std::invalid_argument("Начальный узел/конечный узел/количество узлов не соответствуют таблице.");
    }
    auto weightTable = new std::vector<double>(valuesWeightTable);
    agent firstAgent(startNode, numNodes, *weightTable);
    std::queue<agent> queueOfAgents;
    queueOfAgents.push(firstAgent);
    std::list<agent> possibleSolutions;
    std::mutex queueMu, possibleMu;
    worker *workers[numThreads];
    std::thread *pThreads[numThreads];
    int completedTask[numThreads];
    for (int j = 0; j < numThreads; ++j) {
        completedTask[j] = 0;
        workers[j] = new worker(finishNode, queueOfAgents, queueMu, possibleSolutions, possibleMu);
        pThreads[j] = new std::thread(*workers[j], std::ref(completedTask[j]));
    }
    for (auto t:pThreads) {
        t->join();
    }

    for (int i = 0; i < numThreads; ++i) {
        std::cout << i + 1 << " — " << completedTask[i] << "\n";
    }
    auto bestCost = possibleSolutions.front().getCost();
    std::list<int> bestTrace = possibleSolutions.front().getVisitedNodes();
    for (auto item:possibleSolutions) {
        if (item.getCost() < bestCost) {
            bestCost = item.getCost();
            bestTrace = item.getVisitedNodes();
        }
    }
    for (int j = 0; j < numThreads; ++j) {
        delete workers[j];
        delete pThreads[j];
    }
    delete weightTable;
    return std::tuple<double, std::list<int>>(bestCost, bestTrace);
}


