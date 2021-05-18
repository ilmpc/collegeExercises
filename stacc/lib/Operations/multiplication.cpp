#include "multiplication.h"

IOperation *multiplication::exec() {
    auto tStack = mContext.get_data();
    tStack->push(tStack->pop() * tStack->pop());
    return this;
}
