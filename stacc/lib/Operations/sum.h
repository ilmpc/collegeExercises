#ifndef STACC_SUM_H
#define STACC_SUM_H


#include "../IOperation.h"

class sum : public IOperation {
public:
    using IOperation::IOperation;

    IOperation *exec() override;
};


#endif //STACC_SUM_H
