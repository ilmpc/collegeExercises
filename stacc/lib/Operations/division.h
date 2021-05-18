#ifndef STACC_DIVISION_H
#define STACC_DIVISION_H
#define EPS 1E-30

#include <stdexcept>
#include "../IOperation.h"

class division : public IOperation {
public:
    using IOperation::IOperation;

    IOperation *exec() override;
};


#endif //STACC_DIVISION_H
