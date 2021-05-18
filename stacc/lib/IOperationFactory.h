#ifndef STACC_IOPERATIONFABRIC_H
#define STACC_IOPERATIONFABRIC_H

#include <map>
#include <cassert>
#include <list>
#include "stack.h"
#include "IOperation.h"
#include "Operations/pop.h"
#include "Operations/push.h"
#include "Operations/print.h"
#include "Operations/sum.h"
#include "Operations/subtraction.h"
#include "Operations/division.h"
#include "Operations/multiplication.h"
#include "Operations/sqrt.h"



#include "strSwitch.h"


class IOperationFactory {
    stack *mStack;
    std::map<std::string, IOperation *> *mCache;
public:
    explicit IOperationFactory(stack *stack);

    ~IOperationFactory();

    IOperation *createOperation(std::string name, const std::list<double> *args);
};


#endif //STACC_IOPERATIONFABRIC_H
