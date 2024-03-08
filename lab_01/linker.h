#ifndef LINKER_H
#define LINKER_H

#include "errs.h"
#include <stdio.h>

typedef struct {
    int main_ind;
    int child_ind;
} linker_t;

/**
 * @brief Чтение связок из файла
 * @param [out] linter - Ссылка на структуру линтера, в которую будет загружена информация из файла
 * @param [in, out] file - Указатель на файл для чтения
 * @return Код ошибки (errs_t)
 */
errs_t read_linter(linker_t &linter, FILE *file);

/**
 * @brief Запись связок в файл
 * @param [out] file - Указатель на файл, в который будет записан линтер
 * @param [in] linter - Ссылка на структуру линтера для записи
 */
void write_linter(FILE *file, const linker_t &linter);

#endif // LINKER_H
