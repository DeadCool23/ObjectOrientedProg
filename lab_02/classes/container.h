#ifndef __CONTAINER_H__
#define __CONTAINER_H__

extern "C" {
    #include <stdlib.h>
}

class Container {
public:
    using size_type = std::size_t;

public:
    Container(void) = default;
    Container(const Container&) = default;

    virtual ~Container(void) = default;

    virtual size_type size(void) const = 0;
    virtual bool is_empty(void) const = 0;
protected:
    size_type _size = 0;
};


#endif //__CONTAINER_H__