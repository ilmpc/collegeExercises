#include "stack.h"

void stack::push(double n) {
    if (mLength == mSize) {
        resize();
    }
    mData[mLength++] = n;
}

double stack::pop() {
    if(mLength == 0){
        throw std::out_of_range("No items in stack");
    }
    return mData[--mLength];
}

double stack::pull() {
    if(mLength == 0){
        throw std::out_of_range("No items in stack");
    }
    return mData[mLength - 1];
}

void stack::resize() {
    mSize *= GROWTH_RATE;
    auto data = new double[mSize];
    for (size_t i = 0; i < mLength; ++i) {
        data[i] = mData[i];
    }
    delete[] mData;
    mData = data;
}

stack::stack(size_t size) : mData(new double[size]), mSize(size), mLength(0) {}

stack::stack() : stack(STD_SIZE) {}

stack::~stack() {
    delete[] mData;
}
