#ifndef POINT_H
#define POINT_H

#include "errs.h"
#include <stdio.h>

typedef struct {
    double x;
    double y;
    double z;
} point_t;

/**
 * @brief Считывание точки
 * @param [out] point - Точка
 * @param [in, out] file - Файл
 * @return Код ошибки
 */
errs_t read_point(point_t &point, FILE *file);
/**
 * @brief Запись точки в файл
 * @param [out] file - Указатель на файл, в который будет записана точка
 * @param [in] point - Ссылка на структуру точки для записи
 */
void write_point(FILE *file, const point_t &point);

// --- Аффинные преобразования ---

typedef struct {
    double dx;
    double dy;
    double dz;
} move_coefs_t;

typedef struct {
    double kx;
    double ky;
    double kz;
} scale_coefs_t;

typedef struct {
    point_t rel_center;
    scale_coefs_t coefs;
} scale_data_t;

typedef struct {
    double ox;
    double oy;
    double oz;
} rotate_coefs_t;

typedef struct {
    point_t rel_center;
    rotate_coefs_t coefs;
} rotate_data_t;

/**
 * @brief Перемещение точки
 * @param [in,out] point - Ссылка на структуру точки, которую необходимо переместить
 * @param [in] mover - Структура с коэффициентами для перемещения точки
 */
void move_point(point_t &point, const move_coefs_t &mover);

/**
 * @brief Масштабирование точки
 * @param [in,out] point - Ссылка на структуру точки, которую необходимо масштабировать
 * @param [in] scaler - Структура с коэффициентами для масштабирования точки
 */
void scale_point(point_t &point, const scale_coefs_t &scaler, const point_t &rel_center);

/**
 * @brief Вращение точки
 * @param [in,out] point - Ссылка на структуру точки, которую необходимо повернуть
 * @param [in] rotater - Структура с коэффициентами для вращения точки
 */
void rotate_point(point_t &point, const rotate_coefs_t &rotater, const point_t &rel_center);

#endif // POINT_H
