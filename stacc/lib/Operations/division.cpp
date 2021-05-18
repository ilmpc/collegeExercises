#include "division.h"

IOperation *division::exec() {
    auto tStack = mContext.get_data();
    auto a = tStack->pop();
    auto b = tStack->pop();
    if(b < EPS && b > -EPS){
        throw std::domain_error("Division by zero");
    }
    tStack->push(a/b);
    return this;
}
