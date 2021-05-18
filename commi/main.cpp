#include <agent.h>
#include <worker.h>
#include <iostream>


int main() {
    auto inf = agent::noRoadConst;
    std::initializer_list<double> init{20, inf, 14, 14, inf, 18, inf, 16, 15, 17, 19, inf, inf, 14, inf, 18, 15, inf,
                                       inf, inf, inf};
    auto best = worker::solveMultithreading(init, 0, 6, 7);
    std::cout << std::get<0>(best) << "\n";
    for (auto temp : std::get<1>(best)) {
        std::cout << temp << " ";
    }
}