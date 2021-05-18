#ifndef STACC_PRINT_H
#define STACC_PRINT_H

#include <iostream>
#include "../IOperation.h"

class print: public IOperation {
    using IOperation::IOperation;
    IOperation *exec() override;
};


#endif //STACC_PRINT_H
