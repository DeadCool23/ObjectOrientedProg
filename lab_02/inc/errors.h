#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <string>
#include <exception>

class BaseError: public std::exception {
    public:
        BaseError(std::string filename, std::string classname, int line, const char *time, std::string info = "Undefined") {
            error_info = "\nFile name: " + filename +
                         "\nClass: " + classname +
                         "\nLine: " + std::to_string(line) +
                         "\nTime: " + time +
                         "ERROR: " + info;
        }

        virtual const char* what() const noexcept override {
            return error_info.c_str();
        }

        virtual ~BaseError() = default;

    protected:
        std::string error_info;
};

class MemError: public BaseError {
    public:
        MemError(std::string filename, std::string classname, int line, const char *time, std::string info = "Invalid memory allocation")
        : BaseError(filename, classname, line, time, info) {};
};

class RangeError: public BaseError {
    public:
        RangeError(std::string filename, std::string classname, int line, const char *time, std::string info = "Invalid range")
        : BaseError(filename, classname, line, time, info) {};
};

class SizeError: public BaseError {
    public:
        SizeError(std::string filename, std::string classname, int line, const char *time, std::string info = "Invalid size")
        : BaseError(filename, classname, line, time, info) {};
};

class EmptyError: public BaseError {
    public:
        EmptyError(std::string filename, std::string classname, int line, const char *time, std::string info = "List is empty")
        : BaseError(filename, classname, line, time, info) {};
};

class LogicError: public BaseError {
    public:
        LogicError(std::string filename, std::string classname, int line, const char *time, std::string info = "Invalid logic")
        : BaseError(filename, classname, line, time, info) {};
};

class NoValueError: public BaseError {
    public:
        NoValueError(std::string filename, std::string classname, int line, const char *time, std::string info = "No value found")
        : BaseError(filename, classname, line, time, info) {};
};

class PointerError: public BaseError {
    public:
        PointerError(std::string filename, std::string classname, int line, const char *time, std::string info = "Invalid pointer")
        : BaseError(filename, classname, line, time, info) {};
};

class IteratorError: public BaseError {
    public:
        IteratorError(std::string filename, std::string classname, int line, const char *time, std::string info = "Iter")
        : BaseError(filename, classname, line, time, info) {};
};

#endif // __ERRORS_H__