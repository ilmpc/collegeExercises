#ifndef STACC_CONTEXT_H
#define STACC_CONTEXT_H

#include <list>
#include "stack.h"

class context {

    const std::list<double> *mArgs;
    stack *mData;
public:
    context(stack *data, const std::list<double> *args);

    stack *get_data();

    const std::list<double>& get_args() const;
};


#endif //STACC_CONTEXT_H
