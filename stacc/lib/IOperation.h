#ifndef STACC_IOPERATION_H
#define STACC_IOPERATION_H

#include "context.h"

class IOperation {
    friend class IOperationFactory;
private:
    void set_context(context &context);
protected:
    context mContext;
public:
    explicit IOperation(context &context);
    
    virtual IOperation *exec() = 0;

};


#endif //STACC_IOPERATION_H
