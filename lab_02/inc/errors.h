#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <exception>

extern "C" {
    #include <string.h>
    #include <stdlib.h>
}

class BaseError: public std::exception {
    public:
        BaseError(const char *filename, const char *classname, int line, const char *time, const char *info = "Undefined") {
            strcpy(error_info, "");
            strcat(error_info, "\nFile name: "); strcat(error_info, filename);
            strcat(error_info, "\nClass: "); strcat(error_info, classname);
            char sline[10];
            itoa(line, sline, 10);
            strcat(error_info, "\nClass: "); strcat(error_info, sline);
            strcat(error_info, "\nTime: "); strcat(error_info, time);
            strcat(error_info, "\nERROR: "); strcat(error_info, info);
        }

        virtual const char* what() const noexcept override {
            return error_info;
        }

        virtual ~BaseError() = default;

    protected:
        char error_info[1024];
};

class MemError: public BaseError {
    public:
        MemError(const char *filename, const char *classname, int line, const char *time, const char *info = "Invalid memory allocation")
        : BaseError(filename, classname, line, time, info) {};
};

class RangeError: public BaseError {
    public:
        RangeError(const char *filename, const char *classname, int line, const char *time, const char *info = "Invalid range")
        : BaseError(filename, classname, line, time, info) {};
};

class SizeError: public BaseError {
    public:
        SizeError(const char *filename, const char *classname, int line, const char *time, const char *info = "Invalid size")
        : BaseError(filename, classname, line, time, info) {};
};

class EmptyError: public BaseError {
    public:
        EmptyError(const char *filename, const char *classname, int line, const char *time, const char *info = "List is empty")
        : BaseError(filename, classname, line, time, info) {};
};

class LogicError: public BaseError {
    public:
        LogicError(const char *filename, const char *classname, int line, const char *time, const char *info = "Invalid logic")
        : BaseError(filename, classname, line, time, info) {};
};

class NoValueError: public BaseError {
    public:
        NoValueError(const char *filename, const char *classname, int line, const char *time, const char *info = "No value found")
        : BaseError(filename, classname, line, time, info) {};
};

class PointerError: public BaseError {
    public:
        PointerError(const char *filename, const char *classname, int line, const char *time, const char *info = "Invalid pointer")
        : BaseError(filename, classname, line, time, info) {};
};

class IteratorError: public BaseError {
    public:
        IteratorError(const char *filename, const char *classname, int line, const char *time, const char *info = "Iter")
        : BaseError(filename, classname, line, time, info) {};
};

#endif // __ERRORS_H__