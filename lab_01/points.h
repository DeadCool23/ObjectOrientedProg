#ifndef POINTS_H
#define POINTS_H

#include "point.h"

#include "errs.h"
#include <stdlib.h>

typedef struct {
    size_t n;
    point_t *points;
} points_t;

/**
 * @brief Инициализация точек
 * @return Структура точек
 */
points_t points_init(void);

/**
 * @brief Выделение памяти для массива точек
 * @param [out] points - Ссылка на структуру точек, в которую будут выделены память
 * @param [in] n - Количество точек, которое необходимо выделить
 * @return Код ошибки (errs_t)
 */
errs_t allocate_points(points_t &points, size_t n);

/**
 * @brief Освобождение памяти, занятой массивом точек
 * @param [in, out] points - Ссылка на структуру точек, для которой необходимо освободить память
 */
void free_points(points_t &points);

/**
 * @brief Чтение массива точек из файла
 * @param [out] points - Ссылка на структуру точек, в которую будут считаны точки из файла
 * @param [in, out] file - Указатель на файл для чтения
 * @return Код ошибки (errs_t)
 */
errs_t read_points(points_t &points, FILE *file);

/**
 * @brief Запись массива точек в файл
 * @param [out] file - Указатель на файл, в который будут записаны точки
 * @param [in] points - Ссылка на структуру точек для записи
 * @return Код ошибки (errs_t)
 */
errs_t write_points(FILE *file, const points_t &points);

/**
 * @brief Перемещение массива точек
 * @param [in, out] points - Ссылка на структуру точек, которую необходимо переместить
 * @param [in] mover - Структура с коэффициентами для перемещения точек
 * @return Код ошибки (errs_t)
 */
errs_t move_points(points_t &points, const move_coefs_t &mover);

/**
 * @brief Масштабирование массива точек
 * @param [in, out] points - Ссылка на структуру точек, которую необходимо масштабировать
 * @param [in] scaler - Структура с коэффициентами для масштабирования точек
 * @return Код ошибки (errs_t)
 */
errs_t scale_points(points_t &points, const scale_data_t &scaler);

/**
 * @brief Вращение массива точек
 * @param [in, out] points - Ссылка на структуру точек, которую необходимо повернуть
 * @param [in] rotater - Структура с коэффициентами для вращения точек
 * @return Код ошибки (errs_t)
 */
errs_t rotate_points(points_t &points, const rotate_data_t &rotater);


#endif // POINTS_H
