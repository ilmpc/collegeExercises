#ifndef STACC_PUSH_H
#define STACC_PUSH_H


#include "../IOperation.h"
#include <cstdarg>

class push : public IOperation {
public:
    using IOperation::IOperation;

    IOperation *exec() override;
};


#endif //STACC_PUSH_H
