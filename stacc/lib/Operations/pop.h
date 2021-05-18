#ifndef STACC_POP_H
#define STACC_POP_H


#include "../IOperation.h"


class pop : public IOperation {
public:
    using IOperation::IOperation;

    IOperation *exec() override;
};

#endif //STACC_POP_H
