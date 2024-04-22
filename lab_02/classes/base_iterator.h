#ifndef __BASE_ITERATOR_H__
#define __BASE_ITERATOR_H__

extern "C" {
    #include <stdlib.h>
}

class BaseIterator {
public:
    BaseIterator() = default;
    ~BaseIterator() = default;
protected:
    size_t index = 0;
};

#endif // __BASE_ITERATOR_H__