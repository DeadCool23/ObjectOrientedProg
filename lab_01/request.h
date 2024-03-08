#ifndef REQUEST_H
#define REQUEST_H

#include "errs.h"
#include "drawer.h"

typedef enum {
    DRAW,

    MOVE,
    SCALE,
    ROTATE,

    LOAD_FIGURE,
    WRITE_FIGURE,

    QUIT
} operation_t;

typedef struct {
    operation_t operation;
    union {
        move_coefs_t move_coefs;
        scale_data_t scale_data;
        rotate_data_t rotate_data;
        field_sizes_t sizes;
        const char *filename;
    };
    drawer_t drawer;
} request_t;

/**
 * @brief Выполнение запроса
 * @param [in] request - запрос
 * @return Код ошибки (errs_t)
 */
errs_t request_proc(const request_t &request);

#endif // REQUEST_H
