#include "line.h"
#include <stdio.h>
#include "new.h"

static void *Line_ctor(void *_self, va_list *app) {
    struct Line *self = ((const struct Class *)Point)->ctor(_self, app);
    ((const struct Class *)Point)->ctor((void *)&(self->_2),app);
    return self;
}

#define x(p) (((const struct Point *)(p)) -> x)
#define y(p) (((const struct Point *)(p)) -> y)

static void Line_draw(const void * _self)
{
    const struct Line * self = _self;
    printf("line at ((%d,%d),(%d,%d))\n", x(self), y(self), x(&(self->_2)),y(&(self->_2)));
}

static const struct Class _Line = {
        sizeof(struct Line),      // size
        Line_ctor,                // ctor
        0,                          // dtor
        Line_draw                 // draw
};

const void *Line = &_Line;
