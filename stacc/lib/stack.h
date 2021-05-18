#ifndef STACC_STACK_H
#define STACC_STACK_H

#include <cstddef>
#include <stdexcept>

#define GROWTH_RATE 2
#define STD_SIZE 128

class stack {
    double *mData;
    size_t mSize;
    size_t mLength;
public:
    explicit stack(size_t size);

    explicit stack();

    ~stack();

    void push(double n);

    double pull();

    double pop();

    void resize();
};


#endif //STACC_STACK_H
