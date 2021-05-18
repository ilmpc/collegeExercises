#include "sqrt.h"

IOperation *sqrt::exec() {
    auto tStack = mContext.get_data(); //Если не создавать временнные переменные, то вызова десктруктора не происходит
    auto item = tStack->pop();
    if (item < 0){
        throw std::domain_error("Square root from negative number");
    }
    tStack->push(std::sqrt(item));
    return this; //TODO Вызвался деструктор -> заменил сслыку на указатель, хорошо ли это?
}
