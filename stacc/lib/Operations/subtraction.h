#ifndef STACC_SUBTRACTION_H
#define STACC_SUBTRACTION_H


#include "../IOperation.h"

class subtraction : public IOperation {
public:
    using IOperation::IOperation;

    IOperation *exec() override;
};


#endif //STACC_SUBTRACTION_H
