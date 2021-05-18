#include "context.h"

context::context(stack *data, const std::list<double> *args) : mArgs(args), mData(data) {
}

stack *context::get_data() {
    return mData;
}

const std::list<double> &context::get_args() const{
    return *mArgs;
}


