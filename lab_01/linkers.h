#ifndef LINKERS_H
#define LINKERS_H

#include <stdlib.h>

#include "errs.h"
#include "linker.h"

typedef struct {
    size_t n;
    linker_t *linkers;
} linkers_t;

/**
 * @brief Инициализация списка связей
 * @return Структура списка связей
 */
linkers_t linkers_init(void);

/**
 * @brief Выделение памяти под список связей
 * @param [out] linkers Ссылка на структуру списка связей, которая будет выделена
 * @param [in] n Количество связей для выделения памяти
 * @return Код ошибки (errs_t)
 */
errs_t allocate_linkers(linkers_t &linkers, size_t n);

/**
 * @brief Освобождение памяти, выделенной для списка связей
 * @param [in,out] linkers Ссылка на структуру списка связей, память для которой нужно освободить
 */
void free_linkers(linkers_t &linkers);

/**
 * @brief Чтение списка связей из файла
 * @param [out] linkers Ссылка на структуру списка связей, в которую будет загружена информация из файла
 * @param [in, out] file Указатель на файл для чтения
 * @return Код ошибки (errs_t)
 */
errs_t read_linkers(linkers_t &linkers, FILE *file);

/**
 * @brief Запись списка связей в файл
 * @param [out] file Указатель на файл, в который будет записан список связей
 * @param [in] linkers Ссылка на структуру списка связей для записи
 * @return Код ошибки (errs_t)
 */
errs_t write_linkers(FILE *file, const linkers_t &linkers);


#endif // LINKERS_H
