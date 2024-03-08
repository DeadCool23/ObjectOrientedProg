#ifndef ERRS_H
#define ERRS_H

#include <errno.h>

typedef enum {
    OK,
    ERR_IO,
    ERR_MEM,

    ERR_FILE,
    ERR_FILE_ACCESS,
    ERR_FILE_EXIST,

    ERR_FILE_DATA,
    ERR_FILE_CONTENT,

    ERR_NO_POINTS,
    ERR_NO_LINKS,

    ERR_LINKS,

    ERR_COMMAND
} errs_t;

/**
 * @brief Процедура сообщения об ошибке
 * @param [in] err - код ошибки
 */
void err_msg(errs_t err);
errs_t file_stdErrs2projErrs(void);

#endif // ERRS_H
