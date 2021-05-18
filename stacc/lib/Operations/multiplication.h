#ifndef STACC_MULTIPLICATION_H
#define STACC_MULTIPLICATION_H


#include "../IOperation.h"

class multiplication : public IOperation {
public:
    using IOperation::IOperation;

    IOperation *exec() override;
};


#endif //STACC_MULTIPLICATION_H
