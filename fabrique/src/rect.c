#include "rect.h"
#include <stdio.h>
#include "new.h"

static void *Rect_ctor(void *_self, va_list *app) {
    struct Rect *self = ((const struct Class *)Point)->ctor(_self, app);
    ((const struct Class *)Point)->ctor((void*)&(self->_2),app);
    return self;
}

#define x(p) (((const struct Point *)(p)) -> x)
#define y(p) (((const struct Point *)(p)) -> y)

static void Rect_draw(const void * _self)
{
    const struct Rect * self = _self;
    printf("rect at ((%d,%d),(%d,%d))\n", x(self), y(self), x(&(self->_2)),y(&(self->_2)));
}

static const struct Class _Rect = {
        sizeof(struct Rect),      // size
        Rect_ctor,                // ctor
        0,                          // dtor
        Rect_draw                 // draw
};

const void *Rect = &_Rect;
