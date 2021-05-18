#include "pop.h"

IOperation *pop::exec() {
    mContext.get_data()->pop();
    return this;
}