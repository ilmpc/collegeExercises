#include "print.h"

IOperation *print::exec() {
    auto it = mContext.get_data()->pop();
    std::cout << it << "\n";
    return this;
}
