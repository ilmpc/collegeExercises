#include "push.h"

IOperation *push::exec() {
    for (auto &it : mContext.get_args()) {
        mContext.get_data()->push(it);
    }
    return this;
}
