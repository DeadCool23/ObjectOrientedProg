#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <exception>

extern "C" {
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
}

class BaseError: public std::exception {
    public:
        BaseError(const char *filename, const char *classname, int line, const char *time, const char *info = "Undefined") {
            snprintf(error_info, 1023,
                    "\nFilename: %s \
                    \nClass: %s \
                    \nLine: %d \
                    \nTime: %s \
                    \nERROR: %s", 
                    filename, classname, line, time, info);
        }

        virtual const char* what() const noexcept override {
            return error_info;
        }

        virtual ~BaseError() = default;

    protected:
        char error_info[1024];
};

// Ошибки Списка

class ListBaseError : public BaseError {
    public:
        ListBaseError(const char *filename, const char *classname, int line, const char *time, const char *info)
        : BaseError(filename, classname, line, time, info) {};
};

class MemError: public ListBaseError {
    public:
        MemError(const char *filename, const char *classname, int line, const char *time, const char *info = "Invalid memory allocation")
        : ListBaseError(filename, classname, line, time, info) {};
};

class RangeError: public ListBaseError {
    public:
        RangeError(const char *filename, const char *classname, int line, const char *time, const char *info = "Invalid range")
        : ListBaseError(filename, classname, line, time, info) {};
};

class SizeError: public ListBaseError {
    public:
        SizeError(const char *filename, const char *classname, int line, const char *time, const char *info = "Invalid size")
        : ListBaseError(filename, classname, line, time, info) {};
};

class EmptyError: public ListBaseError {
    public:
        EmptyError(const char *filename, const char *classname, int line, const char *time, const char *info = "List is empty")
        : ListBaseError(filename, classname, line, time, info) {};
};

class NoValueError: public ListBaseError {
    public:
        NoValueError(const char *filename, const char *classname, int line, const char *time, const char *info = "No value found")
        : ListBaseError(filename, classname, line, time, info) {};
};

// Ошибки итератора

class IteratorBaseError : public BaseError {
    public:
        IteratorBaseError(const char *filename, const char *classname, int line, const char *time, const char *info)
        : BaseError(filename, classname, line, time, info) {};
};

class PointerError: public IteratorBaseError {
    public:
        PointerError(const char *filename, const char *classname, int line, const char *time, const char *info = "Invalid pointer")
        : IteratorBaseError(filename, classname, line, time, info) {};
};

class IteratorError: public IteratorBaseError {
    public:
        IteratorError(const char *filename, const char *classname, int line, const char *time, const char *info = "Iter")
        : IteratorBaseError(filename, classname, line, time, info) {};
};

#endif // __ERRORS_H__