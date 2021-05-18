#ifndef STACC_SQRT_H
#define STACC_SQRT_H


#include "../IOperation.h"
#include <cmath>

class sqrt : public IOperation {
public:
    using IOperation::IOperation;

    IOperation *exec() override;
};


#endif //STACC_SQRT_H
