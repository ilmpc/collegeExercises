#include "IOperation.h"

IOperation::IOperation(context &context) : mContext(context) {}

void IOperation::set_context(context &context) {
    mContext = context;
}
